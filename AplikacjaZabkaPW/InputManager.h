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
		 *  Method template which checks if object is clicked.
		 * 
		 * \param object:T - object which we want to check if is clicked
		 * \param button:Button - button of mouse which we want to check if is clicked
		 * \param window:RenderWindow& - window in which we want to check the action
		 * \return true or false:boolean
		 */
		template<typename T>
		bool isObjectClicked(T object, sf::Mouse::Button button, sf::RenderWindow& window)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
			return sf::Mouse::isButtonPressed(button) &&
				object.getGlobalBounds().contains(mousePosFloat);
		};

		/**
		 * Method template which checks if mouse coursor is on the object of Type T.
		 * 
		 * \param object:T - object on which we want to check if the cursor is
		 * \param window:RenderWindow& - window in which we want to check the action
		 * \return true or false:boolean
		 */
		template<typename T>
		bool isMouseCursorOnObject(T object, sf::RenderWindow& window) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
			return object.getGlobalBounds().contains(mousePosFloat);
		};

		/**
		 * Method which checks current cursor position.
		 * 
		 * \param window:RenderWindow& - window in which we want to check the action
		 * \return x and y value (integers) of the window:Vector2i
		 */
		sf::Vector2i getMousePosition(sf::RenderWindow& window);
	};
