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

	/**
	 * Method which loads all files from specific directory.
	 * 
	 * \param directoryPath - path to files which we want to load
	 * \return 
	 */
	std::vector<std::string> loadFilesFromDirectory(const std::string& directoryPath);

	/**
	 * Method for removing file.
	 * 
	 * \param filePath - file path to file which we want to remove
	 * \return 
	 */
	bool removeFile(const std::string& filePath);

	/**
	 * Method for saving file.
	 * 
	 * \param dataFile - file to which we want save the data
	 * \param level - level data
	 * \param enemies - vector with enemies data
	 * \param character - character data
	 * \return 
	 */
	bool saveFile(std::ofstream dataFile, const unsigned& level, const std::vector<Enemy*>& enemies, const Character* character);

};

