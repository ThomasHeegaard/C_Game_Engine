/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : config_loader.c
|Author   : Thomas Heegaard
|Created  : 11/11/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "config_loader.h"
#include "live_define.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Parameter
{
    char* name;
    char* value;
} Parameter;

Parameter* config_file = NULL;
unsigned short parameters = 0;
const char* current_file = "No config file loaded";

ERR ValidCharacter(char c)
{
    if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
        || c == '_' || c == '|' || c == '.' || c == '/')
        return 1;
    return 0;
}

int StringToInt(const char* str)
{
    unsigned char number    = 1;
    unsigned int  i         = 0;
    for(i = 0; str[i] != '\0'; i++)
        if(str[i] < '0' || str[i] > '9')
            number = 0;
    if(number == 1)
        return atoi(str);
    return TranslateDefines(str);
}

int ParseTokens(const char* left, const char* right)
{
    int left_int = StringToInt(left);
    char* tmp = strchr(right, '|');
    if(tmp == NULL)
        return (left_int | StringToInt(right));
    tmp[0] = '\0';
    tmp++;
    return (left_int | ParseTokens(right, tmp));
}

#define NOT_NUMBER  1
#define TOKENS      2

int ParseParameter(const char* parameter)
{
    unsigned char   flags       = 0;
    unsigned int    i           = 0;

    if(parameter == NULL)
    {
        fprintf(stderr, "Null string parse attempt\n");
        return 0;
    }

    for(i = 0; parameter[i] != '\0'; i++)
    {
        if(parameter[i] == '|')
        {
            flags |= TOKENS;
            flags |= NOT_NUMBER;
        }
        else if(parameter[i] < '0' || parameter[i] > '9')
        {
            flags |= NOT_NUMBER;
        }
    }

    if((flags & NOT_NUMBER) == 0)
        return atoi(parameter);
    if((flags & TOKENS) == 0)
        return TranslateDefines(parameter);
    return ParseTokens("0", parameter);
}

//=====================================EXTERNAL===================================

ERR OpenConfigFile(const char* file_name)
{
    if(config_file != NULL)
        if(CloseConfigFile() != 0)
            return 1;

    FILE* file_ptr = fopen(file_name, "r");
    if(file_ptr == NULL)
        return 1;

    config_file = (Parameter*)malloc(MAX_PARAMETERS * sizeof(Parameter));
    if(config_file == NULL)
    {
        fclose(file_ptr);
        return 1;
    }

    current_file = file_name;
    parameters = 0;

    char* line = (char*)malloc(LINE_LENGTH*sizeof(char));
    if(line == NULL)
    {
        fclose(file_ptr);
        CloseConfigFile();
        return 1;
    }

    int i, j;
    while(fgets(line, LINE_LENGTH, file_ptr) != NULL)
    {
        i = 0;
        while(line[i] == ' ')
            i++;
        if(line[i] != '#' && line[i] != '\n' && line[i] != '\r' && line[i] != '\0')
        {
            config_file[parameters].name = (char*)malloc(NAME_LENGTH * sizeof(char));
            if(config_file[parameters].name == NULL)
            {
                fclose(file_ptr);
                CloseConfigFile();
                return 1;
            }
            config_file[parameters].value = (char*)malloc(VALUE_LENGTH * sizeof(char));
            if(config_file[parameters].value == NULL)
            {
                free(config_file[parameters].name);
                fclose(file_ptr);
                CloseConfigFile();
                return 1;
            }

            j = 0;
            while(line[i] != '=')
            {
                if(line[i] == '\n' || line[i] == '\r' || line[i] == '\0')
                {
                    fprintf(stderr, "Error in file %s : %s", file_name, line);
                    free(config_file[parameters].name);
                    free(config_file[parameters].value);
                    fclose(file_ptr);
                    CloseConfigFile();
                    return 1;
                }
                if(ValidCharacter(line[i]) == 1)
                {
                    config_file[parameters].name[j] = line[i];
                    j++;
                }
                i++;   
            }

            config_file[parameters].name[j] = '\0';
            i++;
            j = 0;

            while(line[i] != '\n' && line[i] != '\r' && line[i] != '\0')
            {
                if(ValidCharacter(line[i]) == 1)
                {
                    config_file[parameters].value[j] = line[i];
                    j++;
                }
                i++;   
            }

            config_file[parameters].value[j] = '\0';
            parameters++;
        }
    }

    fclose(file_ptr);
    
    return 0;
}

char* GetParameter(const char* parameter)
{
    if(config_file == NULL)
        return NULL;
    int i;
    for(i = 0; i < parameters; i++)
    {
        if(strcmp(parameter, config_file[i].name) == 0)
            return config_file[i].value;
    }
    fprintf(stderr, "Parameter %s not found in %s\n", parameter, current_file);
    return NULL;
}


int GetParameterInt(const char* parameter)
{
    char* tmp = GetParameter(parameter);
    return ParseParameter(tmp);
}

ERR CloseConfigFile()
{
    if(config_file == NULL)
        return 1;
    int i;
    for(i = 0; i < parameters; i++)
    {
        if(config_file[i].name != NULL)
            free(config_file[i].name);
        if(config_file[i].value != NULL)
            free(config_file[i].value);
    }
    free(config_file);
    config_file = NULL;
    current_file = "No config file loaded";
    parameters = 0;
    return 0;
}
