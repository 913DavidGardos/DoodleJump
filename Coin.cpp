#include "Coin.h"

Coin::Coin(Sprite* sprite, float x, float y, float width, float height):
	Entity(sprite, x, y, width, height) {}

void Coin::CollisionResolution(std::shared_ptr<Entity> a)
{
	std::shared_ptr<Doodle> derived_ptr = std::dynamic_pointer_cast<Doodle>(a);
	if (derived_ptr)
	{
		if (this->isAlive())
		{
			derived_ptr->increaseCoins();
			this->setAlive(false);
		}
		std::cout << "number of coins: " << derived_ptr->getCoins() << std::endl;
	}
}