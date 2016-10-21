#include "Therm.h"
#include <Windows.h>

int main()
{
	Therm t;
	
	int offset = 5;
	while (true)
	{
		t.Update();
		t.SetTemp(t.GetTemp() + offset);
		offset = -offset;
		Sleep(200);
	}

	system("pause");
}