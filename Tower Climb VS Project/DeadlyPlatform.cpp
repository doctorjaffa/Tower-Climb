#include "DeadlyPlatform.h"
#include "AssetManager.h"
#include "LevelScreen.h"
#include "EndPanel.h"

DeadlyPlatform::DeadlyPlatform(sf::Vector2f newPosition, LevelScreen* newLevelScreen)
	: Platform(newPosition)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/DeadlyPlatform.png"));
}

void DeadlyPlatform::HandleCollision(SpriteObject& other)
{
	other.SetAlive(false);
	levelScreen->TriggerEndState(true);
}
