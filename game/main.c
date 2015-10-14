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
#include "sdl_wrapper.h"
#include "fps_manager.h"
#include "sprite.h"
#include "test_controller.h"

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
