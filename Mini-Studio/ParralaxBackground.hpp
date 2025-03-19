#pragma once

#include "includeAll.hpp"
#include "Player.hpp"

class ParralaxBackground {
public:
	ParralaxBackground();
	void instanciateLayers(RenderWindow& window, string level, int numberOfLayers);
	void draw(RenderWindow& window);
	void moveLayers(const float& deltaTime, RenderWindow& window, const Player& player);

private:
	void checkBorders(const Player& player, RenderWindow& window);
	vector<Sprite> layers;
	Texture highSkyTexture, layerTexture0, layerTexture1, layerTexture2, layerTexture3, layerTexture4, layerTexture5, layerTexture6;
	Sprite highSky, layer0, layer1, layer2, layer3, layer4, layer5, layer6;
};