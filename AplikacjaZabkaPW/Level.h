#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Definitions.h"

class Level
{
	GameDataRef _data;

	const float timeLimit; // czas, który gracz ma na przejœcie poziomu (60 sekund)
	float timeRemaining; // pozosta³y czas do koñca poziomu
	float spawnTime; // pozosta³y czas do koñca poziomu

	//Background texture
	sf::Sprite worldBackground;

	//Street texture
	sf::Sprite road;


		// Dane dla ró¿nych poziomów
	struct LevelData {
		float timeLimit;
		float spawnTime;
		std::string backgroundFilePath;
	};

	// Wektor przechowuj¹cy dane dla ró¿nych poziomów
	std::vector<LevelData> levelsData = {
		{ 5, 100.f, "Game background 2" }, // poziom 1 - 5 przeciwników, prêdkoœæ 100, t³o "level1_background.png"
		{ 10, 150.f, "Game background" }, // poziom 2 - 10 przeciwników, prêdkoœæ 150, t³o "level2_background.png"
		{ 15, 200.f, "Game background"} // poziom 3 - 15 przeciwników, prêdkoœæ 200, t³o "level3_background.png"
	};

public:
	Level(float timeLimit, float spawnTime,GameDataRef data);

	void init(int level, sf::RenderTarget& target, std::string backgroundName, std::string roadName);

	void render(sf::RenderTarget& target);

	void setTimeRemaining(float time);

	float getTimeLimit();


	sf::Sprite getRoad();

	// Metody zwracaj¹ce dane dla danego poziomu
	int getEnemyCount(int level);
	float getEnemySpeed(int level);
	float getSpawnTime();
	std::string getBackgroundFilePath(int level);
};

