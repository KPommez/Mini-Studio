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
		!Back.loadFromFile("Assets/backMenu/RetourMenu.png")					   ||
		!Quit.loadFromFile("Assets/backMenu/Quitter.png")					       ||
		!Retry.loadFromFile("Assets/backMenu/retry.png")                           ||
		!Forfeit.loadFromFile("Assets/backMenu/forfeit.png")                       ||
		!textureTouche.loadFromFile("Assets/backMenu/toucheQ.png")                 ||
		!textureTouche1.loadFromFile("Assets/backMenu/toucheS.png")                ||
		!textureTouche2.loadFromFile("Assets/backMenu/toucheD.png")                ||
		!textureTouche3.loadFromFile("Assets/backMenu/toucheSHIFT.png")            ||
		!textureTouche4.loadFromFile("Assets/backMenu/toucheSPACE.png")            ||
		!textureToucheManette.loadFromFile("Assets/backMenu/joystick1.png")        ||
		!textureToucheManette1.loadFromFile("Assets/backMenu/joystick2.png")       ||
		!textureToucheManette2.loadFromFile("Assets/backMenu/joystick3.png")       ||
		!textureToucheManette3.loadFromFile("Assets/backMenu/manetteToucheRB.png") ||
		!textureToucheManette4.loadFromFile("Assets/backMenu/manetteToucheA.png")  ||
		!textureToucheManette5.loadFromFile("Assets/backMenu/manetteToucheB.png"))
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

	spriteChoix1.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x / 8.f), WindowSize.y / 1.90f);
	spriteChoix3.setPosition(WindowSize.x / 2.f - (selectPlay.getSize().x) / 5.f, WindowSize.y / 1.65f);


	///////////Win /////////

	spriteBack.setTexture(Back);
	spriteQuitter.setTexture(Quit);

	spriteBack.setScale(0.5f, 0.5f);
	spriteQuitter.setScale(0.5f, 0.5f);

	spriteBack.setPosition(WindowSize.x / 2.f - (Back.getSize().x / 7.0f), WindowSize.y / 2.f);
	spriteQuitter.setPosition(WindowSize.x / 2.f - (Quit.getSize().x / 15.0f), WindowSize.y / 1.60f);

	WinButton.push_back(spriteBack);
	WinButton.push_back(spriteQuitter);

	///////////Lose /////////

	spriteRetry.setTexture(Retry);
	spriteForfeit.setTexture(Forfeit);

	spriteRetry.setScale(0.5f, 0.5f);
	spriteForfeit.setScale(0.5f, 0.5f);

	spriteRetry.setPosition(WindowSize.x / 2.f - (Retry.getSize().x / 9.0f), WindowSize.y / 1.90f);
	spriteForfeit.setPosition(WindowSize.x / 2.f - (Forfeit.getSize().x / 9.0f), WindowSize.y / 1.60f);

	LoseButton.push_back(spriteRetry);
	LoseButton.push_back(spriteForfeit);


	///Touche 
	touche.setTexture(textureTouche);
	touche.setPosition(450, 400);
	touche.setScale(0.4f, 0.4f);

	touche1.setTexture(textureTouche1);
	touche1.setPosition(580, 400);
	touche1.setScale(0.4f, 0.4f);

	touche2.setTexture(textureTouche2);
	touche2.setPosition(710, 400);
	touche2.setScale(0.4f, 0.4f);

	touche3.setTexture(textureTouche3);
	touche3.setPosition(450, 530);
	touche3.setScale(0.4f, 0.4f);

	touche4.setTexture(textureTouche4);
	touche4.setPosition(580, 530);
	touche4.setScale(0.4f, 0.4f);

	///Touche manette
	toucheManette.setTexture(textureToucheManette);
	toucheManette.setPosition(700, 295);
	toucheManette.setScale(0.4f, 0.4f);

	toucheManette1.setTexture(textureToucheManette1);
	toucheManette1.setPosition(725, 185);
	toucheManette1.setScale(0.4f, 0.4f);

	toucheManette2.setTexture(textureToucheManette2);
	toucheManette2.setPosition(750, 295);
	toucheManette2.setScale(0.4f, 0.4f);

	toucheManette3.setTexture(textureToucheManette3);
	toucheManette3.setPosition(900, 525);
	toucheManette3.setScale(0.4f, 0.4f);

	toucheManette4.setTexture(textureToucheManette4);
	toucheManette4.setPosition(1035, 525);
	toucheManette4.setScale(0.4f, 0.4f);

	toucheManette5.setTexture(textureToucheManette5);
	toucheManette5.setPosition(1675, 850);
	toucheManette5.setScale(0.4f, 0.4f);

	///Texte Option 
	Texte retour(font, "Retour", 40, 0, 0, 0, 1700, 1000);
	Texte dashClavier(font, "Dash", 40, 0, 0, 0, 500, 690);
	Texte sautClavier(font, "Saut", 40, 0, 0, 0, 630, 690);
	
	///texte Option Joystick
	Texte dashJoystick(font, "Dash", 40, 0, 0, 0, 950, 690);
	Texte sautJoystick(font, "Saut", 40, 0, 0, 0, 1085, 690);
	
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

	///Touche manette
	spriteToucheManette.push_back(toucheManette);
	spriteToucheManette.push_back(toucheManette1);
	spriteToucheManette.push_back(toucheManette2);
	spriteToucheManette.push_back(toucheManette3);
	spriteToucheManette.push_back(toucheManette4);
	spriteToucheManette.push_back(toucheManette5);

	///Texte Option
	listeTexteOption.push_back(retour);
	listeTexteOption.push_back(dashClavier);
	listeTexteOption.push_back(sautClavier);
	listeTexteOption.push_back(dashJoystick);
	listeTexteOption.push_back(sautJoystick);
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