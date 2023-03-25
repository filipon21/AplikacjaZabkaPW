#include "Level.h"
#include "DEFINITIONS.h"

Level::Level(float timeLimit, GameDataRef data) : _data(data), timeLimit(timeLimit)
{
}

void Level::init(const char* backgroundFilePath, const char* roadFilePath, sf::RenderTarget& target)
{
	this->_data->assets.loadTexture("game_background", GAME_BACKGROUND_FILEPATH);

	this->worldBackground.setTexture(this->_data->assets.getTexture("game_background"));

	this->_data->assets.loadTexture("road", ROAD_FILEPATH);

	this->road.setTexture(this->_data->assets.getTexture("road"));
	this->road.setPosition(0.f, (this->_data->window.getSize().y - this->road.getGlobalBounds().height) / 2);
}

void Level::render(sf::RenderTarget& target)
{
	target.draw(this->worldBackground);
	target.draw(this->road);
}

void Level::setTimeRemaining(float time)
{
	this->timeRemaining = time;
}

float Level::getTimeLimit()
{
	return this->timeLimit;
}


sf::Sprite Level::getRoad()
{
	return this->road;
}
