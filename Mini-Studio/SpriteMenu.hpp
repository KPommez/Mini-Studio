#pragma once
#include "includeAll.hpp"

class SpriteMenu {
public:
    Font font;
	Sprite sprite;
	Texture texture;

    vector <Sprite> selectSprite;
    Texture selectPlay, selectQuit;
    Sprite selectPlaySprite, selectQuitSprite;

    vector <Sprite> spriteTexte;
    Texture choix1, choix3;
    Sprite spriteChoix1, spriteChoix3;

    Texture bullePlayer, option;
    Sprite spriteBullePlayer, spriteOption;

    vector <Sprite> spriteToucheClavier;
    Texture textureTouche, textureTouche1, textureTouche2, textureTouche3, textureTouche4;
    Sprite touche, touche1, touche2, touche3, touche4;

    vector <Sprite> spriteToucheManette;
    Texture textureToucheManette, textureToucheManette1, textureToucheManette2, textureToucheManette3, textureToucheManette4, textureToucheManette5;
    Sprite toucheManette, toucheManette1, toucheManette2, toucheManette3, toucheManette4, toucheManette5;

    void initAllSpriteMenu(RenderWindow& window);
    void setTexture(const string& PNGfile, RenderWindow& window);
    void drawVector(RenderWindow& window);
};
