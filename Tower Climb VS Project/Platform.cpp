#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
	, position(1300, 250)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Platform.png"));
	sprite.setPosition(position);
}
