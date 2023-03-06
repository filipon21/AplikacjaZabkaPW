#include "Character.h"

void Character::initSprite()
{
	//ustawia texture na sprite
	this->sprite.setTexture(this->texture); //ustawia texture na sprite

	//dopasowuje sprite
	this->sprite.scale(0.4f, 0.4f);
}

void Character::initTexture()
{

	// wczytanie textury
	if (!this->texture.loadFromFile("Textures/frog.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}

}

Character::Character()
{
	this->movementSpeed = 1.f;
	this->initTexture();
	this->initSprite();
}

Character::~Character()
{
}

void Character::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Character::update()
{
}

void Character::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
