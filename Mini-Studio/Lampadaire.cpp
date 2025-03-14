#include "Lampadaire.hpp"

Lampadaire::Lampadaire(Vector2f pos, Player* players) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Red);
	shape.setSize({ 50, 50 });
	currentState = PATROL;
	moveSide = RIGHT;
	
	//lum.setPosition(shape.getPosition());
	lum.setFillColor(Color::Yellow);
}
void Lampadaire::update(const float& deltaTime, RenderWindow& window) {
	
	switch (currentState) {
	case PATROL:
		patrol(deltaTime);
		if (detectPlayer(player->shape.getPosition())) { 
			currentState = CHASE; 
		}
		break;

	case CHASE:
		chase(player->shape.getPosition(), deltaTime);
		if (!detectPlayer(player->shape.getPosition())) {
			currentState = PATROL;
		}
		break;

	case SEARCH:
		break;

	default:
		break;
	}

	switch(moveSide) {
	case MOVEMENTSIDE::LEFT:
		lum.setPointCount(4);
		lum.setPoint(0, { position.x,position.y  });
		lum.setPoint(1, { position.x ,position.y + 50 });
		lum.setPoint(2, { position.x - 150,position.y + 175 });
		lum.setPoint(3, { position.x - 150,position.y - 125 }); 
		break;

	case MOVEMENTSIDE::RIGHT:
		lum.setPointCount(4);
		lum.setPoint(0, { position.x + 50,position.y });
		lum.setPoint(1, { position.x + 50,position.y + 50 });
		lum.setPoint(2, { position.x + 200,position.y + 175 });
		lum.setPoint(3, { position.x + 200,position.y - 125 });
		break;

	default:
		break;
	}

}
void Lampadaire::chase(Vector2f playerPos, const float& deltaTime) {
	float direction = playerPos.x - position.x;
	float distance = sqrt(direction * direction);

	if (distance > 0) {
		direction /= distance;
		position.x += direction * 2.0f;
	}
	shape.move(direction * 250.f * deltaTime,0);
	position = shape.getPosition();

	if (shape.getGlobalBounds().intersects(player->playerSprite.getGlobalBounds())) {
		player->playerSprite.setPosition(500, 500);
	}
	//lum.move(direction);
}

bool Lampadaire::detectPlayer(Vector2f playerPos) {
	
	if (player->playerSprite.getGlobalBounds().intersects(lum.getGlobalBounds())) {
		
		return true;
	}
	else {
		return false;
	}
}
void Lampadaire::patrol(const float& deltaTime) {
	static int currentWaypoint   = 0;
	static Vector2f waypoints[2] = { Vector2f(position.x+100, position.y), Vector2f(position.x-400, position.y) };
	Vector2f target              = waypoints[currentWaypoint];
	Vector2f direction           = target - position;
	float distance               = sqrt(direction.x * direction.x + direction.y * direction.y);

	switch (currentWaypoint) {
	case 0: 
		moveSide = RIGHT;
		break;
	case 1:
		moveSide = LEFT;
		break;
	default:
		break;
	}

	if (distance < 5.0f) {
		currentWaypoint = (currentWaypoint + 1) % 2;
	}
	else {
		direction /= distance;
		position += direction * 2.0f;
	}

	shape.move(direction * 100.f * deltaTime);
	position = shape.getPosition();
	//lum.move(direction);
}

void Lampadaire::draw(RenderWindow& window) {
	window.draw(shape);
	window.draw(lum);
}