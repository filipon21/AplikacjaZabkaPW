#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Character
{
private:
	/**
	 * Method for updating character.
	 *
	 */
	void update();

protected:
	sf::Texture texture;
	sf::Sprite sprite;

	float movementSpeed;

	float spriteScaleX;
	float spriteScaleY;

	//const std::string& filePath;

	virtual void initTexture() = 0;
	void initSprite();

public:
	//Constructors/Destructors
	Character(float movementSpeed, float spriteScaleX, float spriteScaleY);
	~Character();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;

	//Functions

	virtual void move(const float dirX, const float dirY) = 0;


	/**
	 * Method for rendering sprite.
	 * 
	 * \param target:RenderTarget - sprite to render
	 */
	void render(sf::RenderTarget& target);

	/**
	 * MEthod for adding textures initalize textures and add them to character.
	 * 
	 */
	void makeChar();
};

