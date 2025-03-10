#include "Entity.hpp"

class Lampadaire : public Entity
{
public:
	Lampadaire(Vector2f pos);
	
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void chase(sf::Vector2f playerPos);
	Vector2f position;
	Vector2f playerPos;
	float detectionRadius;
	bool detectPlayer(sf::Vector2f playerPos);
	void patrol();
	ConvexShape lum;
	enum State { PATROL, CHASE, SEARCH };
	State currentState;
	enum  MOVEMENTSIDE
	{
		LEFT,
		RIGHT
	};
	MOVEMENTSIDE moveSide;
private:

};

