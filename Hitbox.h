#pragma once
#include "Vector2.h"

class Hitbox
{
public:
	Hitbox(float x, float y, float width, float height);

	float getX();
	float getY();
	float getWidth();
	float getHeight();
	void setX(float);
	void setY(float);
	void setCollision(bool value);
	bool getCollision();
	bool contains(float x_, float y_);
	bool contains(Hitbox other);
	//Vector2 virtual getNormal() const;

private:
	float x;
	float y;
	float width;
	float height;
	bool collision = false;
};