#include "stdafx.h"

#include <Windows.h>

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
using namespace std;

#include "../LibUI/MouseControl.h"
#include "../LibUI/Keyboard.h"

#include "Cfg.h"


DWORD duration = 80;


bool pressCtrl(void)
{
	return (GetAsyncKeyState(VK_CONTROL) & 0x8000);
}
bool pressShift(void)
{
	return (GetAsyncKeyState(VK_SHIFT) & 0x8000);
}
bool pressAlt(void)
{
	return (GetAsyncKeyState(VK_MENU) & 0x8000);
}

void RecordOrLoadPos()
{
	if (pressCtrl())
	{
		Cfg c;
		c.pos = MouseControl::GetPos();
		if (pressShift()) {
			if (pressAlt())
				c.type = 2;
			else
				c.type = 1;
		}
		c.Save();
	}
	else
	{
		Cfg c = Cfg::GetLast();
		if (c.type == 1) {
			MouseControl::MoveTo(c.pos);
			MouseControl::Click(duration);
		} else if (c.type == 2) {
			POINT cur = MouseControl::GetPos();
			MouseControl::MoveTo(c.pos);
			MouseControl::Click(duration);
			MouseControl::MoveTo(cur);
		} else {
			MouseControl::MoveTo(c.pos);
		}
	}
}

void AxisLock(void)
{
	Cfg last = Cfg::GetLast();
	POINT cur = MouseControl::GetPos();

	POINT d;
	d.x = cur.x;
	d.y = cur.y;
	if (abs(d.x - last.pos.x) >= abs(d.y - last.pos.y))
		d.y = last.pos.y;
	else
		d.x = last.pos.x;

	MouseControl::MoveTo(d);
}

void FlipPos(void)
{
	POINT cur = MouseControl::GetPos();

	try
	{
		MouseControl::MoveTo(Cfg::GetLast().pos);
	}
	catch (...)
	{
	}

	Cfg c;
	c.pos = cur;
	c.type = 0;
	c.Save();
}

void DragCurrentToLast(void)
{
	Cfg last = Cfg::GetLast();
	POINT cur = MouseControl::GetPos();

	MouseControl::Drag(cur, last.pos, duration);
	MouseControl::MoveTo(cur);
}

void LoadSavePos(void)
{
	if (Keyboard::IsCtrlPress())
	{
		Cfg c;
		c.pos = MouseControl::GetPos();
		c.type = 0;
		c.Save();
	}
	else
	{
		MouseControl::MoveTo(Cfg::GetLast().pos);
	}
}

void Help(void)
{
	cout << "c : move to record (ctrl+ to record, shift+ to click)" << endl;
	cout << "x : axis lock" << endl;
	cout << "f : flip pos" << endl;
	cout << "d : drag current to last" << endl;
	cout << "s : load/save pos (ctrl->save)" << endl;
}

void mainproc(LPSTR lpCmdLine)
{
	string a0(__argv[1]);
	if (a0.length() == 0)
	{
		cout << "no args" << endl;
		return;
	}

	string cmd;
	cmd.push_back(a0[0]);
	try
	{
		if (cmd == "c") return RecordOrLoadPos();
		if (cmd == "x") return AxisLock();
		if (cmd == "f") return FlipPos();
		if (cmd == "d") return DragCurrentToLast();
		if (cmd == "s") return LoadSavePos();
		return Help();
	}
	catch (...)
	{
		cout << "error" << endl;
	}
}

int WINAPI WinMain(
	HINSTANCE hInstance,      // 現在のインスタンスのハンドル
	HINSTANCE hPrevInstance,  // 以前のインスタンスのハンドル
	LPSTR lpCmdLine,          // コマンドライン
	int nCmdShow              // 表示状態
	)
{
	mainproc(lpCmdLine);
	return 0;
}
