#pragma once
#include "SpriteObject.h"

// Forward declaration allowed because LevelScreen is not used in THIS file and is only a pointer
class LevelScreen;

class Door :
    public SpriteObject
{

public:

    Door(LevelScreen* newLevelScreen);
    void HandleCollision(SpriteObject& other) override;

private:

    LevelScreen* levelScreen;

};

