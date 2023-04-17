#include "GameSaveState.h"

#include <iomanip>
#include <sstream>

GameSaveState::GameSaveState(GameDataRef data, Level level, std::vector<Enemy*> enemies, Character* character, unsigned currentLevel): _data(data), _level(level),
                                                                                                                                       _enemies(enemies), _character(character), _currentLevel(currentLevel)
{
}

void GameSaveState::init()
{
	this->_data->assets.loadTexture("Delete Button", DELETE_BUTTON_FILEPATH);
	this->_data->assets.loadTexture("Overwrite Button", OVERWRITE_BUTTON_FILEPATH);

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

	this->renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
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
		if (this->_data->input.isObjectClicked(this->_saveButton, sf::Mouse::Left, this->_data->window) && savesList.size() < 12)
		{
			// pobranie czasu w formie liczby sekund od 1 stycznia 1970 roku
			std::time_t currentTime = std::time(nullptr);

			// inicjalizacja struktury tm na podstawie czasu
			std::tm dateTime;
			localtime_s(&dateTime, &currentTime);

			// konwersja struktury tm na std::string
			char buffer[80];
			std::strftime(buffer, 80, "%d.%m.%Y %H:%M:%S", &dateTime);
			std::string datetimeStr(buffer);

			sf::Text text(datetimeStr, this->_data->assets.getFont("Pixel font"), 40);
			text.setFillColor(sf::Color::White);
			text.setStyle(sf::Text::Bold);

			sf::Vector2f textPos(200.f, 100.f);

			// Add the new sf::Text object to the savesList vector
			savesList.push_back(text);

			// Re-render the entire savesList vector to the render texture
			this->renderTexture.clear(sf::Color::Transparent);
			for (int i = 0; i < savesList.size(); i++)
			{
				savesList[i].setPosition(textPos);
				this->renderTexture.draw(savesList[i]);

				if ((i + 1) % maxSpritesPerRow == 0) {
					textPos.x = 200.f;
					textPos.y += savesList[i].getGlobalBounds().height + textSpacing;
				}
				else {
					textPos.x += savesList[i].getGlobalBounds().width + textSpacing;
				}
			}
			this->renderTexture.display();

			std::cout << "dodano" << std::endl;
		}
	}
}

void GameSaveState::update(float dt)
{
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

	for (auto& text : savesList) {
		if (this->_data->input.isMouseCursorOnObject(text, this->_data->window)) {
			sf::Cursor cursor;
			cursor.loadFromSystem(sf::Cursor::Hand);
			text.setFillColor(sf::Color::Red);
			text.setOutlineColor(sf::Color::Yellow);
			_data->window.setMouseCursor(cursor);
		}
		else {
			text.setFillColor(sf::Color::White);
			text.setOutlineColor(sf::Color::White);
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

	sf::Sprite sprite(this->renderTexture.getTexture());
	this->_data->window.draw(sprite);

	this->_data->window.display();
}
