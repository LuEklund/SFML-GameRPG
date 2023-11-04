
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

//Accessors
const float &MovementComponent::getMaxVelocity() const
{
	return (maxVelocity);
}

const sf::Vector2f &MovementComponent::getVelocity() const
{
	return(velocity);
}

// Functions
const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (velocity.x == 0.f && velocity.y == 0)
			return (true);
		break;

	case MOVING:
		if (velocity.x != 0.f || velocity.y != 0)
			return (true);
		break;
	
	case MOVING_LEFT:
		if (velocity.x < 0.f)
			return (true);
		break;

	case MOVING_RIGHT:
		if (velocity.x > 0.f)
			return (true);
		break;

	case MOVING_UP:
		if (velocity.y < 0.f)
			return (true);
		break;

	case MOVING_DOWN:
		if (velocity.y > 0.f)
			return (true);
		break;
	}
	return false;
}

void MovementComponent::stopVelocity()
{
	/* Reset the Velocity to 0. */
	velocity.x = 0;
	velocity.y = 0;
}

void MovementComponent::stopVelocityX()
{
	/* Reset the Velocity X to 0. */
	velocity.x = 0;
}

void MovementComponent::stopVelocityY()
{
	/* Reset the Velocity Y to 0. */
	velocity.y = 0;
}

void MovementComponent::move(const float &dt, const float dir_x, const float dir_y)
{
	/* Accelerate the Enitity*/
	velocity.x += acceleration * dir_x * dt;
	velocity.y += acceleration * dir_y * dt;

	
}

void MovementComponent::update(const float &dt)
{
	//speed update X axis
	if (velocity.x > 0.f) //positive
	{
		//deceleration X--
		velocity.x -= deceleration * dt;
		if (velocity.x > maxVelocity)//max limit
			velocity.x = maxVelocity;
		else if (velocity.x < 0.f)//reset
			velocity.x = 0.f;
	}
	else if (velocity.x < 0.f)//negative
	{
		//deceleration X++
		velocity.x += deceleration * dt;
		if (velocity.x < -1 * maxVelocity)//min limit
			velocity.x = -1 * maxVelocity;
		if (velocity.x > 0.f)//reset
			velocity.x = 0.f;
	}

	//speed update Y axis
	if (velocity.y > 0.f)//positive
	{
		//deceleration Y--
		velocity.y -= deceleration * dt;
		if (velocity.y > maxVelocity)//max limit
			velocity.y = maxVelocity;
		else if (velocity.y < 0.f)//reset
			velocity.y = 0.f;
	}
	else if (velocity.y < 0.f)//negative
	{
		//deceleration Y++
		velocity.y += deceleration * dt;
		if (velocity.y < -1 * maxVelocity)//min limit
			velocity.y = -1 * maxVelocity;
		if (velocity.y > 0.f)//reset
			velocity.y = 0.f;
	}

	//Final move
	sprite.move(velocity * dt); //uses velocity

}
