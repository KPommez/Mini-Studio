#include "ParralaxBackground.hpp"

ParralaxBackground::ParralaxBackground() {}

void ParralaxBackground::instanciateLayers(RenderWindow& window, string level, int numberOfLayers) {
	layerTexture0.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer0.png");
	layerTexture1.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer1.png");
	layerTexture2.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer2.png");
	layerTexture3.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer3.png");
	layerTexture4.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer4.png");
	layerTexture5.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer5.png");
	layerTexture6.loadFromFile("Assets/LevelAssets/" + level + "/Parralax/layer6.png");

	layer0.setTexture(layerTexture0);
	layer1.setTexture(layerTexture1);
	layer2.setTexture(layerTexture2);
	layer3.setTexture(layerTexture3);
	layer4.setTexture(layerTexture4);
	layer5.setTexture(layerTexture5);
	layer6.setTexture(layerTexture6);

	layers.push_back(layer0);
	layers.push_back(layer1);
	layers.push_back(layer2);
	layers.push_back(layer3);
	layers.push_back(layer4);
	layers.push_back(layer5);
	layers.push_back(layer6);

	// Copying elements of layers 
	for (int i = 0; i < numberOfLayers; ++i) {
		layers[i].setPosition(0, 0);
		layers.push_back(layers[i]);
		layers[i + numberOfLayers].scale(-1.f, 1.f);
		layers[i + numberOfLayers].setPosition(0 + (float)window.getSize().x, 0);
	}

	// Scaling the sprites properly to the screen's dimensions
	for (auto& layer : layers) {
		layer.setScale(sf::Vector2f((window.getSize().x / layer.getLocalBounds().width), (window.getSize().y / layer.getLocalBounds().height)));
	}
}

void ParralaxBackground::moveLayers(const float& deltaTime, RenderWindow& window, const Player& player) {
	// Movement
	if (player.isGoingRight && !player.isIdling) {
		layers[0].move(-50.f * deltaTime, 0);
		layers[7].move(-50.f * deltaTime, 0);
		layers[1].move(-100.f * deltaTime, 0);
		layers[8].move(-100 * deltaTime, 0);
		layers[2].move(-150.f * deltaTime, 0);
		layers[9].move(-150.f * deltaTime, 0);
		layers[3].move(-200.f * deltaTime, 0);
		layers[10].move(-200.f * deltaTime, 0);
		layers[4].move(-250.f * deltaTime, 0);
		layers[11].move(-250.f * deltaTime, 0);
		layers[5].move(-300.f * deltaTime, 0);
		layers[12].move(-300.f * deltaTime, 0);
		layers[6].move(-350.f * deltaTime, 0);
		layers[13].move(-350.f * deltaTime, 0);
	}
	else if (player.isGoingLeft && !player.isIdling) {
		layers[0].move(50.f * deltaTime, 0);
		layers[7].move(50.f * deltaTime, 0);
		layers[1].move(100.f * deltaTime, 0);
		layers[8].move(100 * deltaTime, 0);
		layers[2].move(150.f * deltaTime, 0);
		layers[9].move(150.f * deltaTime, 0);
		layers[3].move(200.f * deltaTime, 0);
		layers[10].move(200.f * deltaTime, 0);
		layers[4].move(250.f * deltaTime, 0);
		layers[11].move(250.f * deltaTime, 0);
		layers[5].move(300.f * deltaTime, 0);
		layers[12].move(300.f * deltaTime, 0);
		layers[6].move(350.f * deltaTime, 0);
		layers[13].move(350.f * deltaTime, 0);
	}
	// Checking borders
	if(!player.isIdling)
		checkBorders(player, window);
}

void ParralaxBackground::checkBorders(const Player& player, RenderWindow& window) {
	float diff = 0;
	for (int i = 0; i < layers.size(); ++i) {
		diff = player.playerSprite.getPosition().x - layers[i].getPosition().x;
		if (diff >= window.getSize().x * 1.5f && player.isGoingRight) {
			layers[i].move(2.f * window.getSize().x, 0);
		}
		else if(abs(diff) >= window.getSize().x * 0.5f  && diff < 0 && player.isGoingLeft) {
			layers[i].move(-2.f * window.getSize().x, 0);
		}
	}
}

void ParralaxBackground::draw(RenderWindow& window) {
	window.draw(layers[0]);
	window.draw(layers[7]);
	window.draw(layers[1]);
	window.draw(layers[8]);
	window.draw(layers[2]);
	window.draw(layers[9]);
	window.draw(layers[3]);
	window.draw(layers[10]);
	window.draw(layers[4]);
	window.draw(layers[11]);
	window.draw(layers[5]);
	window.draw(layers[12]);
	window.draw(layers[6]);
	window.draw(layers[13]);
}