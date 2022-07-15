#pragma once
#include <math.h>
#include "cell.h"
#include "map.h"
#include "globals.h"


class cell_manager {
private:

	int mapXSize;
	int mapYSize;

	std::vector<cell> cellArray;
	void SpawnCell(int x, int y, char _faction, short _reproduction, short _strength, bool _diseased);
	void SpawnFaction(int _faction, int _spawnDensity, map_class *_map);
	void CreateCellArray(map_class *_map);
	cell *GetAdjacentCell(cell *_currentCell, char _direction);

	void ReproduceCell(cell *_currentCell);
	void ReproductionCheckCell(cell *_currentCell);
	void LifeCheckCell(cell *_currentCell);
	void KillCell(cell *_currentCell);
	void MoveCell(cell *_currentCell);
	void UpdateMap(map_class *map, cell *currentCell);

public:

	std::vector<sf::Color> factionColorArray;
	std::vector<int> factionTotalStrength;
	std::vector<int> factionTotalNumbers;

	int numberOfFactions;

	cell_manager(int _numberOfFactions, short _spawnDensity, map_class *_map);
	void Update(map_class *map);
};
