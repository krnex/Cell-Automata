#include "ui.h"

ui_class::ui_class(cell_manager *cellManager) {

	pos.x = g_winWidth;
	pos.y = g_winHeight;

	padding.x = 10;
	padding.y = 30;
	
	if (!font.loadFromFile("VCR_OSD_MONO_1.001.ttf")) {
		std::cerr << "Error loading font";
	}

	for (int i = 0; i < cellManager->numberOfFactions; i++) {
		sf::Text text;
		text.setFont(font);
		text.setCharacterSize(12);
		text.setFillColor(cellManager->factionColorArray[i+2]);
		text.setStyle(sf::Text::Regular);
		text.setPosition(pos.x + padding.x, padding.y + spacing * i);
		factionTextArray.push_back(text);
	}

}

void ui_class::Update(cell_manager *cellManager) {

	for (int i = 0; i < cellManager->numberOfFactions; i++) {
		std::string tempString = "";
		tempString = "Faction[" + std::to_string(i) + "]:";
		tempString += "Total Cells = " + std::to_string(cellManager->factionTotalNumbers[i]) + " : ";
		tempString += "Avg Strength = " + std::to_string(cellManager->factionTotalStrength[i] / (cellManager->factionTotalNumbers[i]+1));
		factionTextArray[i].setString(tempString);
	}
}

void ui_class::Draw(sf::RenderWindow *window) {
	for (int i = 0; i < factionTextArray.size(); i++) {
		(*window).draw(factionTextArray[i]);
	}
}