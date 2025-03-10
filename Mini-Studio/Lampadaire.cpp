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
	switch (currentState) {
	case PATROL:
		patrol();
		if (detectPlayer(playerPos)) currentState = CHASE; cout << "detected";
		break;

	case CHASE:
		chase(playerPos);
		if (!detectPlayer(playerPos)) {
			currentState = SEARCH;
		}
		break;

	case SEARCH:
		break;
	}
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
	
	
}
void Lampadaire::chase(sf::Vector2f playerPos) {
	sf::Vector2f direction = playerPos - position;
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance > 0) {
		direction /= distance;
		position += direction * 2.0f;
	}
}
void Lampadaire::draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(lum);
}
bool Lampadaire::detectPlayer(sf::Vector2f playerPos) {
	float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
	return (distance < detectionRadius);
}
void Lampadaire::patrol() {
	static int currentWaypoint = 0;
	static sf::Vector2f waypoints[2] = { sf::Vector2f(100, 300), sf::Vector2f(500, 300) };
	sf::Vector2f target = waypoints[currentWaypoint];
	sf::Vector2f direction = target - position;
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 5.0f) {
		currentWaypoint = (currentWaypoint + 1) % 2;
	}
	else {
		direction /= distance;
		position += direction * 2.0f;
	}
	shape.move(direction);
	lum.move(direction);
}