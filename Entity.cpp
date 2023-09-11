#include "Entity.h"

Entity::Entity(Sprite* sprite, float x, float y, float width, float height) :
    sprite(sprite), hitbox(std::make_shared<Hitbox>(x, y, width, height)), isActive(true) {}

void Entity::render() const
{
    if(this->isAlive())
    {
        setSpriteSize(this->sprite, (int)hitbox->getWidth(), (int)hitbox->getHeight());
        drawSprite(this->sprite, (int)hitbox->getX(), (int)hitbox->getY());
    }
}

bool Entity::isAlive() const {
    return isActive;
}

void Entity::setAlive(bool alive) {
    isActive = alive;
}

float Entity::getX()
{
    return hitbox->getX();
}

float Entity::getY()
{
    return hitbox->getY();
}

float Entity::getWidth()
{
    return hitbox->getWidth();
}

float Entity::getHeight()
{
    return hitbox->getHeight();
}

void Entity::setX(float x)
{
    hitbox->setX(x);
}

void Entity::setY(float y)
{
    hitbox->setY(y);
}

void Entity::updateSpriteTo(std::string path)
{
    destroySprite(sprite);
    sprite = createSprite(path.c_str());
    setSpriteSize(sprite, getWidth(), getHeight());
}

bool Entity::collidesWith(Hitbox other)
{
    bool overlapX = (hitbox->getX() + hitbox->getWidth() >= other.getX()) && (other.getX() + other.getWidth() >= hitbox->getX());

    // Check for overlap in the y-axis
    bool overlapY = (hitbox->getY() + hitbox->getHeight() >= other.getY()) && (other.getY() + other.getHeight() >= hitbox->getY());

    // If there's overlap in both axes, there's a collision
    return overlapX && overlapY;
}

Vector2 Entity::displacementVec(Hitbox other)
{
    float dx = (hitbox->getX() + hitbox->getWidth() / 2) - (other.getX() + other.getWidth() / 2);
    float dy = (hitbox->getY() + hitbox->getHeight() / 2) - (other.getY() + other.getHeight() / 2);
    return Vector2(dx, dy);
}

const std::shared_ptr<Hitbox>& Entity::getHitbox()
{
    return this->hitbox;
}

Hitbox Entity::getHitboxCopy()
{
    return *hitbox;
}

Entity::~Entity() {
    if(this->sprite)
        destroySprite(this->sprite);
}