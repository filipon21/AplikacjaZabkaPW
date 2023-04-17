#pragma once

#include <sstream>
#include "DEFINITIONS.h"
#include "GameState.h"
#include "GameOverState.h"
#include "Level.h"
#include <iostream>

#include "GamePauseState.h"


GameState::GameState(GameDataRef data) : _data(data)
{

}

GameState::~GameState() {
	delete this->_character;

	//delete _enemies for avoid memmory leak
	for (auto& i : this->_enemies)
	{
		delete i;
	}
}

void GameState::init()
{
	this->initCharacter();
	this->initEnemies();
	this->initBackground();
	this->initGUI();
	this->initSystems();
	_ifTimeUpdate = true;
}

void GameState::handleInput()
{
	sf::Event ev;

	//Event polling
	while (this->_data->window.pollEvent(ev)) { // jeœli okno z³apie jakikolwiek event, zapisze je w zmiennej ev 
		switch (ev.type)
		{
		case sf::Event::Closed: // jeœli nacisniêto przzycisk close - wyslano Event do zmiennej ev i nale¿y zamknac okno
			this->_data->window.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::LAlt + ev.key.code == sf::Keyboard::F4)
			{
				this->_data->window.close();
			}
			if (ev.key.code == sf::Keyboard::Escape)
			{
				_ifTimeUpdate = false;
				this->_pauseTime = this->_clock.getElapsedTime();
				this->_data->machine.addState(StateRef(new GamePauseState(_data, _level, _enemies, _character, _currentLevel)), false);
			}
			break;
		default:
			break;
		}
	}
}

void GameState::update(float dt)
{
	this->updateInput();

	this->updateEnemies();
	this->updateCollision();

	if (this->_ifTimeUpdate)
	{
		this->updateTime();
	}

	this->updateGUI();
}

void GameState::draw(float dt)
{
	//:: ScopeResolution operator s³u¿y tutaj do wczytania static variable; moze takze sluzyc do wczytywania zmiennej globalnej jesli lokalna ma taka sama nazwe
	this->_data->window.clear(sf::Color::Red);

	//Draw background
	this->renderBackground();

	//Draw charcter and _enemies
	this->_character->render(this->_data->window);

	for (auto* enemy : this->_enemies)
	{
		enemy->render(this->_data->window);
	}

	//Draw GUI
	this->renderGUI();

	//Game over screen
	if (this->_character->getHp() <= 0 || this->_timeRemaining <= 0)
	{
		std::cout << "Go To Game Over screen" << std::endl;
		this->_data->machine.addState(StateRef(new GameOverState(_data)), false);
	}

	//Display all objects
	this->_data->window.display(); // -> bo jest to wskaŸnik i chcemy siê dostaæ do konkretnej kalsy pochodnej (polimorfizm); dynamicznie
}

void GameState::resume()
{
	this->_ifTimeUpdate = true;
	this->_clock.restart();
	this->_clockElapsedTime += _pauseTime;
}

void GameState::initGUI()
{
	//Load fonts
	if (!this->_font.loadFromFile("Resources/fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load _font" << "\n";
	}

	//Init _currentLevel text
	this->_levelText.setFont(this->_font);
	this->_levelText.setCharacterSize(30);
	this->_levelText.setFillColor(sf::Color::White);

	//Init time text
	this->_timeText.setFont(this->_font);
	this->_timeText.setCharacterSize(30);
	this->_timeText.setFillColor(sf::Color::White);

	//init player GUI
	this->characterHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->characterHpBar.setFillColor(sf::Color::Red);
	this->characterHpBar.setPosition(sf::Vector2f(20.f, 50.f));

	this->characterHpBarBack = this->characterHpBar;
	this->characterHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void GameState::initBackground()
{
	this->_data->assets.loadTexture("Game background", GAME_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("Game background 2", GAME_OVER_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("Game background 3", GAME_GRASS_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("Game background 4", GAME_DIRT_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("Game background 5", GAME_DIRT2_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("road", ROAD_FILEPATH);

	this->_levels.push_back(new Level(25.f, 2.5f, _data));
	this->_levels.push_back(new Level(20.f, 2.5f, _data));
	this->_levels.push_back(new Level(15.f, 3.f, _data));
	this->_levels.push_back(new Level(10.f, 3.f, _data));
	this->_levels.push_back(new Level(10.f, 3.5f, _data));

	std::cout <<_levels.size() << std::endl;
	//this->_levels.push_back(*new Level(50.f, _data));
	this->_level = new Level(31.f, 0.5f, _data);
	this->_level->init(1,this->_level->getBackgroundFilePath(0), "road");
}

void GameState::initSystems()
{

	this->_currentLevel = 1;

	this->_timeRemaining = this->_level->getTimeLimit();

}

void GameState::initCharacter()
{
	int hp = 20;
	int movspeed = 3.f;
	float scaleX = 0.5f;
	float scaleY = 0.5f;
	this->_character = new Frog(movspeed, scaleX, scaleY, hp, hp);
	this->_character->makeChar();
	this->_character->setPosition(this->_data->window.getSize().x / 2 - this->_character->getBounds().width, this->_data->window.getSize().y);

}

void GameState::initEnemies()
{
	this->_spawnTimerMax = 50.f;
	this->_spawnTimer = this->_spawnTimerMax;
}

void GameState::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->_character->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->_character->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->_character->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->_character->move(0.f, 1.f);
	}
}

void GameState::updateEnemies()
{
	//Spawning
	this->_spawnTimer += this->_level->getSpawnTime(); // zmiana dla leveli
	if (this->_spawnTimer >= this->_spawnTimerMax)
	{
		this->_enemies.push_back(new Enemy(0, rand() % static_cast<int>(this->_level->getRoad().getGlobalBounds().height - this->_level->getRoad().getGlobalBounds().top)));
		this->_spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->_enemies)
	{
		enemy->update();

		//delete enemie if it reaches right border of window or after collision with player
		if (enemy->getBounds().left + enemy->getBounds().width > this->_data->window.getSize().x)
		{
			//delete enemy
			delete this->_enemies.at(counter);
			this->_enemies.erase(this->_enemies.begin() + counter);
			std::cout << this->_enemies.size() << "\n";
			--counter;

		}

		//Enemy player collision
		else if (enemy->getBounds().intersects(this->_character->getBounds())) {

			this->_character->loseHp(this->_enemies.at(counter)->getDamage());

			//delete enemy
			delete this->_enemies.at(counter);
			this->_enemies.erase(this->_enemies.begin() + counter);
			std::cout << this->_enemies.size() << "\n";
			--counter;
		}
		++counter;
	}

	//for (int i = 0; i < this->_enemies.size(); ++i)
	//{

	//	this->_enemies[i]->update();

	//	//remove enemy at the bottom of the screen
	//	if (this->_enemies[i]->getBounds().left + this->_enemies[i]->getBounds().width > this->window.getSize().x)
	//	{
	//		this->_enemies.erase(this->_enemies.begin() + i);
	//		std::cout << this->_enemies.size() << "\n";
	//	}
	//}
}

void GameState::updateCollision()
{
	//left world collision
	if (this->_character->getBounds().left < 0.f)
	{
		this->_character->setPosition(0.f, this->_character->getBounds().top);
	}

	//right world collision
	else if (this->_character->getBounds().left + this->_character->getBounds().width >= this->_data->window.getSize().x)
	{
		this->_character->setPosition(this->_data->window.getSize().x - this->_character->getBounds().width, this->_character->getBounds().top);
	}

	//top world collision
	if (this->_character->getBounds().top + this->_character->getBounds().height < 0.f)
	{
		/*this->_character->setPosition(this->_character->getBounds().left, 0.f);*/

		this->_character->setPosition(this->_data->window.getSize().x / 2, this->_data->window.getSize().y);
		this->_currentLevel += 1;

		if (_currentLevel - 1 >= _levels.size()) {
			std::cout << "Indeks " << _currentLevel << " jest poza zakresem wektora.\n";
		}

		// Zmiany dla nowego levela
		else {
			this->changeLevel();

			if (this->_character->getHp() != this->_character->getHpMax())
			{
				this->_character->setHp(std::min(this->_character->getHp() + 10, this->_character->getHpMax()));
			}

			std::cout << this->_level->getBackgroundFilePath(_currentLevel - 1) <<std::endl;
		}
	}

	//bottom world collision
	else if (this->_character->getBounds().top + this->_character->getBounds().height >= this->_data->window.getSize().y)
	{
		this->_character->setPosition(this->_character->getBounds().left, this->_data->window.getSize().y - this->_character->getBounds().height);
	}
}

void GameState::changeLevel()
{
	if (_currentLevel - 1 >= 0 && _currentLevel - 1 < _levels.size()) {
		this->_level = _levels[_currentLevel - 1];
		std::cout << "time w _level ";
		std::cout << _levels[_currentLevel - 1]->getTimeLimit();
		this->_level->init(1,this->_level->getBackgroundFilePath(_currentLevel - 1), "road");
	}
	else {
		this->_level = _levels[0];
		this->_level->init(1,this->_level->getBackgroundFilePath(0), "road");
	}

	// Reset zegara dla danego levela
	this->_timeRemaining = this->_level->getTimeLimit();
}

void GameState::updateGUI()
{
	std::stringstream ss;
	ss << "Level: " << this->_currentLevel;
	this->_levelText.setString(ss.str());

	ss << "     Pozostaly czas: " << static_cast<int>(this->_timeRemaining);
	this->_timeText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->_character->getHp()) / this->_character->getHpMax();
	this->characterHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->characterHpBar.getSize().y));
}

void GameState::renderGUI()
{
	this->_data->window.draw(this->_levelText);
	this->_data->window.draw(this->_timeText);
	this->_data->window.draw(this->characterHpBarBack);
	this->_data->window.draw(this->characterHpBar);
}

void GameState::updateTime()
{
	float dt = this->_clock.restart().asSeconds();
	this->_timeRemaining -= dt;
	std::cout << _timeRemaining << std::endl;
}

void GameState::renderBackground()
{
	this->_level->render(this->_data->window);
}