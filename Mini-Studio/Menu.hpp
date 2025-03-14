#pragma once

#include "Texte.hpp"
#include "Button.hpp"
#include "Game.hpp"

enum MenuState {
    MENU, OPTION, START, WIN, LOOSE, PAUSE
};

class Menu {
private:
    vector <Rectangle*> hitbox;
    vector <Texte*> listeText;

    vector <Sprite> spriteMenu;

    Texture playButton, settingsButton, quitButton;
    Sprite spritePlay, spriteSettings, spriteQuit;

public:
    Sprite sprite;
    Texture texture;
    Menu(RenderWindow& window);

    int posButon;
    bool hasStarted = false;

    void setTexture(const string& PNGfile);
    void drawback(RenderWindow& window);
    void start(RenderWindow& window);
    void menu(RenderWindow& window);
    void win(RenderWindow& window);
    void loose(RenderWindow& window);
    void option(RenderWindow& window);

    Font font;
    Game game;

    vector<Texte> listeTexte;
    vector<Rectangle> listeRectangle;

    MenuState menuState;
};