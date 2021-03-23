#pragma once

#include <Windows.h>



class MouseControl
{
public:
	static void LBDown(void);
	static void LBUp(void);

	static void MoveTo(const POINT& p);
	static void MoveTo(int x, int y);

	static POINT GetPos(void);

	static void Drag(const POINT& from, const POINT& to, DWORD duration = 50);
	static void Click(DWORD duration = 50);

private:
	static void RaiseMouseInput(DWORD type);
};
