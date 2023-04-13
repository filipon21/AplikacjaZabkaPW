#pragma once
#include "State.h"
class RegisterState :
    public State
{
public:
	void init() override;
	void handleInput() override;
	void update(float dt) override;
	void draw(float dt) override;
};

