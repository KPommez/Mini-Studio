#pragma once

#include "Entity.hpp"

class Player : public Entity {
private:
	// Pour les variables membres plus tard

public:
	Player();

public:
	void update(const float& deltaTime) override;
	void draw(sf::RenderWindow& window) override;
};