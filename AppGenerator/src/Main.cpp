#include <iostream>
#include <fstream> 
#include <direct.h>
#include <src/monoScript.h>
#include <src/ScriptGen.h>
#include <src/Global.h>
#include <src/Messages.h>
int input(int arc, const char* args[]);
bool charEquals(const char* a, const char* b);
bool isFilePath(const char* a);
bool isNumber(char c);

#define print(x) std::cout << x << '\n'; 

int main(int arc, const char* args[])
{
	int inputCoide = input(arc, args);
	if (inputCoide < 0)
	{
		return inputCoide;
	}
	int createfiles();
	int fileCreateCode = createfiles();
	if (fileCreateCode < 0)
	{
		return fileCreateCode;
	}

}

int input(int arc, const char* args[])
{
	if (arc == 1)
	{
		std::cout << Message::NoInput;
		return -1;
	}
	if (arc > 1)
	{ 
		if (charEquals(args[1],"--help"))
		{
			std::cout << Message::HelpMessage;
			return -2;
		}
		else if (isFilePath(args[1]))
		{
			filePath = args[1];
			std::string disk = args[1];
			disk = disk.substr(0,2);
			struct stat statInfo;
			if (stat(filePath.c_str(), &statInfo) == 0)
			{
				if (arc > 2)
				{
					fileName = args[2];
				}
				else
				{
					print("You provided no file name use: " + appname + " --help to get more info");
				}
			}
			else
			{
				print("filePath \x1B[31m" << filePath << "\033[0m is not an existing dirrectory");
				return -1;
			} 
		}
	}
	return 1;
}
bool charEquals(const char* a, const char* b)
{
	int i = 0;
	while (true)
	{
		if (a[i] == b[i])
		{
			if (a[i] == '\0')
			{
				return true;
			}
		}
		else
		{
			return false;
		}
		i++;
	}
}
bool isFilePath(const char* a)
{
	bool isok = true;
	if (isNumber(a[0]))
	{
		isok = false;
	}
	else if (a[1] != ':')
	{
		isok = false;
	}
	else if (a[2] != '\\' && a[2] != '/')
	{
		isok = false;
	}
	return isok;
}
bool isNumber(char c)
{
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': 
		return true; 
		break;
	default:
		return false;
		break;
	}
}
int createfiles()
{
	struct stat statInfo;
	int createFileError = 0;
	std::string fileStruct[7] =
	{
		"\\Built",
		"\\Debug",
		"\\res",
		"\\res\\assets",
		"\\res\\src",
		"\\res\\bin",
		"\\res\\test",
	};
	if (stat((filePath + "\\" + fileName).c_str(), &statInfo) == 0)
	{
		print("Cannot create files, given file already exists");
	} 
	else
	{
		if (_mkdir((filePath + "\\" + fileName).c_str()) == 0)
		{
			for (int i = 0; i < 7; i++)
			{
				if (_mkdir((filePath + "\\" + fileName +"\\"+ fileStruct[i]).c_str()) == -1)
				{
					createFileError = -1;
					break;
				}
			}
			if (createFileError >= 0)
			{
				std::ofstream RunFile(filePath + "\\" + fileName + "\\" + "\\res\\src\\Run.cpp");
				RunFile.write(RunScript.c_str(), RunScript.size());
				RunFile.close();
				
				std::ofstream vcxprojFile(filePath + "\\" + fileName + "\\"+ fileName + ".mono");
				vcxprojFile.write(getMonoScript(fileName).c_str(), getMonoScript(fileName).size());
				vcxprojFile.close();
			}
		}
		else
		{
			createFileError = -1;
		}
		if (createFileError < 0)
		{
			print("Could not create file");
			return createFileError;
		}
		else
		{
			print("File Created Suckcesfully");
			return 1;
		}
	}
	return 0;
}