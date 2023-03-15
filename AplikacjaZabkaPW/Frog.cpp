#include "Frog.h"

Frog::Frog(float movementSpeed, float spriteScaleX, float spriteScaleY, int hp, int hpMax) : Character(movementSpeed, spriteScaleX, spriteScaleY, hp, hpMax)
{
}

Frog::~Frog()
{
}

void Frog::initTexture()
{
    if (!this->texture.loadFromFile("Resources/res/frog.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
}

void Frog::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}