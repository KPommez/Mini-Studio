#pragma once

#include "Texte.hpp"
#include "Button.hpp"
#include "Game.hpp"

enum MenuState {
    MENU, OPTION, START, WIN, LOOSE
};

class Menu {
public:
    //RectangleShape test;
    Sprite sprite;
    Texture texture;
    Menu();

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