#include "LegitPlatform.h"

void LegitPlatform::CollisionResolution(std::shared_ptr<Entity> doodle)
{

    std::shared_ptr<Doodle> derived_ptr = std::dynamic_pointer_cast<Doodle>(doodle);
    if (derived_ptr) 
    {
        if(derived_ptr->getVelocity().getY() > 0)
            derived_ptr->Bounce();
    }
    else 
    {
        std::cout << "dynamic pointer cast fail\n";
        return;
    }
}

bool LegitPlatform::collidesWith(Hitbox doodle)
{
    std::shared_ptr<Hitbox> hitbox1 = this->getHitbox();
    Hitbox hitbox2 = doodle;

    // Check if the hitboxes overlap in the x-axis
    bool xOverlap = (hitbox1->getX() + hitbox1->getWidth() > hitbox2.getX()) && (hitbox2.getX() + hitbox2.getWidth() > hitbox1->getX());

    // Check if the hitboxes overlap in the y-axis, and that hitbox2' bottom collides with hitbox1' top
    bool yOverlap = (hitbox2.getY() + hitbox2.getHeight() >= hitbox1->getY()) && (hitbox2.getY() + hitbox2.getHeight() <= hitbox1->getY() + hitbox1->getHeight());

    // If both xOverlap and yOverlap are true, the hitboxes collide
    return xOverlap && yOverlap;
}

LegitPlatform::LegitPlatform(Sprite* sprite, float x, float y, float width, float height):
	Entity(sprite, x, y, width, height), passed(false)
{}

bool LegitPlatform::getPassed()
{
    return passed;
}

void LegitPlatform::setPassed(bool value)
{
    passed = value;
}