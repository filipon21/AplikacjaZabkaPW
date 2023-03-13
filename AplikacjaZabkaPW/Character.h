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

	int hp;
	int hpMax;

	float movementSpeed;

	float spriteScaleX;
	float spriteScaleY;

	//const std::string& filePath;

	//protected functions
	virtual void initTexture() = 0;
	void initSprite();


public:
	//Constructors/Destructors
	Character(float movementSpeed, float spriteScaleX, float spriteScaleY, int hp, int hpMax);
	virtual ~Character();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

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

