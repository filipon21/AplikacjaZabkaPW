#include "Game.h"

//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 1400;
	this->window = new sf::RenderWindow(this->videoMode, "ZABKA ULICZNA", sf::Style::Titlebar | sf::Style::Close); //tworzenie okna gry z mozliwoscia zamkniecia i tytulem
}

//Constructors / Destructors
Game::Game() {
	this->initializeVariables();
	this->initWindow();
}

Game::~Game() {
	delete this->window;
}

//Accessors
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
	
}




//Functions
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev)) { // jeœli okno z³apie jakikolwiek event, zapisze je w zmiennej ev 
		switch (this->ev.type)
		{
		case sf::Event::Closed: // jeœli nacisniêto przzycisk close - wyslano Event do zmiennej ev i nale¿y zamknac okno
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::LAlt + ev.key.code == sf::Keyboard::F4)
			{
				this->window->close();
			}
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	//:: ScopeResolution operator s³u¿y tutaj do wczytania static variable; moze takze sluzyc do wczytywania zmiennej globalnej jesli lokalna ma taka sama nazwe


	//Rysuj obiekty w grze
	this->window->display(); // -> bo jest to wskaŸnik i chcemy siê dostaæ do konkretnej kalsy pochodnej (polimorfizm); dynamicznie

}
 
