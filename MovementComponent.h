#ifndef MOVEMENTCOMPONENT_H
# define MOVEMENTCOMPONENT_H


# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <stack>
# include <map>

# include "SFML/Graphics.hpp"

enum move_states
{
	IDLE,
	MOVING,
	MOVING_LEFT,
	MOVING_RIGHT,
	MOVING_UP,
	MOVING_DOWN
};

class MovementComponent
{
private:
	sf::Sprite		&sprite;

	float			maxVelocity;
	float			acceleration;
	float			deceleration;

	sf::Vector2f	velocity;

	//initializer functions
public:
	MovementComponent(sf::Sprite &sprite,
		float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	//Accessors
	const float			&getMaxVelocity() const;
	const sf::Vector2f	&getVelocity() const;

	//Functions
	const bool	getState(const short unsigned state) const;
	void		stopVelocity();
	void		stopVelocityX();
	void		stopVelocityY();
	
	void	move(const float &dt, const float dir_x, const float dir_y);
	void	update(const float &dt);
};

#endif
