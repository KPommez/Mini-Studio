#include "LevelTwo.hpp"

LevelTwo::LevelTwo() {
	wallBGTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/wall.png");
	topLeavesTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/topLeaves.png");
	luminousBeamTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/luminousBeam.png");
	solarPanelTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Sprites/solarPanel.png");
	mirrorTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Sprites/mirror.png");
	// Sprites
	wallBG.setTexture(wallBGTexture); 
	topLeaves.setTexture(topLeavesTexture); 
	luminousBeam.setTexture(luminousBeamTexture); 
	solarPanel.setTexture(solarPanelTexture);
	sprites.reserve(4);
	sprites.emplace_back(wallBG);
	sprites.emplace_back(topLeaves);
	sprites.emplace_back(luminousBeam);
	sprites.emplace_back(solarPanel);
}

void LevelTwo::scaleSprites(RenderWindow& window) {
	for (auto& sprite : sprites) {
		float ratio = (float)window.getSize().x / sprite.getGlobalBounds().width;
		sprite.setScale(ratio, ratio);
		sprite.setPosition(0, 0);
	}
	// Solar panel
	sprites[3].setScale(1, 1);
	sprites[3].setPosition((float)window.getSize().x - sprites[3].getGlobalBounds().width - (float)window.getSize().x / 10.f, window.getSize().y - window.getSize().y / 10.f);
}

const Texture* LevelTwo::getTexture() {
	return &mirrorTexture;
}

void LevelTwo::draw(RenderWindow& window) {
	window.draw(wallBG);
	window.draw(luminousBeam);
	window.draw(topLeaves);
	window.draw(solarPanel);
}