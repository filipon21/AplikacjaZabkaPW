#include "GameOverState.h"
#include <iostream>

#include "GameState.h"
#include "MainMenuState.h"

GameOverState::GameOverState(GameDataRef data, bool ifLost) : _data(data), _ifLost(ifLost)
{

}

void GameOverState::init()
{
	_background.setTexture(this->_data->assets.getTexture("Game over Background"));
	this->_returnButton.setTexture(this->_data->assets.getTexture("Return To Menu"));
	this->_newGameButton.setTexture(this->_data->assets.getTexture("Play Button"));

	this->_returnButton.setScale(0.5f, 0.5f);


	_gameOverText.setFont(this->_data->assets.getFont("Pixel font"));

	_gameOverText.setScale(sf::Vector2f(2.f, 2.f));
	_gameOverText.setOutlineColor(sf::Color::Black);
	_gameOverText.setOutlineThickness(2);
	_gameOverText.setCharacterSize(72);

	if (_ifLost)
	{
		_gameOverText.setFillColor(sf::Color::Red);
		_gameOverText.setString("Przegrales :(");

	}else
	{
		_gameOverText.setFillColor(sf::Color::Green);
		_gameOverText.setString("Brawo! Wygrales! :)");
	}

	_gameOverText.setPosition((SCREEN_WIDTH / 2) - (_gameOverText.getGlobalBounds().width / 2), _gameOverText.getGlobalBounds().height / 2);

	_newGameButton.setPosition((SCREEN_WIDTH / 2) - (_newGameButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_newGameButton.getGlobalBounds().height / 2));
	_returnButton.setPosition(20.f, SCREEN_HEIGHT - _returnButton.getGlobalBounds().height - 20.f);
}

void GameOverState::handleInput()
{
	sf::Event event;

	//Event polling
	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isObjectClicked(this->_newGameButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go To Game Screen" << std::endl;
			this->_data->machine.addState(StateRef(new GameState(_data)), true);
		}

		if (this->_data->input.isObjectClicked(this->_returnButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Return to menu" << std::endl;
			this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
		}
	}
}

void GameOverState::update(float dt)
{
	sf::Cursor cursor;

	if (this->_data->input.isMouseCursorOnObject(this->_newGameButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_newGameButton.setColor(sf::Color::Blue);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_returnButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_returnButton.setColor(sf::Color::Red);
		_data->window.setMouseCursor(cursor);
	}
	else {
		cursor.loadFromSystem(sf::Cursor::Arrow);
		this->_returnButton.setColor(sf::Color::White);
		this->_newGameButton.setColor(sf::Color::White);
		_data->window.setMouseCursor(cursor);
	}
}

void GameOverState::draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_returnButton);
	this->_data->window.draw(this->_newGameButton);
	this->_data->window.draw(this->_gameOverText);

	this->_data->window.display();
}
