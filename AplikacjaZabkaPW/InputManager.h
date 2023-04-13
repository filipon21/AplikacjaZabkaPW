#pragma once

#include "SFML\Graphics.hpp"

/**
 * Class which is handling inputs from user actions.
 *
 */
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		/**
		 * Method which checks if Sprite is clicked.
		 * 
		 * \param object:Sprite - object which we want to check if is clicked
		 * \param button:Button - button of mouse which we want to check if is clicked
		 * \param window:RenderWindow& - window in which we want to check the action
		 * \return true or false:boolean
		 */
		bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);

		/**
		 * Method which checks if mouse coursor is on the Sprite.
		 * 
		 * \param object:Sprite - object on which we want to check if the cursor is
		 * \param window:RenderWindow& - window in which we want to check the action
		 * \return true or false:boolean
		 */
		bool isMouseCursorOnSprite(sf::Sprite object, sf::RenderWindow& window);

		/**
		 * Method which checks current cursor position.
		 * 
		 * \param window:RenderWindow& - window in which we want to check the action
		 * \return x and y value (integers) of the window:Vector2i
		 */
		sf::Vector2i getMousePosition(sf::RenderWindow& window);
	};
