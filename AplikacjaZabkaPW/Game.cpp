#include "Game.h"
#include "SplashState.h"


Game::Game(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	_data->machine.addState(StateRef(new SplashState(this->_data)));

	this->Run();
}

void Game::Run()
{
	float newTime, frameTime, interpolation;

	// time in seconds which start from 0 s and gives us how long the game is running
	float currentTime = this->_clock.getElapsedTime().asSeconds();

	float accumulator = 0.0f;

	// while window is open the game is running
	while (this->_data->window.isOpen())
	{
		// proccess all changes that wee have (switching the states, pausing etc.)
		this->_data->machine.processStateChanges();

		//
		newTime = this->_clock.getElapsedTime().asSeconds();
		
		// checks how long it takes between the next frames
		frameTime = newTime - currentTime;

		if (frameTime > 0.25f)
		{
			// restriction to not go to high
			frameTime = 0.25f; 
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= this->dt)
		{
			this->_data->machine.getActiveState()->handleInput();
			this->_data->machine.getActiveState()->update(dt);

			accumulator -= dt;
		}

		// the process of figuring out unknown intermediary values. By calculating the difference we can use 
		// that information when animating to ensure the objects don't move to fast on power devices or move to slowly on 
		// less powerful devices.
		interpolation = accumulator / dt;
		this->_data->machine.getActiveState()->draw(interpolation);
	}
}
