#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Character
{
private:
	/**
	 * Method for updating _character.
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
	/**
	 * Getter of current character's postion.
	 * 
	 * \return current position
	 */
	const sf::Vector2f& getPos() const;

	/**
	 * Getter of character's bounds vector.
	 * 
	 * \return vector of characters bounds
	 */
	const sf::FloatRect getBounds() const;

	/**
	 * Getter of hp.
	 * 
	 * \return hp
	 */
	const int& getHp() const;

	/**
	 * Getter of movement speed.
	 * 
	 * \return movementSpeed
	 */
	const float& getMovSpeed() const;

	/**
	 * Getter for hpMax.
	 * 
	 * \return hpMax
	 */
	const int& getHpMax() const;

	//Modifiers

	/**
	 * Setter for position.
	 * 
	 * \param x
	 * \param y
	 */
	void setPosition(const float x, const float y);

	/**
	 * Setter for hp.
	 * 
	 * \param hp
	 */
	void setHp(const int hp);
	/**
	 * Method for decreasing character's hp. It can not be lower than 0.
	 * 
	 * \param value - value how much we want to decrease current hp
	 */
	void loseHp(const int value);

	//Functions
	/**
	 * Method for moving character.
	 * 
	 * \param dirX - moves character in x directory
	 * \param dirY -  moves character in y directory
	 */
	virtual void move(const float dirX, const float dirY) = 0;


	/**
	 * Method for rendering sprite.
	 * 
	 * \param target:RenderTarget - sprite to render
	 */
	void render(sf::RenderTarget& target);

	/**
	 * MEthod for adding textures initalize textures and add them to _character.
	 * 
	 */
	void makeChar();
};

std::ostream& operator<<(std::ostream& os, const Character& character);
