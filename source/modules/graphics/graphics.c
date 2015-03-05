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
#include "sdl_wrapper.h"
#include "fps_manager.h"
#include "list.h"

List* sprite_stack = NULL;

ERR DrawSprite(Sprite* sprite)
{
    if(sprite_stack == NULL)
    {
        sprite_stack = NewList();
        InsertValue(sprite, sprite_stack, 0);
        return 0;
    }

    int i = 0;
    Element* ptr = sprite_stack->start;
    while(i < sprite_stack->size && ((Sprite*)ptr->value)->z_index < sprite->z_index)
    {
        ptr = ptr->next;
        i++; 
    }
    InsertValue(sprite, sprite_stack, i);

    return 0;
}

ERR Render()
{
    if(sprite_stack == NULL)
        return 0;
    
    ClearScreen();

    ERR             errors;

    Element* tmp;
    while(sprite_stack->size != 0)
    {
        tmp = RemoveElement(sprite_stack, 0);
        errors += RenderSprite((Sprite*)tmp->value);
        free(tmp);
    }
    ClearList(sprite_stack);
    sprite_stack = NULL;

    UpdateScreen();
    ManageFPS();
    return errors;
}
