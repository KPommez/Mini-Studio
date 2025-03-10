#include "Entity.hpp"

class Lampadaire : public Entity
{
public:
	Lampadaire(Vector2f pos);
	
	void update(const float& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	Vector2f position;
	ConvexShape lum;
	enum  MOVEMENTSIDE
	{
		LEFT,
		RIGHT
	};
	MOVEMENTSIDE moveSide;
private:

};

