#include "Projectile.h"

Projectile::Projectile(Sprite* sprite, float x, float y, float width, float height, Vector2 direction):
	Entity(sprite, x, y, width, height), direction(direction){}


void Projectile::update(float deltaT, float length)
{
	this->setX(this->getX() + length * direction.getX() * deltaT);
	this->setY(this->getY() + length * direction.getY() * deltaT);
}

void Projectile::CollisionResolution(std::shared_ptr<Entity> a)
{
	// set enemy to dead 
}
