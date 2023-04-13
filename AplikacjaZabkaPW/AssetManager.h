#pragma once

#include <map>
#include <SFML/Graphics.hpp>

/**
 * Class for loading assets (textures, fonts).
 */
class AssetManager
{
public:
	AssetManager() { }
	~AssetManager() { }

	/**
	 * Method for loading textures.
	 * 
	 * \param name - assing name to texture for later use
	 * \param fileName - path for file
	 */
	void loadTexture(std::string name, std::string fileName);

	/**
	 * Method for getting the texture.
	 * 
	 * \param name - name for the saved texture
	 * \return reference to saved texture
	 */
	sf::Texture& getTexture(std::string name);

	/**
	 * Method for loading font.
	 *
	 * \param name - assing name to font for later use
	 * \param fileName - path for file
	 */
	void loadFont(std::string name, std::string fileName);

	/**
	 * Method for getting the font.
	 *
	 * \param name - name for the saved font
	 * \return reference to saved font
	 */
	sf::Font& getFont(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};


