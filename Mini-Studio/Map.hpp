#pragma once

#include "includeAll.hpp"
#include "plateforme.hpp"
#include "Lampadaire.hpp"
#include "Pétrifeu.hpp"
#include "Eolienne.hpp"

class ParralaxBackground;
class EntityManager;

class Map {
private:
	RectangleShape mur;
	
	
	float posX;
	float posY;
	Player* player;

public:
	Map();
	void loadAllMaps();
	void loadMap(const string& filename, Player* players, RenderWindow& window, ParralaxBackground* currentLevel);
	void drawMap(RenderWindow& window);

	RectangleShape endLevel;
	RectangleShape end;

	vector<RectangleShape> platforms;
	
	vector <Plateforme*> plateformeTest;
	vector<string> allLevelsTypePath{ "Assets/Map/" };
	vector<string> allLevels;

	shared_ptr<EntityManager>  m_entityManager;
};