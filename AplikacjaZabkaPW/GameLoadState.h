#pragma once
#include "Game.h"
#include "State.h"
class GameLoadState :
    public State
{
	GameDataRef _data;
	sf::Sprite _deleteButton;
	sf::Sprite _returnButton;
	sf::Sprite _loadButton;
	std::vector<sf::Text> _savesList;
	sf::Text* _currentSaveClicked = nullptr;

	const int _maxSpritesPerRow = 3;
	const float _textSpacing = 100.f;
public:
	GameLoadState(GameDataRef data);
	void init() override;
	void loadFiles();
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;
};

