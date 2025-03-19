#include "SpriteMenu.hpp"

void SpriteMenu::initAllSpriteMenu(RenderWindow& window)
{
	Vector2f WindoSize{ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
	if (!font.loadFromFile("Assets/font/Minecraft.ttf") ||
		!bulle1.loadFromFile("Assets/backMenu/texte.png") ||
		!bulle2.loadFromFile("Assets/backMenu/texte1.png") ||
		!bulle3.loadFromFile("Assets/backMenu/texte2.png") ||
		!choix1.loadFromFile("Assets/backMenu/bouton_play.png") ||
		!choix2.loadFromFile("Assets/backMenu/bouton_options.png") ||
		!choix3.loadFromFile("Assets/backMenu/bouton_quitter.png") ||
		!selectPlay.loadFromFile("Assets/backMenu/selection_bouton.png") ||
		!selectSettings.loadFromFile("Assets/backMenu/selection_bouton.png") ||
		!selectQuit.loadFromFile("Assets/backMenu/selection_bouton.png") ||
		!textureTouche.loadFromFile("Assets/backMenu/touche.png") ||
		!textureTouche1.loadFromFile("Assets/backMenu/touche.png") ||
		!textureTouche2.loadFromFile("Assets/backMenu/touche.png") ||
		!textureTouche3.loadFromFile("Assets/backMenu/touche.png"))
	{
		cerr << "Assets du menu non totalement charges" << endl;
	}

	sprite.setOrigin(0, 0);
	///////////Selection//////////////
	selectPlaySprite.setTexture(selectPlay);
	selectSettingsSprite.setTexture(selectSettings);
	selectQuitSprite.setTexture(selectQuit);

	selectPlaySprite.setScale(0.5f, 0.5f);
	selectSettingsSprite.setScale(0.5f, 0.5f);
	selectQuitSprite.setScale(0.5f, 0.5f);

	selectPlaySprite.setPosition(WindoSize.x / 2 - (selectPlay.getSize().x / 2.5), WindoSize.y / 4.5);
	selectSettingsSprite.setPosition(WindoSize.x / 2 - (selectSettings.getSize().x / 1.95), WindoSize.y / 2.5 - (selectSettings.getSize().y / 1.50));
	selectQuitSprite.setPosition(WindoSize.x / 2 - (selectQuit.getSize()).x / 2.5, WindoSize.y / 1.80);

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

	spriteBulle1.setPosition(WindoSize.x / 2 - (selectPlay.getSize().x / 2), WindoSize.y / 5);
	spriteBulle3.setPosition(WindoSize.x / 2 - (selectPlay.getSize().x / 1.5), WindoSize.y / 2.85);
	spriteBulle2.setPosition(WindoSize.x / 2 - (selectPlay.getSize().x / 1.95), WindoSize.y / 1.95);

	///////////Choix Play/Settings/Quit ////////
	spriteChoix1.setTexture(choix1);
	spriteChoix2.setTexture(choix2);
	spriteChoix3.setTexture(choix3);

	spriteChoix1.setScale(0.5f, 0.5f);
	spriteChoix2.setScale(0.5f, 0.5f);
	spriteChoix3.setScale(0.5f, 0.5f);

	spriteChoix1.setPosition(WindoSize.x / 2 - (selectPlay.getSize().x / 3.5), WindoSize.y / 4.5);
	spriteChoix2.setPosition(WindoSize.x / 2 - (selectSettings.getSize().x / 2.5), WindoSize.y / 2.5 - (selectSettings.getSize().y / 1.50));
	spriteChoix3.setPosition(WindoSize.x / 2 - (selectPlay.getSize().x) / 3.75 - (choix1.getSize().x / 5 ), WindoSize.y / 1.81);

	///Touche 
	touche.setTexture(textureTouche);
	touche.setPosition(450, 400);
	touche.setScale(0.25f, 0.25f);

	touche1.setTexture(textureTouche1);
	touche1.setPosition(580, 400);
	touche1.setScale(0.25f, 0.25f);

	touche2.setTexture(textureTouche2);
	touche2.setPosition(710, 400);
	touche2.setScale(0.25f, 0.25f);

	touche3.setTexture(textureTouche3);
	touche3.setPosition(450, 530);
	touche3.setScale(0.25f, 0.25f);

	///Bulle arrière
	spriteVBulle.push_back(spriteBulle1);
	spriteVBulle.push_back(spriteBulle3);
	spriteVBulle.push_back(spriteBulle2);

	///Selection
	selectSprite.push_back(selectPlaySprite);
	selectSprite.push_back(selectSettingsSprite);
	selectSprite.push_back(selectQuitSprite);

	///Texte
	spriteTexte.push_back(spriteChoix1);
	spriteTexte.push_back(spriteChoix2);
	spriteTexte.push_back(spriteChoix3);

	//Touche
	spritTouche.push_back(touche);
	spritTouche.push_back(touche1);
	spritTouche.push_back(touche2);
	spritTouche.push_back(touche3);
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
	for (auto& bulle : spriteVBulle) {
		window.draw(bulle);
	}
	for (auto& button : selectSprite) {
		window.draw(button);
	}
	for (auto& text : spriteTexte) {
		window.draw(text);
	}
}

void SpriteMenu::ViewMenu(RenderWindow& window)
{

}


