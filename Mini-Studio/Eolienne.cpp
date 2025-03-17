#include "Eolienne.hpp"

Eolienne::Eolienne(Vector2f pos, Player* players) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Cyan);
	shape.setSize(Vector2f(50.0f, 50.0f));
	
	currentState = PATROL;
	moveSide = LEFT;
	zone.setFillColor(Color::White);
	zone.setSize({ 1920, 50 });
}

void Eolienne::update(const float& deltaTime, RenderWindow& window) {
	switch (currentState) {
	case PATROL:
		
		if (clock.getElapsedTime().asSeconds() < 10) {
		
			patrol(deltaTime);
			
		}
		else {
			clock.restart();
			currentState = PUSH;
		}
		break;

	case PUSH:
		if (clock.getElapsedTime().asSeconds() < 1.5) {
			cout << "pushing" << endl;
			push(window);
		}
		else {
			clock.restart();
			currentState = PATROL;
		}
		break;

	}
	
	//shape.setPosition({ window.getView().getCenter().x + 750,window.getView().getCenter().y  });
	switch (moveSide)
	{
	case LEFT:
		zone.setPosition(shape.getPosition().x - 1920, shape.getPosition().y);
		break;
	case RIGHT:
		zone.setPosition(shape.getPosition().x + 50, shape.getPosition().y);
		break;
	default:
		break;
	}
	
}

void Eolienne::draw(RenderWindow& window) {
	window.draw(shape);
	window.draw(zone);
}
void Eolienne::push(RenderWindow& window) {
	shape.setPosition(player->playerSprite.getPosition());
	if (player->playerSprite.getGlobalBounds().intersects(zone.getGlobalBounds())) {
		player->playerSprite.move(-2.f, 0.0f);
	}
}
void Eolienne::patrol(const float& deltaTime) {
	
	static int currentWaypoint = 0;
	static sf::Vector2f waypoints[3] = { sf::Vector2f(shape.getPosition().x + 100, 300), sf::Vector2f(shape.getPosition().x, 900), sf::Vector2f(shape.getPosition().x + 50, 600)};
	sf::Vector2f target = waypoints[currentWaypoint];
	sf::Vector2f direction = target - position;
	float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (distance < 5.0f) {
		currentWaypoint = (currentWaypoint + 1) % 3;
	}
	else {
		direction /= distance;
		position += direction * 2.0f;
	}
	shape.move(direction * 100.f * deltaTime);
	position = shape.getPosition();
}