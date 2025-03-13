#pragma once

#include "includeAll.hpp"
#include "plateforme.hpp"

class Map {
private:
	RectangleShape mur;
	float posX;
	float posY;

public:
	Map();
	void loadAllMaps();
	void loadMap(const string& filename);
	void drawMap(RenderWindow& window);

public:
	vector<RectangleShape> platforms;
	vector <Plateforme*> plateformeTest;
	vector<string> allLevelsTypePath{ "Assets/Map/" };
	vector<string> allLevels;
};