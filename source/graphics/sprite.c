/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : sprite.c
|Author   : Thomas Heegaard
|Created  : 10/26/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "../utils/sdl_wrapper.h"
#include "fps_manager.h"
#include "sprite.h"

Sprite* NewSprite(unsigned short texture_id, unsigned char flags)
{
    if(texture_bank[texture_id] == NULL)
        if(LoadTexture(texture_id) != 0)
        {
            fprintf(stderr, "Unable to load texture_id %d", texture_id);
            return NULL;
        }

    Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));
    if(sprite == NULL)
    {
        fprintf(stderr, "Memory allocation failure for sprite %d", texture_id);
        return NULL;
    }

    if(flags != 0 && !(flags & ANIMATION))
    {
        fprintf(stderr, "Corrupted flags %d for sprite %d", flags, texture_id);
        free(sprite);
        return NULL;
    }

    sprite->texture_id  = texture_id;
    sprite->w           = 0;
    sprite->h           = 0;
    sprite->center_x    = 0;
    sprite->center_y    = 0;
    sprite->angle       = 0.0;
    sprite->zoom        = 1.0;
    sprite->flags       = flags;

    if(flags & ANIMATION)
    {
        if(flags & MULTILOOP)
            sprite->data = (char*)malloc(7 * sizeof(char));
        else
            sprite->data = (char*)malloc(5 * sizeof(char));
        if(sprite->data == NULL)
        {
            fprintf(stderr, "Memory allocation failure for sprite %d", texture_id);
            free(sprite);
            return NULL;
        }
        sprite->data[FRAMES]            = 0;
        sprite->data[CURRENT_FRAME]     = 0;
        sprite->data[DIRECTION]         = 0;
        sprite->data[TARGET_FPS]        = 0;
        sprite->data[FRAMES_TO_SKIP]    = 0;
        if(flags & MULTILOOP)
        {
            sprite->data[LOOPS]         = 0;
            sprite->data[CURRENT_LOOP]  = 0;
        }
    }
    else
        sprite->data = NULL;
    
    return sprite;
}

ERR RenderSprite(Sprite* sprite)
{
    RECT src, dst;
    dst.w = sprite->w * sprite->zoom;
    dst.h = sprite->h * sprite->zoom;
    dst.x = sprite->center_x - dst.w / 2;
    dst.y = sprite->center_y - dst.h / 2;

    if(sprite->flags & ANIMATION)
    {
        if(sprite->flags & MULTILOOP)
            src.x = sprite->w * sprite->data[CURRENT_LOOP];
        else
            src.x = 0;

        src.y = sprite->h * sprite->data[CURRENT_FRAME];
    }
    else
    {
        src.x = 0;
        src.y = 0;
    }
    src.w = sprite->w;
    src.h = sprite->h;

    if(DrawTexture(sprite->texture_id, sprite->angle, &src, &dst) != 0)
        return 1;
    if(sprite->flags & ANIMATION && sprite->flags & PLAY)
    {
        if(sprite->data[FRAMES_TO_SKIP] <= 0)
        {
            sprite->data[FRAMES_TO_SKIP] = GetFPS()/sprite->data[TARGET_FPS];
            if(sprite->data[DIRECTION] == 0)
                sprite->data[CURRENT_FRAME]++;
            else
                sprite->data[CURRENT_FRAME]--;

            if(sprite->data[CURRENT_FRAME] >= sprite->data[FRAMES])
            {
                if(sprite->flags & OSCILLATING)
                {
                    sprite->data[DIRECTION] = 1;
                    sprite->data[CURRENT_FRAME] = sprite->data[FRAMES] - 2;
                }
                else
                    sprite->data[CURRENT_FRAME] = 0;
            }
            else if(sprite->data[CURRENT_FRAME] < 0)
            {
                if(sprite->flags & OSCILLATING)
                {
                    sprite->data[DIRECTION] = 0;
                    sprite->data[CURRENT_FRAME] = 1;
                }
                else
                    sprite->data[CURRENT_FRAME] = sprite->data[FRAMES] - 1;
            }
        }
        else
            sprite->data[FRAMES_TO_SKIP]--;
    }
    return 0;
}

ERR FreeSprite(Sprite* sprite)
{
    if(sprite == NULL)
        return 1;
    if(sprite->data != NULL)
        free(sprite->data);
    free(sprite);
    return 0;
}




