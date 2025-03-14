#include "Menu.hpp"


Menu::Menu(RenderWindow& window) : game(window) {
	if (!font.loadFromFile("assets/font/Minecraft.ttf") || 
		!playButton.loadFromFile("assets/backMenu/texte.png") ||
		!settingsButton.loadFromFile("assets/backMenu/texte1.png") ||
		!quitButton.loadFromFile("assets/backMenu/texte2.png"));
	{}
	menuState = MENU;

	spritePlay.setTexture(playButton);
	spriteSettings.setTexture(settingsButton);
	spriteQuit.setTexture(quitButton);

	spritePlay.setScale(0.5f, 0.5f);
	spriteSettings.setScale(0.5f, 0.5f);
	spriteQuit.setScale(0.5f, 0.5f);

	spritePlay.setPosition(770, 250);
	spriteSettings.setPosition(770, 650);
	spriteQuit.setPosition(675, 450);


}

void Menu::setTexture(const string& PNGfile, RenderWindow& window)
{
	if (texture.loadFromFile(PNGfile))
	{
		sprite.setTexture(texture);
		Vector2u textureSize = texture.getSize();
		float scaleX = static_cast<float>(window.getSize().x) / textureSize.x;
		float scaleY = static_cast<float>(window.getSize().y) / textureSize.y;
		sprite.setScale(scaleX, scaleY);
	}
}

void Menu::start(RenderWindow& window) {
	switch (menuState) {
	case MENU:
		menu(window);
		break;
	case OPTION:
		option(window);
		break;
	case START:
		game.Run(window);
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

	bool hasStarted = false;

	spriteMenu.push_back(spritePlay);
	spriteMenu.push_back(spriteSettings);
	spriteMenu.push_back(spriteQuit);



	hitbox.push_back(new Rectangle(120, 70, 870, 400, 255, 255, 255));
	hitbox.push_back(new Rectangle(190, 70, 870, 540, 255, 255, 255));
	hitbox.push_back(new Rectangle(130, 70, 870, 680, 255, 255, 255));

	listeText.push_back(new Texte(font, "try game", 80, 255, 0, 0, 550, 150));
	listeText.push_back(new Texte(font, "Start", 40, 0, 0, 0, 880, 410));
	listeText.push_back(new Texte(font, "Touches", 40, 0, 0, 0, 880, 550));
	listeText.push_back(new Texte(font, "Partir", 40, 0, 0, 0, 880, 690));



		window.clear(Color::Black);
	
		setTexture("assets/backMenu/menutel.png", window);
		drawback(window);

		for (auto& button : spriteMenu) {
			window.draw(button);
		}

		for (auto& Texte : listeText) {
			window.draw(Texte->creation());
		}

		window.display();

		Vector2i mouse = Mouse::getPosition(window);
		Event gameEvent;
		while (window.pollEvent(gameEvent)) {
			if (gameEvent.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::K))
				window.close();

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (spriteMenu[0].getGlobalBounds().contains(mouse.x,mouse.y)) {
					listeTexte.clear();
					listeRectangle.clear();
					menuState = START;
					hasStarted = true;
					game.setRunning(true);
				}
				if (spriteMenu[1].getGlobalBounds().contains(mouse.x, mouse.y)) {
					listeTexte.clear();
					listeRectangle.clear();
					menuState = OPTION;
				}
				if (spriteMenu[2].getGlobalBounds().contains(mouse.x, mouse.y)) {
					window.close();
				}
			}
			if (Joystick::getAxisPosition(0, Joystick::PovY) >= 10) {
				posButon++;
			}
			else if (Joystick::getAxisPosition(0, Joystick::PovY) <= -10) {
				posButon--;
			}
		}
		hitbox.clear();
		listeText.clear();

		for (auto& Rectangle : hitbox) {
			delete Rectangle;
		}
		for (auto& Texte : listeText) {
			delete Texte;
		}

	}


void Menu::option(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();
	setTexture("assets/backMenu/menu.png", window);
	drawback(window);

	Texte retour(font, "Retour", 40, 0, 0, 0, 1700, 1000);
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
	}
}

void Menu::win(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();

	Texte Titre(font, "Vous avez .... gagné ??", 80, 255, 0, 0, 480, 255);
	listeTexte.push_back(Titre);

	Texte start(font, "Restart", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(font, "Quitter", 40, 0, 0, 0, 880, 550);
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

	Texte Titre(font, "Vous avez perdu, vous n'êtes pas le héros", 80, 255, 0, 0, 180, 255);
	listeTexte.push_back(Titre);

	Texte start(font, "Restart", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(font, "Quitter", 40, 0, 0, 0, 880, 550);
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

void Menu::drawback(RenderWindow& window) {
	window.draw(sprite);
}