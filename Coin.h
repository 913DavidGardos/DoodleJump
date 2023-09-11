#pragma once
#include "Entity.h"
#include "Doodle.h"
#include <iostream>

class Coin : public Entity
{
public:
	Coin(Sprite* sprite, float x, float y, float width, float height);

	void CollisionResolution(std::shared_ptr<Entity> a) override;
};

