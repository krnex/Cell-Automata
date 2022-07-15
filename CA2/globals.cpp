#include "globals.h"

sf::Color g_GenerateRandomColor() {
	sf::Color color;
	color.r = rand() % 255;
	color.g = rand() % 255;
	color.b = rand() % 255;
	return color;
}

sf::Color g_GenerateRandomColor(unsigned char r, unsigned char g, unsigned char b) {
	sf::Color color;
	color.r = rand() % r;
	color.g = rand() % g;
	color.b = rand() % b;
	return color;
}