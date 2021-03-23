#include "stdafx.h"
#include "MouseControl.h"



void MouseControl::LBDown(void)
{
	RaiseMouseInput(MOUSEEVENTF_LEFTDOWN);
}

void MouseControl::LBUp(void)
{
	RaiseMouseInput(MOUSEEVENTF_LEFTUP);
}

void MouseControl::RaiseMouseInput(DWORD type)
{
	INPUT input[] = {{INPUT_MOUSE, 0, 0, 0, type, 0, 0,}};
	::SendInput(1, input, sizeof(INPUT));
}

void MouseControl::MoveTo(const POINT& p)
{
	SetCursorPos(p.x, p.y);
}

void MouseControl::MoveTo(int x, int y)
{
	SetCursorPos(x, y);
}

POINT MouseControl::GetPos(void)
{
	POINT p;
	GetCursorPos(&p);
	return p;
}

void MouseControl::Drag(const POINT& from, const POINT& to, DWORD duration)
{
	MoveTo(from);
	Sleep(duration);

	LBDown();
	Sleep(duration);

	MoveTo(to);
	Sleep(duration);

	LBUp();
}

void MouseControl::Click(DWORD duration)
{
	LBDown();
	Sleep(duration);
	LBUp();
}
