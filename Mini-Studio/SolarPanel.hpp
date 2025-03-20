#include "Entity.hpp"
#include "Player.hpp"

class SolarPanel : public Entity {
public:
	SolarPanel(Vector2f pos, Player* players, RenderWindow& window);
	void update(const float& deltaTime, RenderWindow& window) override;
	void draw(RenderWindow& window) override;
	int faisceau;
	Player* player;
	bool isOn;
	Sprite spriteOff, spriteOn, spriteGlobal;
	Texture textureOff, textureOn;
	Vector2f position; // Position of the solar panel
};