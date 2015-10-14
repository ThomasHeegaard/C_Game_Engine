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

//=============================================================
//          STRUCTURES
//=============================================================

typedef struct Element
{
    void*   value;
    struct  Element* next;
} Element;

typedef struct List
{
    Element*    start;
    int         size;
} List;

//=============================================================
//          FUNCTIONS
//=============================================================
List* NewList();    //New empty list, with no elements
                    //and size 0

List* CopyList(List* original);   
                    //returns a new list identical to the original

//=============================================================
ERR InsertElement(List* list, Element* element, int position);
                    //Inserts given element into the given
                    //list at the given position
                    //(0 for front, -1 for back)

//=============================================================
ERR InsertValue(void* value, List* list, int position);
                    //Add element of given value to given
                    //position (0 for front, -1 for back)

//=============================================================
Element* GetElement(List* list, int position);
                    //Get element at given position
                    //(0 for front, -1 for back)

//=============================================================
void* GetValue(List* list, int position);
                    //Get value of element at given position
                    //(0 for front, -1 for back)

//=============================================================
Element* RemoveElement(List* list, int position);
                    //Returns element at given position
                    //removing it from the list
                    //(0 for front, -1 for back)

//=============================================================
ERR FreeElement(List* list, int position);
                    //Removes and frees the element at
                    //the given position
                    //(0 for front, -1 for back)

//=============================================================
ERR MoveElement(List* list, int from_pos, int to_pos);
                    //Moves the element at position from_pos
                    //to position to_pos

//=============================================================
ERR SwitchElements(List* list, int pos_a, int pos_b);
                    //Switches the two elements at the 
                    //given positions

//=============================================================
ERR InvertList(List* list);
                    //Inverts the order of the elements in
                    //the list

//=============================================================
void ClearList(List* list);
                    //Frees all elements and the list itself

#endif //LIST_H
