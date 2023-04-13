#pragma once //#pragma once pozwala na includowanie pliku do woli :)

#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Character.h"
#include "Frog.h"
#include "Enemy.h"
#include "Game.h"
#include "Level.h"

struct GameStateData
{
	Character* character;
	Level level;
};

/*
* Class that acts as the game engine.
* Wrapper class.
*/
class GameState : public State
{
public:
	GameState(GameDataRef data);

	virtual ~GameState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
	void resume();

private:
	GameDataRef _data;

	//GUI
	sf::Font font;
	sf::Text levelText;

	sf::Text timeText;

	//Systems
	Level* level;
	unsigned currentLevel;
	sf::Clock clock; // utworzenie obiektu klasy Clock
	float timeRemaining;

	std::vector<Level *> levels;

	// Character
	Character* character;

	// Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	void initGUI();
	void initBackground();
	void initSystems();


	void initCharacter();
	void initEnemies();

	void updateInput();
	void updatePollEvents();

	//PlayerGUI
	sf::RectangleShape characterHpBar;
	sf::RectangleShape characterHpBarBack;

	//Accessors
	/**
	 * Method that checks if the game is still running (is window still open?)
	 *
	 */
	void run();

	/**
	 * Method used to updates all data of game in each frame
	 *
	 */
	void update();
	/**
	 * Method used to render the game objects (draw objects).
	 * - clears old frame
	 * - render objects
	 * - display frame in window
	 */
	void render();

	void updateEnemies();

	void updateCombat();

	void updateCollision();
	void changeLevel();


	void updateGUI();
	void renderGUI();
	void updateTime();

	void renderBackground();
};
