#include "Entity.h"

void Entity::initVariales()
{
	hitboxComponent = NULL;
	movementComponent = NULL;
	animationComponent = NULL;
}

Entity::Entity()
{
	initVariales();
}

Entity::~Entity()
{
	delete hitboxComponent;
	delete movementComponent;
	delete animationComponent;
}

//Component functions
void Entity::setTexture(sf::Texture &texture)
{
	sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite &sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	if (hitboxComponent == NULL)
		hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	if (movementComponent == NULL)
		movementComponent = new MovementComponent(sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &tetxureSheet)
{
	if (animationComponent == NULL)
		animationComponent = new AnimationComponent(sprite, tetxureSheet);
}

const sf::Vector2f &Entity::getPosition() const
{
	if (hitboxComponent)
		return (hitboxComponent->getPosition());
	return (sprite.getPosition());
}

const sf::Vector2i Entity::getGridPosition(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return (sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI)
			);
	return (sf::Vector2i(
			static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
			static_cast<int>(this->sprite.getPosition().y) / gridSizeI)
			);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (hitboxComponent)
		return(hitboxComponent->getGlobalBounds());
	return(sprite.getGlobalBounds());
}

const sf::FloatRect Entity::getNextPositionBounds(const float &dt) const
{
	if (hitboxComponent && movementComponent)
		return (hitboxComponent->getNextPosition(movementComponent->getVelocity() * dt));
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

void Entity::setPosition(const float x, const float y)
{
	if (hitboxComponent)
		hitboxComponent->setPosition(x, y);
	else
		sprite.setPosition(x,y);
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
	if (movementComponent)
	{
		movementComponent->move(dt, dir_x, dir_y); //sets velocity
	}
}

void Entity::update(const float &dt)
{
	// if (movementComponent)
	// 	movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget &target)
{

}
