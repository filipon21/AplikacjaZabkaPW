#include "Game.h"


void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 1400;
	this->window = new sf::RenderWindow(this->videoMode, "ZABKA ULICZNA", sf::Style::Titlebar | sf::Style::Close); //tworzenie okna gry z mozliwoscia zamkniecia i tytulem
	this->window->setFramerateLimit(144); //TODO zmiana w mnenu
	this->window->setVerticalSyncEnabled(false); //TODO zmiana w mnenu
}

void Game::initCharacter()
{
	this->character = new Character();
}

//Constructors / Destructors
Game::Game() {
	this->initWindow();
	this->initCharacter();
}

Game::~Game() {
	delete this->window;
	delete this->character;
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

void Game::update()
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

	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->character->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->character->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->character->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->character->move(0.f, 1.f);
	}
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	//:: ScopeResolution operator s³u¿y tutaj do wczytania static variable; moze takze sluzyc do wczytywania zmiennej globalnej jesli lokalna ma taka sama nazwe

	this->character->render(*this->window);

	//Rysuj obiekty w grze
	this->window->display(); // -> bo jest to wskaŸnik i chcemy siê dostaæ do konkretnej kalsy pochodnej (polimorfizm); dynamicznie

}
 
