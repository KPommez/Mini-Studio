#include "Pétrifeu.hpp"

Petrifeu::Petrifeu(Vector2f pos, Player* players) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	
	shape.setSize({ 50, 50 });
	clock.restart();
	feucolor = RED;
}
void Petrifeu::update(const float& deltaTime, RenderWindow& window) {
	shape.setPosition({ window.getView().getCenter().x+500,window.getView().getCenter().y - 500 });
	change();
	
}
void Petrifeu::change() {
	int random;
	switch (feucolor) {
	case GREEN:
		shape.setFillColor(Color::Green);
		random = rand() % 3 + 1;

		switch (random) {
		case 1:
			if (clock.getElapsedTime().asSeconds() > 3) {

				cout << "Partie 1" << endl;

				clock.restart();
				feucolor = RED;
			}
			break;
		case 2:
			if (clock.getElapsedTime().asSeconds() > 5) {

				cout << "Partie 2" << endl;

				feucolor = RED;
				clock.restart();

			}
			break;
		case 3:
			if (clock.getElapsedTime().asSeconds() > 8) {

				cout << "Partie 3" << endl;

				feucolor = RED;
				clock.restart();

			}
			break;
		}
		break;
		
	case RED:
		shape.setFillColor(Color::Red);
		if (clock.getElapsedTime().asSeconds() > 2) {
			shape.setFillColor(Color::Green);
			feucolor = GREEN;
			clock.restart();
		}
		break;
	}
}
void Petrifeu::draw(RenderWindow& window) {
	
	window.draw(shape);
}