#include "MainMenuState.h"

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	background.setSize(
		sf::Vector2f
		(static_cast<float>(window->getSize().x),
		static_cast<float>(window->getSize().y)));
	if (!backgroundTexture.loadFromFile("Textures/background.png"))
	{
		throw("ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE");
	}
	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Fonts/SIXTY.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeyBinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
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

void MainMenuState::initButtons()
{
	buttons["GAME_STATE"] = new gui::Button(1400.f,200.f,150.f,50.f,
		&font, "New Game", 65,
		sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,0), sf::Color(150,150,150,220), sf::Color(20,20,20,0));

	buttons["SETTINGS_STATE"] = new gui::Button(1400.f,300.f,150.f,50.f,
		&font, "Settings", 65,
		sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

	buttons["EDITOR_STATE"] = new gui::Button(1400.f,400.f,150.f,50.f,
		&font, "Editor", 65,
		sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

	buttons["EXIT_STATE"] = new gui::Button(1400.f,500.f,150.f,50.f,
		&font, "Quit", 65,
		sf::Color(70,70,70,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));
}

MainMenuState::MainMenuState(StateData *state_data)
	: State(state_data)
{
	initVariables();
	initBackground();
	initFonts();
	initKeyBinds();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	auto it = buttons.begin();
	for(it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float &dt)
{

}

void MainMenuState::updateButtons()
{
	//updates all the buttons i this sates, and handlers their functionallity
	for (auto &it : buttons)
	{
		it.second->update(mousePosWindow);
	}
	//New game
	if (buttons["GAME_STATE"]->isPressed())
	{
		states->push(new GameState(stateData));
		std::cout << "We create game" << std::endl;
	}
	
	//Settings
	if (buttons["SETTINGS_STATE"]->isPressed())
	{
		states->push(new SettingsState(stateData));
		std::cout << "this is settings" << std::endl;
	}

	//Editor
	if (buttons["EDITOR_STATE"]->isPressed())
	{
		states->push(new EditorState(stateData));
		std::cout << "We went to editor wooo" << std::endl;
	}
	//Quit Game
	if (buttons["EXIT_STATE"]->isPressed())
		endState();
}

void MainMenuState::update(const float &dt)
{
	updateMousePosition();
	updateInput(dt);
	updateButtons();

	
	// system("cls");
	// std::cout << "screen: " << mousePosScreen.x << " " << mousePosScreen.y << std::endl;
	// std::cout << "window: " << mousePosWindow.x << " " << mousePosWindow.y << std::endl;
	// std::cout << "view: " << mousePosView.x << " " << mousePosView.y << std::endl;
}

void MainMenuState::renderButtons(sf::RenderTarget &target)
{
	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;
	target->draw(background);
	renderButtons(*target);

	//Remove later
	// sf::Text mouseText;
	// mouseText.setPosition(mousePosView.x, mousePosView.y-50);
	// mouseText.setFont(font);
	// mouseText.setCharacterSize(12);
	// std::stringstream ss;
	// ss << mousePosView.x << " " << mousePosView.y;
	// mouseText.setString(ss.str());
	// target->draw(mouseText);

}
