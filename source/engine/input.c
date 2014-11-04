/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : input.c
|Author   : Thomas Heegaard
|Created  : 11/04/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "input.h"

void InputFocus() 
{
    //Pure virtual, do nothing
}

void InputBlur() 
{
    //Pure virtual, do nothing
}

void KeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
    //Pure virtual, do nothing
}

void KeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 
{
    //Pure virtual, do nothing
}

void MouseFocus() 
{
    //Pure virtual, do nothing
}

void MouseBlur() 
{
    //Pure virtual, do nothing
}

void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) 
{
    //Pure virtual, do nothing
}

void MouseWheel(bool Up, bool Down) 
{
    //Pure virtual, do nothing
}

void LButtonDown(int mX, int mY) 
{
    //Pure virtual, do nothing
}

void LButtonUp(int mX, int mY) 
{
    //Pure virtual, do nothing
}

void RButtonDown(int mX, int mY) 
{
    //Pure virtual, do nothing
}

void RButtonUp(int mX, int mY) 
{
    //Pure virtual, do nothing
}

void MButtonDown(int mX, int mY) 
{
    //Pure virtual, do nothing
}

void MButtonUp(int mX, int mY) 
{
    //Pure virtual, do nothing
}

void JoyAxis(Uint8 which,Uint8 axis,Sint16 value) 
{
    //Pure virtual, do nothing
}

void JoyButtonDown(Uint8 which,Uint8 button) 
{
    //Pure virtual, do nothing
}

void JoyButtonUp(Uint8 which,Uint8 button) 
{
    //Pure virtual, do nothing
}

void JoyHat(Uint8 which,Uint8 hat,Uint8 value) 
{
    //Pure virtual, do nothing
}

void JoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) 
{
    //Pure virtual, do nothing
}

void Minimize() 
{
    //Pure virtual, do nothing
}

void Restore() 
{
    //Pure virtual, do nothing
}

void Resize(int w,int h) 
{
    //Pure virtual, do nothing
}

void Expose() 
{
    //Pure virtual, do nothing
}

void Exit() 
{
    //Pure virtual, do nothing
}

void User(Uint8 type, int code, void* data1, void* data2) 
{
    //Pure virtual, do nothing
}
