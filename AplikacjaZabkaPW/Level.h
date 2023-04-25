#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "Game.h"

class Level
{
	const float _timeLimit; // czas, który gracz ma na przejœcie poziomu (60 sekund)
	float _timeRemaining; // pozosta³y czas do koñca poziomu
	float _spawnTime; // pozosta³y czas do koñca poziomu

	unsigned _currentLevel;
	//Background texture
	sf::Sprite _worldBackground;
	sf::Texture _worldTexture;

	//Street texture
	sf::Sprite _road;
	sf::Texture _roadTexture;

public:
	Level(float timeLimit, float spawnTime, unsigned currentLevel);
	Level() = delete;
	~Level();

	/**
	 * Method for init textures for level.
	 */
	void init(std::string backgroundName, std::string roadName);

	/**
	 * Method for rendering current level textures in specific window (target).
	 */
	void render(sf::RenderTarget& target) const;

	void setTimeRemaining(float time);
	void setRoadTexture(sf::Texture& texture);
	void setWorldTexture(sf::Texture& texture);

	sf::Sprite getRoad();

	// Metody zwracaj¹ce dane dla danego poziomu
	/*int getEnemyCount(int level);
	float getEnemySpeed(int level);*/

	float getSpawnTime() const;
	float getTimeLimit() const;
	float getCurrentLevel() const;
};

std::ostream& operator<<(std::ostream& os, const Level& level);