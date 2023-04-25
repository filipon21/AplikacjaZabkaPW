#pragma once
#include "State.h"
#include "Game.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>

class GameOverState :
    public State
{
public:
    GameOverState(GameDataRef data, bool ifLost);

    // Inherited via State
     void init() override;
     void handleInput() override;
     void update(float dt) override;
     void draw(float dt) override;

private:
    GameDataRef _data;

    sf::Text _gameOverText;
    sf::Sprite _background;

    sf::Sprite _returnButton;
    sf::Sprite _newGameButton;
    bool _ifLost;
};

