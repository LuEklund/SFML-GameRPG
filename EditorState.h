#ifndef EDITORSTATE_H
# define EDITORSTATE_H

# include "GameState.h"
# include "Gui.h"
# include "PauseMenu.h"
# include "TileMap.h"

class EditorState : public State
{
private:
	//Variables
	sf::View	view;
	float		cameraSpeed;

	sf::Font	font;
	sf::Text	cursorText;
	PauseMenu	*pauseMenu;

	std::map<std::string, gui::Button *> buttons;

	TileMap	*tileMap;

	sf::RectangleShape	sideBar;

	sf::IntRect			textureRect;
	sf::RectangleShape 	selectorRect;



	gui::TextureSelector	*textureSelector;

	bool					collision;
	short					type;
	int						layer;

	//Functions
	void	initVariables();
	void	initView();
	void	updateEditorInput(const float &dt);
	void	initBackground();
	void	initFonts();
	void	initText();
	void	initKeyBinds();
	void	initPuaseMenu();
	void	initButtons();
	void	initTileMap();
	void	initGui();

public:
	EditorState(StateData *state_data);
	~EditorState();

	//Functions
	void	updateInput(const float &dt);
	void	updateButtons();
	void	updateGui(const float &dt);
	void	updatePauseMenuButtons();
	void	update(const float &dt);

	void	renderGui(sf::RenderTarget &target);
	void	renderButtons(sf::RenderTarget &target);
	void	render(sf::RenderTarget *target = NULL);
};



#endif
