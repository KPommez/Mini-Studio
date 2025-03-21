#include "LevelTwo.hpp"

LevelTwo::LevelTwo() {
	wallBGTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/background.png");
	topLeavesTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/topLeaves.png");
	luminousBeamTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/luminousBeam.png");
	mirrorTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Sprites/mirror.png");
	floorTexture.loadFromFile("Assets/LevelAssets/LevelTwo/Background/floor.png");
	// Sprites
	wallBG.setTexture(wallBGTexture); 
	topLeaves.setTexture(topLeavesTexture); 
	luminousBeam.setTexture(luminousBeamTexture);
	floorSprite.setTexture(floorTexture);
	sprites.reserve(4);
	sprites.emplace_back(wallBG);
	sprites.emplace_back(luminousBeam);
	sprites.emplace_back(topLeaves);
	sprites.emplace_back(floorSprite);
}

void LevelTwo::scaleSprites(RenderWindow& window) {
	for (auto& layer : sprites) {
		layer.setScale(sf::Vector2f((window.getSize().x / layer.getLocalBounds().width), (window.getSize().y / layer.getLocalBounds().height)));
	}
}

const Texture* LevelTwo::getTexture() {
	return &mirrorTexture;
}

void LevelTwo::draw(RenderWindow& window) {
	window.draw(sprites[0]);
	window.draw(sprites[1]);
	window.draw(sprites[2]);
	window.draw(sprites[3]);
}