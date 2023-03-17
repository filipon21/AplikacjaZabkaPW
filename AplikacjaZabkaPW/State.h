#pragma once

/**
 * Abstract class used to deliver methods for all the states in the game.
 */
class State
{
public:
	/**
	 * Method for initialize variables and load all required fonts
	 */
	virtual void init() = 0;

	/**
	 * Method for handle all user input (interactions)
	 */
	virtual void handleInput() = 0;

	/**
	 * Method for update all variables etc.
	 * 
	 * \param dt - time difference between frames which allows to create frame independent gameplay (same frame rate on all devices)
	 */
	virtual void update(float dt) = 0;

	/**
	 * Method for displaying all objects.
	 * 
	 * \param dt - time difference between frames which allows to create frame independent gameplay (same frame rate on all devices)
	 */
	virtual void draw(float dt) = 0;

	/**
	 * Method called when user pause the game.
	 * 
	 */
	virtual void pause() { }

	/**
	 * Method called when user want to resume the game after pause.
	 * 
	 */
	virtual void resume() { }
};
