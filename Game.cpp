#include "Game.h"

//Static functions

//InitFunctions

void Game::initVariables()
{
	window = NULL;
	dt = 0.f;
	gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
	gfxSettings.loadFromFile("Config/graphics.ini");
}


void Game::initWindow()
{
	if (gfxSettings.fullscreen)
		window = new sf::RenderWindow(
			gfxSettings.resolution,
			gfxSettings.title,
			sf::Style::Fullscreen,
			gfxSettings.contextSettings);
	else
		window = new sf::RenderWindow(
			gfxSettings.resolution,
			gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			gfxSettings.contextSettings);
	window->setFramerateLimit(gfxSettings.farmeRateLimit);
	window->setVerticalSyncEnabled(gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");
	if(ifs.is_open())
	{
		std::string key;
		int			key_value = 0;
		while(ifs >> key >> key_value)
		{
			supportedKeys[key] = key_value;

		}
	}
	ifs.close();
}

void Game::initStateData()
{
	stateData.window = window;
	stateData.gfxSettings = &gfxSettings;
	stateData.supportedKeys = &supportedKeys;
	stateData.states = &states;
	stateData.gridSize = gridSize;
}

void Game::initStates()
{
	states.push(new MainMenuState(&stateData));
}


// Constructors/destructors
Game::Game()
{
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeys();
	initStateData();
	initStates();
}

Game::~Game()
{
	delete  window;
	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

// Functions
void Game::endApplication()
{
	std::cout << "ending application" << std::endl;
}

void Game::updateSFMLEvents()
{
	//iter trough the events
	while(window->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::updateDt()
{
	//updates the dt var with the time it took to update and render one frame
	dt = dtClock.restart().asSeconds();

	// system("cls");
	// std::cout << dt << std::endl;
}

void Game::update()
{
	updateSFMLEvents();

	//update our top state
	if (!states.empty())
	{
		if (window->hasFocus())
		{
			states.top()->update(dt);
			if (states.top()->getQuit())
			{
				states.top()->endState();
				delete states.top();
				states.pop();
			}
		}
	}
	else //Application end
	{
		endApplication();
		window->close();
	}

}

void Game::render()
{
	window->clear();

	//Big draw happen yeah!
	//render our top state
	if (!states.empty())
		states.top()->render(window);

	window->display();

}

void Game::run()
{

	while(window->isOpen())
	{
		updateDt();
		update();
		render();
	}

}
