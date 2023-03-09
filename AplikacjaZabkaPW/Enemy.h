#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
	sf::CircleShape shape;

	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initShape();
	void initVariables();

public:
	Enemy();
	Enemy(float posX, float posY);
	virtual ~Enemy();

	//Accessor
	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

