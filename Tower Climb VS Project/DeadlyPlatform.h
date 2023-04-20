#pragma once
#include "Platform.h"

// Forward declaration allowed because LevelScreen is not used in THIS file and is only a pointer
class LevelScreen;

class DeadlyPlatform :
    public Platform
{
public:

    DeadlyPlatform(sf::Vector2f newPosition, LevelScreen* newLevelScreen);

    void HandleCollision(SpriteObject& other) override;

private:

    LevelScreen* levelScreen;

};
