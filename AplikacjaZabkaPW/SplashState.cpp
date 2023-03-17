#pragma once

#include <sstream>
#include "SplashState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

#include <iostream>


	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::init()
	{
		this->_data->assets.loadTexture("splash_background", SPLASH_SCREEN);

		this->_background.setTexture(this->_data->assets.getTexture("splash_background"));
	}

	void SplashState::handleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switch To Main Menu
			this->_data->machine.addState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);

		this->_data->window.display();
	}
