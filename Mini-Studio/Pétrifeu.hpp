#pragma once

#include "Player.hpp"

class Player;
class Petrifeu : public Entity {
public:
	Petrifeu(Vector2f pos, Player* players);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;

private:
	void patrol(const float& deltaTime);
	void change();
private:
	Player* player;
	Clock clock;
	enum FeuColor { RED, GREEN };	
	FeuColor feucolor;
	Vector2f position;
};