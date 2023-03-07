#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Enemy
{
private:
	sf::CircleShape shape;

	int type;

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

	void update();
	void render(sf::RenderTarget* target);
};

