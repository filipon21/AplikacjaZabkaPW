#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Game.h"
#include "Level.h"
#include "State.h"
class GameSaveState :
    public State
{
	GameDataRef _data;

	Level* _level;

	unsigned _currentLevel;

	Character* _character;

	std::vector<Enemy*> _enemies;

	sf::Sprite _overwriteButton;

	sf::Sprite _deleteButton;

	sf::Sprite _returnButton;

	sf::Sprite _saveButton;

	std::vector<sf::Text> _savesList;

	sf::Text* _currentSaveClicked = nullptr;

	const int _maxSpritesPerRow = 3;

	const float _textSpacing = 100.f;

	void loadFiles();

	void saveFile();

public:
	GameSaveState(GameDataRef data, Level* level, std::vector<Enemy*> enemies, Character* character, unsigned currentLevel);
	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;
};

