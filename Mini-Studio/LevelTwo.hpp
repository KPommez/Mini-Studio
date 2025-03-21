#pragma once

#include "includeAll.hpp"
#include "SolarPanel.hpp"

class LevelTwo {
private:
	Texture wallBGTexture, topLeavesTexture, luminousBeamTexture, mirrorTexture, floorTexture;
	Sprite wallBG, topLeaves, luminousBeam, mirror, floorSprite;
	vector<Sprite> sprites;

public:
	SolarPanel endSolarPanel;

public:
	LevelTwo();
	const Texture* getTexture();
	void scaleSprites(RenderWindow& window);
	void draw(RenderWindow& window);
};