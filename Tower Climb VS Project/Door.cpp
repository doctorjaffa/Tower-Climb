#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	collisionOffset = sf::Vector2f(0, 10);
	collisionScale = sf::Vector2f(0.5f, 0.9f);
	collisionType = CollisionType::AABB;
}
