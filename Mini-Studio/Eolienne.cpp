#include "Eolienne.hpp"

Eolienne::Eolienne(Vector2f pos, Player* players, RenderWindow& window) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Cyan);
	shape.setSize(Vector2f(50.0f, 50.0f));
	
	currentState = PATROL;
	moveSide = LEFT;
	zone.setFillColor(Color::Transparent);
	zone.setSize({ 5.f * window.getSize().x, 2.f * window.getSize().y});
}

void Eolienne::update(const float& deltaTime, RenderWindow& window) {
	switch (currentState) {
	case PATROL:
		shape.setPosition({ window.getView().getCenter().x + 750,window.getView().getCenter().y - 300 });
		if (clock.getElapsedTime().asSeconds() < 10) {
		
			patrol(deltaTime);
			
		}
		else {
			clock.restart();
			currentState = PUSH;
		}
		break;

	case PUSH:
		player->isGoingLeft = true;
		player->isIdling = false;
		if (clock.getElapsedTime().asSeconds() < 1.5) {
			push(window, deltaTime);
		}
		else {
			clock.restart();
			currentState = PATROL;
		}
		break;

	}
	
	
	switch (moveSide)
	{
	case LEFT:
		zone.setPosition(shape.getPosition().x - zone.getSize().x, shape.getPosition().y);
		break;
	case RIGHT:
		zone.setPosition(shape.getPosition().x + zone.getSize().y, shape.getPosition().y);
		break;
	default:
		break;
	}
	
}

void Eolienne::draw(RenderWindow& window) {
	window.draw(shape);
	window.draw(zone);
}
void Eolienne::push(RenderWindow& window, const float& deltaTime) {
	shape.setPosition(player->playerSprite.getPosition().x +300,player->playerSprite.getPosition().y);
	if (player->playerSprite.getGlobalBounds().intersects(zone.getGlobalBounds())) {
		player->playerSprite.move(-800.f * deltaTime, 0.0f);
	}
}
void Eolienne::patrol(const float& deltaTime) {
	
	static int currentWaypoint = 0;
	static sf::Vector2f waypoints[3] = { 
		sf::Vector2f(shape.getPosition().x + 100, 300), 
		sf::Vector2f(shape.getPosition().x, 900), 
		sf::Vector2f(shape.getPosition().x + 50, 600)
	};

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