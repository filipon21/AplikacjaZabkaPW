#include "FileManager.h"

#include <filesystem>
#include <fstream>

#include "Character.h"

std::vector<std::string> FileManager::loadFilesFromDirectory(const std::string& directoryPath)
{
    std::vector<std::string> fileNames;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        if (!entry.is_directory())
        {
            std::string fileName = entry.path().stem().string();
            fileNames.push_back(fileName);
        }
    }
    return fileNames;
}

bool FileManager::removeFile(const std::string& filePath)
{
    if (remove(filePath.c_str()) != 0) {
        perror("Nie udalo sie usunac pliku");
        return false;
    }
    puts("Plik usuniety pomyslnie");
    return true;
}

bool FileManager::saveFile(std::ofstream dataFile, const unsigned& level, const std::vector<Enemy*>& enemies, const Character *character)
{
	if (!dataFile.is_open()) {
		std::cerr << "Nie udalo siê otworzyc pliku" << std::endl;
		return false;
	}

	// zapisz wektor enemyVector oddzielaj¹c ka¿dy obiekt separatorem ";"
	for (const auto& enemy : enemies) {
		dataFile << *enemy << "\n"; // za³ó¿my, ¿e klasa Enemy obs³uguje operator <<
	}

	// oddziel separatorem obiekt Level
	dataFile << "|" << "\n";

	// zapisz obiekt level
	dataFile << level <<"\n";

	dataFile << *character;

	// zamknij plik
	dataFile.close();

	return true;
}
