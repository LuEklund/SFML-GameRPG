#ifndef ENTITY_H
# define ENTITY_H


#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "AttributeComponent.h"

class Entity
{
private:
	void	initVariales();

protected:
	sf::Sprite			sprite;

	HitboxComponent		*hitboxComponent;
	MovementComponent	*movementComponent;
	AnimationComponent	*animationComponent;
	AttributeComponent	*attributeComponent;

public:
	Entity();
	virtual	~Entity();

	//Component functions
	void	setTexture(sf::Texture &texture);
	void	createHitboxComponent(sf::Sprite &sprite,
				float offset_x, float offset_y,
				float width, float height);
	void	createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void	createAnimationComponent(sf::Texture &tetxureSheet);
	void	createAttributeComponent();

	//Accessors
	virtual const sf::Vector2f	&getPosition() const;
	virtual const sf::Vector2i	getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect	getGlobalBounds() const;
	virtual const sf::FloatRect	getNextPositionBounds(const float &dt) const;

	//Modifiers
	virtual void	setPosition(const float x, const float y);
	virtual void	stopVelocity();
	virtual void	stopVelocityX();
	virtual void	stopVelocityY();
	//Functions
	virtual void	move(const float &dt, const float dir_x, const float dir_y);
	
	virtual void	update(const float & dt) = 0;
	virtual void	render(sf::RenderTarget &target) = 0;
};


#endif