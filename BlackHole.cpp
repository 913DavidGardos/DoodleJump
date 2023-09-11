#include "BlackHole.h"

BlackHole::BlackHole(Sprite* sprite, float x, float y, float width, float height):
Entity(sprite, x, y, width, height){}

void BlackHole::CollisionResolution(std::shared_ptr<Entity> a)
{
	a->setAlive(false);
}
