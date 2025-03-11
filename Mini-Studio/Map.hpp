#pragma once

#include "includeAll.hpp"

class Map {
private:
	RectangleShape mur;
	float posX;
	float posY;

public:
	Map();

	vector<RectangleShape> listeMur;
	RectangleShape rectNormalGravity;
	RectangleShape rectInvertedGravity;

public:
	void loadMap(const string& filename, RenderWindow& window);
	void drawMap(RenderWindow& window);
};