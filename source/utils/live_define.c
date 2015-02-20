//Created by script

#include <string.h>
#include <stdio.h>


int TranslateDefines(const char* value)
{
    if(strcmp("STATIC", value) == 0)
        return 0;
    if(strcmp("ANIMATION", value) == 0)
        return 1;
    if(strcmp("PLAY", value) == 0)
        return 2;
    if(strcmp("OSCILLATING", value) == 0)
        return 4;
    if(strcmp("MULTILOOP", value) == 0)
        return 8;
    if(strcmp("FRAMES", value) == 0)
        return 0;
    if(strcmp("CURRENT_FRAME", value) == 0)
        return 1;
    if(strcmp("DIRECTION", value) == 0)
        return 2;
    if(strcmp("TARGET_FPS", value) == 0)
        return 3;
    if(strcmp("FRAMES_TO_SKIP", value) == 0)
        return 4;
    if(strcmp("LOOPS", value) == 0)
        return 5;
    if(strcmp("CURRENT_LOOP", value) == 0)
        return 6;
    if(strcmp("TEXTURE_COUNT", value) == 0)
        return 4;
    if(strcmp("EXAMPLE1_TEX", value) == 0)
        return 0;
    if(strcmp("EXAMPLE2_TEX", value) == 0)
        return 1;
    if(strcmp("SHIP1_TEX", value) == 0)
        return 2;
    if(strcmp("FIRE_TEX", value) == 0)
        return 3;

    fprintf(stderr, "No define found for %s returning 0\n", value);
    return 0;
}
