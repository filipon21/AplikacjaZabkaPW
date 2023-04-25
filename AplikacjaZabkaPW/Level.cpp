#include "Level.h"

#include <iostream>
#include <utility>

Level::Level(float timeLimit, float spawnTime, unsigned currentLevel) :
_timeLimit(timeLimit), _spawnTime(spawnTime), _currentLevel(currentLevel)
{
}


Level::~Level()
{
}

void Level::init(std::string backgroundName, std::string roadName)
{
	if (!_worldTexture.loadFromFile(backgroundName))
	{
		std::cout << "ERROR::BACKGROUND_WORLD::INITTEXTURE::Could not load texture file." << "\n";
	}else
	{
		this->_worldBackground.setTexture(_worldTexture);
	}

	if (!_roadTexture.loadFromFile(roadName))
	{
		std::cout << "ERROR::BACKGROUND_WORLD::INITTEXTURE::Could not load texture file." << "\n";
	} else
	{
		this->_road.setTexture(_roadTexture);
	}

	this->_road.setPosition(0.f, (SCREEN_HEIGHT - this->_road.getGlobalBounds().height) / 2);
}

void Level::render(sf::RenderTarget& target) const
{
	target.draw(this->_worldBackground);
	target.draw(this->_road);
}

void Level::setTimeRemaining(float time)
{
	this->_timeRemaining = time;
}

void Level::setRoadTexture(sf::Texture& texture)
{
	this->_road.setTexture(texture);
	this->_road.setPosition(0.f, (SCREEN_HEIGHT - this->_road.getGlobalBounds().height) / 2);
}

void Level::setWorldTexture(sf::Texture& texture)
{
	this->_worldBackground.setTexture(texture);
}

float Level::getTimeLimit() const
{
	return this->_timeLimit;
}


sf::Sprite Level::getRoad()
{
	return this->_road;
}

float Level::getSpawnTime() const
{
	return this->_spawnTime;
}

float Level::getCurrentLevel() const
{
	return this->_currentLevel;
}

std::ostream& operator<<(std::ostream& os, const Level& level)
{
	os << level.getSpawnTime() << ';' << level.getTimeLimit() << ';' << level.getCurrentLevel();
	return os;
}
