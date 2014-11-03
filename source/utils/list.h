/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : list.h
|Author   : Thomas Heegaard
|Created  : 10/26/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef LIST_H
#define LIST_H

#include "global_defines.h"
#include "../graphics/sprite.h"

//=============================================================
//          STRUCTURES
//=============================================================

typedef struct Element
{
    void*   object;
    struct  Element* next;
} Element;

typedef struct List
{
    Element*    start;
    unsigned short         size;
} List;

//=============================================================
//          FUNCTIONS
//=============================================================
List* NewList();    //New empty list, with no elements
                    //and size 0

//=============================================================
ERR InsertElement(List* list, Element* element, unsigned short position);
                    //Inserts given element into the given
                    //list at the given position
                    //(0 for front, -1 for back)

//=============================================================
ERR AddElement(void* object, List* list, unsigned short position);
                    //Add element of given value to given
                    //position (0 for front, -1 for back)

//=============================================================
Element* GetElement(List* list, unsigned short position);
                    //Get element at given position
                    //(0 for front, -1 for back)

//=============================================================
Element* RemoveElement(List* list, unsigned short position);
                    //Returns element at given position
                    //removing it from the list
                    //(0 for front, -1 for back)

//=============================================================
ERR FreeElement(List* list, unsigned short position);
                    //Removes and frees the element at
                    //the given position
                    //(0 for front, -1 for back)

//=============================================================
ERR MoveElement(List* list, unsigned short from_pos, unsigned short to_pos);
                    //Moves the element at position from_pos
                    //to position to_pos

//=============================================================
ERR SwitchElements(List* list, unsigned short pos_a, unsigned short pos_b);
                    //Switches the two elements at the 
                    //given positions

//=============================================================
void PrintList(List* list);
                    //Print entire list, in order

//=============================================================
void ClearList(List* list);
                    //Frees all elements and the list itself

#endif //LIST_H
