#pragma once

#include "includeAll.hpp"

class Texte {
public:
    Texte(Font typeface, String text, int fontSize, int red, int green, int blue, float xPos, float yPos) : 
        font(typeface), texte(text), tailleChar(fontSize), R(red), G(green), B(blue), X(xPos), Y(yPos) {}
    Text creation() const {
        Text text;
        text.setFont(font);
        text.setString(texte);
        text.setCharacterSize(tailleChar);
        text.setFillColor(Color(R, G, B));
        text.setPosition(X, Y);
        return text;
    }

private:
    Font font;
    string texte;
    int tailleChar;
    int R;
    int G;
    int B;
    float X;
    float Y;
};