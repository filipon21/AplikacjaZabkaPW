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
	delete this->character;

	//delete enemies for avoid memmory leak
	for (auto& i : this->enemies)
	{
		delete i;
	}
}

void GameState::init()
{
	//this->_data->window.setFramerateLimit(144); //TODO zmiana w mnenu
	this->initCharacter();
	this->initEnemies();
	this->initBackground();
	this->initGUI();
	this->initSystems();
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
				this->_data->machine.addState(StateRef(new GamePauseState(_data)), false);
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

	this->updateTime();

	this->updateGUI();
}

void GameState::draw(float dt)
{
	//:: ScopeResolution operator s³u¿y tutaj do wczytania static variable; moze takze sluzyc do wczytywania zmiennej globalnej jesli lokalna ma taka sama nazwe
	this->_data->window.clear(sf::Color::Red);

	//Draw background
	this->renderBackground();

	//Draw charcter and enemies
	this->character->render(this->_data->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->_data->window);
	}

	//Draw GUI
	this->renderGUI();

	//Game over screen
	if (this->character->getHp() <= 0 || this->timeRemaining <= 0)
	{
		std::cout << "Go To Game Over screen" << std::endl;
		this->_data->machine.addState(StateRef(new GameOverState(_data)), false);
	}

	//Display all objects
	this->_data->window.display(); // -> bo jest to wskaŸnik i chcemy siê dostaæ do konkretnej kalsy pochodnej (polimorfizm); dynamicznie
}

void GameState::resume()
{
	Character *lastChar = this->character;
	Level* lastLevel = this->level;
	unsigned lastLevelText = this->currentLevel;
	float lastTimeRemaining = this->timeRemaining;
	this->init();
	this->character = lastChar;
	this->currentLevel = lastLevelText;
	this->timeRemaining = lastTimeRemaining;
	this->changeLevel();

}

void GameState::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("Resources/fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	}

	//Init currentLevel text
	this->levelText.setFont(this->font);
	this->levelText.setCharacterSize(30);
	this->levelText.setFillColor(sf::Color::White);

	//Init time text
	this->timeText.setFont(this->font);
	this->timeText.setCharacterSize(30);
	this->timeText.setFillColor(sf::Color::White);

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

	this->levels.push_back(new Level(25.f, 2.5f, _data));
	this->levels.push_back(new Level(20.f, 2.5f, _data));
	this->levels.push_back(new Level(15.f, 3.f, _data));
	this->levels.push_back(new Level(10.f, 3.f, _data));
	this->levels.push_back(new Level(10.f, 3.5f, _data));

	std::cout <<levels.size() << std::endl;
	//this->levels.push_back(*new Level(50.f, _data));
	this->level = new Level(31.f, 0.5f, _data);
	this->level->init(1, this->_data->window, "Game background", "road");

}

void GameState::initSystems()
{

	this->currentLevel = 1;

	this->timeRemaining = this->level->getTimeLimit();

}

void GameState::initCharacter()
{
	int hp = 20;
	int movspeed = 3.f;
	float scaleX = 0.5f;
	float scaleY = 0.5f;
	this->character = new Frog(movspeed, scaleX, scaleY, hp, hp);
	this->character->makeChar();
	this->character->setPosition(this->_data->window.getSize().x / 2 - this->character->getBounds().width, this->_data->window.getSize().y);

}

void GameState::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void GameState::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->character->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->character->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->character->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->character->move(0.f, 1.f);
	}
}

void GameState::updateEnemies()
{
	//Spawning
	this->spawnTimer += this->level->getSpawnTime(); // zmiana dla leveli
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(0, rand() % static_cast<int>(this->level->getRoad().getGlobalBounds().height - this->level->getRoad().getGlobalBounds().top)));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		//delete enemie if it reaches right border of window or after collision with player
		if (enemy->getBounds().left + enemy->getBounds().width > this->_data->window.getSize().x)
		{
			//delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			std::cout << this->enemies.size() << "\n";
			--counter;

		}

		//Enemy player collision
		else if (enemy->getBounds().intersects(this->character->getBounds())) {

			this->character->loseHp(this->enemies.at(counter)->getDamage());

			//delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			std::cout << this->enemies.size() << "\n";
			--counter;
		}
		++counter;
	}

	//for (int i = 0; i < this->enemies.size(); ++i)
	//{

	//	this->enemies[i]->update();

	//	//remove enemy at the bottom of the screen
	//	if (this->enemies[i]->getBounds().left + this->enemies[i]->getBounds().width > this->window.getSize().x)
	//	{
	//		this->enemies.erase(this->enemies.begin() + i);
	//		std::cout << this->enemies.size() << "\n";
	//	}
	//}
}

void GameState::updateCollision()
{
	//left world collision
	if (this->character->getBounds().left < 0.f)
	{
		this->character->setPosition(0.f, this->character->getBounds().top);
	}

	//right world collision
	else if (this->character->getBounds().left + this->character->getBounds().width >= this->_data->window.getSize().x)
	{
		this->character->setPosition(this->_data->window.getSize().x - this->character->getBounds().width, this->character->getBounds().top);
	}

	//top world collision
	if (this->character->getBounds().top + this->character->getBounds().height < 0.f)
	{
		/*this->character->setPosition(this->character->getBounds().left, 0.f);*/

		this->character->setPosition(this->_data->window.getSize().x / 2, this->_data->window.getSize().y);
		this->currentLevel += 1;

		if (currentLevel - 1 >= levels.size()) {
			std::cout << "Indeks " << currentLevel << " jest poza zakresem wektora.\n";
		}

		// Zmiany dla nowego levela
		else {
			this->changeLevel();

			if (this->character->getHp() != this->character->getHpMax())
			{
				this->character->setHp(std::min(this->character->getHp() + 10, this->character->getHpMax()));
			}

			std::cout << this->level->getBackgroundFilePath(currentLevel - 2) <<std::endl;
		}
	}

	//bottom world collision
	else if (this->character->getBounds().top + this->character->getBounds().height >= this->_data->window.getSize().y)
	{
		this->character->setPosition(this->character->getBounds().left, this->_data->window.getSize().y - this->character->getBounds().height);
	}
}

void GameState::changeLevel()
{
	this->level = levels[currentLevel - 2];
	std::cout << "time w level ";
	std::cout << levels[currentLevel - 2]->getTimeLimit();

	this->level->init(1, this->_data->window,
		this->level->getBackgroundFilePath(currentLevel - 2), "road");
	// Reset zegara dla danego levela
	this->timeRemaining = this->level->getTimeLimit();
}

void GameState::updateGUI()
{
	std::stringstream ss;
	ss << "Level: " << this->currentLevel;
	this->levelText.setString(ss.str());

	ss << "     Pozostaly czas: " << static_cast<int>(this->timeRemaining);
	this->timeText.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->character->getHp()) / this->character->getHpMax();
	this->characterHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->characterHpBar.getSize().y));
}

void GameState::renderGUI()
{
	this->_data->window.draw(this->levelText);
	this->_data->window.draw(this->timeText);
	this->_data->window.draw(this->characterHpBarBack);
	this->_data->window.draw(this->characterHpBar);
}

void GameState::updateTime()
{
	float dt = this->clock.restart().asSeconds();
	this->timeRemaining -= dt;	
}

void GameState::renderBackground()
{
	this->level->render(this->_data->window);
}