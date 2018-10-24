#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <cstdlib>

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	CImitator* imitator = new CImitator();

	imitator->Scan();

	delete imitator;
	_getch();
	return 0;
}

