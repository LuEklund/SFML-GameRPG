#ifndef GAME_H
# define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//variables
	GraphicsSettings			gfxSettings;
	StateData					stateData;
	sf::RenderWindow			*window;
	sf::Event					event;
	
	sf::Clock					dtClock;
	float						dt;

	std::stack<State *>			states;
	std::map<std::string, int>	supportedKeys;
	float	gridSize;

	//Inits
	void	initVariables();
	void	initGraphicsSettings();
	void	initWindow();
	void	initKeys();
	void	initStateData();
	void	initStates();

	//Functions

	void	endApplication();

	//Update
	void	updateSFMLEvents();
	void	updateDt();
	void	update();
	
	//Render
	void	render();

public:
	Game();
	~Game();


	//Functions
	//Core
	void	run();

	//Getters and Setters

};

#endif