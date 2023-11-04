#include "Player.h"

//init functions
void Player::initVariables()
{
	attacking = false;
}

void Player::initComponets()
{
	
}

//constructor / deconstructors
Player::Player(float x, float y, sf::Texture &textureSheet)
{
	setPosition(x,y);

	createHitboxComponent(sprite, 54.f, 64.f, 32.f, 64.f);
	createMovementComponent(300.f, 1500.f, 500.f);
	createAnimationComponent(textureSheet);

	animationComponent->addAniamtion("IDLE", 11.f, 0, 0, 3, 0, 128, 128);
	animationComponent->addAniamtion("WALK", 8.f, 0, 1, 7, 1, 128, 128);
	animationComponent->addAniamtion("ATTACK", 14.f, 0, 4, 4, 4, 128, 128);
}

Player::~Player()
{
}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		attacking = true;
	}
}

void Player::updateAnimation(const float &dt)
{
	if (attacking)
	{
		if (animationComponent->play("ATTACK", dt, true))
			attacking = false;
	}
	if (movementComponent->getState(IDLE))
	{
		animationComponent->play("IDLE", dt);
	}
	else if (movementComponent->getState(MOVING_RIGHT))
	{
		if (sprite.getScale().x < 0.f)
		{
			sprite.setOrigin(0, 0);
			sprite.setScale(1.f,1.f);
		}
		animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	}
	else if (movementComponent->getState(MOVING_LEFT))
	{
		if (sprite.getScale().x > 0.f)
		{
			sprite.setOrigin(140, 0);
			sprite.setScale(-1.f,1.f);
		}
		animationComponent->play("WALK", dt, movementComponent->getVelocity().x, movementComponent->getMaxVelocity());
	}
	else if (movementComponent->getState(MOVING_UP))
	{
		animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
	}
	else if (movementComponent->getState(MOVING_DOWN))
	{
		animationComponent->play("WALK", dt, movementComponent->getVelocity().y, movementComponent->getMaxVelocity());
	}
}

// Functions
void Player::update(const float &dt)
{
	movementComponent->update(dt);
	updateAttack();
	updateAnimation(dt);
	hitboxComponent->update();
}

void Player::render(sf::RenderTarget &target)
{
	target.draw(sprite);
	hitboxComponent->render(target);
}