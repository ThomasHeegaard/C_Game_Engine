/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : collision_object.c
|Author   : Thomas Heegaard
|Created  : 01/20/2015
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "collision_object.h"
#include "extra_math.h"
#include <stdio.h>
#include <stdlib.h>

CollisionObject* NewCollisionObject()
{
    CollisionObject* ret = (CollisionObject*)malloc(sizeof(CollisionObject));
    if(ret == NULL)
    {
        fprintf(stderr, "Memory allocation failed, Collision Object Initialisation failed\n");
        return NULL;
    }
    ret->center_x       = 0;
    ret->center_y       = 0;
    ret->radius         = 0;
    ret->element_count  = 0;
    ret->elements       = NULL;
    return ret;
}

CollisionObject* CopyCollisionObject(CollisionObject* original)
{
    CollisionObject* ret = NewCollisionObject();
    if(ret == NULL)
        return NULL;
    ret->center_x = original->center_x;
    ret->center_y = original->center_y;
    ret->radius = original->radius;
    ret->element_count = original->element_count;
    ret->elements = NULL;
    if(original->elements != NULL)
        ret->elements = CopyList(original->elements);
    if(ret->element_count != 0 && ret->elements == NULL)
    {
        fprintf(stderr, "Error copying element list, CopyCollisionObject failed\n");
        free(ret);
        return NULL;
    }

    return ret;
}

ERR AddCollisionElement(CollisionObject* obj, unsigned char shape, int dx, int dy, int w, int h, double da)
{
    if(obj == NULL)
    {
        fprintf(stderr, "Attempting to add element to NULL collision object\n");
        return 1;
    }
    if(obj->elements == NULL)
    {
        obj->elements = NewList();
        if(obj->elements == NULL)
        {
            fprintf(stderr, "Memory allocation failure, AddCollisionElement failed\n");
            return 1;
        }
    }
    CollisionElement* element = (CollisionElement*)malloc(sizeof(CollisionElement));
    if(element == NULL)
    {
        fprintf(stderr, "Memory allocation failure, AddCollisionElement failed\n");
        return 1;
    }
    
    element->shape = shape;
    element->x_offset = dx;
    element->y_offset = dy;
    element->width = w;
    element->height = h;
    element->angular_offset = da;

    InsertValue(element, obj->elements, 0);
    return 0;
}

ERR FreeCollisionObject(CollisionObject* obj)
{
    ClearList(obj->elements);
    obj->elements = NULL;
    free(obj);
    return 0;
}

ERR CheckElementCollision(CollisionElement* el_a, CollisionElement* el_b, int o_a_x, int o_a_y, int o_b_x, int o_b_y)
{
    if(el_a == NULL || el_b == NULL)
    {
        fprintf(stderr, "NULL collision element encountered\n");
        return 1;
    }
    if(el_a->shape == CIRCLE_SHAPE && el_b->shape == CIRCLE_SHAPE)
    {
        if(Distance(o_a_x + el_a->x_offset, o_a_y + el_a->y_offset, o_b_x + el_b->x_offset, o_b_y + el_b->y_offset)
                <= el_a->width + el_b->width)
            return 1;
    }
    return 0;
}

ERR CheckCollision(CollisionObject* obj_a, CollisionObject* obj_b)
{
    if(Distance(obj_a->center_x, obj_a->center_y, obj_b->center_x, obj_b->center_y) > obj_a->radius + obj_b->radius)
        return 0;
    if(obj_a->elements == NULL && obj_b->elements == NULL)
        return 1;
printf("COllision problem\n");
    Element* tmp_a;
    Element* tmp_b;
    tmp_a = obj_a->elements->start;
    while(tmp_a != NULL)
    {
        tmp_b = obj_b->elements->start;
        while(tmp_b != NULL)
        {
            if(CheckElementCollision((CollisionElement*)(tmp_a->value), (CollisionElement*)(tmp_b->value),
                        obj_a->center_x, obj_a->center_y, obj_b->center_x, obj_b->center_y) != 0)
                return 1;
            tmp_b = tmp_b->next;
        }
        tmp_a = tmp_a->next;
    }
    return 0;
}
