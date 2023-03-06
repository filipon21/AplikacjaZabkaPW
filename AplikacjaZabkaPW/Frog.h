#pragma once

#include "Character.h"

class Frog : public Character
{
protected:
    void initTexture() override;

public:
    //Constructors/Destructors
    Frog(float movementSpeed, float spriteScaleX, float spriteScaleY);
    ~Frog();

    //Functions
    void move(const float dirX, const float dirY) override;

};