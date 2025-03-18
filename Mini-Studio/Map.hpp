#pragma once

#include "includeAll.hpp"
#include "plateforme.hpp"
#include "Lampadaire.hpp"
#include "Pétrifeu.hpp"
#include "Eolienne.hpp"
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
	void loadMap(const string& filename, Player* players, RenderWindow& window);
	void drawMap(RenderWindow& window);

	vector<RectangleShape> platforms;
	vector<RectangleShape> end;
	vector <Plateforme*> plateformeTest;
	vector<string> allLevelsTypePath{ "Assets/Map/" };
	vector<string> allLevels;

	shared_ptr<EntityManager>  m_entityManager;
};