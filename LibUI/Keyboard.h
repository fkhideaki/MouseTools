#pragma once


class Keyboard
{
public:
	static bool IsKeyPress(int key);

	static bool IsCtrlPress();
	static bool IsShiftPress();
};
