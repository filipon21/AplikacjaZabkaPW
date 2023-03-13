#include "Character.h"

Character::Character(float movementSpeed, float spriteScaleX, float spriteScaleY, int hp, int hpMax): movementSpeed(movementSpeed), spriteScaleX(spriteScaleX), 
spriteScaleY(spriteScaleY), hp(hp), hpMax(hpMax)
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

const int& Character::getHp() const
{
    return this->hp;
}

const int& Character::getHpMax() const
{
    return this->hpMax;
}

void Character::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x,y);
}

void Character::setHp(const int hp)
{
    this->hp = hp;
}

void Character::loseHp(const int value)
{
    this->hp -= value;
    if (this->hp < 0)
    {
        this->hp = 0;
    }
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
