#pragma once

#include "InputManager.h"


	bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
		return sf::Mouse::isButtonPressed(button) &&
			object.getGlobalBounds().contains(mousePosFloat);
	}

	bool InputManager::isMouseCursorOnSprite(sf::Sprite object, sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);
		return object.getGlobalBounds().contains(mousePosFloat);
	}

	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
