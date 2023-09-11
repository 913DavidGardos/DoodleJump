#include "Enemy.h"

Enemy::Enemy(Sprite* sprite, float x, float y, float width, float height) :
	Entity(sprite, x, y, width, height) {}

void Enemy::CollisionResolution(std::shared_ptr<Entity> a)
{
    std::shared_ptr<Hitbox> hitbox1 = this->getHitbox();
    Hitbox hitbox2 = a->getHitboxCopy();

    bool yOverlap = (hitbox2.getY() + hitbox2.getHeight() - hitbox1->getY() < hitbox1->getHeight() / 10);

    if (yOverlap)
    {
        // enemy dies
        this->setAlive(false);
    }
    else
    {
        //doodle dies
        a->setAlive(false);
    }
}


