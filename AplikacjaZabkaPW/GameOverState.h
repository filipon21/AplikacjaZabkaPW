#pragma once
#include "State.h"
#include "Game.h"
#include "Definitions.h"
#include <SFML/Graphics.hpp>

class GameOverState :
    public State
{
public:
    GameOverState(GameDataRef data);

    // Inherited via State
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void draw(float dt) override;

private:
    GameDataRef _data;

    sf::Text _gameOverText;
    sf::Sprite _background;

};

