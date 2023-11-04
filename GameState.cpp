#include "GameState.h"


//Init functions

void GameState::initDeferredRender()
{
	renderTexture.create(
		stateData->gfxSettings->resolution.width,
		stateData->gfxSettings->resolution.height
	);

	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(
		sf::IntRect(
			0,
			0,
			stateData->gfxSettings->resolution.width,
			stateData->gfxSettings->resolution.height
			)
		);
}

void GameState::initView()
{
	view.setSize(
		sf::Vector2f(
			static_cast<float>(stateData->gfxSettings->resolution.width),
			static_cast<float>(stateData->gfxSettings->resolution.height)
		)
	);
	view.setCenter(
		static_cast<float>(stateData->gfxSettings->resolution.width) / 2.f,
		static_cast<float>(stateData->gfxSettings->resolution.height) / 2.f
	);
}

void GameState::initFonts()
{
	if (!font.loadFromFile("Fonts/SIXTY.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initKeyBinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
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

void GameState::initTextures()
{
	sf::Texture tmp;
	if (!textures["PLAYER_SHEET"].loadFromFile("Textures/knight.png"))
	{
		throw ("ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_SHEET");
	}
}

void GameState::initPuaseMenu()
{
	pauseMenu = new PauseMenu(*window, font);
	pauseMenu->addButton("QUIT", 200.f, "Quit");
}

void GameState::initPlayers()
{
	player = new Player(0,0,textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	tileMap = new TileMap(stateData->gridSize, 1000, 1000, "Textures/tileSheet.png");
	tileMap->loadFromFile("text.txt");
}

//constructors/ deconstructors
GameState::GameState(StateData *state_data)
	: State(state_data)
{
	initDeferredRender();
	initView();
	initKeyBinds();
	initFonts();
	initTextures();
	initPuaseMenu();
	initPlayers();
	initTileMap();
}

GameState::~GameState()
{
	delete pauseMenu;
	delete player;
	delete tileMap;
}

void GameState::updateView(const float &dt)
{
	view.setCenter(std::floor(player->getPosition().x), std::floor(player->getPosition().y));
}

void GameState::updateInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
	{
		if (!paused)
			pauseState();
		else
			unPauseState();
	}
}

void GameState::updatePlayerInput(const float &dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(dt,-1.f,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(dt,1.f,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(dt,0.f,-1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(dt,0.f,1.f);
}

void GameState::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPrerssed("QUIT"))
		endState();
}

void GameState::updateTileMap(const float &dt)
{
	tileMap->update();
	tileMap->updateColision(dt, player);
}

void GameState::update(const float &dt)
{
	updateMousePosition(&view);
	updateKeytime(dt);
	updateInput(dt);
	if (!paused) //UnPaused update
	{
		updateView(dt);
		updatePlayerInput(dt);
		updateTileMap(dt);
		player->update(dt);
	}
	else// Paused update
	{
		pauseMenu->update(mousePosWindow);
		updatePauseMenuButtons();
	}


}

void GameState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;
	
	renderTexture.clear();

	renderTexture.setView(view);
	tileMap->render(renderTexture, player->getGridPosition(static_cast<int>(stateData->gridSize)));

	player->render(renderTexture);

	tileMap->renderDeferred(renderTexture);

	if (paused)
	{
		renderTexture.setView(renderTexture.getDefaultView());
		pauseMenu->render(renderTexture);
	}

	//FINAL RENDER
	renderTexture.display();
	renderSprite.setTexture(renderTexture.getTexture());
	target->draw(renderSprite);
}
