#pragma once
#include "State.h"

class GamePauseState :
    public State
{
    // Inherited via State
    virtual void init() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void draw(float dt) override;
};

