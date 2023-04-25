#include "Enemy.h"
#include <sstream>
#include <utility>

#include "EnemyTypeEnum.h"

void Enemy::initEnemy(const sf::Texture& texture)
{
	this->shape.setTexture(texture);
	this->shape.setScale(0.5f, 0.5f);
}

Enemy::Enemy()
= default;

//Enemy::Enemy(float posX, float posY)
//{
//	this->initVariables();
//	this->initEnemy();
//
//	this->shape.setPosition(posX, posY);
//}

Enemy::Enemy(const int hp, const int hpMax, const float speed, const int damage, const int points, const int pointCount,
             const sf::Texture& texture, const int textureName, const float posX, const float posY) :
    speed(speed), hp(hp), hpMax(hpMax), damage(damage), points(points), pointCount(pointCount), _textureName(
	    std::move(textureName))
{
	initEnemy(texture);

	this->shape.setPosition(posX, posY);
}

Enemy::~Enemy()
= default;

sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

const EnemyTypeEnum& Enemy::getType() const
{
	return type;
}

const float& Enemy::getSpeed() const
{
	return speed;
}

const int& Enemy::getHp() const
{
	return hp;
}

const int& Enemy::getHpMax() const
{
	return hpMax;
}

const int& Enemy::getPoints() const
{
	return points;
}

const int& Enemy::getPointCount() const
{
	return pointCount;
}

float Enemy::getPositionX() const
{
	return this->shape.getPosition().x;
}

float Enemy::getPositionY() const
{
	return this->shape.getPosition().y;
}
int Enemy::getTextureName() const
{
	return _textureName;
}

void Enemy::update()
{
	this->shape.move(this->speed, 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
{
	os << enemy.getHpMax() << ';' << enemy.getHp() << ';' << enemy.getDamage() << ';' << enemy.getPointCount()
		<< ';' << enemy.getPoints() << ';' << enemy.getSpeed() << ';' << enemy.getPositionX()
		<< ';' << enemy.getPositionY() << ';' << enemy.getTextureName();
	return os;
}
 