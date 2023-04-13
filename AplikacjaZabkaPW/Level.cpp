#include "Level.h"

Level::Level(float timeLimit, float spawnTime,GameDataRef data) : timeLimit(timeLimit), spawnTime(spawnTime), _data(data)
{
}

void Level::init(int level, sf::RenderTarget& target, std::string backgroundName, std::string roadName)
{

	this->worldBackground.setTexture(this->_data->assets.getTexture(std::move(backgroundName)));


	this->road.setTexture(this->_data->assets.getTexture(std::move(roadName)));
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


float Level::getSpawnTime()
{
	return this->spawnTime;
}
std::string Level::getBackgroundFilePath(int level)
{
	return this->levelsData[level].backgroundFilePath;
}