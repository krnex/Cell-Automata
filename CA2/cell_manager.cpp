#include "cell_manager.h"


cell_manager::cell_manager(int _numberOfFactions, short _spawnDensity, map_class *_map) {

	numberOfFactions = _numberOfFactions;
	CreateCellArray(_map);
	factionColorArray.push_back(g_waterColor);
	factionColorArray.push_back(g_floorColor);

	for (int i = 0; i < numberOfFactions; i++) {
		SpawnFaction(i+2, _spawnDensity, _map);
	}
}

void cell_manager::CreateCellArray(map_class *_map) {

	mapXSize = _map->getMapX();
	mapYSize = _map->getMapY();

	for (int i = 0; i < _map->getMapY(); i++) {
		for (int k = 0; k < _map->getMapX(); k++) {
			if (_map->GetPixel(k, i) == g_waterColor) {
				cellArray.push_back(CreateCell(k, i, 0));
			}
			else {
				cellArray.push_back(CreateCell(k, i, 1));
			}
		}
	}

}

void cell_manager::SpawnFaction(int _faction, int _spawnDensity, map_class *_map) {

	bool validMapSpot;
	int spawnCount;
	int densityRoot;
	sf::Vector2u freeLocation;

	factionColorArray.push_back(g_GenerateRandomColor(255, 254, 255));
	factionTotalNumbers.push_back(0);
	factionTotalStrength.push_back(0);
	validMapSpot = false;

	spawnCount = 0;
	densityRoot = ceil(sqrt(_spawnDensity));

	while (!validMapSpot) {
		freeLocation.x = rand() % (_map->getMapX()- densityRoot);
		freeLocation.y = rand() % (_map->getMapY() - densityRoot);

		if (_map->GetPixel(freeLocation.x, freeLocation.y) == g_floorColor) {
			validMapSpot = true;
		}
	}


	for (int i = 0; i < densityRoot * 2; i = i + 2) {
		for (int k = 0; k < densityRoot * 2; k = k + 2) {
			if (spawnCount >= _spawnDensity) {
				return;
			}
			if (_map->GetPixel(freeLocation.x + k, freeLocation.y + i) == g_floorColor) {
				SpawnCell(freeLocation.x + k, 
					freeLocation.y + i,
					_faction, 
					g_strength / g_numberOfChildrenPerLife,//g_reproduction, // + ((rand() % g_reproductionVarience) - (g_reproductionVarience /2)), 
					g_strength + ((rand() % g_strengthVarience) - g_strengthVarience/2), 
					false);
				spawnCount++;
			}
		}
	}
}

void cell_manager::SpawnCell(int x, int y, char _faction, short _reproduction, short _strength, bool _diseased) {
	cell newCell;
	int index = ((y*mapXSize) + x);
	newCell = CreateCell(x, y, _faction, _reproduction, _strength, _diseased);
	cellArray[index] = newCell;
}


void cell_manager::Update(map_class *_map) {

	std::fill(factionTotalStrength.begin(), factionTotalStrength.end(), 0);
	std::fill(factionTotalNumbers.begin(), factionTotalNumbers.end(), 0);

	for (int i = 0; i < cellArray.size(); i++) {
		UpdateMap(_map, &cellArray[i]);
		if (cellArray[i].faction >= 2) {

			ReproductionCheckCell(&cellArray[i]);
			LifeCheckCell(&cellArray[i]);
			MoveCell(&cellArray[i]);

			factionTotalStrength[cellArray[i].faction - 2] += cellArray[i].strength;
			factionTotalNumbers[cellArray[i].faction - 2]++;

		}
	}
}

void cell_manager::ReproduceCell(cell *_currentCell) {
	cell *cellP;

	/* Check for free spot */
	for (int i = 1; i <= 4; i++) {
		cellP = GetAdjacentCell(_currentCell, i);
		if (cellP->faction == 1) {
			break;
		}
	}

	/* If there is not free spots then no child is born */
	if (cellP->faction > 1 || cellP->faction == 0) {
		return;
	}

	/* Sets strength to parents then checks mutation chance. If it does mutate then changes by mutation. */
	short newStrength = _currentCell->strength;
	if (rand() % 100 + 1 < g_strMutationChance) {
		newStrength = newStrength + ((rand() % g_strengthVarience) - ((g_strengthVarience /2)));
	}

	short childrenPerLife = 0;

	if (g_numberOfChildrenPerLifeVarience != 0) {
		childrenPerLife = g_numberOfChildrenPerLife + ((rand() % (2 * g_numberOfChildrenPerLifeVarience)) - (g_numberOfChildrenPerLifeVarience));
	}
	else {
		childrenPerLife = g_numberOfChildrenPerLife;
	}

	short newReproduction = (newStrength-1) / childrenPerLife;
	/* Sets reproduction to parents then checks mutation chance. If it does mutate then changes by mutation. 
	short newReproduction = _currentCell->reproductionThreshhold;
	if (rand() % 100 + 1 < g_repMutationChance) {
		newReproduction = newReproduction + ((rand() % g_reproductionVarience) - ((g_reproductionVarience / 2)));
	} */

	//TODO: DISEASE
	*cellP = CreateCell(0, 0, _currentCell->faction, newReproduction, newStrength, false);
}

void cell_manager::ReproductionCheckCell(cell *_currentCell) {
	if (_currentCell->reproduction > _currentCell->reproductionThreshhold) {

		_currentCell->reproduction = 0;
		ReproduceCell(_currentCell);
	}
	_currentCell->reproduction++;
}

void cell_manager::LifeCheckCell(cell *_currentCell) {
	if (_currentCell->life > _currentCell->strength) {
		KillCell(_currentCell);
	}
	else {
		_currentCell->life++;
	}
}

void cell_manager::KillCell(cell *_currentCell) {
	int index = (((_currentCell->pos.y) * mapXSize) + _currentCell->pos.x);
	cellArray[index] = CreateCell(_currentCell->pos.x, _currentCell->pos.y, 1);
}

void cell_manager::UpdateMap(map_class *_map, cell *_currentCell) {
	_map->SetPixel(_currentCell->pos.x, _currentCell->pos.y, factionColorArray[_currentCell->faction]);
}

void cell_manager::MoveCell(cell *_currentCell) {
	char direction = rand() % 4 + 1;
	cell *cellP = GetAdjacentCell(_currentCell, direction);
	if (cellP->faction == 1) {
		SwapCells(_currentCell, cellP);
	}
	else if (cellP->faction > 1 && cellP->faction != _currentCell->faction) {
		if (_currentCell->strength > cellP->strength) {
			//*cellP = *_currentCell;
			//*_currentCell = CreateCell(0, 0, 1);
			*cellP = CreateCell(0, 0, 1);
		}
	}

}

cell *cell_manager::GetAdjacentCell(cell *_currentCell, char _direction) {
	int index;
	cell *cellP = NULL;

	if (_direction == 1) {

		index = (((_currentCell->pos.y - 1) * mapXSize) + _currentCell->pos.x);
		cellP = &cellArray[index];

	}
	else if (_direction == 2) {

		index = (((_currentCell->pos.y)  * mapXSize) + _currentCell->pos.x + 1);
		cellP = &cellArray[index];

	}
	else if (_direction == 3) {

		index = (((_currentCell->pos.y + 1) * mapXSize) + _currentCell->pos.x);
		cellP = &cellArray[index];

	}
	else if (_direction == 4) {

		index = (((_currentCell->pos.y) * mapXSize) + _currentCell->pos.x - 1);
		cellP = &cellArray[index];

	}

	return cellP;
}
