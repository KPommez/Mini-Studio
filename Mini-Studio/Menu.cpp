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
		posButon = 3;
	}
	cout << posButon << endl;
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
	RectangleShape NivTest(Vector2f{ 50,50 });
	NivTest.setFillColor(Color::Black);
	window.draw(NivTest);
	spriteMenu.setTexture("assets/backMenu/MenuDef.png", window);

	Vector2i n_mouse = Mouse::getPosition(window);
	Vector2f mouse = { (float)n_mouse.x, (float)n_mouse.y };
	Event gameEvent;
	while (window.pollEvent(gameEvent)) {

		if (gameEvent.type == Event::Closed)
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::K))
			window.close();

		if (spriteMenu.spriteTexte[0].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 1) { //Play
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 255));
			spriteMenu.spriteOption.setColor(Color(255, 255, 255, 255));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 0));
		}
		else if (spriteMenu.spriteOption.getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 2) { //Settings
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 0));
			spriteMenu.spriteOption.setColor(Color(127, 127, 127, 255));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 0));
		}
		else if (spriteMenu.spriteTexte[1].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 0) { //Quit
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 0));
			spriteMenu.spriteOption.setColor(Color(255, 255, 255, 255));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 255));
		}
		else if (posButon == 3) {
			spriteMenu.selectSprite[0].setColor(Color(255, 255, 255, 0));
			spriteMenu.spriteOption.setColor(Color(255, 255, 255, 255));
			spriteMenu.selectSprite[1].setColor(Color(255, 255, 255, 0));
		}

		if (spriteMenu.spriteTexte[0].getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0,1) && posButon == 1) {
			listeTexte.clear();
			listeRectangle.clear();
			menuState = START;
			game.setRunning(true);
		}
		if (spriteMenu.spriteOption.getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1) && posButon == 2) {
			listeTexte.clear();
			listeRectangle.clear();
			menuState = OPTION;
		}
		if (spriteMenu.spriteTexte[1].getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left) || Joystick::isButtonPressed(0, 1) && posButon == 0) {
			window.close();
		}
		if (NivTest.getGlobalBounds().contains(mouse.x, mouse.y) && Mouse::isButtonPressed(Mouse::Left))
		{
			cout << "test niveau";
			/*game.index = 2;*/
		}
	}
	window.display();
}


void Menu::option(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();
	drawback(window);

	///////////////////////////////////////////////////////////////////


	Rectangle RectRetour(180, 55, 1690, 1000, 255, 255, 255); //tailleX, tailleY posX, posY, R, G, B 

	for (auto& Rectangle : listeRectangle) {
		window.draw(Rectangle.creation());
	}

	for (auto& Texte : spriteMenu.listeTexteOption) {
		window.draw(Texte.creation());
	}

	for (auto& Touche : spriteMenu.spriteToucheClavier) {
		window.draw(Touche);
	}

	for (auto& ToucheManette : spriteMenu.spriteToucheManette) {
		window.draw(ToucheManette);
	}

	window.display();

	Event gameEvent;
	while (window.pollEvent(gameEvent)) {
		if (gameEvent.type == Event::Closed)
			window.close();

		if (Keyboard::isKeyPressed(Keyboard::K))
			window.close();

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (Mouse::getPosition(window).x > RectRetour.posX && Mouse::getPosition(window).y > RectRetour.posY && Mouse::getPosition(window).x < RectRetour.posX + RectRetour.tailleX && Mouse::getPosition(window).y < RectRetour.posY + RectRetour.tailleY) {
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
	drawback(window);
	spriteMenu.setTexture("assets/backMenu/victory.png", window);
	Vector2i n_mouse = Mouse::getPosition(window);
	Vector2f mouse = { (float)n_mouse.x, (float)n_mouse.y };

	for (auto& winButton : spriteMenu.WinButton) {
		window.draw(winButton);
	}
	window.display();

	Event gameEvent;
	while (window.pollEvent(gameEvent)) {
		if (gameEvent.type == Event::Closed)
			window.close();
		if (spriteMenu.WinButton[0].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 1) {
			spriteMenu.WinButton[0].setColor(Color(127, 127, 127, 255));
			spriteMenu.WinButton[1].setColor(Color(255, 255, 255, 255));
		}
		else if (spriteMenu.WinButton[1].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 0) {
			spriteMenu.WinButton[1].setColor(Color(127, 127, 127, 255));
			spriteMenu.WinButton[0].setColor(Color(255, 255, 255, 255));
		}
		else {
			spriteMenu.WinButton[0].setColor(Color(255, 255, 255, 255));
			spriteMenu.WinButton[1].setColor(Color(255, 255, 255, 255));
		}

		if (Mouse::isButtonPressed(Mouse::Left) && spriteMenu.WinButton[0].getGlobalBounds().contains(mouse.x, mouse.y) || Joystick::isButtonPressed(0, 1) && posButon == 1) {
			menuState = MENU;
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && spriteMenu.WinButton[1].getGlobalBounds().contains(mouse.x, mouse.y) || Joystick::isButtonPressed(0, 1) && posButon == 0) {
			window.close();
		}

	}

}

void Menu::loose(RenderWindow& window) {
	window.clear(Color::Black);
	listeTexte.clear();
	listeRectangle.clear();
	drawback(window);
	spriteMenu.setTexture("assets/backMenu/defeat.png", window);

	Vector2i n_mouse = Mouse::getPosition(window);
	Vector2f mouse = { (float)n_mouse.x, (float)n_mouse.y };

	for (auto& loseButton : spriteMenu.LoseButton) {
		window.draw(loseButton);
	}

	window.display();

	Event gameEvent;
	while (window.pollEvent(gameEvent)) {
		if (gameEvent.type == Event::Closed)
			window.close();

		if (spriteMenu.LoseButton[0].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 1) {
			spriteMenu.LoseButton[0].setColor(Color(127, 127, 127, 255));
			spriteMenu.LoseButton[1].setColor(Color(255, 255, 255, 255));
		}
		else if (spriteMenu.LoseButton[1].getGlobalBounds().contains(mouse.x, mouse.y) || posButon == 0) {
			spriteMenu.LoseButton[1].setColor(Color(127, 127, 127, 255));
			spriteMenu.LoseButton[0].setColor(Color(255, 255, 255, 255));
		}
		else {
			spriteMenu.LoseButton[0].setColor(Color(255, 255, 255, 255));
			spriteMenu.LoseButton[1].setColor(Color(255, 255, 255, 255));
		}

		if (Mouse::isButtonPressed(Mouse::Left) && spriteMenu.LoseButton[0].getGlobalBounds().contains(mouse.x, mouse.y) || Joystick::isButtonPressed(0, 1) && posButon == 1) {
			menuState = START;
		}
		else if (Mouse::isButtonPressed(Mouse::Left) && spriteMenu.LoseButton[1].getGlobalBounds().contains(mouse.x, mouse.y) || Joystick::isButtonPressed(0, 1) && posButon == 0) {
			window.close();
		}
	}
}

void Menu::drawback(RenderWindow& window) {
	window.draw(spriteMenu.sprite);
}