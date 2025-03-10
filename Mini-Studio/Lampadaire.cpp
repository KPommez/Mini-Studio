#include "Lampadaire.hpp"

Lampadaire::Lampadaire(Vector2f pos) {
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Blue);
	shape.setSize({ 50, 50 });
	
	 
	//lum.setPosition(shape.getPosition());
	lum.setFillColor(Color::Yellow);
}
void Lampadaire::update(const float& deltaTime, sf::RenderWindow& window) {
	switch(moveSide) {
		case LEFT:
			lum.setPointCount(4);
			lum.setPoint(0, { position.x,position.y + 50 });
			lum.setPoint(1, { position.x + 50,position.y + 50 });
			lum.setPoint(2, { position.x + 150,position.y + 200 });
			lum.setPoint(3, { position.x - 100,position.y + 200 });
		case RIGHT:
			lum.setPointCount(4);
			lum.setPoint(0, { position.x+50,position.y });
			lum.setPoint(1, { position.x+50,position.y + 50 });
			lum.setPoint(2, { position.x + 200,position.y + 200 });
			lum.setPoint(3, { position.x + 200,position.y - 150 });
	}
	shape.move(0, 1);
	lum.move(0, 1);
	
}

void Lampadaire::draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(lum);
}