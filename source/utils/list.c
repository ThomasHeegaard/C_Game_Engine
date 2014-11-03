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

ERR InsertElement(List* list, Element* element, unsigned short position)
{
    if(list == NULL || element == NULL || position > list->size || (list->start == NULL && position > 0))
        return 1;

    if(position == 0 || list->start == NULL)
    {
        element->next   = list->start;
        list->start     = element;
        list->size++;
        return 0;
    }

    Element* previous = list->start;
    if(position < 0)
    while(previous->next != NULL)
        previous = previous->next;
    else
        while(position > 1)
        {
            if(previous->next == NULL)
            {
                printf("Accessing inexistant position\n");
                return 1;
            }
            previous = previous->next;   
            position--;
        }

    element->next   = previous->next;
    previous->next  = element;
    list->size++;
    return 0;

}

ERR AddElement(void* object, List* list, unsigned short position)
{
    Element* new    = (Element*)malloc(sizeof(Element));
    new->value      = value;
    new->next       = NULL;
    return InsertElement(list, new, position);
}

Element* GetElement(List* list, unsigned short position)
{
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

Element* RemoveElement(List* list, unsigned short position)
{
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

ERR FreeElement(List* list, unsigned short position)
{
    Element* tmp = RemoveElement(list, position);
    if(tmp == NULL)
        return 1;
    free(tmp);
    return 0;
}

ERR MoveElement(List* list, unsigned short from_pos, unsigned short to_pos)
{
    if(from_pos == to_pos)
        return 0;

    Element* from = RemoveElement(list, from_pos);
    return InsertElement(list, from, to_pos) != 0;
}

ERR SwitchElements(List* list, unsigned short pos_a, unsigned short pos_b)
{
    if(pos_a == pos_b)
        return 0;
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

void PrintList(List* list)
{
    Element* element = list->start;
    while(element->next != NULL)
    {
        printf("%d\n", element->value);
        element = element->next;
    }
    printf("%d\n", element->value);
}

void ClearList(List* list)
{
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
