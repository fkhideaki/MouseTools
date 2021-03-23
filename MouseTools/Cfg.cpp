#include "stdafx.h"
#include "Cfg.h"

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
using namespace std;


static string posFile;

string getFileFromArg()
{
	if (__argc != 3)
		return "";

	return __argv[2];
}

string getPosFile(void)
{
	if (posFile.empty())
	{
		posFile = getFileFromArg();
		if (posFile.empty())
		{
			posFile = "pos.txt";
		}
	}

	return posFile;
}

Cfg Cfg::GetLast(void)
{
	ifstream in(getPosFile());
	if (!in.is_open())
		throw exception("load error");

	Cfg c;
	in >> c.pos.x >> c.pos.y >> c.type;
	return c;
}

void Cfg::Save(void)
{
	ofstream out(getPosFile());
	if (!out.is_open())
		throw exception("save error");

	out << pos.x << " " << pos.y << " " << type << endl;
}
