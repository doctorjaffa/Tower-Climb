#include "EndPanel.h"
#include "AssetManager.h"

EndPanel::EndPanel(sf::RenderWindow* newWindow)
	: background()
	, title()
	, message()
	, position(0,0)
	, window(newWindow)
{
	background.setTexture(AssetManager::RequestTexture("Assets/Graphics/Panel.png"));
	background.setScale(5.0f, 5.0f);

	title.setFont(AssetManager::RequestFont("Assets/Fonts/mainFont.ttf"));
	title.setCharacterSize(70);
	title.setString("YOU WIN!");
	title.setFillColor(sf::Color::Black);

	message.setFont(AssetManager::RequestFont("Assets/Fonts/mainFont.ttf"));
	message.setCharacterSize(30);
	message.setString("Press R to restart, \nor ESCAPE to quit.");
	message.setFillColor(sf::Color::Black);

	float xPos = window->getSize().x * 0.5f - background.getGlobalBounds().width * 0.5f;
	float yPos = window->getSize().y * 0.5f - background.getGlobalBounds().height * 0.5f;
	SetPosition(sf::Vector2f(xPos, yPos));
}

void EndPanel::Update(sf::Time frameTime)
{
}

void EndPanel::Draw(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(title);
	target.draw(message);
}

void EndPanel::SetPosition(sf::Vector2f newPosition)
{
	background.setPosition(sf::Vector2f(newPosition));

	// Center the title on the x direction
	float titleX = background.getGlobalBounds().width * 0.5f - title.getGlobalBounds().width * 0.5f;
	title.setPosition(sf::Vector2f(newPosition.x + titleX, newPosition.y + 50));

	// Center the message on the x and y direction
	float messageX = background.getGlobalBounds().width * 0.5f - message.getGlobalBounds().width * 0.5f;
	float messageY = background.getGlobalBounds().height * 0.5f - message.getGlobalBounds().height * 0.5f;
	message.setPosition(sf::Vector2f(newPosition.x + messageX, newPosition.y + messageY));
}
