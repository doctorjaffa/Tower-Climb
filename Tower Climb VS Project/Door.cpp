#include "Door.h"
#include "AssetManager.h"

Door::Door()
	: SpriteObject()
	, position(1300, 100)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	sprite.setPosition(position);
}
