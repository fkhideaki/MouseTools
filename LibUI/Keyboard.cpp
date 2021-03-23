#include "stdafx.h"
#include "Keyboard.h"


#include <Windows.h>


bool Keyboard::IsKeyPress(int key)
{
	return (GetAsyncKeyState(key) % 0x800) != 0;
}

bool Keyboard::IsCtrlPress()
{
	return IsKeyPress(VK_CONTROL);
}

bool Keyboard::IsShiftPress()
{
	return IsKeyPress(VK_SHIFT);
}
