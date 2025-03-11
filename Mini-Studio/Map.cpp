#include "Map.hpp"

Map::Map() {
	posX = 0;
	posY = 0;
}

void Map::loadMap(const string& filename) {
	ifstream file(filename);

	string line;
	float y = 0.f;

	while (getline(file, line)) {
		for (int x = 0; x < line.size(); ++x) {
			posX = (float)x * 40.f;
			posY = (float)y * 40.f;
			if (line[x] == '/') {
				mur.setSize({ 40.f,40.f });
				mur.setFillColor(Color::Blue);
				mur.setPosition(posX, posY);
				platforms.push_back(mur);
				
			}
		}
		++y;
	}

}

void Map::drawMap(RenderWindow& window) {
	for (auto& Rectangle : platforms) {
		window.draw(Rectangle);
	}
}