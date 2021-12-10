#include "FilePathManager.h"
#include <commdlg.h>
#include <shlobj_core.h>


std::string FilePathManager::OpenFileDialog(HWND hwind, std::string path, std::string filters)
{
	OPENFILENAME ofn;
	CHAR lpstrfile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = lpstrfile;
	ofn.lpstrInitialDir = path.c_str();
	ofn.nMaxFile = sizeof(lpstrfile);
	ofn.lpstrFilter = filters.c_str();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == true) {
		return ofn.lpstrFile;
	}
	else {
		return std::string();
	}
}

std::vector<std::string> FilePathManager::OpenFilesDialog(HWND hwind, std::string path, std::string filters)
{
	std::vector<std::string> retVals;
	OPENFILENAME ofn;
	CHAR lpstrfile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = lpstrfile;
	ofn.lpstrInitialDir = path.c_str();
	ofn.nMaxFile = sizeof(lpstrfile);
	ofn.lpstrFilter = filters.c_str();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	if (GetSaveFileNameA(&ofn) == true) {
		char* lpstrFileStr = ofn.lpstrFile;
		while (*lpstrFileStr != '\0') {
			retVals.push_back(std::string(lpstrFileStr));
			lpstrFileStr += retVals.back().size()+1;
		}
		return retVals;
	}
	else {
		return std::vector<std::string>{};
	}
}

std::string FilePathManager::OpenFolderDialog(HWND hwind, std::string path, std::string filters)
{
	//TODO implemend opening browsers
	/*
	LPBROWSEINFOA bfn;
	CHAR lpstrfile[260] = { 0 };
	ZeroMemory(&bfn, sizeof(LPBROWSEINFOA));
	bfn->hwndOwner = nullptr;
	bfn->
	bfn->lpstrFile = lpstrfile;
	bfn.lpstrInitialDir = path.c_str();
	bfn.nMaxFile = sizeof(lpstrfile);
	bfn.lpstrFilter = filters.c_str();
	bfn.nFilterIndex = 1;
	bfn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
	if (SHBrowseForFolderA(&ofn) == true) {
		return ofn.lpstrFile;
	}
	else {
		
	}
	*/
	return std::string();
}


std::string FilePathManager::SaveFileDialog(HWND hwind, std::string path, std::string filters)
{
	OPENFILENAME ofn;
	CHAR lpstrfile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = lpstrfile;
	ofn.lpstrInitialDir = path.c_str();
	ofn.nMaxFile = sizeof(lpstrfile);
	ofn.lpstrFilter = filters.c_str();
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == true) {
		return ofn.lpstrFile;
	}
	else {
		return std::string();
	}
}
