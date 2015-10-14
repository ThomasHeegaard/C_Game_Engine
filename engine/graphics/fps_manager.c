/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : fps_manager.c
|Author   : Thomas Heegaard
|Created  : 11/01/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "fps_manager.h"

unsigned long previous_ticks;
unsigned char target_fps;
unsigned long target_time_per_frame;

unsigned long previous_sample_ticks;
unsigned char frames_until_sample;
unsigned char average_fps;

ERR InitFPS()
{
    SetFPS(30);
    frames_until_sample = SAMPLE_RATE;
    average_fps = 30;
    previous_ticks = SDL_GetTicks();
    previous_sample_ticks = SDL_GetTicks();
    return 0;
}

unsigned char GetFPS()
{
    return average_fps;   
}

ERR SetFPS(unsigned char target)
{
    target_fps = target;
    target_time_per_frame = 1000/target_fps;
    return 0;
}

ERR ManageFPS()
{
    frames_until_sample--;
    if(frames_until_sample <= 0)
    {
        average_fps = (1000 * SAMPLE_RATE)/(SDL_GetTicks() - previous_sample_ticks);
        frames_until_sample = SAMPLE_RATE;
        previous_sample_ticks = SDL_GetTicks();
    }

    if(SDL_GetTicks() > previous_ticks + target_time_per_frame)
    {
        previous_ticks = SDL_GetTicks();
        return 1;
    }
    SDL_Delay(target_time_per_frame -  (SDL_GetTicks() - previous_ticks));
    previous_ticks = SDL_GetTicks();
    return 0;
}
