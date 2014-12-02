/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : list.c
|Author   : Thomas Heegaard
|Created  : 10/26/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

List* NewList()
{
    List* list = (List*)malloc(sizeof(List));
    if(list == NULL)
    {
        printf("Memory allocation error\n");
        return NULL;
    }
    
    list->start = NULL;
    list->size  = 0;
    return list;
}

ERR InsertElement(List* list, Element* element, int position)
{
    if(list == NULL || element == NULL)
        return 1;
    if(position > 0 && (position >= list->size || list->start == NULL))
        return 1;

    if(position == 0 || list->start == NULL)
    {
        element->next   = list->start;
        list->start     = element;
        list->size++;
        return 0;
    }

    Element* previous = GetElement(list, position - 1);
    if(previous == NULL)
        return 1;
    element->next   = previous->next;
    previous->next  = element;
    list->size++;
    return 0;

}

ERR InsertValue(void* value, List* list, int position)
{
    if(list == NULL)
        return 1;
    Element* new    = (Element*)malloc(sizeof(Element));
    new->value      = value;
    new->next       = NULL;
    return InsertElement(list, new, position);
}

Element* GetElement(List* list, int position)
{
    if(list == NULL)
        return NULL;
    if(list->start == NULL || position >= list->size)
        return NULL;

    Element* element = list->start;

    if(position < 0)
    while(element->next != NULL)
        element = element->next;
    else
        while(position > 0)
        {
            if(element->next == NULL)
            {
                printf("Accessing inexistant position\n");
                return NULL;
            }
            element = element->next;   
            position--;
        }
    return element;
}

void* GetValue(List* list, int position)
{
    Element* tmp = GetElement(list, position);
    if(tmp == NULL)
        return -1;
    return tmp->value;
}

Element* RemoveElement(List* list, int position)
{
    if(list == NULL)
        return NULL;
    if(list->start == NULL || position >= list->size)
        return NULL;

    if(position < 0)
        position = list->size - 1;
    Element* element = GetElement(list, position);
    if(element == NULL)
    {
        printf("Accessing inexistant position\n");
        return NULL;
    }

    if(position == 0)
        list->start = element->next;
    else
    {
        Element* previous = GetElement(list, position - 1);
        if(previous == NULL)
        {
            printf("Accessing inexistant position\n");
            return NULL;
        }
        previous->next = element->next;
    }

    list->size--;
    return element;
}

ERR FreeElement(List* list, int position)
{
    Element* tmp = RemoveElement(list, position);
    if(tmp == NULL)
        return 1;
    free(tmp);
    return 0;
}

ERR MoveElement(List* list, int from_pos, int to_pos)
{
    if(from_pos == to_pos)
        return 0;

    Element* from = RemoveElement(list, from_pos);
    if(from == NULL)
        return 1;
    return InsertElement(list, from, to_pos) != 0;
}

ERR SwitchElements(List* list, int pos_a, int pos_b)
{
    if(pos_a == pos_b)
        return 0;

    if(list == NULL)
        return 1;
    if(list->start == NULL || pos_a > list->size || pos_b > list->size)
        return 1;
    
    if(pos_a == -1)
        pos_a = list->size - 1;
    if(pos_b == -1)
        pos_b = list->size - 1;
    if(pos_a > pos_b)
    {
        pos_a ^= pos_b;
        pos_b ^= pos_a;
        pos_a ^= pos_b;
    }

    if(MoveElement(list, pos_b, pos_a + 1) != 0)
        return 1;
    if(MoveElement(list, pos_a, pos_b) != 0)
        return 1;
    return 0;
}

ERR InvertList(List* list)
{
    if(list == NULL || list->size < 2)
        return 1;

    Element* previous   = list->start;
    Element* tmp        = previous->next;
    Element* next       = tmp->next;
    previous->next      = NULL;
    tmp->next           = previous;

    while(next != NULL)
    {
        previous = tmp;
        tmp = next;
        next = tmp->next;
        tmp->next = previous;
    }

    list->start = tmp;
    return 0;
}

void ClearList(List* list)
{
    if(list == NULL)
        return;
    if(list->start == NULL)
        return;

    Element* element = list->start;
    if(element != NULL)
    {
        Element* next = element->next;
        while(next != NULL)
        {
            free(element);
            element = next;
            next = element->next;
        }
        free(element);
    }
    free(list);
    list = NULL;
}
