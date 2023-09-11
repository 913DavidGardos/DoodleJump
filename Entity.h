#pragma once
#include "Framework.h"
#include "Hitbox.h"
#include "Vector2.h"
#include <memory>
#include <string>

class Entity {
protected:
    Sprite* sprite;
    std::shared_ptr<Hitbox> hitbox;
    bool isActive;

public:
    Entity(Sprite* sprite, float, float, float, float);

    virtual void render() const;
    bool isAlive() const;
    void setAlive(bool alive);
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    void setX(float x);
    void setY(float y);
    void updateSpriteTo(std::string path);

    virtual void CollisionResolution(std::shared_ptr<Entity> a) = 0;
    virtual bool collidesWith(Hitbox other);

    Vector2 displacementVec(Hitbox other);

    const std::shared_ptr<Hitbox>& getHitbox();
    Hitbox getHitboxCopy();
    Vector2& getVelocity();
    virtual ~Entity();
};
