#include "Enemy.h"

void Enemy::initShape()
{
	this->shape.setRadius(rand()%20+20);
	this->shape.setPointCount(rand()%20+3);
	this->shape.setFillColor(sf::Color(rand()%255+1, rand()%255+1, rand() % 255 + 1, 255));
}

void Enemy::initVariables()
{
	 this->type = 0;
	 this->hp = 10;
	 this->hpMax = 0;
	 this->damage = 1;
	 this->points = 5;
}



Enemy::Enemy()
{
}

Enemy::Enemy(float posX, float posY)
{
	this->initShape();
	this->initVariables();

	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Enemy::update()
{
	this->shape.move(10.f, 0.f);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
