#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

class Level
{
	GameDataRef _data;

	const float timeLimit; // czas, który gracz ma na przejœcie poziomu (60 sekund)
	float timeRemaining; // pozosta³y czas do koñca poziomu

	//Background texture
	sf::Sprite worldBackground;

	//Street texture
	sf::Sprite road;

	//zmiana spawnowania enemies i ich szybkosc?

public:
	Level(float timeLimit, GameDataRef data);

	void init(const char* backgroundFilePath, const char* roadFilePath, sf::RenderTarget& target);

	void render(sf::RenderTarget& target);

	void setTimeRemaining(float time);

	float getTimeLimit();

	sf::Sprite getRoad();

};

