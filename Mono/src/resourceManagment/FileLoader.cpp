#include "FileLoader.h"
#include <fstream>
#include <MonoStd/Timer.h>

void FileLoader::getContent(std::vector<std::string>& fileContent, const std::string& filePath) {
#ifdef Debug
	Timer::LifeTimeTimer timer([=](float time) {
		Log("file _"+ filePath + "_: " << time << "\n");
		});
#endif
	std::string line;
	std::ifstream file(filePath);
	if (file.is_open())
	{
		while (getline(file, line, '\n'))
		{
			fileContent.push_back(line);
		}
	}
	else
	{
		Log("Could not open the file");
		return;
	}

}

