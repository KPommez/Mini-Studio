#pragma once

#include "includeAll.hpp"

class LevelTwo {
private:
	Texture wallBGTexture, topLeavesTexture, luminousBeamTexture, solarPanelTexture, mirrorTexture;
	Sprite wallBG, topLeaves, luminousBeam, solarPanel, mirror;
	vector<Sprite> sprites;

public:
	LevelTwo();
	const Texture* getTexture();
	void scaleSprites(RenderWindow& window);
	void draw(RenderWindow& window);
};