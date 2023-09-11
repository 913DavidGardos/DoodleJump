#pragma once
#include "Entity.h"
#include "Projectile.h"
#include <vector>

class Doodle : public Entity
{
public:
	Doodle(Sprite* sprite, float x, float y, float width, float height, std::shared_ptr<Vector2> velocity, std::shared_ptr<Vector2> gravity);
	void setupSprite();
	void DrawDoodle();

	float getX();
	float getY();
	int getPlatformsPassed();
	int getInitialYValue();
	float getGameUnitsPassed();
	Vector2 getVelocity();
	Vector2 getGravity();
	Vector2 getPosition();
	const std::vector<std::unique_ptr<Projectile>>& getActiveBullets();


	void setGameUnitsPassed(float amount);

	void renderBullets();
	void updatePosition(Vector2&, float screenHight);
	void updateVelocity(Vector2&);
	void updateBullets(float deltaT, float length);
	void Bounce();
	void scaleVelocity(float scalar);
	void KeepDoodleInsideFrame(int, int);
	void KeepBulletsInsideFrame(int, int);
	virtual void CollisionResolution(std::shared_ptr<Entity> a);
	void shoot(Vector2 direction);

	void increasePlatformsPassed(int amount);
	void increaseInitialYvalue(float amount);
	void increaseCoins();
	int getCoins();
	void addToCoins(int amount);

private:
	Sprite* sprite = nullptr;
	std::shared_ptr<Vector2> velocity;
	std::shared_ptr<Vector2> gravity;
	std::vector<std::unique_ptr<Projectile>> activeBullets;
	float velocityXvalue = 0.f;
	float velocityYvalue = 0.f;
	int platformsPassed = 0;
	float gameUnitsPassed = 0.f;
	int initialYvalue;
	int coins = 0;
};

