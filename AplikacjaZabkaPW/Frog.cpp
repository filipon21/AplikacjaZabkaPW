#include "Frog.h"

Frog::Frog(float movementSpeed, float spriteScaleX, float spriteScaleY) : Character(movementSpeed, spriteScaleX, spriteScaleY)
{
}

Frog::~Frog()
{
}

void Frog::initTexture()
{
    if (!this->texture.loadFromFile("Textures/frog.png"))
        std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
}

void Frog::move(const float dirX, const float dirY)
{
    this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}