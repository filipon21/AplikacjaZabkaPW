#pragma once //#pragma once pozwala na includowanie pliku do woli :)

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Character.h"
#include "Frog.h"
#include "Enemy.h"

/*
* Class that acts as the game engine.
* Wrapper class.
*/
class Game
{
private:
	
	//GUI
	sf::Font font;
	sf::Text pointText;

	//Background texture
	sf::Sprite worldBackground;
	sf::Texture backgroundTexture;

	// Window
	sf::RenderWindow* window; //u¿yto wska¿nik, dziêki niemu mozna dostaæ siê do ktorejkolwiek z klas pochodnych (polimorfizm), czyli dynamicznie
	sf::VideoMode videoMode;
	
	//Resources
	std::map<std::string, sf::Texture*> textures; // * bo nie chcemy kopiowac tekstur tylko odnieœæ siê do tej konkretnej bez kopiowania dla optymalizacji

	//Event
	sf::Event ev; //zmienna do ³apania eventów np. klikania przyciskow

	// Character
	Character* character;

	// Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;


	//Private functions
	void initGUI();
	void initBackground();

	void initWindow();
	void initTextures();

	void initCharacter();
	void initEnemies();

	void updateInput();
	void updatePollEvents();

public:
	// Contructors / Destructors
	Game();
	virtual ~Game();

	//Accessors
	/**
	 * Method that checks if the game is still running (is window still open?)
	 *
	 */
	void run();
	
	/**
	 * Method used to updates all data of game in each frame
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

	void updateEnemies();

	void updateCombat();


	void updateGUI();
	void renderGUI();

	void renderBackground();
};

