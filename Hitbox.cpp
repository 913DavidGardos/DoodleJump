#include "Hitbox.h"

Hitbox::Hitbox(float x, float y, float width, float height) :
	x(x), y(y), width(width), height(height) {}

float Hitbox::getWidth()
{
	return this->width;
}
float Hitbox::getHeight()
{
	return this->height;
}

void Hitbox::setCollision(bool value)
{
	this->collision = value;
}

bool Hitbox::getCollision()
{
	return this->collision;
}

bool Hitbox::contains(float x_, float y_)
{
	return x_ >= x && x_ <= x + width && y_ >= y && y_ <= y + height;
}

bool Hitbox::contains(Hitbox other)
{
	return other.getX() >= x && other.getX() + other.getWidth()  <= x + width && 
		   other.getY() >= y && other.getY() + other.getHeight() <= y + height;
}

void Hitbox::setX(float val)
{
	this->x = val;
}

void Hitbox::setY(float val)
{
	this->y = val;
}

float Hitbox::getX()
{
	return this->x;
}
float Hitbox::getY()
{
	return this->y;
}

