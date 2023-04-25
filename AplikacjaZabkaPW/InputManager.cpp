#pragma once

#include "InputManager.h"

	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
