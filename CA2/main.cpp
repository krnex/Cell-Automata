#include <iostream>
#include <time.h>

#include <SFML/Graphics.hpp>
#include "globals.h"
#include "map.h"
#include "cell_manager.h"
#include "ui.h"

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(g_winWidth + g_UIWidth, g_winHeight), g_title);
	window.setFramerateLimit(g_frameRate);
	sf::RenderWindow *windowP = &window;

	map_class map(g_fileName);
	map_class *mapP = &map;

	cell_manager cellManager(g_numberOfFactions, g_sizeOfFactions, mapP);
	ui_class ui(&cellManager);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.clear(sf::Color::White);
		map.Update();
		cellManager.Update(mapP);
		map.Draw(windowP);

		ui.Update(&cellManager);
		ui.Draw(windowP);

		window.display();
	}

	return 0;
}