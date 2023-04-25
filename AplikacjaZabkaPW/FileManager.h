#pragma once
#include <string>
#include <vector>

#include "Character.h"
#include "Enemy.h"
class Level; // potrebne zeby klasa filemamnager wiedziala o klasie Level inaczej sie nie kompilluje program

class FileManager
{
public:
	FileManager() = default;
	~FileManager() = default;
	std::vector<std::string> loadFilesFromDirectory(const std::string& directoryPath);

	bool removeFile(const std::string& filePath);

	bool saveFile(std::ofstream dataFile, const unsigned& level, const std::vector<Enemy*>& enemies, const Character* character);

};

