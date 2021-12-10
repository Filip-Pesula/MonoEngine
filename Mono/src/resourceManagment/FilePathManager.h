#pragma once
#include <string>
#include <Windows.h>
#include <vector>
//doc: https://docs.microsoft.com/en-us/windows/win32/api/commdlg/ns-commdlg-openfilenamea
class FilePathManager
{
public:
	static std::string OpenFileDialog(HWND hwind, std::string path, std::string filters);
	static std::vector<std::string> OpenFilesDialog(HWND hwind, std::string path, std::string filters);
	static std::string OpenFolderDialog(HWND hwind, std::string path, std::string filters);
	static std::string SaveFileDialog(HWND hwind, std::string path, std::string filters);
};

