#pragma once
#include "Entity.h"
#include "Doodle.h"
#include <iostream>
class LegitPlatform : public Entity
{
public:
	virtual void CollisionResolution(std::shared_ptr<Entity> a);
	bool collidesWith(Hitbox other) override;

	//LegitPlatform(float x, float y, float width, float height, Sprite* sprite);
	LegitPlatform(Sprite* sprite, float x, float y, float width, float height);

	bool getPassed();

	void setPassed(bool value);

private:
	bool passed;
};

