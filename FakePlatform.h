#pragma once
#include "Entity.h"
#include "Doodle.h"
#include "Hitbox.h"
#include <iostream>

class FakePlatform : public Entity
{
public:
	virtual void CollisionResolution(std::shared_ptr<Entity> a);

	//FakePlatform(float x, float y, float width, float height, Sprite* sprite);
	FakePlatform(Sprite* sprite, float x, float y, float width, float height);

	bool getPassed();

	void setPassed(bool value);
	
private:
	bool passed;
};

