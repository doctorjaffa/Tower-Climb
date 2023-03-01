#pragma once
#include <SFML/Graphics.hpp>

class Screen;

class Game
{

public:

	Game();

	void RunGameLoop();

	void EventHandling();
	void Update();
	void Draw();


private:

	sf::RenderWindow window;
	sf::Clock gameClock;

	Screen* currentScreen;

};

