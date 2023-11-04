#include "SettingsState.h"

void SettingsState::initVariables()
{
	modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground()
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

void SettingsState::initFonts()
{
	if (!font.loadFromFile("Fonts/SIXTY.ttf"))
	{
		throw("ERROR::SettingsState::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeyBinds()
{
	std::ifstream ifs("Config/SettingsState_keybinds.ini");
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

void SettingsState::initGui()
{
	buttons["BACK"] = new gui::Button(
		1500.f,880.f,150.f,50.f,
		&font, "Back", 65,
		sf::Color(255,255,255,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));

	buttons["APPLY"] = new gui::Button(
		1300.f,880.f,150.f,50.f,
		&font, "Apply", 65,
		sf::Color(255,255,255,200), sf::Color(250,250,250,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,0), sf::Color(150,150,150,0), sf::Color(20,20,20,0));


	//retrive all the video modes (resolutuions) and store them as strings in modes_str
	std::vector<std::string> modes_str;
	for (auto &i : modes)
	{
		modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
	}
	dropDownLists["RESOLUTION"] = new gui::DropDownList(800,400,200,50, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText()
{
	optionsText.setFont(font);
	optionsText.setPosition(sf::Vector2f(100.f, 450.f));
	optionsText.setCharacterSize(30);
	optionsText.setFillColor(sf::Color(255,255,255,200));
	optionsText.setString(
		"Resolution \n\nFUllscreen \n\nVscync \n\nAntialiasing" 
		);
}

SettingsState::SettingsState(StateData *state_data)
	: State(state_data)
{
	initVariables();
	initBackground();
	initFonts();
	initKeyBinds();
	initGui();
	initText();
}

SettingsState::~SettingsState()
{
	auto it = buttons.begin();
	for(it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = dropDownLists.begin();
	for(it2 = dropDownLists.begin(); it2 != dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
}


void SettingsState::updateInput(const float &dt)
{

}

void SettingsState::updateGui(const float &dt)
{
	//updates all the gui elements in this sates, and handlers their functionallity
	//Buttons
	for (auto &it : buttons)
	{
		it.second->update(mousePosWindow);
	}

	//go back to main menu
	if (buttons["BACK"]->isPressed())
		endState();
	//apply selected seettings
	if (buttons["APPLY"]->isPressed())
	{
		//TEST remove later
		stateData->gfxSettings->resolution = modes[dropDownLists["RESOLUTION"]->getActiveElementId()];
		window->create(stateData->gfxSettings->resolution, stateData->gfxSettings->title, sf::Style::Default);
	}

	//dropdown lists
	for (auto &it : dropDownLists)
	{
		it.second->update(mousePosWindow, dt);
	}
}

void SettingsState::update(const float &dt)
{
	updateMousePosition();
	updateInput(dt);
	updateGui(dt);



	
	// system("cls");
	// std::cout << "screen: " << mousePosScreen.x << " " << mousePosScreen.y << std::endl;
	// std::cout << "window: " << mousePosWindow.x << " " << mousePosWindow.y << std::endl;
	// std::cout << "view: " << mousePosView.x << " " << mousePosView.y << std::endl;
}

void SettingsState::renderGui(sf::RenderTarget &target)
{
	for (auto &it : buttons)
	{
		it.second->render(target);
	}
	for (auto &it : dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;
	target->draw(background);
	renderGui(*target);

	target->draw(optionsText);


	//Remove later
	sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y-50);
	mouseText.setFont(font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);

}
