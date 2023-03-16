#include "Player.h"
#include "AssetManager.h"

enum class PhysicsType {
    FORWARD_EULER,
    BACKWARD_EULER,
    SYMPLECTIC_EULER,
    POSITION_VERLET,
    VELOCITY_VERLET
};


Player::Player()
	: SpriteObject()
    , twoFramesOldPos(100, 300)
	, velocity()
	, acceleration()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/PlayerStand.png"));
    collisionOffset = sf::Vector2f(0, 30);
    collisionScale = sf::Vector2f(0.5f, 0.5f);
}

void Player::Update(sf::Time frameTime)
{
    const float DRAG_MULT = 10.0f;
    const PhysicsType physics = PhysicsType::FORWARD_EULER;

    switch (physics)
    {
    case PhysicsType::FORWARD_EULER:
        {
            // EXPLICIT EULER (FORWARD EULER)

            SetPosition(GetPosition() + velocity * frameTime.asSeconds());
            velocity = velocity + acceleration * frameTime.asSeconds();

            // Drag
            velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();

            // Update acceleration
            UpdateAcceleration();
        }
        break;

    case PhysicsType::BACKWARD_EULER:
        {
            // IMPLICIT EULER (BACKWARD EULER) 
        
            // Update acceleration
            UpdateAcceleration();

            velocity = velocity + acceleration * frameTime.asSeconds();

            // Drag
            velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();

            SetPosition(GetPosition() + velocity * frameTime.asSeconds());
        }
        break;

    case PhysicsType::SYMPLECTIC_EULER:
        {
            // SEMI-IMPLICIT EULER (SYMPLECTIC_EULER)

            velocity = velocity + acceleration * frameTime.asSeconds();

            // Drag
            velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();

            SetPosition(GetPosition() + velocity * frameTime.asSeconds());

            // Update acceleration
            UpdateAcceleration();
        }
        break;

    case PhysicsType::POSITION_VERLET:
    {
        // Update acceleration
        UpdateAcceleration();

        sf::Vector2f lastFramePos = GetPosition();

        // Current frame's position 
        SetPosition(2.0f*lastFramePos - twoFramesOldPos + acceleration * frameTime.asSeconds() * frameTime.asSeconds());

        // Two frames ago (for next frame)
        twoFramesOldPos = lastFramePos;
    }
    break;

    case PhysicsType::VELOCITY_VERLET:
    {
        // Get half frame velocity using previous frame's acceleration
        sf::Vector2f halfFrameVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

        //Get new frame's position using half frame velocity
        SetPosition(GetPosition() + halfFrameVelocity * frameTime.asSeconds());

        // Update acceleration
        UpdateAcceleration();

        // Get new frame's velocity using half frame velocity and updated acceleration
        velocity = halfFrameVelocity + acceleration * frameTime.asSeconds() / 2.0f;

        // Drag
        velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();
    }
    break;

    default:
        break;
    }
}

void Player::UpdateAcceleration()
{
    const float ACCEL = 8500;

    // Update acceleration
    acceleration.x = 0;
    acceleration.y = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        acceleration.x = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        acceleration.x = ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        acceleration.y = -ACCEL;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        acceleration.y = ACCEL;
    }

}
