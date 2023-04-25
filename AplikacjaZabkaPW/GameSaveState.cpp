#include "GameSaveState.h"

#include <fstream>
#include <filesystem>
#include <utility>

GameSaveState::GameSaveState(GameDataRef data, Level* level, std::vector<Enemy*> enemies, Character* character, unsigned currentLevel):
_data(std::move(data)), _level(level), _currentLevel(currentLevel), _character(character), _enemies(std::move(enemies))
{
}

void GameSaveState::init()
{
	this->_saveButton.setTexture(this->_data->assets.getTexture("Save Button"));
	this->_overwriteButton.setTexture(this->_data->assets.getTexture("Overwrite Button"));
	this->_deleteButton.setTexture(this->_data->assets.getTexture("Delete Button"));
	this->_returnButton.setTexture(this->_data->assets.getTexture("Return To Menu"));

	this->_returnButton.setScale(0.5f, 0.5f);
	this->_overwriteButton.setScale(0.5f, 0.5f);
	this->_deleteButton.setScale(0.5f, 0.5f);
	this->_saveButton.setScale(0.5f, 0.5f);

	this->_returnButton.setPosition(20.f,
		SCREEN_HEIGHT - _returnButton.getGlobalBounds().height - 20.f);

	this->_overwriteButton.setPosition(SCREEN_WIDTH - _overwriteButton.getGlobalBounds().width - 20.f,
		SCREEN_HEIGHT - _overwriteButton.getGlobalBounds().height - 20.f);

	float buttonSpacing = 10.f; // odstêp miêdzy przyciskami
	sf::Vector2f overwritePos = _overwriteButton.getPosition();
	sf::FloatRect overwriteBounds = _overwriteButton.getGlobalBounds();

	// ustawienie pozycji pierwszego przycisku po lewej stronie przycisku _overwriteButton
	sf::Vector2f button1Pos = sf::Vector2f(overwritePos.x - overwriteBounds.width - buttonSpacing,
		SCREEN_HEIGHT - _returnButton.getGlobalBounds().height - 20.f);
	this->_saveButton.setPosition(button1Pos);

	// ustawienie pozycji drugiego przycisku po lewej stronie przycisku _overwriteButton
	sf::Vector2f button2Pos = sf::Vector2f(button1Pos.x - _deleteButton.getGlobalBounds().width - buttonSpacing,
		SCREEN_HEIGHT - _returnButton.getGlobalBounds().height - 20.f);
	this->_deleteButton.setPosition(button2Pos);

	this->loadFiles();
}
void GameSaveState::loadFiles()
{
	this->_savesList.clear();
	std::vector<std::string> f = this->_data->fileManager.loadFilesFromDirectory("../Saves/");
	for (auto& fi : f)
	{
		sf::Text t(fi, this->_data->assets.getFont("Pixel font"), 40);
		this->_savesList.push_back(t);
	}
}

void GameSaveState::saveFile()
{
	// pobranie czasu w formie liczby sekund od 1 stycznia 1970 roku
	std::time_t currentTime = std::time(nullptr);

	// inicjalizacja struktury tm na podstawie czasu
	std::tm dateTime;
	localtime_s(&dateTime, &currentTime);

	// konwersja struktury tm na std::string
	char buffer[80];
	std::strftime(buffer, 80, "%d-%m-%Y %H:%M:%S", &dateTime);
	std::string datetimeStr(buffer);

	std::replace(datetimeStr.begin(), datetimeStr.end(), ' ', 'T');
	std::replace(datetimeStr.begin(), datetimeStr.end(), ':', '_');
	std::string filename = "../Saves/" + datetimeStr + ".txt";
	std::ofstream dataFile(filename);

	sf::Text text(datetimeStr, this->_data->assets.getFont("Pixel font"), 40);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);


	if (this->_data->fileManager.saveFile(std::move(dataFile), _currentLevel, _enemies, _character))
	{
		this->loadFiles();
	}
}

void GameSaveState::handleInput()
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
			&& this->_currentSaveClicked!=nullptr)
		{
			std::string s = _currentSaveClicked->getString();
			std::string filePath = "../Saves/" + s + ".txt";

			if (this->_data->fileManager.removeFile(filePath)) {
				this->loadFiles();
				this->_currentSaveClicked = nullptr;
			}
		}

		if (this->_data->input.isObjectClicked(this->_overwriteButton, sf::Mouse::Left, this->_data->window)
			&& this->_currentSaveClicked != nullptr)
		{
			std::string s = _currentSaveClicked->getString();
			std::string filePath = "../Saves/" + s + ".txt";

			if (this->_data->fileManager.removeFile(filePath)) {
				this->saveFile();
				this->_currentSaveClicked = nullptr;
			}
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


		// Dodaj nowy tekst tylko wtedy, gdy przycisk myszy jest wciœniêty i kursor myszy jest nad przyciskiem "save"
		if (this->_data->input.isObjectClicked(this->_saveButton, sf::Mouse::Left, this->_data->window)
			&& _savesList.size() < 12)
		{
			this->saveFile();
		}
	
	}

}

void GameSaveState::update(float dt)
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
	else if (this->_data->input.isMouseCursorOnObject(this->_saveButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_saveButton.setColor(sf::Color::Blue);
		_data->window.setMouseCursor(cursor);
	}
	else if (this->_data->input.isMouseCursorOnObject(this->_overwriteButton, this->_data->window))
	{
		cursor.loadFromSystem(sf::Cursor::Hand);
		this->_overwriteButton.setColor(sf::Color::Yellow);
		_data->window.setMouseCursor(cursor);
	}
	else {
		cursor.loadFromSystem(sf::Cursor::Arrow);
		this->_deleteButton.setColor(sf::Color::White);
		this->_returnButton.setColor(sf::Color::White);
		this->_saveButton.setColor(sf::Color::White);
		this->_overwriteButton.setColor(sf::Color::White);
		_data->window.setMouseCursor(cursor);
	}
	for (auto& text : _savesList) {
		if (this->_data->input.isMouseCursorOnObject(text, this->_data->window)) {
			cursor.loadFromSystem(sf::Cursor::Hand);
			_data->window.setMouseCursor(cursor);
		}
	}
}

void GameSaveState::draw(float dt)
{
	this->_data->window.clear(sf::Color::Black);

	this->_data->window.draw(this->_returnButton);
	this->_data->window.draw(this->_saveButton);
	this->_data->window.draw(this->_deleteButton);
	this->_data->window.draw(this->_overwriteButton);

	for (int i = 0; i < _savesList.size(); i++)
	{
		this->_data->window.draw(this->_savesList[i]);
	}

	this->_data->window.display();
}
