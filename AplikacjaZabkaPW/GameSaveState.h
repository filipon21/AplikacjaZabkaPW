#pragma once
#include "Level.h"
#include "State.h"
class GameSaveState :
    public State
{
	GameDataRef _data;

	Level _level;
public:
	GameSaveState(GameDataRef data, Level level);
	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;
};

