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

    if (State == 1) {
        wayPoint1 = posX + 100;
        wayPoint2 = posX - 50;
        deplacementX = 1;
        deplacementY = 0;

    }
    else if (State == 2) {
        wayPoint1 = posX - 100;
        wayPoint2 = posX +50;
        deplacementX = -1;
        deplacementY = 0;
     
    }
    else if (State == 3) {
        wayPoint1 = posY + 100;
        wayPoint2 = posY -50;
        deplacementX = 0;
        deplacementY = 1;
       
    }
    else if (State == 4) {
        wayPoint1 = posY - 100;
        wayPoint2 = posY +50;
        deplacementX = 0;
        deplacementY = -1;
      
    }
}

void Plateforme::platUpdate(const float& deltatime) {

    if (State == 1) {
        if (plat.getPosition().x >= wayPoint1) {
            plat.setPosition(wayPoint1, plat.getPosition().y);
            deplacementX *= -1;
        }
        else if (plat.getPosition().x <= wayPoint2) {
            plat.setPosition(wayPoint2, plat.getPosition().y);
            deplacementX *= -1;
        }
        plat.move(deplacementX * deltatime * 100.0f, 0);
    }
    else if (State == 2) {
        if (plat.getPosition().x <= wayPoint1) {
            plat.setPosition(wayPoint1, plat.getPosition().y);
            deplacementX *= -1;
        }
        else if (plat.getPosition().x >= wayPoint2) {
            plat.setPosition(wayPoint2, plat.getPosition().y);
            deplacementX *= -1;
        }
        plat.move(deplacementX * deltatime * 100.0f, 0);
    }
    else if (State == 3) {
        if (plat.getPosition().y > wayPoint1) {
            plat.setPosition(plat.getPosition().x, wayPoint1);
            deplacementY *= -1;
        }
        else if (plat.getPosition().y < wayPoint2) {
            plat.setPosition(plat.getPosition().x, wayPoint2);
            deplacementY *= -1;
        }
        plat.move(0, deplacementY * deltatime * 100.0f);
    }
    else if (State == 4) {
        if (plat.getPosition().y < wayPoint1) {
            plat.setPosition(plat.getPosition().x, wayPoint1);
            deplacementY *= -1;
        }
        else if (plat.getPosition().y > wayPoint2) {
            plat.setPosition(plat.getPosition().x, wayPoint2);
            deplacementY *= -1;
        }
        plat.move(0, deplacementY * deltatime * 200.0f);
        
    }

}

