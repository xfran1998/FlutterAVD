#include <iostream>
#include <windows.h>

// Faster harcoded version, click and run

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
	// Change the route and the android device for what ever you want to use
	system("D: && cd D:\\Programas\\android-sdk\\emulator && emulator -avd Nexus_5_API_30");
	
	return 0;
}
