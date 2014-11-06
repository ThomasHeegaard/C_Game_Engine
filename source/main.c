/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : main.c
|Author   : Thomas Heegaard
|Created  : 10/30/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/


#include <stdlib.h>
#include <stdio.h>
#include "utils/sdl_wrapper.h"
#include "graphics/fps_manager.h"
#include "graphics/sprite.h"
#include "engine/test_controller.h"

#include <SDL2/SDL.h>

int main()
{
    if(InitSDL() != 0)
        return 1;
    InitFPS();

    StartTestController();

    printf("FPS: %d\n", GetFPS());

    ExitSDL();
    return 0;
}
