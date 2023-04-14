#pragma once
#include "Game.h"
#include "State.h"
class GameLoadState :
    public State
{
	GameDataRef _data;

public:
	GameLoadState(GameDataRef data);
	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;
};

