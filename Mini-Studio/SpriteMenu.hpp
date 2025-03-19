#pragma once
#include "includeAll.hpp"

class SpriteMenu {
public:
    Font font;
	Sprite sprite;
	Texture texture;

    vector <Sprite> selectSprite;
    Texture selectPlay, selectSettings, selectQuit;
    Sprite selectPlaySprite, selectSettingsSprite, selectQuitSprite;

    vector <Sprite> spriteVBulle;
    Texture bulle1, bulle2, bulle3;
    Sprite spriteBulle1, spriteBulle2, spriteBulle3;

    vector <Sprite> spriteTexte;
    Texture choix1, choix2, choix3;
    Sprite spriteChoix1, spriteChoix2, spriteChoix3;

    vector <Sprite> spritTouche;
    Texture textureTouche, textureTouche1, textureTouche2, textureTouche3;
    Sprite touche, touche1, touche2, touche3;

    void initAllSpriteMenu(RenderWindow& window);
    void setTexture(const string& PNGfile, RenderWindow& window);
    void drawVector(RenderWindow& window);
};
