#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>

void SetLocation();
void GetLocation(std::string* cmd);
std::string Exec(const char* cmd); 
bool ValidOption(int option, int maxSize);
void SplitAVD(std::vector<std::string>& avdDevices, std::string output);
void ShowAvdDevices(std::vector<std::string> avdDevices);

int main()
{
	std::vector<std::string> avdDevices;
	
	SetLocation();
	
	try
	{
		std::string output = Exec("D: && cd D:\\Programas\\android-sdk\\emulator && emulator -list-avds");
		
		// Spliting all the Android devices for later choose
		SplitAVD(avdDevices, output);
		
		int option = -1;
		bool missed = false;
		
		while (!ValidOption(option, avdDevices.size()))
		{
			ShowAvdDevices(avdDevices);
			
			if (missed){
				std::cout << "Option no valid" << std::endl;
			}
			
			std::cout << "Option: ";
			std::cin >> option;
			
			if (ValidOption(option, avdDevices.size()))
			{
				std::string runAvd = "D: && cd D:\\Programas\\android-sdk\\emulator && emulator -avd " + avdDevices[option];
				ShowWindow(GetConsoleWindow(), SW_HIDE);
				system(runAvd.c_str());
			}
			else
			{
				missed = true;
				system("cls");
			}
		}
	}
	catch (std::runtime_error e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	
	return 0;	
}

void SetLocation()
{	
	// Checking if already exists, so it's setted
	std::fstream file;
	file.open("avdSetting.txt");
	
	if (file.fail()) // No exists so need to set location for first time
	{
		std::ofstream fOut("avdSetting.txt", std::ofstream::out);
		std::string emulatorRoute;
		
		std::cout << "Note: YOU CAN CHANGE this route on ( avdSetting.txt ) if you get it wrong";
		//std::cout << "in case you want to change it manually you should use \\\\ instead of \\\n\n";
		
		std::cout << "What is the route of the emulator?" << std::endl;
		std::cout << "Example: D:\\Programas\\android-sdk\\emulator" << std::endl;
		
		std::cout << "Route: ";
		getline(std::cin, emulatorRoute);
		
		// Debug
		std::cout << "Route: " << emulatorRoute << std::endl;
		while(true);
		
		// Erasing posible white space on the first char
		int spaceIndex = emulatorRoute.find(' ');
		while(spaceIndex != 0)
		{
			emulatorRoute.erase(emulatorRoute.begin());
			spaceIndex = emulatorRoute.find(' ');
		}
		
		fOut << "Route: " << emulatorRoute;
	}
}

/*
*	Function for take the output log of the cmd 
*
*	Param in:
*		const char* cmd: Command used in the cmd to get into emulator folder and get all available Android devices
*	
*	Param out:
*		std::string result: Output of the console log with all available Android Android devices
*				
*/
std::string Exec(const char* cmd) 
{
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

bool ValidOption(int option, int maxSize)
{
	return (option < maxSize && option >= 0);
}

void ShowAvdDevices(std::vector<std::string> avdDevices)
{
	for (int i=0; i < avdDevices.size(); i++)
	{
		std::cout << i << ") " << avdDevices[i] << std::endl;
	}
	
	std::cout << std::endl;
}

void SplitAVD(std::vector<std::string>& avdDevices, std::string output)
{
	int index = output.find('\n');
	
	while(index > 0){
		avdDevices.push_back(output.substr(0, index));
		output.erase(0, index+1);
		index = output.find('\n');
	}	
}

