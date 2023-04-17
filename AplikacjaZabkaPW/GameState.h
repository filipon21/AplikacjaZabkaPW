#pragma once //#pragma once pozwala na includowanie pliku do woli :)

#include <vector>
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
	sf::Font _font;
	sf::Text _levelText;

	sf::Text _timeText;

	//Systems
	Level* _level;
	unsigned _currentLevel;
	sf::Clock _clock; // utworzenie obiektu klasy Clock
	float _timeRemaining;

	std::vector<Level*> _levels;

	// Character
	Character* _character;

	// Enemies
	float _spawnTimer;
	float _spawnTimerMax;
	std::vector<Enemy*> _enemies;
	bool _ifTimeUpdate;
	sf::Time _clockElapsedTime;
	sf::Time _pauseTime;

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
