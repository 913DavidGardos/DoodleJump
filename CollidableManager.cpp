#include "CollidableManager.h"

CollidableManager::CollidableManager(): entities(), enemies(), screenWidth(0.f), screenHeight(0.f) {}

CollidableManager::CollidableManager(float screenWidth, float screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight)
{}

void CollidableManager::InitCollidables()
{
	///init platforms and enemies and so on
    generatePlatforms(20);
    generateEnemies(1);
    generateCoins(3);
    generateBlackHoles(2);
}

void CollidableManager::repositionEntitiesInScreen()
{
     //reposition entities
    std::vector<std::shared_ptr<Entity>> pushedOutOfScreenEntities;
    std::vector<std::shared_ptr<Entity>> entitiesNotInFrameYet;

    for (auto& element : entities)
        if (element->getY() >= screenHeight)
            pushedOutOfScreenEntities.push_back(element);
            
    for (auto& element : entities)
        if (element->getY() < 0)
            entitiesNotInFrameYet.push_back(element);

    for(auto& entity : entitiesNotInFrameYet)
        for (auto& element : pushedOutOfScreenEntities)
        {
            if (auto legitPlatform = dynamic_cast <LegitPlatform*>(element.get()))
            {
                repositionElement(element);
                if (legitPlatform->getPassed())
                    legitPlatform->setPassed(false);
                if (entity->collidesWith(element->getHitboxCopy()))
                    solveCollisionBetweenEntities(entity, element);
            }
            if (auto fakePlatform = dynamic_cast <FakePlatform*>(element.get()))
            {
                repositionElement(element);
                if (fakePlatform->getPassed())
                    fakePlatform->setPassed(false);
                if (entity->collidesWith(element->getHitboxCopy()))
                    solveCollisionBetweenEntities(entity, element);
            }
            if (auto blackHole = dynamic_cast <BlackHole*>(element.get()))
            {
                repositionElement(element);
                if (entity->collidesWith(element->getHitboxCopy()))
                    solveCollisionBetweenEntities(entity, element);
            }
            if (auto coin = dynamic_cast <Coin*>(element.get()))
            {
                repositionElement(element);
                if (entity->collidesWith(element->getHitboxCopy()))
                    solveCollisionBetweenEntities(entity, element);
            }
            if (auto enemy = dynamic_cast <Enemy*> (element.get())) // reposition the enemy
            {
                repositionEnemy(element, entitiesNotInFrameYet);
                if (entity->collidesWith(element->getHitboxCopy()))
                    solveCollisionBetweenEntities(entity, element);
            }
        }
}

void CollidableManager::solveCollisionBetweenEntities(std::shared_ptr<Entity> entity, std::shared_ptr<Entity> element)
{
    Vector2 displacement(0, 0);
    displacement = entity->displacementVec(element->getHitboxCopy());
    entity->setX(entity->getX() + displacement.getX());
    entity->setY(entity->getY() + displacement.getY());
}

const std::vector<std::shared_ptr<Entity>>& CollidableManager::getEntities()
{
    return entities;
}

template<typename T>
void CollidableManager::repositionElement(std::shared_ptr<T>& element)
{
    float x = std::rand() % ((int)element->getWidth() - (int)screenWidth);
    float y = (std::rand() % ((int)element->getHeight() - (int)screenHeight)) -screenHeight;

    element->setX(x);
    element->setY(y);
}

void  CollidableManager::generatePlatforms(int count)
{
    // Set the seed for the random number generator
    std::srand(std::time(nullptr));

    // Generate the platforms
    for (int i = 0; i < count; ++i) 
    {
        // Generate random values for the position
        int width = 60;
        int height = 13;
        
        float x = std::rand() % (width - (int)screenWidth);
        //float y = std::rand() % (height - (int)screenHeight);
        float y = (float)(std::rand() % (int)(height + screenHeight * 2) - screenHeight);

        float w = 60.f;
        float h = 13.f;

        std::shared_ptr<Entity> somePlatform = std::make_shared<LegitPlatform>(createSprite("../Dependencies/data/LegitPlatform.png"), x, y, w, h);
        
        bool colideFound = false;
        if(!entities.empty())
        for (const auto& elem : entities)
        {
            if (somePlatform->collidesWith(elem->getHitboxCopy()))
            {
                colideFound = true;
                break;
            }
        }

        int coinFlip = std::rand() % 5;

        if (!colideFound)
        {
            if (coinFlip < 4)
            {
                std::shared_ptr<Entity> ptr = std::make_shared<LegitPlatform>(createSprite("../Dependencies/data/LegitPlatform.png"), x, y, w, h);
                entities.push_back(ptr);
            }
            else
            {
                std::shared_ptr<Entity> ptr = std::make_shared<FakePlatform>(createSprite("../Dependencies/data/FakePlatform.png"), x, y, w, h);
                entities.push_back(ptr);
            }
        }
    } 

}

void CollidableManager::manageCoins()
{
    coins.erase(std::remove_if(coins.begin(), coins.end(), [](const auto& coin) {
        return !coin->isAlive(); }), coins.end());

    if (coins.empty())
        this->generateCoins(3);
}

void CollidableManager::generateCoins(int count)
{
    for (int i = 0; i < count; ++i)
    {
        int width = 40;
        int height = 40;

        float x = std::rand() % (width - (int)screenWidth);
        float y = (float)(std::rand() % (height - (int)screenHeight)) - screenHeight;;

        float w = 40.f;
        float h = 40.f;

        std::shared_ptr<Entity> somePlatform = std::make_shared<Coin>(createSprite("../Dependencies/data/Coin.png"), x, y, w, h);

        bool colideFound = false;
        if (!entities.empty())
            for (const auto& elem : entities)
            {
                if (somePlatform->collidesWith(elem->getHitboxCopy()))
                {
                    colideFound = true;
                    break;
                }
            }

        if (!colideFound)
        {
            std::shared_ptr<Coin> ptrCoin= std::make_shared<Coin>(createSprite("../Dependencies/data/Coin.png"), x, y, width, height);
            std::shared_ptr<Entity> ptr = ptrCoin;
            entities.push_back(ptr);
            coins.push_back(ptrCoin);
        }
    }
}

void CollidableManager::renderCollidables()
{
    for (const auto& entity : entities)
    {
        if(entity->isAlive())
            entity->render();
    }
}

void CollidableManager::checkCollisions(std::shared_ptr<Doodle> doodle)
{
    for (auto& element : entities) // doodle and entities
    {
        if(element->isAlive())
        {
            if (element->collidesWith(doodle->getHitboxCopy()))
            {
                element->CollisionResolution(doodle);
            }
        }
    }
    for (const auto& enemy : enemies) // every enemie with every bullet
    {
        for (const auto& bullet : doodle->getActiveBullets()) 
        {
            if (bullet->collidesWith(enemy->getHitboxCopy()))
            {
                enemy->setAlive(false);
            }
        }
    }
}

void CollidableManager::generateEnemies(int count)
{
    float width = 35.f;
    float height = 35.f;
    float x = 0.f, y = 0.f;
    // Set the seed for the random number generator
    
    for(int i = 0; i < count; i++)
    {
        int position = std::rand() % (entities.size() - 1);

        auto platformForSpawn = entities.at(position).get();

        if (auto fakePlatform = dynamic_cast <FakePlatform*> (platformForSpawn))
        {
            x = fakePlatform->getX() + (fakePlatform->getWidth()) / 2.f - width / 2;
            y = fakePlatform->getY() - height;
            std::shared_ptr<Enemy>ptrEnemy = std::make_shared<Enemy>(createSprite("../Dependencies/data/Enemy.png"), x, y, width, height);
            std::shared_ptr<Entity> ptr = ptrEnemy;
            entities.push_back(ptr);
            enemies.push_back(ptrEnemy);
        }

        if (auto legitPlatform = dynamic_cast <LegitPlatform*> (platformForSpawn))
        {
            x = legitPlatform->getX() + (legitPlatform->getWidth()) / 2.f - width / 2;
            y = legitPlatform->getY() - height;
            std::shared_ptr<Enemy>ptrEnemy = std::make_shared<Enemy>(createSprite("../Dependencies/data/Enemy.png"), x, y, width, height);
            std::shared_ptr<Entity> ptr = ptrEnemy;
            entities.push_back(ptr);
            enemies.push_back(ptrEnemy);
        }
    }
}

void CollidableManager::generateBlackHoles(int count)
{
    float width = 35.f;
    float height = 35.f;

    for (int i = 0; i < count; i++)
    {
        float x = std::rand() % (int)(width - (int)screenWidth);
        float y = (float)(std::rand() % (int)(height + screenHeight * 2) - screenHeight);

        std::shared_ptr<BlackHole> ptrBlackHole = std::make_shared<BlackHole>(createSprite("../Dependencies/data/BlackHole.png"), x, y, width, height);
        std::shared_ptr<Entity> ptr = ptrBlackHole;
        entities.push_back(ptr);
        blackHoles.push_back(ptrBlackHole);
    }
}

void CollidableManager::IncreaseYForAllEntities(float amount)
{
    for (auto& element : entities)
    {
        Vector2 position(element->getX(), element->getY());
        Vector2 change(0, amount);
        Vector2 result = position.addVector(change);

        element->setY(result.getY());
    }
}

const std::vector<std::shared_ptr<BlackHole>>& CollidableManager::getBlackHoles()
{
    return blackHoles;
}

void CollidableManager::repositionEnemy(std::shared_ptr<Entity> enemy, std::vector<std::shared_ptr<Entity>> entities)
{
    enemy->setAlive(true);
    //std::cout << "rand value" << randomValue<<std::endl;

    //reposition enemy
    int position = std::rand() % (entities.size() - 1);

    auto platformForSpawn = entities.at(position).get();
    if (auto fakePlatform = dynamic_cast <FakePlatform*> (platformForSpawn))
    {
        float x = fakePlatform->getX() + (fakePlatform->getWidth()) / 2.f - enemy->getWidth() / 2;
        float y = fakePlatform->getY() - enemy->getHeight();
        enemy->setX(x);
        enemy->setY(y);
    }
    if (auto legitPlatform = dynamic_cast <LegitPlatform*> (platformForSpawn))
    {
        float x = legitPlatform->getX() + (legitPlatform->getWidth()) / 2.f - enemy->getWidth() / 2;
        float y = legitPlatform->getY() - enemy->getHeight();
        enemy->setX(x);
        enemy->setY(y);
    }

}
