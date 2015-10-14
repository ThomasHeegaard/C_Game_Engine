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

typedef struct Image
{
    Sprite* sprite;
    PixelMap* pixel_map;
    unsigned char z_index;
}
Image;

List* graphics_stack = NULL;

ERR InsertImage(Image* image)
{
    if(graphics_stack == NULL)
    {
        graphics_stack = NewList();
        InsertValue(image, graphics_stack, 0);
        return 0;
    }

    int i = 0;
    Element* ptr = graphics_stack->start;
    while(i < graphics_stack->size && ((Image*)ptr->value)->z_index < image->z_index)
    {
        ptr = ptr->next;
        i++; 
    }
    InsertValue(image, graphics_stack, i);

    return 0;
}

ERR DrawSprite(Sprite* sprite)
{
    if(sprite == NULL)
        return 1;

    Image* image = (Image*)malloc(sizeof(Image));
    image->sprite = sprite;
    image->pixel_map = NULL;
    image->z_index = sprite->z_index;

    return InsertImage(image);
}

ERR DrawPixelMap(PixelMap* pm)
{
    if(pm == NULL)
        return 1;

    Image* image = (Image*)malloc(sizeof(Image));
    image->sprite = NULL;
    image->pixel_map = pm;
    image->z_index = pm->z_index;

    return InsertImage(image);
}

ERR Render()
{
    if(graphics_stack == NULL)
        return 0;
    
    ClearScreen();

    ERR errors = 0;

    Element* tmp;
    Image* tmp_image;
    while(graphics_stack->size != 0)
    {
        tmp = RemoveElement(graphics_stack, 0);
        tmp_image = (Image*)tmp->value;
        if(tmp_image->pixel_map == NULL)
        {
            errors += RenderSprite(tmp_image->sprite);
        }
        else if(tmp_image->sprite == NULL)
        {
            errors += RenderPixelMap(tmp_image->pixel_map);
        }
        else
            errors += 1;
        free(tmp_image);
        free(tmp);
    }
    ClearList(graphics_stack);
    graphics_stack = NULL;

    UpdateScreen();
    ManageFPS();
    return errors;
}
