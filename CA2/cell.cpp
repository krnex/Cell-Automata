#include "cell.h"

cell CreateCell(int x, int y, char faction, short reproductionThreshold, short strength, bool diseased) {
	cell Cell;
	Cell.pos = sf::Vector2u(x, y);
	Cell.faction = faction;
	Cell.life = 0;
	Cell.reproduction = 0;
	Cell.reproductionThreshhold = reproductionThreshold;
	Cell.strength = strength;
	Cell.diseased = diseased;
	return Cell;
}

cell CreateCell(int x, int y, char faction) {
	cell Cell;
	Cell.pos = sf::Vector2u(x, y);
	Cell.faction = faction;
	Cell.life = 0;
	Cell.reproduction = 0;
	Cell.reproductionThreshhold = 0;
	Cell.strength = 0;
	Cell.diseased = false;
	return Cell;
}

void SwapCells(cell *cell1, cell *cell2) {
	cell tempCell;
	tempCell = *cell1;
	*cell1 = *cell2;
	*cell2 = tempCell;
}