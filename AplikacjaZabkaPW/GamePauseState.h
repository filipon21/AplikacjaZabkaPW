#pragma once
#include "State.h"
#include "Game.h"
#include "Level.h"

class GamePauseState :
    public State
{
public:
    GamePauseState(GameDataRef data, Level* level);

    // Inherited via State
    void init() override;
	void handleInput() override;
    void update(float dt) override;
    void draw(float dt) override;

private:
    GameDataRef _data;
    Level _level;

    sf::Sprite _background;
    sf::Sprite _playButton;
    sf::Sprite _saveButton;
    sf::Sprite _newGameButton;
    sf::Sprite _menuButton;

    sf::Text _title;
};

