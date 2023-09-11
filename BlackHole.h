#pragma once
#include "Entity.h"

class BlackHole : public Entity
{
public:
	BlackHole(Sprite* sprite, float x, float y, float width, float height);

	void CollisionResolution(std::shared_ptr<Entity> a) override;
};

