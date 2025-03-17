#include "Menu.hpp"


Menu::Menu(RenderWindow& window) : game(window) {
	if (!font.loadFromFile("Assets/font/Minecraft.ttf") ||
		!bulle1.loadFromFile("Assets/backMenu/texte.png") ||
		!bulle2.loadFromFile("Assets/backMenu/texte1.png") ||
		!bulle3.loadFromFile("Assets/backMenu/texte2.png") ||
		!choix1.loadFromFile("Assets/backMenu/bouton_play.png") ||
		!choix2.loadFromFile("Assets/backMenu/bouton_options.png") ||
		!choix3.loadFromFile("Assets/backMenu/bouton_quitter.png") ||
		!selectPlay.loadFromFile("Assets/backMenu/selection_bouton.png") ||
		!selectSettings.loadFromFile("Assets/backMenu/selection_bouton.png") ||
		!selectQuit.loadFromFile("Assets/backMenu/selection_bouton.png"))
	{
		cerr << "Assets du menu non totalement charges" << endl;
	}
	menuState = MENU;

	///////////Selection//////////////
	selectPlaySprite.setTexture(selectPlay);
	selectSettingsSprite.setTexture(selectSettings);
	selectQuitSprite.setTexture(selectQuit);

	selectPlaySprite.setScale(0.5f, 0.5f);
	selectSettingsSprite.setScale(0.5f, 0.5f);
	selectQuitSprite.setScale(0.5f, 0.5f);

	selectPlaySprite.setPosition(820, 275);
	selectSettingsSprite.setPosition(750, 475);
	selectQuitSprite.setPosition(840, 700);

	selectPlaySprite.setColor(Color(255, 255, 255, 0));
	selectSettingsSprite.setColor(Color(255, 255, 255, 0));
	selectQuitSprite.setColor(Color(255, 255, 255, 0));

	//////////Bulle/////////////////
	spriteBulle1.setTexture(bulle1);
	spriteBulle2.setTexture(bulle2);
	spriteBulle3.setTexture(bulle3);

	spriteBulle1.setScale(0.5f, 0.5f);
	spriteBulle2.setScale(0.5f, 0.5f);
	spriteBulle3.setScale(0.5f, 0.5f);

	spriteBulle1.setPosition(770, 250);
	spriteBulle2.setPosition(770, 650);
	spriteBulle3.setPosition(675, 450);

	///////////Choix Play/Settings/Quit ////////
	spriteChoix1.setTexture(choix1);
	spriteChoix2.setTexture(choix2);
	spriteChoix3.setTexture(choix3);

	spriteChoix1.setScale(0.5f, 0.5f);
	spriteChoix2.setScale(0.5f, 0.5f);
	spriteChoix3.setScale(0.5f, 0.5f);

	spriteChoix1.setPosition(900, 275);
	spriteChoix2.setPosition(800, 475);
	spriteChoix3.setPosition(890, 700);

	posButon = 0;


	///Bulle arrière
	spriteMenu.push_back(spriteBulle1);
	spriteMenu.push_back(spriteBulle3);
	spriteMenu.push_back(spriteBulle2);

	///Selection
	selectSprite.push_back(selectPlaySprite);
	selectSprite.push_back(selectSettingsSprite);
	selectSprite.push_back(selectQuitSprite);

	///Texte
	spriteTexte.push_back(spriteChoix1);
	spriteTexte.push_back(spriteChoix2);
	spriteTexte.push_back(spriteChoix3);

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
	cout << "hello" << endl;
	bool hasStarted = false;


		window.clear(Color::Black);

		drawback(window);

		for (auto& bulle : spriteMenu) {
			window.draw(bulle);
		}
		for (auto& button : selectSprite) {
			window.draw(button);
		}
		for (auto& text : spriteTexte) {
			window.draw(text);
		}
	
		setTexture("assets/backMenu/menutel.png", window);


		Vector2i n_mouse = Mouse::getPosition(window);
		Vector2f mouse = { (float)n_mouse.x, (float)n_mouse.y };
		Event gameEvent;
		while (window.pollEvent(gameEvent)) {
			if (gameEvent.type == Event::Closed)
				window.close();

			if (Keyboard::isKeyPressed(Keyboard::K))
				window.close();

			if (spriteMenu[0].getGlobalBounds().contains(mouse.x, mouse.y)) { //Play
				selectSprite[0].setColor(Color(255, 255, 255, 255));
				selectSprite[1].setColor(Color(255, 255, 255, 0));
				selectSprite[2].setColor(Color(255, 255, 255, 0));
				cout << "test";
			}
			else if (spriteMenu[1].getGlobalBounds().contains(mouse.x, mouse.y)) { //Settings
				selectSprite[0].setColor(Color(255, 255, 255, 0));
				selectSprite[1].setColor(Color(255, 255, 255, 255));
				selectSprite[2].setColor(Color(255, 255, 255, 0));

			}
			else if (spriteMenu[2].getGlobalBounds().contains(mouse.x, mouse.y)) { //Quit
				selectSprite[0].setColor(Color(255, 255, 255, 0));
				selectSprite[1].setColor(Color(255, 255, 255, 0));
				selectSprite[2].setColor(Color(255, 255, 255, 255));
			}
			


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
		for (auto& Rectangle : hitbox) {
			delete Rectangle;
		}



		window.display();

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