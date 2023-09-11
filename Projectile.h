#pragma once
#include "Entity.h"
class Projectile : public Entity
{
public:
	Projectile(Sprite* sprite, float x, float y, float width, float height, Vector2 direction);

	void update(float deltaT, float length);
	void CollisionResolution(std::shared_ptr<Entity> a) override;

	Vector2 getDirection();

private:
	Vector2 direction;
};

