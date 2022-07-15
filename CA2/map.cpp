#include "map.h"

/*
Constructor initalizes the Texture, sprite and pixel array.
*/
map_class::map_class(std::string fileName) {

	LoadMapTexture(fileName); // Loads file
	mapSize = mapTexture.getSize(); // Gets x, y
	mapSprite.setTexture(mapTexture); // Sets sprite to texture
	CreatePixelArray(); // Creates Pixel Array

}

/*
Takes the name of a file
Loads the image from file, prints error if failed
*/
void map_class::LoadMapTexture(std::string fileName) {
	if (!mapTexture.loadFromFile(fileName))
		std::cerr << "Cannot load image";
}

/*
Creates a pixel array [red1,green1,blue1,alpha1,red2,green2,blue2,alpha2,....red*x*y,green4*x*y,blue4*x*y,alpha4*x*y]
*/
void map_class::CreatePixelArray() {
	sf::Image image;
	sf::Color pixelColor;
	image = mapTexture.copyToImage();

	for (unsigned int y = 0; y < mapSize.y; y++) {
		for (unsigned int x = 0; x < mapSize.x; x++) {
			pixelColor = image.getPixel(x, y);
			mapPixelArray.push_back(pixelColor.r);
			mapPixelArray.push_back(pixelColor.g);
			mapPixelArray.push_back(pixelColor.b);
			mapPixelArray.push_back(255);
		}
	}
}

/*
Takes: x, y and color
Sets the color the given pixel
*/
void map_class::SetPixel(int x, int y, sf::Color color) {
	int index = (mapSize.x*y * 4) + (x * 4);
	mapPixelArray[index] = color.r;
	mapPixelArray[index + 1] = color.g;
	mapPixelArray[index + 2] = color.b;
}

/*
Takes: x, y
returns: sf::Color
*/
sf::Color map_class::GetPixel(int x, int y) {
	int index = (mapSize.x*y * 4) + (x * 4);
	sf::Color pixelColor;
	pixelColor.r = mapPixelArray[index];
	pixelColor.g = mapPixelArray[index + 1];
	pixelColor.b = mapPixelArray[index + 2];
	return pixelColor;
}

/*
Updates the texture with pixel array
*/
void map_class::Update() {
	mapTexture.update(&mapPixelArray.front());
}

/*
Draws the map on window
*/
void map_class::Draw(sf::RenderWindow *window) {
	(*window).draw(mapSprite);
}

// Returns Map int X
int map_class::getMapX() {
	return mapSize.x;
}


// Returns Map int Y
int map_class::getMapY() {
	return mapSize.y;
}
