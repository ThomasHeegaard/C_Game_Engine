/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : graphics.c
|Author   : Thomas Heegaard
|Created  : 11/06/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "graphics.h"
#include "../utils/sdl_wrapper.h"
#include "../graphics/fps_manager.h"

typedef struct SpriteStack
{
    Sprite*             sprite;
    struct SpriteStack* next;
} SpriteStack;

SpriteStack* spritestack = NULL;

ERR DrawSprite(Sprite* sprite)
{
    if(spritestack == NULL)
    {
        spritestack = (SpriteStack*)malloc(sizeof(SpriteStack));
        spritestack->sprite = sprite;
        spritestack->next = NULL;
        return 0;
    }

    SpriteStack* new = (SpriteStack*)malloc(sizeof(SpriteStack));
    if(new == NULL)
        return 1;
    new->sprite = sprite;
    new->next = NULL;

    if(sprite->z_index < spritestack->sprite->z_index)
    {
        new->next = spritestack;
        spritestack = new;
        return 0;
    }

    SpriteStack* tmp = spritestack;

    while(tmp->sprite->z_index < sprite->z_index && tmp->next != NULL)
        tmp = tmp->next;

    new->next = tmp->next;
    tmp->next = new;

    return 0;
}

ERR Render()
{
    if(spritestack == NULL)
        return 0;
    
    ClearScreen();

    SpriteStack*    tmp = spritestack;
    SpriteStack*    del;
    ERR             errors;

    while(tmp->next != NULL)
    {
        errors += RenderSprite(tmp->sprite);
        del = tmp;
        tmp = tmp->next;
        free(del);
    }
    errors += RenderSprite(tmp->sprite);
    free(tmp);
    spritestack = NULL;

    UpdateScreen();
    ManageFPS();
    return errors;
}
