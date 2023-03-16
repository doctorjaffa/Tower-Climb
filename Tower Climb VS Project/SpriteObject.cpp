#include "SpriteObject.h"
#include "VectorHelper.h"
#include <algorithm>

SpriteObject::SpriteObject()
	: sprite()
	, position(0, 0)
	, colliding(false)
	, collisionOffset(0, 0)
	, collisionScale(1, 1)
	, collisionType(CollisionType::AABB)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	target.draw(sprite);

	bool drawCollider = true;

	if (drawCollider)
	{
		switch (collisionType)
		{

		case CollisionType::CIRCLE:
		{
			sf::CircleShape circle;
			sf::Vector2f shapePosition = GetCollisionCentre();

			float circleRadius = GetCircleColliderRadius();

			shapePosition.x -= circleRadius;
			shapePosition.y -= circleRadius;

			circle.setPosition(shapePosition);
			circle.setRadius(circleRadius);
			sf::Color collisionColor = sf::Color::Green;
			// TODO: Turn this red if a collision is occurring
			if (colliding)
				collisionColor = sf::Color::Red;

			collisionColor.a = 100;
			circle.setFillColor(collisionColor);

			target.draw(circle);
		}
			break;

		case CollisionType::AABB:
		{
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));

			sf::Color collisionColor = sf::Color::Green;
			// Turn this red if a collision is occurring
			if (colliding)
				collisionColor = sf::Color::Red;

			collisionColor.a = 100;
			rectangle.setFillColor(collisionColor);

			target.draw(rectangle);
		}
			break;

		default:
			break;
		}
		
	}
}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{
	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newX, float newY)
{
	SetPosition(sf::Vector2f(newX, newY));
}

bool SpriteObject::CheckCollision(SpriteObject other)
{
	switch (collisionType)
	{

		case CollisionType::CIRCLE:
		{
			switch (other.collisionType)
			{

				case CollisionType::CIRCLE:
				{
					// Get the vector representing the displacement between the two circles 
					sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();

					// Get the magnitude of that vector, which is how far apart the circles centres are
					float squareDistance = VectorHelper::SquareMagnitude(displacement);

					// Compare that to the combined radii of the two circles
					float combinedRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();

					return squareDistance <= combinedRadii * combinedRadii;
				}
				break;

				// Handles a circle colliding with a rectangle (AABB)
				case CollisionType::AABB:
				{
					sf::Vector2f nearestPointToCircle = GetCollisionCentre(); // Actual circle centre to start with
					sf::FloatRect otherAABB = other.GetAABB();

					// Clamp the circle centre to the AABB of the other object 
					nearestPointToCircle.x = fmaxf(otherAABB.left, fminf(nearestPointToCircle.x, otherAABB.left + otherAABB.width));
					nearestPointToCircle.y = fmaxf(otherAABB.top, fminf(nearestPointToCircle.y, otherAABB.top + otherAABB.height));

					sf::Vector2f displacement = nearestPointToCircle - GetCollisionCentre();
					float squareDistance = VectorHelper::SquareMagnitude(displacement);
					float circleRadius = GetCircleColliderRadius();

					return squareDistance <= circleRadius * circleRadius;
				}
				break;

				default:
					break;
			}
			}
		break;

		case CollisionType::AABB:
		{
			switch (other.collisionType)
			{

				case CollisionType::AABB:
				{
					return GetAABB().intersects(other.GetAABB());
				}

				case CollisionType::CIRCLE:
				{
					// Handles a rectangle colliding with a circle
					sf::Vector2f nearestPointToCircle = other.GetCollisionCentre(); // Actual circle centre to start with
					sf::FloatRect thisAABB = GetAABB();

					// Clamp the circle centre to the AABB of the other object 
					nearestPointToCircle.x = fmaxf(thisAABB.left, fminf(nearestPointToCircle.x, thisAABB.left + thisAABB.width));
					nearestPointToCircle.y = fmaxf(thisAABB.top, fminf(nearestPointToCircle.y, thisAABB.top + thisAABB.height));

					sf::Vector2f displacement = nearestPointToCircle - other.GetCollisionCentre();
					float squareDistance = VectorHelper::SquareMagnitude(displacement);
					float circleRadius = other.GetCircleColliderRadius();

					return squareDistance <= circleRadius * circleRadius;
				}
				break;

				default:
					break;
			}
		}
		break;

		default:
			return false;
		break;
		}
}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;

	sf::FloatRect bounds = sprite.getGlobalBounds();
	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;

	centre.x += collisionOffset.x;
	centre.y += collisionOffset.y;

	return centre;
}

float SpriteObject::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	if (bounds.width > bounds.height)
		return bounds.width * 0.5f;
	else
		return bounds.height * 0.5f;
}

sf::FloatRect SpriteObject::GetAABB()
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	bounds.width = bounds.width * collisionScale.x;
	bounds.height = bounds.height * collisionScale.y;

	sf::Vector2f centre = GetCollisionCentre();

	bounds.left = centre.x - bounds.width * 0.5f;
	bounds.top = centre.y - bounds.height * 0.5f;

	return bounds;
}
