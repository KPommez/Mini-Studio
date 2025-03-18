#pragma once

#include "Texte.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "SpriteMenu.hpp"


enum MenuState {
    MENU, OPTION, START, WIN, LOOSE, PAUSE
};

class Menu {
public:
    Menu(RenderWindow& window);
    void start(RenderWindow& window);
public:

    int posButon;
    bool hasStarted = false;


private:
    Clock menuNavigationClock;
    //void setTexture(const string& PNGfile, RenderWindow& window);
    void drawback(RenderWindow& window);
    void menu(RenderWindow& window);
    void win(RenderWindow& window);
    void loose(RenderWindow& window);
    void option(RenderWindow& window);
    
    //vector <Rectangle*> hitbox;
    vector <Texte*> listeText;

    Game game;
    SpriteMenu spriteMenu;
    vector<Texte> listeTexte;
    vector<Rectangle> listeRectangle;
    MenuState menuState;
};