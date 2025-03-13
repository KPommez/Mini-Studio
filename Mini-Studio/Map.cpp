#include "Map.hpp"

Map::Map() {
	posX = 0;
	posY = 0;
	loadAllMaps();
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

void Map::loadMap(const string& filename) {
	plateformeTest.clear();
	platforms.clear();
	ifstream file(filename);

	string line;
	float y = 0.f;

	while (getline(file, line)) {
		for (size_t x = 0; x < line.size(); ++x) {
			posX = (float)x * 40.f;
			posY = (float)y * 40.f;
			if (line[x] == '/') {
				mur.setSize({ 40.f,40.f });
				mur.setFillColor(Color::Blue);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
			}
			else if (line[x] == '*') {
				plateformeTest.push_back(new Plateforme(posX,posY,1));
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
}