#include "GameLoadState.h"

#include <fstream>
#include <sstream>
#include <utility>

#include "DEFINITIONS.h"
#include "GameState.h"

GameLoadState::GameLoadState(GameDataRef data): _data(std::move(data))
{
}

void GameLoadState::init()
{
	this->_loadButton.setTexture(this->_data->assets.getTexture("Load Button"));
	this->_returnButton.setTexture(this->_data->assets.getTexture("Return To Menu"));
	this->_deleteButton.setTexture(this->_data->assets.getTexture("Delete Button"));

	this->_returnButton.setScale(0.5f, 0.5f);
	this->_deleteButton.setScale(0.5f, 0.5f);
	this->_loadButton.setScale(0.5f, 0.5f);

	this->_returnButton.setPosition(20.f,
		SCREEN_HEIGHT - _returnButton.getGlobalBounds().height - 20.f);

	this->_deleteButton.setPosition(SCREEN_WIDTH - _loadButton.getGlobalBounds().width - 20.f,
		SCREEN_HEIGHT - _loadButton.getGlobalBounds().height - 20.f);

	float buttonSpacing = 10.f; // odstêp miêdzy przyciskami
	sf::Vector2f overwritePos = _deleteButton.getPosition();
	sf::FloatRect overwriteBounds = _deleteButton.getGlobalBounds();

	// ustawienie pozycji pierwszego przycisku po lewej stronie przycisku _overwriteButton
	sf::Vector2f button1Pos = sf::Vector2f(overwritePos.x - overwriteBounds.width - buttonSpacing,
		SCREEN_HEIGHT - _returnButton.getGlobalBounds().height - 20.f);
	this->_loadButton.setPosition(button1Pos);

	this->loadFiles();
}

void GameLoadState::loadFiles()
{
	this->_savesList.clear();
	std::vector<std::string> f = this->_data->fileManager.loadFilesFromDirectory("../Saves/");
	for (auto& fi : f)
	{
		sf::Text t(fi, this->_data->assets.getFont("Pixel font"), 40);
		this->_savesList.push_back(t);
	}
}

void GameLoadState::handleInput()
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			this->_data->window.close();
		}

		if (this->_data->input.isObjectClicked(this->_returnButton, sf::Mouse::Left, this->_data->window))
		{
			std::cout << "Return to pause menu" << std::endl;
			this->_data->machine.removeState();
		}

		if (this->_data->input.isObjectClicked(this->_deleteButton, sf::Mouse::Left, this->_data->window)
			&& this->_currentSaveClicked != nullptr)
		{
			std::string s = _currentSaveClicked->getString();
			std::string filePath = "../Saves/" + s + ".txt";

			if (this->_data->fileManager.removeFile(filePath)) {
				this->loadFiles();
				this->_currentSaveClicked = nullptr;
			}
		}

		if (this->_data->input.isObjectClicked(this->_loadButton, sf::Mouse::Left, this->_data->window)
			&& this->_currentSaveClicked != nullptr)
		{
			std::string s = _currentSaveClicked->getString();
			std::string filePath = "../Saves/" + s + ".txt";


			std::ifstream file(filePath);
			if (!file) {
				// obs³uga b³êdu
			}

			std::vector<Enemy*> enemies;
			unsigned currentLevel;
			int hpMax, hp;
			float speed, posX, posY;

			std::string line;
			std::string lastValue;
			char delimiter;

			while (std::getline(file, line) && line != "|") {
				int hpMax, hp, damage, pointCount, points, textureName;
				float speed, posX, posY;
				std::istringstream iss(line);
				iss >> hpMax >> delimiter >> hp >> delimiter >> damage >> delimiter >> pointCount >> delimiter
					>> points >> delimiter >> speed >> delimiter >> posX >> delimiter >> posY >> delimiter >> textureName;

				Enemy* enemy = new Enemy(hp, hpMax, speed, damage, points, pointCount, 
					this->_data->assets.getTexture(std::to_string(textureName)), textureName, posX, posY);
				enemies.push_back(enemy);
			}
			file >> currentLevel;

			file.close();
			this->_data->machine.addState(StateRef(new GameState(_data, currentLevel, enemies, true)), false);
		}

		sf::Text* previousSaveClicked = this->_currentSaveClicked;

		for (sf::Text& text : _savesList) {
			if (this->_data->input.isObjectClicked(text, sf::Mouse::Left, this->_data->window)) {
				if (this->_currentSaveClicked == &text)
				{
				}
				else {
					// Ustaw kolor tekstu na niebieski dla aktualnego tekstu
					text.setFillColor(sf::Color::Blue);
					this->_currentSaveClicked = &text;

					if (previousSaveClicked != nullptr) {
						// Ustaw kolor tekstu na bia³y dla poprzedniego tekstu
						previousSaveClicked->setFillColor(sf::Color::White);
					}
				}
			}
		}

	}

}

void GameLoadState::update(float dt)
{
	sf::Vector2f textPos(150.f, 100.f);

	for (int i = 0; i < _savesList.size(); i++)
	{
		_savesList[i].setPosition(textPos);

		if ((i + 1) % _maxSpritesPerRow == 0) {
			textPos.x = 150.f;
			textPos.y += _savesList[i].getGlobalBounds().height + _textSpacing;
		}
		else {
			textPos.x += _savesList[i].getGlobalBounds().width + _textSpacing;
		}
	}
	sf::Cursor cursor;

	if (this->_data->input.isMouseCursorOnObject(this->_returnButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_returnButton.setColor(sf::Color::Red);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_deleteButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_deleteButton.setColor(sf::Color::Red);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_loadButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_loadButton.setColor(sf::Color::Blue);
		_data->window.setMouseCursor(cursor);
	}
	
	else {
		cursor.loadFromSystem(sf::Cursor::Arrow);
		this->_deleteButton.setColor(sf::Color::White);
		this->_returnButton.setColor(sf::Color::White);
		this->_loadButton.setColor(sf::Color::White);
		_data->window.setMouseCursor(cursor);
	}
	for (auto& text : _savesList) {
		if (this->_data->input.isMouseCursorOnObject(text, this->_data->window)) {
			cursor.loadFromSystem(sf::Cursor::Hand);
			_data->window.setMouseCursor(cursor);
		}
	}
}

void GameLoadState::draw(float dt)
{
	this->_data->window.clear(sf::Color::Black);

	this->_data->window.draw(this->_returnButton);
	this->_data->window.draw(this->_loadButton);
	this->_data->window.draw(this->_deleteButton);

	for (int i = 0; i < _savesList.size(); i++)
	{
		this->_data->window.draw(this->_savesList[i]);
	}

	this->_data->window.display();
}
