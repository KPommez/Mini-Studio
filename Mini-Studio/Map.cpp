#include "Map.hpp"

Map::Map() {
	posX = 0;
	posY = 0;
}

void Map::loadMap(const string& filename, RenderWindow& window) {
	ifstream file(filename);

	string line;
	float y = 0.f;

	/*while (getline(file, line)) {
		for (int x = 0; x < line.size(); ++x) {
			posX = (float)x * 40.f;
			posY = (float)y * 40.f;
			if (line[x] == '/') {
				mur.setSize({ 40.f,40.f });
				mur.setFillColor(Color::Blue);
				mur.setPosition(posX, posY);
				listeMur.push_back(mur);
			}
		}
		++y;
	}*/

	rectNormalGravity.setFillColor(sf::Color::Green);
	rectNormalGravity.setSize(Vector2f(window.getSize().x / 2.f, window.getSize().y));
	rectNormalGravity.setPosition(Vector2f(0, 0));

	rectInvertedGravity.setFillColor(sf::Color::Red);
	rectInvertedGravity.setSize(Vector2f(window.getSize().x / 2.f, window.getSize().y));
	rectInvertedGravity.setPosition(Vector2f(window.getSize().x / 2.f, 0));

	listeMur.push_back(rectNormalGravity);
	listeMur.push_back(rectInvertedGravity);
}

void Map::drawMap(RenderWindow& window) {
	for (auto& Rectangle : listeMur) {
		window.draw(Rectangle);
	}
}