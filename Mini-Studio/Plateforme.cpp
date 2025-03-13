#include "Plateforme.hpp"

Plateforme::Plateforme(float xPos, float yPos, int state) : posX(xPos), posY(yPos), State(state) {
    wayPoint1 = 0;
    wayPoint2 = 0;
    i = 0;
    creation(xPos, yPos);
}

void Plateforme::creation(float posX,float posY) {
    plat.setSize({ 40.f, 40.f });
    plat.setPosition(posX, posY);
    plat.setFillColor(Color::Red);

    if (State = 1) {
        wayPoint1 = posX + 100;
        point.push_back(wayPoint1);
        wayPoint2 = posX;
        point.push_back(wayPoint2);
    }
    else if (State = 2) {
        wayPoint1 = posX - 100;
        point.push_back(wayPoint1);
        wayPoint2 = posX;
        point.push_back(wayPoint2);
    }
    else if (State = 3) {
        wayPoint1 = posY + 100;
        point.push_back(wayPoint1);
        wayPoint2 = posX;
        point.push_back(wayPoint2);
    }
    else if (State = 4) {
        wayPoint1 = posY - 100;
        point.push_back(wayPoint1);
        wayPoint2 = posX;
        point.push_back(wayPoint2);
    }
}

void Plateforme::platUpdate() {
    if (plat.getPosition().x <= point.at(i)) {
        plat.move(1, 0);
    }
    else {
        plat.move(-1, 0);  
    }
}