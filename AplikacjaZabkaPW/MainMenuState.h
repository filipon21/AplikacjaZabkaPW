#pragma once

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "State.h"


	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void init();
		void handleInput();
		void update(float dt);
		void draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		//sf::Sprite _title;
		sf::Text _title;
		sf::Sprite _playButton;
		sf::Sprite _charSelectorButton;
		sf::Sprite _optionsButton;
		sf::Sprite _exitButton;
	};
