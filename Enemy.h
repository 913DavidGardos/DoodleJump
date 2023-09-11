#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(Sprite* sprite, float x, float y, float width, float height);

	void CollisionResolution(std::shared_ptr<Entity> a) override;
};