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
                if(line[i] != ' ')
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
                if(line[i] != ' ')
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
    if(tmp == NULL)
        return 0;
    return atoi(tmp);
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
    current_file = "No config file loaded";
    parameters = 0;
    return 0;
}

