#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

enum class EnemyTypeEnum;

class Enemy
{
	sf::Sprite shape;

	EnemyTypeEnum type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
	int pointCount;
	int _textureName;

	void initEnemy(const sf::Texture& texture);

public:
	Enemy();
	//Enemy(float posX, float posY);
	Enemy(const int hp, const int hpMax, const float speed, const int damage, const int points, const int pointCount, 
		const sf::Texture& texture, const int textureName, const float posX, const float posY);
	virtual ~Enemy();

	//Accessor
	sf::FloatRect getBounds() const;
	const int& getDamage() const;
	const EnemyTypeEnum& getType() const;
	const float& getSpeed() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const int& getPoints() const;
	const int& getPointCount() const;
	float getPositionX() const;
	float getPositionY() const;
	int getTextureName() const;

	void update();
	void render(sf::RenderTarget& target);
};

std::ostream& operator<<(std::ostream& os, const Enemy& enemy);