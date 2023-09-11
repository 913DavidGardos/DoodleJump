#include "MyFramework.h"
#define CONSTANT_MAGNITUDE_BLACK_HOLE 4000

MyFramework::MyFramework(int width, int height)
	: gameIsRunning(true), screenWidth(width), screenHeight(height), doodle(nullptr), mouseX(0), mouseY(0) {}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	std::cout << "PreInit was called" << std::endl;
	width = this->screenWidth;
	height = this->screenHeight;
	fullscreen = false;
}

bool MyFramework::Init() 
{
	std::cout << "Init was called" << std::endl;
	
	gameIsRunning = true;
	InitDoodle();
	InitCollidableManager();
	InitScore();
	InitBackground();

	return true;
}

void MyFramework::Close()
{
	destroySprite(backgroundSprite);
	setVariableMemebersToDefault();

	std::cout << "Close was called" << std::endl;
}

bool MyFramework::Tick()
{
	this->previousTime = this->currentTime;
	this->currentTime = getTickCount();
	float deltaT = (float)(this->currentTime - this->previousTime);
	deltaT = deltaT / 50.f;

	if (deltaT > 0.15f) deltaT = 0.15f;
	
	if (!doodle.get()->isAlive()) gameOver();
	
	HandleKeyboardInput();
	collidableManager->manageCoins();
	collidableManager->checkCollisions(doodle);
	collidableManager->repositionEntitiesInScreen();

	computeScoreForDoodle();
	score->setGameUnitsPassed(doodle->getGameUnitsPassed());
	score->setPlatformsPassed(doodle->getPlatformsPassed());

	toggleOnAbility();
	Update(deltaT);

	//draws
	drawDoodleBackground();
	collidableManager->renderCollidables();
	doodle->renderBullets();
	doodle->render();
	score->render();
	
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	this->mouseX = x;
	this->mouseY = y;
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (button == FRMouseButton::LEFT && !isReleased)
	{
		Vector2 bulletVector(doodle->getX(), doodle->getY());
		Vector2 cursorVector((float)mouseX, (float)mouseY);
		Vector2 direction = cursorVector.Substract(bulletVector);
		Vector2 normalizedDirection = direction.Normalize();
		this->doodle->shoot(normalizedDirection);
	}

	if (button == FRMouseButton::RIGHT && !isReleased)
	{
		startTimeOfAbility = getTickCount();
		endTimeOfAbility = getTickCount() + 20000;
	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	if (k == FRKey::RIGHT) rightIsPressed = true;
	if (k == FRKey::LEFT) leftIsPressed = true;
}

void MyFramework::onKeyReleased(FRKey k)
{
	if (k == FRKey::RIGHT) rightIsPressed = false;
	if (k == FRKey::LEFT) leftIsPressed = false;
}

const char* MyFramework::GetTitle()
{
	std::cout << "GetTitle was called" << std::endl;
	return "Doodle";
}

void MyFramework::Update(float deltaT)
{
	Vector2 position = doodle->getPosition().Scale(1, 1);
	Vector2 velocity = doodle->getVelocity().Scale(1, 1);
	Vector2 gravity = doodle->getGravity().Scale(1, 1);

	// Update the position and velocity of the doodle
	position = position.addVector(velocity.Scale(deltaT));
	velocity = velocity.addVector(gravity.Scale(deltaT));

	// Calculate the total gravitational force on the player from all the black holes
	Vector2 totalGravitationalForce = Vector2(0, 0);
	for (auto& blackHole : collidableManager->getBlackHoles())
	{
		Vector2 blackHolePos(blackHole->getX(), blackHole->getY());
		float distanceDoodleToHole = position.Substract(blackHolePos).length();
		float forceMagnitude = CONSTANT_MAGNITUDE_BLACK_HOLE / (distanceDoodleToHole * distanceDoodleToHole);
		Vector2 forceDirection = (blackHolePos.Substract(position)).Normalize();
		Vector2 gravitationalForce = forceDirection.Scale(forceMagnitude);
		totalGravitationalForce = totalGravitationalForce.addVector(gravitationalForce);
	}

	//// Apply the total gravitational force to the player velocity
	velocity = velocity.addVector(totalGravitationalForce.Scale(deltaT));

	// Calculate the difference between the current and previous position of the doodle
	float yDiff = position.getY() - doodle->getPosition().getY();
	if (doodle->getInitialYValue() - doodle->getPosition().getY() > doodle->getGameUnitsPassed())
		doodle->setGameUnitsPassed(doodle->getInitialYValue() - doodle->getPosition().getY());


	// Check if the doodle has passed the middle of the screen
	if (doodle->getY() <= screenHeight / 2)
	{
		// Push down all other entities based on the difference between the current and previous position of the doodle
		if(velocity.getY()< 0)
		{
			collidableManager->IncreaseYForAllEntities(-yDiff);
			doodle->increaseInitialYvalue(-yDiff);
		}
	}

	//update bullets position and velocity
	doodle->updateBullets(deltaT, 20.f);
	
	// Update the position and velocity of the doodle normally
	doodle->updatePosition(position, this->screenHeight);
	doodle->updateVelocity(velocity);
	doodle->KeepDoodleInsideFrame(this->screenWidth, this->screenHeight); // keep also the bullets in frame
	doodle->KeepBulletsInsideFrame(this->screenWidth, this->screenHeight); // keep also the bullets in frame
}

void MyFramework::InitDoodle()
{
	float doodleX = screenWidth / 2 - 50 / 2;
	float doodleY = screenHeight - 2 * 50;
	Sprite* s = createSprite("../Dependencies/Data/blue-lik-right.png");
	doodle = std::make_shared<Doodle>(s, doodleX, doodleY, 50, 50, std::make_shared<Vector2>(0.f, -26.f), std::make_shared<Vector2>(0.f, 2.f));
}

void MyFramework::InitCollidableManager()
{
	collidableManager = std::make_shared<CollidableManager>(this->screenWidth, this->screenHeight);
	collidableManager->InitCollidables();
}

void MyFramework::HandleKeyboardInput()
{
	if (rightIsPressed) doodle->setX(doodle->getX() + 1.f);
	if (leftIsPressed) doodle->setX(doodle->getX() - 1.f);
}

void MyFramework::LockCameraToDoodle()
{
	// when the doodle gets to half the screen
	if (doodle->getY() <= screenHeight / 2)
	{
		collidableManager->IncreaseYForAllEntities(doodle->getVelocity().getY());
	}
	// increase all entities Y value by the ammount doodle decreases
}

void MyFramework::toggleOnAbility()
{

	if (getTickCount() > startTimeOfAbility && getTickCount() < endTimeOfAbility) // 20s
	{
		if (doodle->getCoins() >= 20)
		{
			doodle->addToCoins(-20);
			if (!abilitySwitch)
			{
				doodle->scaleVelocity(2.5);
				abilitySwitch = true;
			}
		}
	}
	else
	{
		if (abilitySwitch)
		{
			doodle->scaleVelocity(0.4);
			abilitySwitch = false;
		}
	}
	
}

void MyFramework::gameOver()
{
	this->Close();
	this->Init();
}

void MyFramework::drawDoodleBackground()
{
	drawSprite(backgroundSprite, 0, 0);
}

void MyFramework::computeScoreForDoodle()
{
	for (auto& elem : collidableManager->getEntities())
	{
		if (auto legitPlatform = dynamic_cast<LegitPlatform*>(elem.get()))
		{
			if (doodle->getY() < legitPlatform->getY() + legitPlatform->getHeight() && !legitPlatform->getPassed())
			{
				legitPlatform->setPassed(true);
				doodle->increasePlatformsPassed(1);
			}
		}
		if (auto fakePlatform = dynamic_cast<FakePlatform*>(elem.get()))
		{
			if (doodle->getY() < fakePlatform->getY() + fakePlatform->getHeight() && !fakePlatform->getPassed())
			{
				fakePlatform->setPassed(true);
				doodle->increasePlatformsPassed(1);
			}
		}
	}
}

void MyFramework::InitScore()
{
	score = std::make_shared<ScoreDoodle>(screenWidth, screenHeight);
}

void MyFramework::InitBackground()
{
	backgroundSprite = createSprite("../Dependencies/Data/hop-bck.png");
	if (backgroundSprite)
		setSpriteSize(backgroundSprite, screenWidth, screenHeight);
}

void MyFramework::setVariableMemebersToDefault()
{
	rightIsPressed = false;
	leftIsPressed = false;
	abilitySwitch = false;
	startTimeOfAbility = UINT_MAX;
	endTimeOfAbility = UINT_MAX;
}