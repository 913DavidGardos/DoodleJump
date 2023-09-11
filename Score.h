#pragma once
#include "Framework.h"
#include <vector>
#include <string>
#include <iostream>

#define NUMBER_WIDTH 20
#define NUMBER_HEIGHT 20

class ScoreDoodle
{
public:
	ScoreDoodle(int screenWidth, int screenHeight);
	~ScoreDoodle();

	void setPlatformsPassed(int number);
	void setGameUnitsPassed(int number);
	void render();

private:
	std::vector<Sprite*> numbers;
	int platformsPassed = 0;
	int gameUnitsPassed = 0;
	int screenWidth, screenHeight;

	Sprite* platformText;
	Sprite* distanceText;
};

