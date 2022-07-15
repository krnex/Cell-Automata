#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class map_class {

private:
	sf::Vector2u mapSize;

	sf::Texture mapTexture;
	sf::Sprite mapSprite;
	std::vector<sf::Uint8> mapPixelArray;

	void LoadMapTexture(std::string fileName);
	void CreatePixelArray();

public:
	map_class(std::string fileName);

	void SetPixel(int x, int y, sf::Color color);
	sf::Color GetPixel(int x, int y);

	int getMapX();
	int getMapY();

	void Draw(sf::RenderWindow *window);
	void Update();
};