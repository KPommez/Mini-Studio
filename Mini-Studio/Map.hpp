#pragma once

#include "includeAll.hpp"
#include "plateforme.hpp"
#include "Lampadaire.hpp"
#include "Pétrifeu.hpp"
#include "Eolienne.hpp"

class ParralaxBackground;
class EntityManager;

class Map {
public:
	Map();
	void loadAllMaps();
	void loadMap(const string& filename, Player* players, RenderWindow& window, ParralaxBackground* currentLevel);
	void drawMap(RenderWindow& window);

public:
	RectangleShape endLevel;
	RectangleShape end;
	vector<RectangleShape> platforms;
	
	vector <Plateforme*> plateformeTest;
	vector<string> allLevels;
	shared_ptr<EntityManager> m_entityManager;

private:
	void loadMapTextures();

private:
	RectangleShape mur;
	float posX;
	float posY;
	Player* player;
	vector<string> allLevelsTypePath{ "Assets/Map/" };
	Texture
		leftRegularPlatform, rightRegularPlatform, middleRegularPlatform,
		leftLeafPlatform, rightLeafPlatform, middleNoLeafPlatform;
};