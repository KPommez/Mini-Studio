#pragma once

#include "Texte.hpp"
#include "Button.hpp"
#include "Game.hpp"

enum MenuState {
    MENU, OPTION, START, WIN, LOOSE, PAUSE
};

class Menu {
public:
    Menu(RenderWindow& window);
    void start(RenderWindow& window);

public:
    Sprite sprite;
    Texture texture;
    int posButon;
    bool hasStarted = false;

private:
    void setTexture(const string& PNGfile, RenderWindow& window);
    void drawback(RenderWindow& window);
    void menu(RenderWindow& window);
    void win(RenderWindow& window);
    void loose(RenderWindow& window);
    void option(RenderWindow& window);

private:
    vector <Rectangle*> hitbox;
    vector <Texte*> listeText;
    vector <Sprite> spriteMenu;
    Texture playButton, settingsButton, quitButton;
    Sprite spritePlay, spriteSettings, spriteQuit;
    Font font;
    Game game;
    vector<Texte> listeTexte;
    vector<Rectangle> listeRectangle;
    MenuState menuState;
};