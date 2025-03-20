#include "Lampadaire.hpp"
#include "Player.hpp"
#include "ParralaxBackground.hpp"

Lampadaire::Lampadaire(Vector2f pos, Player* players, ParralaxBackground* _currentLevel) {
	player = players;
	position = pos;
	shape.setPosition(pos);
	shape.setFillColor(Color::Transparent);
	shape.setSize({ 375, 125 });
	currentState = PATROL;
	moveSide = LEFT; 
	currentWaypoint = 0;
	waypoints[0] = Vector2f(position.x + 100, position.y);
	waypoints[1] = Vector2f(position.x - 400, position.y);
	spriteTexture.loadFromFile("Assets/Lampadaire/lamp_idle.png");
	spriteChar.setTexture(spriteTexture);
	spriteChar.setPosition(pos);
	spriteChar.setScale(0.25, 0.25);
	changedSide = false;
	
	
	currentLevel = _currentLevel;
	//lum.setPosition(shape.getPosition());
	lum.setFillColor(Color::Yellow);
}
void Lampadaire::update(const float& deltaTime, RenderWindow& window) {
	if (shape.getGlobalBounds().intersects(player->playerSprite.getGlobalBounds())) {
		player->playerSprite.setPosition(500, 500);
		player->hitcount++;
		if (player->isGoingRight) {
			player->isGoingLeft = true;
			player->isGoingRight = false;
		}
		currentLevel->moveLayers(deltaTime, window, *player);
		player->isGoingLeft = false;
		player->isGoingRight = true;

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
		lum.setPoint(0, { position.x+30,position.y +35 });
		lum.setPoint(1, { position.x+30 ,position.y + 90 });
		lum.setPoint(2, { position.x - 350,position.y + 125 });
		lum.setPoint(3, { position.x - 350,position.y - 75 });
		break;

	case MOVEMENTSIDE::RIGHT:
		lum.setPointCount(4);
		lum.setPoint(0, { position.x + 345,position.y + 35 });
		lum.setPoint(1, { position.x + 345,position.y + 90 });
		lum.setPoint(2, { position.x + 775,position.y + 125 });
		lum.setPoint(3, { position.x + 775,position.y - 75 });
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
		spriteChar.move(direction * 250.f * deltaTime, 0);
		break;
	case MOVEMENTSIDE::RIGHT:
		shape.move(-direction * 250.f * deltaTime, 0);
		spriteChar.move(-direction * 250.f * deltaTime, 0);
		break;
	};
	position = shape.getPosition();

	
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
	Vector2f scale = sprite.getScale();
	Vector2f target              = waypoints[currentWaypoint];
	Vector2f direction           = target - position;
	float distance               = sqrt(direction.x * direction.x + direction.y * direction.y);
	//cout << currentWaypoint << "  " << target.x << " " << target.y << endl;
	switch (currentWaypoint) {
	case 0: 
		moveSide = RIGHT;
		if (changedSide) {
			spriteChar.scale(-1, 1);
			spriteChar.move(-spriteChar.getGlobalBounds().width, 0);
		}
		changedSide = false;
		break;
	case 1:
		moveSide = LEFT;
		if (!changedSide) {
			spriteChar.scale(-1, 1);
			spriteChar.move(spriteChar.getGlobalBounds().width, 0);
		}
		changedSide = true;
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
	spriteChar.move(direction * 100.f * deltaTime);
	position = shape.getPosition();
	//lum.move(direction);
}

void Lampadaire::draw(RenderWindow& window) {
	window.draw(shape);
	window.draw(lum);
	window.draw(spriteChar);
}