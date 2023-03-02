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
	const bool running() const;

	// Functions
	void pollEvents();
	void update();
	void render();
};

