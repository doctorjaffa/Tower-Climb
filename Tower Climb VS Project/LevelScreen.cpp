#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
{
	player.SetPosition(500, 500);
	tempPlatform.SetPosition(500, 650);
	tempDoor.SetPosition(500, 500);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);

	player.SetColliding(false);
	tempPlatform.SetColliding(false);
	tempDoor.SetColliding(false);

	if (player.CheckCollision(tempPlatform))
	{
		player.SetColliding(true);
		tempPlatform.SetColliding(true);
	}
	if (player.CheckCollision(tempDoor))
	{
		player.SetColliding(true);
		tempDoor.SetColliding(true);
	}

}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	tempDoor.Draw(target);
	tempPlatform.Draw(target);
	player.Draw(target);
}
