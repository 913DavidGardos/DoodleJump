#include "Doodle.h"
#include <iostream>

Doodle::Doodle(Sprite* sprite, float x, float y, float width, float height, std::shared_ptr<Vector2> velocity, std::shared_ptr<Vector2> gravity)
	: Entity(sprite, x, y, width, height), velocity(velocity), gravity(gravity), velocityXvalue(velocity->getX()), velocityYvalue(velocity->getY()), initialYvalue(y)
{}

void Doodle::setupSprite()
{
	this->sprite = createSprite("../Dependencies/data/blue-lik-left.png");
	if (this->sprite != nullptr)
		setSpriteSize(this->sprite, (int)hitbox->getWidth(), (int)hitbox->getHeight());
	else
		std::cout << "sprite is null" << std::endl;
}

void Doodle::DrawDoodle()
{
	drawSprite(this->sprite, (int)hitbox->getX(), (int)hitbox->getY());
}


float Doodle::getX()
{
	return hitbox->getX();
}

float Doodle::getY()
{
	return hitbox->getY();
}

Vector2 Doodle::getVelocity()
{
	return *velocity;
}

Vector2 Doodle::getGravity()
{
	return *gravity;
}

Vector2 Doodle::getPosition()
{
	Vector2 v(hitbox->getX(), hitbox->getY());
	return v;
}

const std::vector<std::unique_ptr<Projectile>>& Doodle::getActiveBullets()
{
    return this->activeBullets;
}

void Doodle::renderBullets()
{
    for (const auto& bullet : activeBullets)
    {
        bullet->render();
    }
}

void Doodle::updatePosition(Vector2& pos, float screenHeight)
{
    hitbox->setX(pos.getX());

    if(pos.getY() > screenHeight/3)
        hitbox->setY(pos.getY());
}

void Doodle::updateVelocity(Vector2& ve)
{
    *velocity = ve;
}

void Doodle::updateBullets(float deltaT, float length)
{
    for (auto it = activeBullets.rbegin(); it != activeBullets.rend(); it++)
    {
        auto bullet = it->get();
        if (bullet->isAlive())
        {
            bullet->update(deltaT, length);
        }
    }

    //erase bullets that are flagged dead
    activeBullets.erase(std::remove_if(activeBullets.begin(), activeBullets.end(), [](const auto& bullet) {
        return !bullet->isAlive(); }), activeBullets.end());
}

void Doodle::Bounce()
{
    Vector2 vs = Vector2(velocityXvalue, velocityYvalue);
    *velocity = vs;
}

void Doodle::scaleVelocity(float scalar)
{
    velocityXvalue *= scalar;
    velocityYvalue *= scalar;
    Vector2 vs = Vector2(velocityXvalue, velocityYvalue);
    *velocity = vs;
}

void Doodle::KeepDoodleInsideFrame(int screenWidth, int screenHeight)
{
    // Calculate the position of the hitbox's edges
    int hx1 = hitbox->getX();
    int hx2 = hitbox->getX() + hitbox->getWidth();
    int hy1 = hitbox->getY();
    int hy2 = hitbox->getX() + hitbox->getHeight();

    if ( hitbox->getY() + hitbox->getHeight() >= screenHeight) {
        // Hitbox collides with the bottom edge of the game frame
        this->setAlive(false);
        std::cout << "bottom collision" << std::endl;
        std::cout << "velocity x = " << velocity->getX() << "velocity y = " << velocity->getY() << std::endl;
    }

    if (hx1 > screenWidth) {
        // Hitbox has passed the right edge of the game frame, wrap around to the left
        hx1 = 0 - hitbox->getWidth();
        hx2 = 0;
        hitbox->setX(hx1);
    }
    else if (hx2 < 0) {
        // Hitbox has passed the left edge of the game frame, wrap around to the right
        hx1 = screenWidth;
        hx2 = screenWidth + hitbox->getWidth();
        hitbox->setX(hx1);
    }
}

void Doodle::KeepBulletsInsideFrame(int screenWidth, int screenHeight)
{
    // Calculate the position of the hitbox's edges
    for(const auto& bullet : activeBullets)
    {
        int hx1 = bullet->getX();
        int hx2 = bullet->getX() + bullet->getWidth();
        int hy1 = bullet->getY();
        int hy2 = bullet->getX() + bullet->getHeight();

        if (bullet->getY() + bullet->getHeight() >= screenHeight) {
            // Hitbox collides with the bottom edge of the game frame
            bullet->setAlive(false);
        }
        if (bullet->getY() + bullet->getHeight() < 0)
        {
            bullet->setAlive(false);
        }

        if (hx1 > screenWidth) {
            // Hitbox has passed the right edge of the game frame, wrap around to the left
            hx1 = 0 - bullet->getWidth();
            hx2 = 0;
            bullet->setX(hx1);
        }
        else if (hx2 < 0) {
            // Hitbox has passed the left edge of the game frame, wrap around to the right
            hx1 = screenWidth;
            hx2 = screenWidth + bullet->getWidth();
            bullet->setX(hx1);
        }
    }
}

void Doodle::CollisionResolution(std::shared_ptr<Entity> a)
{
    this->Bounce();
}

void Doodle::shoot(Vector2 direction)
{
    float bulletX = this->getX();
    float bulletY = this->getY();
    float bulletWidth = 10.f;
    float bulletHeight = 10.f;

    activeBullets.push_back(std::make_unique<Projectile>(createSprite("../Dependencies/data/bullet.jpg"), bulletX, bulletY, bulletWidth, bulletHeight, direction));
}

void Doodle::increasePlatformsPassed(int amount)
{
    platformsPassed++;
}

int Doodle::getPlatformsPassed()
{
    return platformsPassed;
}

float Doodle::getGameUnitsPassed()
{
    return gameUnitsPassed;
}


int Doodle::getInitialYValue()
{
    return initialYvalue;
}

void Doodle::increaseInitialYvalue(float amount)
{
    initialYvalue += amount;
}

void Doodle::increaseCoins()
{
    coins++;
}

int Doodle::getCoins()
{
    return coins;
}

void Doodle::addToCoins(int amount)
{
    coins += amount;
}

void Doodle::setGameUnitsPassed(float amount)
{
    gameUnitsPassed = amount;
}
