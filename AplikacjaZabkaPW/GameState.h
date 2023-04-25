#pragma once //#pragma once pozwala na includowanie pliku do woli :)

#include <vector>
#include "Character.h"
#include "Frog.h"
#include "Enemy.h"
#include "Game.h"
#include "Level.h"

/*
* Class that acts as the game engine.
* Wrapper class.
*/
class GameState : public State
{
public:
	GameState(GameDataRef data);

	GameState(GameDataRef data, unsigned level, std::vector<Enemy*> enemies, bool ifLoaded);

	~GameState() override;

	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;
	void resume() override;

private:
	GameDataRef _data;

	//GUI
	sf::Font _font;
	sf::Text _levelText;

	sf::Text _timeText;

	//Systems
	unsigned _currentLevel;
	sf::Clock _clock; // utworzenie obiektu klasy Clock
	float _timeRemaining;
	bool _ifLoaded = false;

	std::vector<Level*> _levels;

	// Character
	Character* _character;

	// Enemies
	float _spawnTimer;
	float _spawnTimerMax;
	std::vector<Enemy*> _enemies;
	bool _ifTimeUpdate = false;
	sf::Time _clockElapsedTime;
	sf::Time _pauseTime;

	//PlayerGUI
	sf::RectangleShape characterHpBar;
	sf::RectangleShape characterHpBarBack;

	void initGUI();
	void initBackground();
	void initSystems();
	void initCharacter();
	void initEnemies();

	void updateInput();
	void updateEnemies();
	void updateCollision();
	void changeLevel();
	void updateGUI();
	void renderGUI();
	void updateTime();
	void renderBackground();

	// Wektor przechowuj¹cy dane dla ró¿nych poziomów
	std::vector<std::string> levelsData = {
		{ "Game background"}, // poziom 1 - 5 przeciwników, prêdkoœæ 100, t³o "level1_background.png"
		{ "Game background 2" }, // poziom 1 - 5 przeciwników, prêdkoœæ 100, t³o "level1_background.png"
		{  "Game background 3"}, // poziom 2 - 10 przeciwników, prêdkoœæ 150, t³o "level2_background.png"
		{ "Game background 4"},
		{ "Game background 5"}
	};

	struct EnemyData {
		const int hp;
		const int hpMax;
		const float speed;
		const int damage;
		const int points;
		const int pointCount;
		int texture;
	};

	// Wektor przechowuj¹cy dane dla ró¿nych poziomów
	std::vector<EnemyData> _enemyData = {
	   { 5, 5, 5.0f / 3.0f, 3, 3, 3, 1},
	   { 8, 8, 8.0f / 3.0f, 5, 5, 5, 2 },
	   { 10, 10, 10.0f / 3.0f, 10, 10, 10, 3 },
	   { 15, 15, 15.0f / 3.0f, 15, 15, 15, 4 }
	};

};
