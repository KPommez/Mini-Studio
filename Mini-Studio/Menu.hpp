#pragma once

#include "Texte.hpp"
#include "Button.hpp"
#include "Game.hpp"

enum MenuState {
    MENU, OPTION, START, WIN, LOOSE
};

class Menu {
public:
    Menu();
    void start(RenderWindow& window);

private:
    void setTexture(const string& PNGfile, RenderWindow& window);
    void drawback(RenderWindow& window);
    void menu(RenderWindow& window);
    void win(RenderWindow& window);
    void loose(RenderWindow& window);
    void option(RenderWindow& window);

private:
    Sprite sprite;
    Texture texture;
    Font font;
    vector<Texte> listeTexte;
    vector<Rectangle> listeRectangle;
    MenuState menuState;
};