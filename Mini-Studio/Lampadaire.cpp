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
	moveSide = RIGHT; 
	currentWaypoint = 0;
	waypoints[0] = Vector2f(position.x + 100, position.y);
	waypoints[1] = Vector2f(position.x - 400, position.y);
	animationTime = 0;
	spriteChar.setPosition(pos);
	spriteChar.setScale(0.25, 0.25);
	changedSide = false;
	
	isIdlingAnimationStarted = true;
	isAnimationStarted = false;
	
	
	currentLevel = _currentLevel;
	//lum.setPosition(shape.getPosition());
	lum.setFillColor(Color::Yellow);
	loadAssets();
}
void Lampadaire::loadAssets() {
	idleTexture.loadFromFile("Assets/Lampadaire/lamp_idle.png");
	walk1Texture.loadFromFile("Assets/Lampadaire/lamp_walk1.png");
	walk2Texture.loadFromFile("Assets/Lampadaire/lamp_walk2.png");
	
	spriteIdle.setTexture(idleTexture);
	spriteWalk1.setTexture(walk1Texture);
	spriteWalk2.setTexture(walk2Texture);

	spriteIdle.setScale(0.25, 0.25);
	spriteWalk1.setScale(0.25, 0.25);
	spriteWalk2.setScale(0.25, 0.25);

	ennemySprites.reserve(3);
	ennemySprites.emplace_back(spriteIdle);
	ennemySprites.emplace_back(spriteWalk1);
	ennemySprites.emplace_back(spriteWalk2);

	
}
void Lampadaire::anim(const float& deltaTime) {
	
	animationTime += deltaTime;
	Vector2f scale = sprite.getScale();
	
		if (!isAnimationStarted) {
			isAnimationStarted = true;
			isIdlingAnimationStarted = false;
			animationTime = 0.f;
		}
		// Restart the animation loop after 0.5 seconds
		if (animationTime > 0.75f) {
			animationTime = 0.f;
		}
		else if (animationTime < .25f) {
			ennemySprites[0].setPosition(spriteChar.getPosition());
			spriteChar = ennemySprites[0];
		}
		else if (animationTime < .5f) {
			ennemySprites[1].setPosition(spriteChar.getPosition());
			spriteChar = ennemySprites[1];
		}
		else {
			ennemySprites[2].setPosition(spriteChar.getPosition());
			spriteChar = ennemySprites[2];
		}
	
}
void Lampadaire::update(const float& deltaTime, RenderWindow& window) {
	//if (changedSide) {
	//	cout << "sprite scaled" << endl;
	//	spriteChar.scale(-1, 1);
	//}
	anim(deltaTime);
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
			changedSide = false; 
			for (auto& e : ennemySprites)
				e.scale(-1, 1);
			spriteChar.move(-spriteChar.getGlobalBounds().width, 0);
			
		}
		break;
	case 1:
		moveSide = LEFT;

		if (!changedSide) {
			for (auto& e : ennemySprites)
				e.scale(-1, 1);
			spriteChar.move(spriteChar.getGlobalBounds().width, 0);
			changedSide = true;
		}
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