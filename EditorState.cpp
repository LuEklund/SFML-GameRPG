#include "EditorState.h"

void EditorState::initVariables()
{
	textureRect = sf::IntRect(0, 0, static_cast<int>(stateData->gridSize), static_cast<int>(stateData->gridSize));
	collision = false;
	type = TileTypes::DEFAULT;
	cameraSpeed = 100.f;
	layer = 0;
}

void EditorState::initView()
{
	view.setSize(
		sf::Vector2f(
			static_cast<float>(stateData->gfxSettings->resolution.width),
			static_cast<float>(stateData->gfxSettings->resolution.height)
			)
		);
	view.setCenter(
		static_cast<float>(stateData->gfxSettings->resolution.width)/2.f,
		static_cast<float>(stateData->gfxSettings->resolution.height)/2.f
		);
}

void EditorState::initBackground()
{

}

void EditorState::initFonts()
{
	if (!font.loadFromFile("Fonts/SIXTY.ttf"))
	{
		throw("ERROR::EditorState::COULD NOT LOAD FONT");
	}
}

void EditorState::initText()
{
	cursorText.setFillColor(sf::Color::White);
	cursorText.setFont(font);
	cursorText.setCharacterSize(12);
}

void EditorState::initKeyBinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");
	if(ifs.is_open())
	{
		std::string key;
		std::string	key2;
		while(ifs >> key >> key2)
		{
			keybinds[key] = supportedKeys->at(key2);
		}
	}
	ifs.close();
}

void EditorState::initPuaseMenu()
{
	pauseMenu = new PauseMenu(*window, font);
	pauseMenu->addButton("QUIT", 200.f, "Quit");
	pauseMenu->addButton("SAVE", 300.f, "Save");
	pauseMenu->addButton("LOAD", 400.f, "Load");
}


void EditorState::initButtons()
{
}

void EditorState::initTileMap()
{
	tileMap = new TileMap(stateData->gridSize, 10, 10, "Textures/tileSheet.png");
}

void EditorState::initGui()
{
	sideBar.setSize(sf::Vector2f(80.f, static_cast<float>(stateData->gfxSettings->resolution.height)));
	sideBar.setFillColor(sf::Color(50.f, 50.f, 50.f, 100.f));
	sideBar.setOutlineColor(sf::Color(200.f, 200.f, 200.f, 150.f));
	sideBar.setOutlineThickness(1.f);

	selectorRect.setSize(sf::Vector2f(stateData->gridSize, stateData->gridSize));
	selectorRect.setFillColor(sf::Color(255,255,255,150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
	selectorRect.setTexture(tileMap->getTileSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(
		20.f, 20.f, 500.f, 500.f,
		stateData->gridSize, tileMap->getTileSheet(),
		font, "TS"
		);
}

EditorState::EditorState(StateData *state_data)
	: State(state_data)
{
	initVariables();
	initView();
	initBackground();
	initFonts();
	initText();
	initKeyBinds();
	initPuaseMenu();
	initButtons();
	initTileMap();
	initGui();
}

EditorState::~EditorState()
{
	auto it = buttons.begin();
	for(it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	delete pauseMenu;
	delete tileMap;
	delete textureSelector;
}


void EditorState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
	{
		if (!paused)
			pauseState();
		else
			unPauseState();
	}
}

void EditorState::updateEditorInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_UP"))))
	{
		view.move(0.f, -cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		view.move(0.f, cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		view.move(-cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		view.move(cameraSpeed * dt, 0.f);
	}

	//add a tile to the tilemap if we clcik within a valid field.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
		&& getKeytime()
		&& !sideBar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow)))
	{
		//check that we are not on texture selector field
		if (!textureSelector->getActive())
		{

			tileMap->addTile(mousePosGrid.x, mousePosGrid.y, 0, textureRect, collision, type);
		}
		else
		{
			textureRect = textureSelector->getTextureRect();
		}
	}
	//Remove a tile from the tilemap
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)
		&& getKeytime()
		&& !sideBar.getGlobalBounds().contains(sf::Vector2f(mousePosWindow)))
	{
		if (!textureSelector->getActive())
		{
			tileMap->removeTile(mousePosGrid.x, mousePosGrid.y, 0);
		}
	}
	//Toggle collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("TOGGLE_COLLISION"))) && getKeytime())
	{
		collision = !collision;			
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("INCREASE_TYPE"))) && getKeytime())
	{
		if (type < 100)
			++type;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("DECREASE_TYPE"))) && getKeytime())
	{
		if (type > 0)
			--type;
	}
}

void EditorState::updateButtons()
{
	for (auto &it : buttons)
	{
		it.second->update(mousePosWindow);
	}
}


void EditorState::updateGui(const float &dt)
{
	textureSelector->update(mousePosWindow, dt);

	//highlights the current cell in the tilemap that the curser is hovering,
	//if we are not selecting a texture
	if (!textureSelector->getActive())
	{
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(mousePosGrid.x * gridSize, mousePosGrid.y * gridSize);
	}

	cursorText.setPosition(mousePosView.x + 100.f, mousePosView.y - 50.f);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y << "\n" <<
	mousePosGrid.x << " " << mousePosGrid.y << "\n" <<
	textureRect.left << " " << textureRect.top << "\n" <<
	"Collision: " << collision << "\n" <<
	"Type: " << type << "\n" <<
	"Tiles: " << tileMap->getLayerSize(mousePosGrid.x, mousePosGrid.y, layer) << std::endl;
	cursorText.setString(ss.str());

}



void EditorState::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPrerssed("QUIT"))
		endState();
	if (pauseMenu->isButtonPrerssed("SAVE"))
		tileMap->saveToFile("text.txt");
	if (pauseMenu->isButtonPrerssed("LOAD"))
		tileMap->loadFromFile("text.txt");
}

void EditorState::update(const float &dt)
{
	updateMousePosition(&view);
	updateKeytime(dt);
	updateInput(dt);
	if(!paused) //UnPaused
	{
		updateGui(dt);
		updateButtons();
		updateEditorInput(dt);
	}
	else //Pasued
	{
		pauseMenu->update(mousePosWindow);
		updatePauseMenuButtons();
	}
}


void EditorState::renderGui(sf::RenderTarget &target)
{
	//render a ghost of the texture that we want to place. if we are not on the texture-selector
	if (!textureSelector->getActive())
	{
		target.setView(view);
		target.draw(selectorRect);

	}

	//render the texture-selector interface
	target.setView(target.getDefaultView());
	textureSelector->render(target);
	target.draw(sideBar);

	//render cursor information
	target.setView(view);
	target.draw(cursorText);

}

void EditorState::renderButtons(sf::RenderTarget &target)
{
	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;

	target->setView(view);
	tileMap->render(*target, mousePosGrid);
	tileMap->renderDeferred(*target);

	target->setView(target->getDefaultView());

	renderButtons(*target);

	renderGui(*target);

	if (paused) //PauseMenu render
	{
		target->setView(target->getDefaultView());
		pauseMenu->render(*target);
	}



}

