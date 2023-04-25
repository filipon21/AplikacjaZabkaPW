#pragma once

#include "Character.h"

class Frog : public Character
{
protected:
    void initTexture() override;

public:
    //Constructors/Destructors
    Frog(float movementSpeed, float spriteScaleX, float spriteScaleY, int hp, int hpMax);
    ~Frog();

    //Functions
    /**
     * Method for moving character.
     *
     * \param dirX - moves character in x directory
     * \param dirY -  moves character in y directory
     */
    void move(const float dirX, const float dirY) override;

};