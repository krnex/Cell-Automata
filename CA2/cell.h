#pragma once
#include <SFML/Graphics.hpp>

struct cell{
	sf::Vector2u pos;
	char faction;
	short life;
	short reproduction;
	short reproductionThreshhold;
	short strength;
	bool diseased;

	cell& operator =(const cell& other) {
		faction = other.faction;
		life = other.life;
		strength = other.strength;
		reproduction = other.reproduction;
		reproductionThreshhold = other.reproductionThreshhold;
		diseased = other.diseased;
		return *this;
	}
};

cell CreateCell(int x, int y, char faction, short reproductionThreshold, short strength, bool diseased);
cell CreateCell(int x, int y, char faction);

void SwapCells(cell *cell1, cell *cell2);