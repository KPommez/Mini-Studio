#pragma once

#include "includeAll.hpp"
//#include "Window.hpp"

enum ButtonID {
	NOTHING, PLAY, QUIT, SETTINGS, BACK
};

class Button {
private:
	Vector2f position;
	ButtonID id;
	Color color;
	RectangleShape hitbox;	
	Vector2f textureCoords;
	Sprite* sprite;

public:
	Button(Vector2f position_, ButtonID id_, Color color_, RectangleShape hitbox_, Vector2f textureCoords_);
	Button(Vector2f position_, ButtonID id_, Color color_, RectangleShape hitbox_);

	virtual ~Button();

	ButtonID getId() const { return id; }
	Vector2f getposition() const { return position; }
	RectangleShape getHitbox() const { return hitbox; }
	Vector2f getTextureCoords() const { return textureCoords; }
	Sprite* getSprite() const { if (sprite) { return sprite; } return nullptr; }
	void setSprite(Sprite* newSprite) { sprite = newSprite; }
	void setTextureCoords(Vector2f newCoords) { sprite = nullptr; textureCoords = newCoords; }

};

class MenuManager {
private:
	vector <Button*> buttons;
	
	sf::Sprite* background;

	sf::Texture smallButtonsTexture;
	sf::Texture bigButtonsTexture;

	sf::Texture menuTexture;
	sf::Texture optionsTexture;
	sf::Texture levelsSelectTexture;
	sf::Texture victoryTexture;
	sf::Texture losingTexture;


	vector <ButtonID> smallButtons;

public: 
	MenuManager();

	bool loadTexture();
	void setSprites();

	void addBackground(sf::Texture& texture);
	void openGame();
	void openMenu();
	void openOption();
	void openVictory();
	void openLose();
	void drawButtons(RenderWindow& window);
	void activateButtons(ButtonID id);
	ButtonID isMouseOnButton(Vector2i mousePosition);
};