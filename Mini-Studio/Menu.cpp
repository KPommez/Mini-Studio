#include "Menu.hpp"


Menu::Menu(RenderWindow& window) : game(window) {
	menuState = MENU;
	posButon = 3;
	spriteMenu.initAllSpriteMenu(window);
}


void Menu::start(RenderWindow& window) {
	// gestion du int des boutons 
	if (Joystick::getAxisPosition(0, Joystick::PovY) >= 80 && menuNavigationClock.getElapsedTime().asSeconds() > 0.2) {
		menuNavigationClock.restart();
		posButon++;
	}
	else if (Joystick::getAxisPosition(0, Joystick::PovY) <= -80 && menuNavigationClock.getElapsedTime().asSeconds() > 0.2) {
		menuNavigationClock.restart();
		posButon--;
	}
	if (posButon >= 4) {
		posButon = 0;
	}
	else if (posButon <= -1) {
		posButon = 0;
	}
	//cout << game.getRunning();
	if (game.lose == true)
	{
		menuState = LOOSE;
	}
	switch (menuState) {
	case MENU:
		menu(window);
		break;
	case OPTION:
		option(window);
		break;
	case START:
		game.player.hitcount = 0;
		game.Run(window);
		exit(0);
		menuState = MENU;
		break;
	case WIN:
		win(window);
		break;
	case LOOSE:
		loose(window);
		break;
	default:
		break;
	}
}

void Menu::menu(RenderWindow& window) {
	window.clear(Color::Black);

	drawback(window);
	spriteMenu.drawVector(window);
	spriteMenu.setTexture("assets/backMenu/Menu_jeu_fond.png", window);

	Vector2i n_mouse = Mouse::getPosition(window);
	Vector2f mouse = { (float)n_mouse.x, (float)n_mouse.y };
	Event gameEvent;
	while (window.pollEvent(gameEvent)) {

		if (gameEvent.type == Event::Closed)
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::K))
			window.close();

		if (spriteMenu.spriteVBulle[0].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 2) { //Play
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 255));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 0));
			spriteMenu.selectSprite[2].setColor(Color(255, 255, 255, 0));
		}
		else if (spriteMenu.spriteVBulle[1].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 1) { //Settings
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 0));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 255));
			spriteMenu.selectSprite[2].setColor(Color(255, 255, 255, 0));
		}
		else if (spriteMenu.spriteVBulle[2].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 0) { //Quit
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 0));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 0));
			spriteMenu.selectSprite[2].setColor(Color(255, 255, 255, 255));
		}
		else if (posButon == 3) {
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 0));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 0));
			spriteMenu.selectSprite[2].setColor(Color(255, 255, 255, 0));
		}

		if (spriteMenu.spriteVBulle[0].getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0,1) && posButon == 2) {
			listeTexte.clear();
			listeRectangle.clear();
			menuState = START;
			game.setRunning(true);
		}
		if (spriteMenu.spriteVBulle[1].getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1) && posButon == 1) {
			listeTexte.clear();
			listeRectangle.clear();
			menuState = OPTION;
		}
		if (spriteMenu.spriteVBulle[2].getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1) && posButon == 0) {
			window.close();
		}
	}
	window.display();
}


void Menu::option(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();
	drawback(window);

	Texte retour(spriteMenu.font, "Retour", 40, 0, 0, 0, 1700, 1000);
	listeTexte.push_back(retour);

	///////////////////////////////////////////////////////////////////


	Rectangle RecRetour(155, 55, 1690, 1000, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	listeRectangle.push_back(RecRetour);

	for (auto& Rectangle : listeRectangle) {
		window.draw(Rectangle.creation());
	}

	for (auto& Texte : listeTexte) {
		window.draw(Texte.creation());
	}

	for (auto& Touche : spriteMenu.spritTouche) {
		window.draw(Touche);
	}

	window.display();

	Event gameEvent;
	while (window.pollEvent(gameEvent)) {
		if (gameEvent.type == Event::Closed)
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::K))
			window.close();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (Mouse::getPosition(window).x > RecRetour.posX && Mouse::getPosition(window).y > RecRetour.posY && Mouse::getPosition(window).x < RecRetour.posX + RecRetour.tailleX && Mouse::getPosition(window).y < RecRetour.posY + RecRetour.tailleY) {
				listeTexte.clear();
				listeRectangle.clear();
				menuState = MENU;
			}
		}
		else if (Joystick::isButtonPressed(0, 2)) {
			listeTexte.clear();
			listeRectangle.clear();
			menuState = MENU;
		}
	}
}

void Menu::win(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();

	Texte Titre(spriteMenu.font, "Vous avez .... gagné ??", 80, 255, 0, 0, 480, 255);
	listeTexte.push_back(Titre);

	Texte start(spriteMenu.font, "Restart", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(spriteMenu.font, "Quitter", 40, 0, 0, 0, 880, 550);
	listeTexte.push_back(touche);

	Rectangle RecTitre(170, 70, 870, 400, 255, 255, 255);
	listeRectangle.push_back(RecTitre);

	Rectangle RecTouche(150, 70, 870, 540, 255, 255, 255);
	listeRectangle.push_back(RecTouche);

	for (auto& Rectangle : listeRectangle) {
		window.draw(Rectangle.creation());
	}

	for (auto& Texte : listeTexte) {
		window.draw(Texte.creation());
	}
	window.display();

	Event gameEvent;
	while (window.pollEvent(gameEvent)) {
		if (gameEvent.type == Event::Closed)
			window.close();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (Mouse::getPosition(window).x > RecTitre.posX && Mouse::getPosition(window).y > RecTitre.posY && Mouse::getPosition(window).x < RecTitre.posX + RecTitre.tailleX && Mouse::getPosition(window).y < RecTitre.posY + RecTitre.tailleY) {
				listeTexte.clear();
				listeRectangle.clear();
				menuState = START;

			}
			if (Mouse::getPosition(window).x > RecTouche.posX && Mouse::getPosition(window).y > RecTouche.posY && Mouse::getPosition(window).x < RecTouche.posX + RecTouche.tailleX && Mouse::getPosition(window).y < RecTouche.posY + RecTouche.tailleY) {
				listeTexte.clear();
				listeRectangle.clear();
				menuState = MENU;
			}
		}
	}

}

void Menu::loose(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();

	Texte Titre(spriteMenu.font, "Vous avez perdu, vous n'êtes pas le héros", 80, 255, 0, 0, 180, 255);
	listeTexte.push_back(Titre);

	Texte start(spriteMenu.font, "Restart", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(spriteMenu.font, "Quitter", 40, 0, 0, 0, 880, 550);
	listeTexte.push_back(touche);

	Rectangle RecTitre(170, 70, 870, 400, 255, 255, 255);
	listeRectangle.push_back(RecTitre);

	Rectangle RecTouche(150, 70, 870, 540, 255, 255, 255);
	listeRectangle.push_back(RecTouche);

	for (auto& Rectangle : listeRectangle) {
		window.draw(Rectangle.creation());
	}

	for (auto& Texte : listeTexte) {
		window.draw(Texte.creation());
	}

	window.display();

	Event gameEvent;
	while (window.pollEvent(gameEvent)) {
		if (gameEvent.type == Event::Closed)
			window.close();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (Mouse::getPosition(window).x > RecTitre.posX && Mouse::getPosition(window).y > RecTitre.posY && Mouse::getPosition(window).x < RecTitre.posX + RecTitre.tailleX && Mouse::getPosition(window).y < RecTitre.posY + RecTitre.tailleY) {
				listeTexte.clear();
				listeRectangle.clear();
				menuState = MENU;
				game.lose = false;
			}
			if (Mouse::getPosition(window).x > RecTouche.posX && Mouse::getPosition(window).y > RecTouche.posY && Mouse::getPosition(window).x < RecTouche.posX + RecTouche.tailleX && Mouse::getPosition(window).y < RecTouche.posY + RecTouche.tailleY) {
				window.close();
			}
		}
	}
}

void Menu::drawback(RenderWindow& window) {
	window.draw(spriteMenu.sprite);
}