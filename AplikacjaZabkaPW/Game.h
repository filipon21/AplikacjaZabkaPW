#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"


struct GameData
{
	StateMachine machine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
};

// reference to all game data
typedef std::shared_ptr<GameData> GameDataRef;

/**
 * Class which handles all states, assets, inputs and the window (game loop).
 */
class Game
{
public:
	Game(int width, int height, std::string title);

private:
	// How many times we want to update the game per seconds. 
	// Updates run at 60 per second. Here you can change how fast game render elements (frames per seconds)
	const float dt = 1.0f / 60.0f;

	// Required to handling frame rate
	sf::Clock _clock;

	// Used in different states to acces all pieces from data
	GameDataRef _data = std::make_shared<GameData>();

	/**
	 * Method used to start the game.
	 * 
	 */
	void Run();
};
