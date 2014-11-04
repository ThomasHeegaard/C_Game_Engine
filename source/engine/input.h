/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : input.h
|Author   : Thomas Heegaard
|Created  : 11/04/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef INPUT_H
#define INPUT_H


void InputFocus() 

void InputBlur() 

void KeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) 

void KeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) 

void MouseFocus() 

void MouseBlur() 

void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) 

void MouseWheel(bool Up, bool Down) 

void LButtonDown(int mX, int mY) 

void LButtonUp(int mX, int mY) 

void RButtonDown(int mX, int mY) 

void RButtonUp(int mX, int mY) 

void MButtonDown(int mX, int mY) 

void MButtonUp(int mX, int mY) 

void JoyAxis(Uint8 which,Uint8 axis,Sint16 value) 

void JoyButtonDown(Uint8 which,Uint8 button) 

void JoyButtonUp(Uint8 which,Uint8 button) 

void JoyHat(Uint8 which,Uint8 hat,Uint8 value) 

void JoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) 

void Minimize() 

void Restore() 

void Resize(int w,int h) 

void Expose() 

void Exit() 

void User(Uint8 type, int code, void* data1, void* data2) 

#endif //INPUT_H
