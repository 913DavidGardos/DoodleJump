#include "Score.h"

ScoreDoodle::ScoreDoodle(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight)
{
	platformText = createSprite("../Dependencies/Data/Platforms.png");
	setSpriteSize(platformText, NUMBER_WIDTH * 8, NUMBER_HEIGHT);
	distanceText = createSprite("../Dependencies/Data/Distance.png");
	setSpriteSize(distanceText, NUMBER_WIDTH * 8, NUMBER_HEIGHT);

	for (int i = 0; i < 10; i++)
	{
		std::string path = "../Dependencies/Data/" + std::to_string(i) + ".png";
		const char* charPath = path.c_str();
		numbers.push_back(createSprite(charPath));

	}

	for (int i = 0; i < numbers.size() - 1; i++)
	{
		setSpriteSize(numbers[i], NUMBER_WIDTH, NUMBER_HEIGHT);
	}
	setSpriteSize(numbers[9], NUMBER_WIDTH, NUMBER_HEIGHT);

}

ScoreDoodle::~ScoreDoodle()
{
	for (int i = 0; i < numbers.size(); i++)
	{
		destroySprite(numbers[i]);
	}
	destroySprite(platformText);
	destroySprite(distanceText);
}

void ScoreDoodle::setPlatformsPassed(int number)
{
	platformsPassed = number;
}

void ScoreDoodle::setGameUnitsPassed(int number)
{
	gameUnitsPassed = number;
}

void ScoreDoodle::render()
{
	drawSprite(platformText, screenWidth - 90 - NUMBER_WIDTH * 8, 10);

	int copyOfNumber = platformsPassed;

	std::vector<int> arrayMirror;
	for (int i = copyOfNumber; i >= 1; i = i / 10)
	{
		arrayMirror.push_back(i % 10);
	}

	int x = screenWidth - 90;
	int y = 10;

	for (auto it = arrayMirror.rbegin(); it != arrayMirror.rend(); it++)
	{
		int digit = *it;
		if (numbers[digit] != nullptr)
		{
			drawSprite(numbers[digit], x, y);
			x += NUMBER_WIDTH ;
		}
	}

	drawSprite(distanceText, screenWidth - 90 - NUMBER_WIDTH * 8, 40);

	std::vector<int> distance;
	for (int i = gameUnitsPassed; i >= 1; i = i / 10)
	{
		distance.push_back(i % 10);
	}

	x = screenWidth - 90;
	y = 40;

	for (auto it = distance.rbegin(); it != distance.rend(); it++)
	{
		int digit = *it;
		if (numbers[digit] != nullptr)
		{
			drawSprite(numbers[digit], x, y);
			x += NUMBER_WIDTH;
		}
	}
}
