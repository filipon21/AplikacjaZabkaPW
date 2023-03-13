#include "Enemy.h"

void Enemy::initVariables()
{
	 this->pointCount = rand() % 8 + 3; //min = 3, max = 10
	 this->type = 0;
	 this->speed = static_cast<float>(this->pointCount/3);
	 this->hpMax = static_cast<float>(this->pointCount);
	 this->hp = this->hpMax;
	 this->damage = this->pointCount;
	 this->points = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy()
{
}

Enemy::Enemy(float posX, float posY)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::update()
{
	this->shape.move(this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
