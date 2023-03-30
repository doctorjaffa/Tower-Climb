#pragma once
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include "EndPanel.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game;
class Platform;

class LevelScreen :
    public Screen
{

public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerEndState(bool _win);

private:

    Player player;
    Door tempDoor;
    EndPanel endPanel;
    bool gameRunning;

    std::vector<Platform*> platforms;
};

