#pragma once //#pragma once pozwala na includowanie pliku do woli :)

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
* Class that acts as the game engine.
* Wrapper class.
*/
class Game
{
private:
	//Variables
	
	// Window
	sf::RenderWindow* window; //u¿yto wska¿nik, dziêki niemu mozna dostaæ siê do ktorejkolwiek z klas pochodnych (polimorfizm)
	sf::VideoMode videoMode;
	sf::Event ev; //zmienna do ³apania eventów np. klikania przyciskow

	//Private functions
	void initializeVariables();
	void initWindow();

public:
	// Contructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	/**
	 * Method that checks if the game is still running (is window still open?)
	 *
	 * \return true or false:bool
	 */
	const bool running() const;
	
	// Functions
	/**
	 * Method used to poll events (it checks for new events like mouse click etc.).
	 * 
	 */
	void pollEvents();
	/**
	 * Method used to run pollEvents() method.
	 *
	 */
	void update();
	/**
	 * Method used to render the game objects (draw objects).
	 * - clears old frame
	 * - render objects
	 * - display frame in window
	 */
	void render();
};

