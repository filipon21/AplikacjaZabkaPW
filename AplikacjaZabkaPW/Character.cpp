#include "Character.h"

Character::Character(float movementSpeed, float spriteScaleX, float spriteScaleY): movementSpeed(movementSpeed), spriteScaleX(spriteScaleX), spriteScaleY(spriteScaleY)
{
}

Character::~Character()
{
}

const sf::Vector2f& Character::getPos() const
{
    return this->sprite.getPosition();
}

const sf::FloatRect Character::getBounds() const
{
    return this->sprite.getGlobalBounds();
}

void Character::initSprite()
{
    // set the texture to the sprite
    this->sprite.setTexture(this->texture);

    //resize the sprite
    this->sprite.scale(this->spriteScaleX, this->spriteScaleY);
}

void Character::update()
{
}

void Character::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}

void Character::makeChar()
{
    this->initTexture();
    this->initSprite();
}
