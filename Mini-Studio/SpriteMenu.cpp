#include "SpriteMenu.hpp"

void SpriteMenu::initAllSpriteMenu(RenderWindow& window)
{
	Vector2f WindowSize{ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
	if (!font.loadFromFile("Assets/font/Minecraft.ttf")                            ||
		!ami1.loadFromFile("Assets/backMenu/ami1.png")                             ||
		!ami2.loadFromFile("Assets/backMenu/ami2.png")                             ||
		!bullePlayer.loadFromFile("Assets/backMenu/bulleMenu.png")                 ||
		!option.loadFromFile("Assets/backMenu/optionIcone.png")                    ||
		!choix1.loadFromFile("Assets/backMenu/okarriveb.png")                      ||
		!choix3.loadFromFile("Assets/backMenu/pasmtnR.png")                        ||
		!selectPlay.loadFromFile("Assets/backMenu/selection_bouton.png")           ||
		!selectQuit.loadFromFile("Assets/backMenu/selection_bouton.png")           ||
		!textureTouche.loadFromFile("Assets/backMenu/toucheQ.png")                 ||
		!textureTouche1.loadFromFile("Assets/backMenu/toucheS.png")                ||
		!textureTouche2.loadFromFile("Assets/backMenu/toucheD.png")                ||
		!textureTouche3.loadFromFile("Assets/backMenu/toucheSHIFT.png")            ||
		!textureTouche4.loadFromFile("Assets/backMenu/toucheSPACE.png")            ||
		!textureTouche5.loadFromFile("Assets/backMenu/toucheE.png")                ||
		!textureTouche6.loadFromFile("Assets/backMenu/toucheR.png")                ||
		!textureToucheManette.loadFromFile("Assets/backMenu/joystick1.png")        ||
		!textureToucheManette1.loadFromFile("Assets/backMenu/joystick2.png")       ||
		!textureToucheManette2.loadFromFile("Assets/backMenu/joystick3.png")       ||
		!textureToucheManette3.loadFromFile("Assets/backMenu/manetteToucheRB.png") ||
		!textureToucheManette4.loadFromFile("Assets/backMenu/manetteToucheA.png")  ||
		!textureToucheManette5.loadFromFile("Assets/backMenu/manetteToucheB.png")  ||
		!textureToucheManette6.loadFromFile("Assets/backMenu/manetteTouchex.png")  ||
		!textureToucheManette7.loadFromFile("Assets/backMenu/manetteToucheY.png")   )
	{
		cerr << "Assets du menu non totalement charges" << endl;
	}

	sprite.setOrigin(0, 0);

	///////////Texte Ami /////////////
	Sami1.setTexture(ami1);
	Sami2.setTexture(ami2);

	Sami1.setScale(0.5f, 0.5f);
	Sami2.setScale(0.5f, 0.5f);

	Sami1.setPosition(WindowSize.x / 2.f - (ami1.getSize().x / 3.35f), WindowSize.y / 9.f);
	Sami2.setPosition(WindowSize.x / 2.f - (ami1.getSize().x / 3.35f), WindowSize.y / 3.5f);

	TexteAmi.push_back(Sami1);
	TexteAmi.push_back(Sami2);
	///////////Selection//////////////
	selectPlaySprite.setTexture(selectPlay);
	selectQuitSprite.setTexture(selectQuit);

	selectPlaySprite.setScale(0.6f, 0.6f);
	selectQuitSprite.setScale(0.60f, 0.75f);

	selectPlaySprite.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x / 5.5f), WindowSize.y / 1.90f);
	selectQuitSprite.setPosition(WindowSize.x / 2.f - (selectQuit.getSize()).x / 5.f, WindowSize.y / 1.63f);

	selectPlaySprite.setColor(Color(255, 255, 255, 0));
	selectQuitSprite.setColor(Color(255, 255, 255, 0));
	spriteOption.setColor(Color(127, 127, 127, 0));

	//////////Bulle/////////////////

	spriteBullePlayer.setTexture(bullePlayer);
	spriteBullePlayer.setScale(0.40f, 0.40f);
	spriteBullePlayer.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x / 2.5f), WindowSize.y / 2.5f);

	spriteOption.setTexture(option);
	spriteOption.setScale(0.15f, 0.15f);
	spriteOption.setPosition(WindowSize.x / 2.f + (selectPlay.getSize().x / 3.5f), WindowSize.y / 5.f - (option.getSize().x / 10.f) );


	///////////Choix Play/Settings/Quit ////////
	spriteChoix1.setTexture(choix1);
	spriteChoix3.setTexture(choix3);

	spriteChoix1.setScale(0.5f, 0.5f);
	spriteChoix3.setScale(0.35f, 0.35f);

	//spriteChoix1.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x / 20.f), WindowSize.y / 1.90f);
	spriteChoix1.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x / 8.f), WindowSize.y / 1.90f);
	spriteChoix3.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x) / 5.f, WindowSize.y / 1.65f);

	///Touche 
	touche.setTexture(textureTouche);
	touche.setPosition(WindowSize.x / 2.66f, WindowSize.y / 6.35f);
	touche.setScale(0.4f, 0.4f);

	touche1.setTexture(textureTouche1);
	touche1.setPosition(WindowSize.x / 2.26f, WindowSize.y / 6.35f);
	touche1.setScale(0.4f, 0.4f);

	touche2.setTexture(textureTouche2);
	touche2.setPosition(WindowSize.x / 1.95f, WindowSize.y / 6.35f);
	touche2.setScale(0.4f, 0.4f);

	touche3.setTexture(textureTouche3);
	touche3.setPosition(WindowSize.x / 2.96f, WindowSize.y / 3.85f);
	touche3.setScale(0.4f, 0.4f);

	touche4.setTexture(textureTouche4);
	touche4.setPosition(WindowSize.x / 2.46f, WindowSize.y / 3.85f);
	touche4.setScale(0.4f, 0.4f);

	touche5.setTexture(textureTouche5);
	touche5.setPosition(WindowSize.x / 2.09f, WindowSize.y / 3.85f);
	touche5.setScale(0.4f, 0.4f);

	touche6.setTexture(textureTouche6);
	touche6.setPosition(WindowSize.x / 1.83f, WindowSize.y / 3.85f);
	touche6.setScale(0.4f, 0.4f);

	///Touche manette
	toucheManette.setTexture(textureToucheManette);
	toucheManette.setPosition(WindowSize.x / 3.64f, WindowSize.y / 2.48f);
	toucheManette.setScale(0.4f, 0.4f);

	toucheManette1.setTexture(textureToucheManette1);
	toucheManette1.setPosition(WindowSize.x / 3.5f, WindowSize.y / 3.32f);
	toucheManette1.setScale(0.4f, 0.4f);

	toucheManette2.setTexture(textureToucheManette2);
	toucheManette2.setPosition(WindowSize.x / 3.38f, WindowSize.y / 2.48f);
	toucheManette2.setScale(0.4f, 0.4f);

	toucheManette3.setTexture(textureToucheManette3);
	toucheManette3.setPosition(WindowSize.x / 2.97f, WindowSize.y / 1.67f);
	toucheManette3.setScale(0.4f, 0.4f);

	toucheManette4.setTexture(textureToucheManette4);
	toucheManette4.setPosition(WindowSize.x / 2.3f, WindowSize.y / 1.53f);
	toucheManette4.setScale(0.475f, 0.475f);

	toucheManette5.setTexture(textureToucheManette5);
	toucheManette5.setPosition(WindowSize.x / 1.1f, WindowSize.y / 1.2f);
	toucheManette5.setScale(0.475f, 0.475f);

	toucheManette6.setTexture(textureToucheManette6);
	toucheManette6.setPosition(WindowSize.x / 1.98f, WindowSize.y / 1.53f);
	toucheManette6.setScale(0.5f, 0.5f);

	toucheManette7.setTexture(textureToucheManette7);
	toucheManette7.setPosition(WindowSize.x / 1.74f, WindowSize.y / 1.53f);
	toucheManette7.setScale(0.5f, 0.5f);

	///Texte Option 
	Texte retour(font, "Retour", 40, 0, 0, 0, WindowSize.x / 1.129f, WindowSize.y / 1.08f);
	Texte clavier(font, "Clavier", 40, 0, 0, 0, WindowSize.x/ 2.23f, WindowSize.y / 7.2f);
	Texte dashClavier(font, "Dash", 32.5f, 0, 0, 0, WindowSize.x / 2.72f, WindowSize.y / 2.51f);
	Texte sautClavier(font, "Saut", 32.5f, 0, 0, 0, WindowSize.x / 2.28f, WindowSize.y / 2.51f);
	Texte rotateLeftClavier(font, "Turn-L", 32.5f, 0, 0, 0, WindowSize.x / 2.0f, WindowSize.y / 2.51f);
	Texte rotateRightClavier(font, "Turn-R", 32.5f, 0, 0, 0, WindowSize.x / 1.76f, WindowSize.y / 2.51f);
	
	///texte Option Joystick
	Texte joystick(font, "Joystick", 40, 0, 0, 0, WindowSize.x / 2.23f, WindowSize.y / 2.07f);
	Texte dashJoystick(font, "Dash", 32.5f, 0, 0, 0, WindowSize.x / 2.72f, WindowSize.y / 1.37f);
	Texte sautJoystick(font, "Saut", 32.5f, 0, 0, 0, WindowSize.x / 2.28f, WindowSize.y / 1.37f);
	Texte rotateLeftJoystick(font, "Turn-L", 32.5f, 0, 0, 0, WindowSize.x / 2.0f, WindowSize.y / 1.37f);
	Texte rotateRightJoystick(font, "Turn-R", 32.5f, 0, 0, 0, WindowSize.x / 1.76f, WindowSize.y / 1.37f);
	
	///Bulle arrière
	/*spriteVBulle.push_back(spriteBulle1);
	spriteVBulle.push_back(spriteBulle3);
	spriteVBulle.push_back(spriteBulle2);*/

	///Selection
	selectSprite.push_back(selectPlaySprite);
	selectSprite.push_back(selectQuitSprite);

	///Texte
	spriteTexte.push_back(spriteChoix1);
	spriteTexte.push_back(spriteChoix3);

	//Touche
	spriteToucheClavier.push_back(touche);
	spriteToucheClavier.push_back(touche1);
	spriteToucheClavier.push_back(touche2);
	spriteToucheClavier.push_back(touche3);
	spriteToucheClavier.push_back(touche4);
	spriteToucheClavier.push_back(touche5);
	spriteToucheClavier.push_back(touche6);

	///Touche manette
	spriteToucheManette.push_back(toucheManette);
	spriteToucheManette.push_back(toucheManette1);
	spriteToucheManette.push_back(toucheManette2);
	spriteToucheManette.push_back(toucheManette3);
	spriteToucheManette.push_back(toucheManette4);
	spriteToucheManette.push_back(toucheManette5);
	spriteToucheManette.push_back(toucheManette6);
	spriteToucheManette.push_back(toucheManette7);

	///Texte Option
	listeTexteOption.push_back(retour);
	listeTexteOption.push_back(clavier);
	listeTexteOption.push_back(joystick);
	listeTexteOption.push_back(dashClavier);
	listeTexteOption.push_back(sautClavier);
	listeTexteOption.push_back(rotateLeftClavier);
	listeTexteOption.push_back(rotateRightClavier);
	listeTexteOption.push_back(dashJoystick);
	listeTexteOption.push_back(sautJoystick);
	listeTexteOption.push_back(rotateLeftJoystick);
	listeTexteOption.push_back(rotateRightJoystick);
}

void SpriteMenu::setTexture(const string& PNGfile, RenderWindow& window)
{
	if (texture.loadFromFile(PNGfile))
	{
		sprite.setTexture(texture);
		sf::Vector2u windowSize = window.getSize();

		// Calculer le facteur d'échelle pour ajuster le sprite à l'écran
		float scaleX = static_cast<float>(windowSize.x) / sprite.getLocalBounds().width;
		float scaleY = static_cast<float>(windowSize.y) / sprite.getLocalBounds().height;

		// Appliquer l'échelle au sprite
		sprite.setScale(scaleX, scaleY);
	}
}

void SpriteMenu::drawVector(RenderWindow& window) {
	//for (auto& bulle : spriteVBulle) {
	//	window.draw(bulle);
	//}
	window.draw(spriteBullePlayer);
	window.draw(spriteOption);
	for (auto& ami : TexteAmi) {
		window.draw(ami);
	}
	for (auto& button : selectSprite) {
		window.draw(button);
	}
	for (auto& text : spriteTexte) {
		window.draw(text);
	}
}