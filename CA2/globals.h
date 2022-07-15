#pragma once
#include <SFML/Graphics.hpp>

const int g_winWidth = 1366;
const int g_winHeight = 768;

const int g_UIWidth = 400;

const int g_frameRate = 60;

const short g_strength = 80;
//const short g_reproduction = 20;

const short g_strengthVarience = 4;
//const short g_reproductionVarience = 3;

const char g_strMutationChance = 50; // out of 100. 100 being 100% mutation
//const char g_repMutationChance = 2; // out of 100. 100 being 100% mutation

const short g_numberOfChildrenPerLife = 3;
const short g_numberOfChildrenPerLifeVarience = 1;

const std::string g_title = "Cell Automata";
const std::string g_fileName = "World.png";

const sf::Color g_floorColor = sf::Color(0, 255, 0);
const sf::Color g_waterColor = sf::Color(0, 0, 255);

sf::Color g_GenerateRandomColor();
sf::Color g_GenerateRandomColor(unsigned char r, unsigned char g, unsigned char b);

const int g_numberOfFactions = 5;
const int g_sizeOfFactions = 1;



