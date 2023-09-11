#pragma once
#include <Framework.h>
#include "Doodle.h"
#include "Vector2.h"
#include "Score.h"
#include "CollidableManager.h"

class MyFramework : public Framework
{
private:
	bool gameIsRunning;
	int screenWidth;
	int screenHeight;

	int mouseX, mouseY;

	unsigned int startTimeOfAbility = UINT_MAX, endTimeOfAbility = UINT_MAX;
	
	bool rightIsPressed = false;
	bool leftIsPressed = false;
	bool abilitySwitch = false;

	void HandleKeyboardInput();
	void LockCameraToDoodle();
	void setVariableMemebersToDefault();
	Sprite* backgroundSprite = nullptr;

private:
	int previousTime = 0;
	int currentTime = getTickCount();
	std::shared_ptr<Doodle> doodle{};
	std::shared_ptr<CollidableManager> collidableManager{};
	std::shared_ptr<ScoreDoodle> score{};

	void InitBackground();
	void InitScore();

public:
	MyFramework(int, int);

	// no function calls are available here, this function should only return width, height and fullscreen values
	void PreInit(int& width, int& height, bool& fullscreen) override;

	// return : true - ok, false - failed, application will exit
	bool Init() override;

	void Close() override;

	// return value: if true will exit the application
	bool Tick() override;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	void onKeyPressed(FRKey k) override;

	void onKeyReleased(FRKey k) override;

	const char* GetTitle()override;

	void Update(float deltaT);

	void InitDoodle();

	void InitCollidableManager();

	void gameOver();

	void toggleOnAbility();

	void drawDoodleBackground();

	void computeScoreForDoodle();
};