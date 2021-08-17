#include <iostream>
#include <windows.h>


int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	system("D: && cd D:\\Programas\\android-sdk\\emulator && emulator -avd Nexus_5_API_30");
	
	return 0;
}
