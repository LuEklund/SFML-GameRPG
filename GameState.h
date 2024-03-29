#ifndef GAMESTATE_H
# define GAMESTATE_H

# include "State.h"
# include "PauseMenu.h"
# include "TileMap.h"

class PauseMenu;
class Player;
class TileMap;

class GameState : public State
{
private:
	sf::View			view;
	sf::RenderTexture	renderTexture;
	sf::Sprite			renderSprite;

	PauseMenu	*pauseMenu;
	sf::Font	font;

	Player 		*player;

	TileMap		*tileMap;


	// Functions
	void	initDeferredRender();
	void	initView();
	void 	initFonts();
	void	initKeyBinds();
	void	initTextures();
	void	initPuaseMenu();
	void	initPlayers();
	void	initTileMap();

public:
	GameState(StateData *state_data);
	~GameState();

	//Functions
	void	updateView(const float &dt);
	void	updateInput(const float &dt);
	void	updatePlayerInput(const float &dt);
	void	updatePauseMenuButtons();
	void	updateTileMap(const float &dt);
	void	update(const float &dt);
	void	render(sf::RenderTarget *target = nullptr);
};

#endif