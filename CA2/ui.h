#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "cell_manager.h"

class ui_class {

private:
	std::vector<sf::Text> factionTextArray;

	sf::Vector2u pos;
	sf::Vector2u padding;
	sf::Font font;

	int spacing = 30;

public:
	ui_class(cell_manager *cellManager);

	void Update(cell_manager *cellManager);
	void Draw(sf::RenderWindow *window);
};