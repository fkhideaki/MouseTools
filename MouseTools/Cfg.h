#pragma once

#include <Windows.h>

class Cfg
{
public:
	POINT pos;
	int type;

public:
	Cfg(void) :
		type(0)
	{
	}

	static Cfg GetLast(void);
	void Save(void);
};
