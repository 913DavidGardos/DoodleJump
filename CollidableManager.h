#pragma once
#include "Score.h"
#include "Doodle.h"
#include "Enemy.h"
#include "BlackHole.h"
#include "LegitPlatform.h"
#include "FakePlatform.h"
#include "Coin.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class CollidableManager
{
private:

	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<BlackHole>> blackHoles;
	std::vector<std::shared_ptr<Coin>> coins;


	float screenWidth;
	float screenHeight;

	void repositionEnemy(std::shared_ptr<Entity> enemy, std::vector<std::shared_ptr<Entity>> entities);
	void solveCollisionBetweenEntities(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> element);

public:
	CollidableManager();
	CollidableManager(float screenWidth, float screenHeight);

	CollidableManager(const CollidableManager& o) = delete;
	void operator = (const CollidableManager& o) = delete;

	void InitCollidables();
	void resolveCollisionBetweenEntities();
	void repositionEntitiesInScreen();

	const std::vector<std::shared_ptr<Entity>>& getEntities();
	
	template<typename T>
	void repositionElement(std::shared_ptr<T>& element);
	
	void generateEnemies(int count);
	void generateBlackHoles(int count);
	void generatePlatforms(int count);
	void generateCoins(int count);
	
	void renderCollidables();
	void checkCollisions(std::shared_ptr<Doodle> doodle);
	void IncreaseYForAllEntities(float amount);

	const std::vector<std::shared_ptr<BlackHole>>& getBlackHoles();

	void manageCoins();
};

