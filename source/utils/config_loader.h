/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : config_loader.h
|Author   : Thomas Heegaard
|Created  : 11/11/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include "global_defines.h"

#define LINE_LENGTH      150
#define MAX_LINES        100
#define MAX_PARAMETERS   50
#define NAME_LENGTH      20
#define VALUE_LENGTH     100

ERR OpenConfigFile(const char* file_name);

char* GetParameter(const char* parameter);

int GetParameterInt(const char* parameter);

ERR CloseConfigFile();

#endif //CONFIG_LOADER_H
