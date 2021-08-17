#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <vector>
#include <windows.h>

std::string exec(const char* cmd) {
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

bool ValidOption(int option, int maxSize);
void ShowAvdDevices(std::vector<std::string> avdDevices);

int main()
{
	std::vector<std::string> avdDevices;
	
	try
	{
		std::string output = exec("D: && cd D:\\Programas\\android-sdk\\emulator && emulator -list-avds");
		int index = output.find('\n');
		
		while(index > 0){
			avdDevices.push_back(output.substr(0, index));
			output.erase(0, index+1);
			index = output.find('\n');
		}
		
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
		std::cout << "Error cmd" << std::endl;
	}
	
	
	//system("D: && cd D:\\Programas\\android-sdk\\emulator && emulator -list-avds");
	//emulator -avd Nexus_5_API_30
	
	return 0;	
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
