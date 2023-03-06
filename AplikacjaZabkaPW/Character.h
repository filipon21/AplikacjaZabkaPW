#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Character
{
private:

private:
	sf::Texture texture;
	sf::Sprite sprite;

	float movementSpeed;

	//virtual void initTexture() = 0;
	void initTexture();
	void initSprite();

public:
	//Constructors/Destructors
	Character();
	~Character();

	//Functions

	void move(const float dirX, const float dirY);

	/**
	 * Method for updating character.
	 * 
	 */
	void update();

	/**
	 * Method for rendering sprite.
	 * 
	 * \param target:RenderTarget - sprite to render
	 */
	void render(sf::RenderTarget& target);
};

