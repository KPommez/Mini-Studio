#include "Menu.hpp"


Menu::Menu(RenderWindow& window) : game(window) {
	if (!font.loadFromFile("assets/font/Minecraft.ttf")) {}
	menuState = MENU;
}




void Menu::setTexture(const string& PNGfile)
{
	if (texture.loadFromFile(PNGfile))
	{
		sprite.setTexture(texture);
		Vector2u textureSize = texture.getSize();
		float scaleX = static_cast<float> (1920) / textureSize.x;
		float scaleY = static_cast<float>(1080) / textureSize.y;
		sprite.setScale(scaleX, scaleY);
	}
}

void Menu::drawback(RenderWindow& window)
{
	window.draw(sprite);
}

void Menu::start(RenderWindow& window)
{
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

	hitbox.push_back(new Rectangle(120, 70, 870, 400, 255, 255, 255));
	hitbox.push_back(new Rectangle(190, 70, 870, 540, 255, 255, 255));
	hitbox.push_back(new Rectangle(130, 70, 870, 680, 255, 255, 255));

	listeTexte.clear();
	listeRectangle.clear();

	Texte Titre(font, "try game", 80, 255, 0, 0, 550, 150); //font, texte, taille,R,G,B, X, Y , 
	listeTexte.push_back(Titre);

	Texte start(font, "Start", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(font, "Touches", 40, 0, 0, 0, 880, 550);
	listeTexte.push_back(touche);

	Texte Partir(font, "Partir", 40, 0, 0, 0, 880, 690);
	listeTexte.push_back(Partir);

	//Rectangle RecTitre(120, 70, 870, 400, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	//listeRectangle.push_back(RecTitre);

	//Rectangle RecTouche(190, 70, 870, 540, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	//listeRectangle.push_back(RecTouche);

	//Rectangle RecPartir(130, 70, 870, 680, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	//listeRectangle.push_back(RecPartir);


		window.clear(Color::Black);
	
		setTexture("assets/backMenu/menutel.png");
		drawback(window);

		for (auto& Rectangle : hitbox) {
			window.draw(Rectangle->creation());
		}

		for (auto& Texte : listeTexte) {
			window.draw(Texte.creation());
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
				if (hitbox[1]->contains(mouse)) {
					listeTexte.clear();
					listeRectangle.clear();
					menuState = START;
					hasStarted = true;
				}
				//if (Mouse::getPosition(window).x > RecTouche.posX && Mouse::getPosition(window).y > RecTouche.posY && Mouse::getPosition(window).x < RecTouche.posX + RecTouche.tailleX && Mouse::getPosition(window).y < RecTouche.posY + RecTouche.tailleY) {
				//	listeTexte.clear();
				//	listeRectangle.clear();
				//	menuState = OPTION;
				//}
				//if (Mouse::getPosition(window).x > RecPartir.posX && Mouse::getPosition(window).y > RecPartir.posY && Mouse::getPosition(window).x < RecPartir.posX + RecPartir.tailleX && Mouse::getPosition(window).y < RecPartir.posY + RecPartir.tailleY) {
				//	window.close();
				//}
			}

			if (Joystick::getAxisPosition(0, Joystick::PovY) >= 10) {
				posButon++;
			}
			else if (Joystick::getAxisPosition(0, Joystick::PovY) <= -10) {
				posButon--;
			}
		}
		for (auto& rect : hitbox) {
			//if (rect->contains)
		}

	}


void Menu::option(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();
	setTexture("assets/backMenu/menu.png");
	drawback(window);

	Texte retour(font, "Retour", 40, 0, 0, 0, 1700, 1000);
	listeTexte.push_back(retour);

	////////////////////////////////////////////////////////////////////


	Rectangle RecClicd(400, 60, window.getSize().x / 2 - 200, window.getSize().y / 2, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	listeRectangle.push_back(RecClicd);



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

void Menu::win(RenderWindow& window)
{
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();

	Texte Titre(font, "Vous avez .... Gagne ??", 80, 255, 0, 0, 480, 255); //font, texte, taille,R,G,B, X, Y , 
	listeTexte.push_back(Titre);

	Texte start(font, "Restart", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(font, "Quitter", 40, 0, 0, 0, 880, 550);
	listeTexte.push_back(touche);

	Rectangle RecTitre(170, 70, 870, 400, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	listeRectangle.push_back(RecTitre);

	Rectangle RecTouche(150, 70, 870, 540, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
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

void Menu::loose(RenderWindow& window)
{
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();

	Texte Titre(font, "Vous avez perdu, vous n'etes pas le heros", 80, 255, 0, 0, 180, 255); //font, texte, taille,R,G,B, X, Y , 
	listeTexte.push_back(Titre);

	Texte start(font, "Restart", 40, 0, 0, 0, 880, 410);
	listeTexte.push_back(start);

	Texte touche(font, "Quitter", 40, 0, 0, 0, 880, 550);
	listeTexte.push_back(touche);

	Rectangle RecTitre(170, 70, 870, 400, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
	listeRectangle.push_back(RecTitre);

	Rectangle RecTouche(150, 70, 870, 540, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 
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