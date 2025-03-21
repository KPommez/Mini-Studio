#include "Map.hpp"
#include "EntityManager.hpp"

Map::Map() {
	m_entityManager = make_shared<EntityManager>();
	posX = 0;
	posY = 0;
	loadMapTextures();
	loadAllMaps();
}

void Map::loadMapTextures() {
	leftRegularPlatform.loadFromFile  ("Assets/Map/Platforms/leftBorder.png");
	rightRegularPlatform.loadFromFile ("Assets/Map/Platforms/rightBorder.png");
	middleRegularPlatform.loadFromFile("Assets/Map/Platforms/centralBubble.png");
	leftLeafPlatform.loadFromFile     ("Assets/Map/Platforms/leftLeafBlock.png");
	rightLeafPlatform.loadFromFile    ("Assets/Map/Platforms/rightLeafBlock.png");
	middleNoLeafPlatform.loadFromFile ("Assets/Map/Platforms/noLeafBlock.png");
	mirror.loadFromFile               ("Assets/LevelAssets/LevelTwo/Sprites/mirror.png");
}

void Map::loadAllMaps() {
	try {
		for (auto& path : allLevelsTypePath) {
			try {				
				for (const auto& entry : fs::directory_iterator(path)) {
					if (fs::is_regular_file(entry) && entry.path().extension() == ".txt") {
						allLevels.push_back(entry.path().string());
					}
				}
			}
			catch (const exception& e) {
				cerr << "Erreur lors du chargement des maps depuis le repertoire " << path << " : " << e.what() << endl;
			}
		}
	}
	catch (const exception& e) {
		// Gestion d'erreur globale
		cerr << "Erreur lors du chargement des maps : " << e.what() << endl;
	}
}

void Map::loadMap(const string& filename, Player* players, RenderWindow& window, ParralaxBackground* currentLevel) {
	plateformeTest.clear();
	platforms.clear();
	ifstream file(filename);
	string line;
	float y = 0.f;

	while (getline(file, line)) {
		for (size_t x = 0; x < line.size(); ++x) {
			posX = (float)x * 40.f;
			posY = (float)y * 40.f;
			/**********************************************plateforme***********************************************************/
			if (line[x] == 'm') {
				mur.setSize({ 40.f,40.f });
				mur.setTexture(&middleNoLeafPlatform);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			else if (line[x] == 'l') {
				mur.setSize({ 40.f,40.f });
				mur.setTexture(&leftLeafPlatform);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			else if (line[x] == 'r') {
				mur.setSize({ 40.f,40.f });
				mur.setTexture(&rightLeafPlatform);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			else if (line[x] == 'L') {
				mur.setSize({ 40.f,40.f });
				mur.setTexture(&leftRegularPlatform);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			else if (line[x] == 'R') {
				mur.setSize({ 40.f,40.f });
				mur.setTexture(&rightRegularPlatform);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			else if (line[x] == 'M') {
				mur.setSize({ 40.f,40.f });
				mur.setTexture(&middleRegularPlatform);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			/****************************************************plateforme mobile**********************************************/

			else if (line[x] == '*') {
				plateformeTest.push_back(new Plateforme(posX,posY,4, middleNoLeafPlatform));
			}
			else if (line[x] == '+') {
				plateformeTest.push_back(new Plateforme(posX, posY, 1, middleNoLeafPlatform));
			}
			else if (line[x] == '-') {
				plateformeTest.push_back(new Plateforme(posX, posY, 2, middleNoLeafPlatform));
			}
			else if (line[x] == '/') {
				plateformeTest.push_back(new Plateforme(posX, posY, 3, middleNoLeafPlatform));
			}
			/***************************************end level*******************************************************************/
			else if (line[x] == 'E') {
				endLevel.setSize({ 40.f,40.f });
				endLevel.setFillColor(Color::Green);
				endLevel.setPosition(posX, posY);
			}
			else if (line[x] == 'F') {
				end.setSize({ 40.f,40.f });
				end.setFillColor(Color::Yellow);
				end.setPosition(posX, posY);
			}
			/********************************************************************ennemie************************************************************/
			else if (line[x] == 'C') {
				m_entityManager->addEnnemy(make_shared<Lampadaire>(Vector2f(posX, posY), players, currentLevel));
			}
			else if (line[x] == 'P') {
				m_entityManager->addEnnemy(make_shared<Petrifeu>(Vector2f(posX, posY), players)); //coriger la vitesse
			}
			else if (line[x] == 'V') {
				m_entityManager->addEnnemy(make_shared<Eolienne>(Vector2f(posX, posY), players, window)); // corriger la poussé
			}
		}
		++y;
	}
}

void Map::drawMap(RenderWindow& window) {
	for (auto& Rectangle : platforms) {
		window.draw(Rectangle);
	}
	for (auto& Plateforme : plateformeTest) {
		window.draw(Plateforme->plat);
	}
	m_entityManager->drawEntities(window);

	window.draw(end);
	window.draw(endLevel);
}