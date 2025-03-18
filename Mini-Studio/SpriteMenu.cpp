#include "SpriteMenu.h"

void SpriteMenu::initAllSpriteMenu()
{
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
	///////////Selection//////////////
	selectPlaySprite.setTexture(selectPlay);
	selectSettingsSprite.setTexture(selectSettings);
	selectQuitSprite.setTexture(selectQuit);

	selectPlaySprite.setScale(0.5f, 0.5f);
	selectSettingsSprite.setScale(0.5f, 0.5f);
	selectQuitSprite.setScale(0.5f, 0.5f);

	selectPlaySprite.setPosition(820, 275);
	selectSettingsSprite.setPosition(750, 475);
	selectQuitSprite.setPosition(840, 705);

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
}

void SpriteMenu::setTexture(const string& PNGfile, RenderWindow& window)
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


