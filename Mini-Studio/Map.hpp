#pragma once
#include "includeAll.hpp"
class Map
{
public:
	Map();
	void loadMap(/*string filename*/);

	void drawMap(RenderWindow& window);

	RectangleShape mur;

	vector<RectangleShape> listeMur;

	float posX;
	float posY;
};

