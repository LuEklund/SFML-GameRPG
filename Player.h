#ifndef PLAYER_H
# define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
	//Variables
	bool	attacking;

	//init functions
	void	initVariables();
	void	initComponets();

public:
	Player(float x, float y, sf::Texture &textureSheet);
	~Player();


	//Functions
	void			updateAttack();
	void			updateAnimation(const float &dt);
	void			update(const float &dt);
	void			render(sf::RenderTarget &target);


};


#endif