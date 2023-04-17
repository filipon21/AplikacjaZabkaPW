#include "GamePauseState.h"

#include <iostream>

#include "Definitions.h"
#include "GameSaveState.h"
#include "GameState.h"
#include "MainMenuState.h"

GamePauseState::GamePauseState(GameDataRef data, Level* level, std::vector<Enemy*> enemies, Character* character, unsigned currentLevel) :
_data(data),_level(*level), _enemies(enemies), _currentLevel(currentLevel), _character(character)
{
}

void GamePauseState::init()
{
	this->_data->assets.loadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
	this->_data->assets.loadTexture("Return To Game", RETURN_TO_GAME_BUTTON_FILEPATH);
	this->_data->assets.loadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
	this->_data->assets.loadTexture("Return To Menu", RETURN_TO_MENU_BUTTON_FILEPATH);
	this->_data->assets.loadTexture("New Game", NEW_GAME_BUTTON_FILEPATH);
	this->_data->assets.loadTexture("Save Button", SAVE_BUTTON_FILEPATH);

	_background.setTexture(this->_data->assets.getTexture("Main Menu Background"));
	_title.setFont(this->_data->assets.getFont("Pixel font"));
	_playButton.setTexture(this->_data->assets.getTexture("Return To Game"));
	_menuButton.setTexture(this->_data->assets.getTexture("Return To Menu"));
	_newGameButton.setTexture(this->_data->assets.getTexture("New Game"));
	_saveButton.setTexture(this->_data->assets.getTexture("Save Button"));

	_title.setFillColor(sf::Color::White);
	_title.setScale(sf::Vector2f(2.f, 2.f));
	_title.setOutlineColor(sf::Color::Black);
	_title.setOutlineThickness(2);
	_title.setCharacterSize(72);
	_title.setString("Zabka uliczna");

	_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
	_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
	_newGameButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
		(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + _playButton.getGlobalBounds().height + 50.f);
	_saveButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
		(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + _playButton.getGlobalBounds().height 
		+ _newGameButton.getGlobalBounds().height + 100.f);
	_menuButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
		(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + _playButton.getGlobalBounds().height
		+ _newGameButton.getGlobalBounds().height + _saveButton.getGlobalBounds().height + 150.f);
}

void GamePauseState::handleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isObjectClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go To Game Screen" << std::endl;
			this->_data->machine.removeState();
		}

		if (this->_data->input.isObjectClicked(this->_newGameButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go To Game Screen" << std::endl;
			this->_data->machine.addState(StateRef(new GameState(_data)), true);
		}

		if (this->_data->input.isObjectClicked(this->_saveButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Go To save screem" << std::endl;
			this->_data->machine.addState(StateRef(new GameSaveState(_data, _level, _enemies, _character, _currentLevel)), false);
		}

		if (this->_data->input.isObjectClicked(this->_menuButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Return to menu" << std::endl;
			this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
		}
	}
}

void GamePauseState::update(float dt)
{
	sf::Cursor cursor;

	if (this->_data->input.isMouseCursorOnObject(this->_playButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_playButton.setColor(sf::Color::Blue);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_newGameButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_newGameButton.setColor(sf::Color::Green);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_menuButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_menuButton.setColor(sf::Color::Red);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_saveButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_saveButton.setColor(sf::Color::Yellow);
		_data->window.setMouseCursor(cursor);
	}
	else {
		cursor.loadFromSystem(sf::Cursor::Arrow);
		this->_playButton.setColor(sf::Color::White);
		this->_menuButton.setColor(sf::Color::White);
		this->_newGameButton.setColor(sf::Color::White);
		this->_saveButton.setColor(sf::Color::White);
		_data->window.setMouseCursor(cursor);
	}
}

void GamePauseState::draw(float dt)
{
	this->_data->window.clear(sf::Color::Red);

	this->_data->window.draw(this->_background);
	this->_data->window.draw(this->_title);
	this->_data->window.draw(this->_playButton);
	this->_data->window.draw(this->_newGameButton);
	this->_data->window.draw(this->_saveButton);
	this->_data->window.draw(this->_menuButton);

	this->_data->window.display();
}
