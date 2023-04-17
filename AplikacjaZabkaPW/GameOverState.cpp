#include "GameOverState.h"
#include <iostream>

GameOverState::GameOverState(GameDataRef data) : _data(data)
{

}

void GameOverState::init()
{
	this->_data->assets.loadTexture("Game over Background", GAME_OVER_BACKGROUND_FILEPATH);
	_background.setTexture(this->_data->assets.getTexture("Game over Background"));

	_gameOverText.setFont(this->_data->assets.getFont("Pixel font"));

	_gameOverText.setFillColor(sf::Color::Red);
	_gameOverText.setScale(sf::Vector2f(2.f, 2.f));
	_gameOverText.setOutlineColor(sf::Color::Black);
	_gameOverText.setOutlineThickness(2);
	_gameOverText.setCharacterSize(72);
	_gameOverText.setString("Przegrales :(");

	_gameOverText.setPosition((SCREEN_WIDTH / 2) - (_gameOverText.getGlobalBounds().width / 2), _gameOverText.getGlobalBounds().height / 2);

}

void GameOverState::handleInput()
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
			if (ev.key.code == sf::Keyboard::LAlt)
			{

				this->_data->machine.removeState();

			}
			break;
		default:
			break;
		}
	
	/*	if (this->_data->input.isObjectClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go To Game Screen" << std::endl;
			this->_data->machine.addState(StateRef(new GameState(_data)), true);
		}*/
	}
}

void GameOverState::update(float dt)
{

}

void GameOverState::draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_gameOverText);


	this->_data->window.display();
}
