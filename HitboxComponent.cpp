
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite &sprite,
	float offset_x, float offset_y,
	float width, float height)
	:	sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{

	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	hitbox.setPosition(
		sprite.getPosition().x + offset_x,
		sprite.getPosition().y + offset_y
		);
	hitbox.setSize(sf::Vector2f(width, height));

	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(-1.f);
	hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

//Accessors
const sf::Vector2f &HitboxComponent::getPosition() const
{
	return(hitbox.getPosition());
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return(hitbox.getGlobalBounds());
}

const sf::FloatRect &HitboxComponent::getNextPosition(const sf::Vector2f &velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;
	return (this->nextPosition);
}

//Modifiers
void HitboxComponent::setPosition(sf::Vector2f &position)
{
	hitbox.setPosition(position);
	sprite.setPosition(
		position.x - offsetX,
		position.y - offsetY
		);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	hitbox.setPosition(x,y);
	sprite.setPosition(
		x - offsetX,
		y - offsetY
		);
}

//Functions
bool HitboxComponent::Intersect(const sf::FloatRect &fRect)
{
	return (hitbox.getGlobalBounds().intersects(fRect));
}

void HitboxComponent::update()
{
	hitbox.setPosition(
		sprite.getPosition().x + offsetX,
		sprite.getPosition().y + offsetY
		);
}

void HitboxComponent::render(sf::RenderTarget &target)
{
	target.draw(hitbox);
}
