#pragma once
#include "includeAll.hpp"

class Map {
private:
	RectangleShape mur;

	vector<RectangleShape> listeMur;

	float posX;
	float posY;
};

	vector<RectangleShape> platforms;
	void loadMap(const string& filename);
	void drawMap(RenderWindow& window);
};