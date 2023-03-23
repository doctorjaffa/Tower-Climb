#include "DeadlyPlatform.h"
#include "AssetManager.h"

DeadlyPlatform::DeadlyPlatform()
	: Platform()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/DeadlyPlatform.png"));
}

void DeadlyPlatform::HandleCollision(SpriteObject& other)
{
	other.SetAlive(false);
}
