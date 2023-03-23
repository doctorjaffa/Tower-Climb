#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, tempDoor()
	, tempPlatform()
	, tempMovingPlatform(sf::Vector2f(0,700), sf::Vector2f(1000, 700))
{
	player.SetPosition(500, 500);
	tempPlatform.SetPosition(500, 650);
	tempMovingPlatform.SetPosition(sf::Vector2f(500, 700));
	tempDoor.SetPosition(500, 500);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	tempMovingPlatform.Update(frameTime);

	player.SetColliding(false);
	tempPlatform.SetColliding(false);
	tempMovingPlatform.SetColliding(false);
	tempDoor.SetColliding(false);

	if (player.CheckCollision(tempPlatform))
	{
		player.SetColliding(true);
		tempPlatform.SetColliding(true);
		player.HandleCollision(tempPlatform);
	}
	if (player.CheckCollision(tempMovingPlatform))
	{
		player.SetColliding(true);
		tempMovingPlatform.SetColliding(true);
		player.HandleCollision(tempMovingPlatform);
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
	tempMovingPlatform.Draw(target);
	player.Draw(target);
}
