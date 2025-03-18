#include "Lampadaire.hpp"
#include "Player.hpp"
#include "ParralaxBackground.hpp"

Lampadaire::Lampadaire(Vector2f pos, Player* players, ParralaxBackground* _currentLevel) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Red);
	shape.setSize({ 50, 50 });
	currentState = PATROL;
	moveSide = LEFT; 
	currentWaypoint = 0;
	waypoints[0] = Vector2f(position.x + 100, position.y);
	waypoints[1] = Vector2f(position.x - 400, position.y);

	
	
	currentLevel = _currentLevel;
	//lum.setPosition(shape.getPosition());
	lum.setFillColor(Color::Yellow);
}
void Lampadaire::update(const float& deltaTime, RenderWindow& window) {
	if (shape.getGlobalBounds().intersects(player->playerSprite.getGlobalBounds())) {
		player->playerSprite.setPosition(player->playerSprite.getPosition().x, 100);
	}
	switch (currentState) {
	case PATROL:
		patrol(deltaTime);
		if (detectPlayer(player->sprite.getPosition())) { 
			currentState = CHASE; 
		}
		break;

	case CHASE:
		chase(player->sprite.getPosition(), deltaTime, window);
		if (!detectPlayer(player->sprite.getPosition())) {
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
		lum.setPoint(2, { position.x - 350,position.y + 125 });
		lum.setPoint(3, { position.x - 350,position.y - 75 }); 
		break;

	case MOVEMENTSIDE::RIGHT:
		lum.setPointCount(4);
		lum.setPoint(0, { position.x + 50,position.y });
		lum.setPoint(1, { position.x + 50,position.y + 50 });
		lum.setPoint(2, { position.x + 400,position.y + 125 });
		lum.setPoint(3, { position.x + 400,position.y - 75 });
		break;

	default:
		break;

	}

}
void Lampadaire::chase(Vector2f playerPos, const float& deltaTime, RenderWindow& window) {
	float direction = playerPos.x - position.x;
	float distance = sqrt(direction * direction);

	if (distance > 0) {
		direction /= distance;
		position.x += direction * 2.0f;
	}
	switch (moveSide) {
	case MOVEMENTSIDE::LEFT:
		shape.move(direction * 250.f * deltaTime, 0);
		break;
	case MOVEMENTSIDE::RIGHT:
		shape.move(-direction * 250.f * deltaTime, 0);
		break;
	};
	position = shape.getPosition();

	if (shape.getGlobalBounds().intersects(player->playerSprite.getGlobalBounds())) {
		player->playerSprite.setPosition(1500, 500);
		if (player->isGoingRight) {
			player->isGoingLeft = true;
			player->isGoingRight = false;
		}
		currentLevel->moveLayers(deltaTime, window, *player);
		player->isGoingLeft = false;
		player->isGoingRight = true;
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
	
	Vector2f target              = waypoints[currentWaypoint];
	Vector2f direction           = target - position;
	float distance               = sqrt(direction.x * direction.x + direction.y * direction.y);
	cout << currentWaypoint << "  " << target.x << " " << target.y << endl;
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