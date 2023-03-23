#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, tempDoor()
	, platforms()
{
	player.SetPosition(500, 500);
	tempDoor.SetPosition(500, 500);

	platforms.push_back(new Platform(sf::Vector2f(500, 650)));
	platforms.push_back(new MovingPlatform(sf::Vector2f(500, 700), sf::Vector2f(0, 700), sf::Vector2f(1000, 700)));
	platforms.push_back(new BreakingPlatform(sf::Vector2f(750, 1000)));
	platforms.push_back(new DeadlyPlatform(sf::Vector2f(1000, 700)));

}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);

	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Update(frameTime);
	}

	player.SetColliding(false);
	tempDoor.SetColliding(false);

	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->SetColliding(false);
	}

	for (int i = 0; i < platforms.size(); ++i)
	{
		if (platforms[i]->CheckCollision(player))
		{
			player.SetColliding(true);
			platforms[i]->SetColliding(true);
			player.HandleCollision(*platforms[i]);
			platforms[i]->HandleCollision(player);
		}
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

	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}

	player.Draw(target);
}
