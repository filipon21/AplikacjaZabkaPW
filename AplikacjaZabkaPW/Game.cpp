#include "Game.h"


void Game::initGUI()
{
	//Load fonts
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "ERROR::GAME::Failed to load font" << "\n";
	}

	//Init point text
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(12);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");
}

void Game::initBackground()
{
	if (!this->backgroundTexture.loadFromFile("Textures/grass3.jpg"))
	{
		std::cout << "ERROR::GAME:: Could not load background texture" << "\n";
	}
	this->worldBackground.setTexture(this->backgroundTexture);
}

void Game::initWindow()
{
	this->videoMode.height = 900;
	this->videoMode.width = 1400;
	this->window = new sf::RenderWindow(this->videoMode, "ZABKA ULICZNA", sf::Style::Titlebar | sf::Style::Close); //tworzenie okna gry z mozliwoscia zamkniecia i tytulem
	this->window->setFramerateLimit(144); //TODO zmiana w mnenu
	this->window->setVerticalSyncEnabled(false); //TODO zmiana w mnenu
}

void Game::initTextures()
{
	
}

void Game::initCharacter()
{
	this->character = new Frog(2.f, 0.5f, 0.5f);
	this->character->makeChar();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::updateInput()
{
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

void Game::updatePollEvents()
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

//Constructors / Destructors
Game::Game() {
	this->initWindow();
	this->initTextures();
	this->initCharacter();
	this->initEnemies();
	this->initBackground();
	this->initGUI();

}

Game::~Game() {
	delete this->window;
	delete this->character;

	//delete textures for avoid memmory leak
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	//delete enemies for avoid memmory leak
	for (auto& i : this->enemies)
	{
		delete i;
	}
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
	this->updatePollEvents();
	this->updateInput();

	this->updateEnemies();

	this->updateGUI();
}

void Game::render()
{
	this->window->clear(sf::Color::Black);
	//:: ScopeResolution operator s³u¿y tutaj do wczytania static variable; moze takze sluzyc do wczytywania zmiennej globalnej jesli lokalna ma taka sama nazwe

	//Draw background
	this->renderBackground();

	//Draw charcter and enemies
	this->character->render(*this->window);

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	//Draw GUI
	this->renderGUI();

	//Display all objects
	this->window->display(); // -> bo jest to wskaŸnik i chcemy siê dostaæ do konkretnej kalsy pochodnej (polimorfizm); dynamicznie

}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(0, rand() % this->window->getSize().y - 20.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().left + enemy->getBounds().width > this->window->getSize().x)
		{
			//delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
			std::cout << this->enemies.size() << "\n";
		}
	}

	//for (int i = 0; i < this->enemies.size(); ++i)
	//{

	//	this->enemies[i]->update();

	//	//remove enemy at the bottom of the screen
	//	if (this->enemies[i]->getBounds().left + this->enemies[i]->getBounds().width > this->window->getSize().x)
	//	{
	//		this->enemies.erase(this->enemies.begin() + i);
	//		std::cout << this->enemies.size() << "\n";
	//	}
	//}
}

void Game::updateCombat()
{

}

void Game::updateGUI()
{

}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
}

void Game::renderBackground()
{
	this->window->draw(this->worldBackground);
}

