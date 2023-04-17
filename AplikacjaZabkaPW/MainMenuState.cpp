#pragma once

#include <sstream>
#include "DEFINITIONS.h"
#include "MainMenuState.h"

#include <iostream>

#include "Game.h"
#include "GameLoadState.h"
#include "GameState.h"
#include "StateMachine.h"


MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::init()
	{
		this->_data->assets.loadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		//this->_data->assets.loadTexture("Game Title", GAME_TITLE_FILEPATH);
		this->_data->assets.loadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		this->_data->assets.loadTexture("Exit Button", EXIT_BUTTON_FILEPATH);
		this->_data->assets.loadTexture("Load Button", LOAD_GAME_BUTTON_FILEPATH);
		this->_data->assets.loadTexture("Select Char Button", SELECT_CHAR_BUTTON_FILEPATH);
		this->_data->assets.loadFont("Pixel font", PIXEL_FONT);

		_background.setTexture(this->_data->assets.getTexture("Main Menu Background"));
		_title.setFont(this->_data->assets.getFont("Pixel font"));
		_playButton.setTexture(this->_data->assets.getTexture("Play Button"));
		_charSelectorButton.setTexture(this->_data->assets.getTexture("Select Char Button"));
		_loadButton.setTexture(this->_data->assets.getTexture("Load Button"));
		_exitButton.setTexture(this->_data->assets.getTexture("Exit Button"));

		_title.setFillColor(sf::Color::White);
		_title.setScale(sf::Vector2f(2.f,2.f));
		_title.setOutlineColor(sf::Color::Black);
		_title.setOutlineThickness(2);
		_title.setCharacterSize(72);
		_title.setString("Zabka uliczna");

		_title.setPosition((SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width / 2), _title.getGlobalBounds().height / 2);
		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), (SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));
		_charSelectorButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + _playButton.getGlobalBounds().height + 50.f);
		_loadButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2), 
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + _playButton.getGlobalBounds().height+ _charSelectorButton.getGlobalBounds().height + 100.f);
		_exitButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2) + _playButton.getGlobalBounds().height + _charSelectorButton.getGlobalBounds().height+
			_loadButton.getGlobalBounds().height + 150.f);
		
	}

	void MainMenuState::handleInput()
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
				this->_data->machine.addState(StateRef(new GameState(_data)), true);
			}

			if (this->_data->input.isObjectClicked(this->_loadButton, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Load" << std::endl;
				this->_data->machine.addState(StateRef(new GameLoadState(_data)), true);
			}

			if (this->_data->input.isObjectClicked(this->_exitButton, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Exit" << std::endl;
				this->_data->window.close();
			}
		}
	}

	void MainMenuState::update(float dt)
	{
		sf::Cursor cursor;

		if (this->_data->input.isMouseCursorOnObject(this->_playButton, this->_data->window))
		{
			cursor.loadFromSystem(sf::Cursor::Hand);
			this->_playButton.setColor(sf::Color::Green);
			_data->window.setMouseCursor(cursor);
		}
		else if (this->_data->input.isMouseCursorOnObject(this->_exitButton, this->_data->window))
		{
			cursor.loadFromSystem(sf::Cursor::Hand);
			this->_exitButton.setColor(sf::Color::Red);
			_data->window.setMouseCursor(cursor);
		}
		else if (this->_data->input.isMouseCursorOnObject(this->_charSelectorButton, this->_data->window))
		{
			cursor.loadFromSystem(sf::Cursor::Hand);
			this->_charSelectorButton.setColor(sf::Color::Cyan);
			_data->window.setMouseCursor(cursor);
		}
		else if (this->_data->input.isMouseCursorOnObject(this->_loadButton, this->_data->window))
		{
			cursor.loadFromSystem(sf::Cursor::Hand);
			this->_loadButton.setColor(sf::Color::Magenta);
			_data->window.setMouseCursor(cursor);
		}
		else {
			cursor.loadFromSystem(sf::Cursor::Arrow);
			this->_playButton.setColor(sf::Color::White);
			this->_exitButton.setColor(sf::Color::White);
			this->_charSelectorButton.setColor(sf::Color::White);
			this->_loadButton.setColor(sf::Color::White);
			_data->window.setMouseCursor(cursor);
		}
	}

	void MainMenuState::draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_playButton);
		this->_data->window.draw(this->_charSelectorButton);
		this->_data->window.draw(this->_loadButton);
		this->_data->window.draw(this->_exitButton);

		this->_data->window.display();
	}
