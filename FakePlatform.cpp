#include "FakePlatform.h"


void FakePlatform::CollisionResolution(std::shared_ptr<Entity> a)
{
    // should not be drawn anymore
}

FakePlatform::FakePlatform(Sprite* sprite, float x, float y, float width, float height):
    Entity(sprite, x, y, width, height), passed(false) {}


bool FakePlatform::getPassed()
{
    return passed;
}

void FakePlatform::setPassed(bool value)
{
    passed = value;
}