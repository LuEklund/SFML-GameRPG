#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	title = "Default";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	farmeRateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
};

GraphicsSettings::~GraphicsSettings(){};


//Functions
void	GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream	ofs(path);
	if(ofs.is_open())
	{
		ofs << title;
		ofs << resolution.width << " " << resolution.height;
		ofs << fullscreen;
		ofs << farmeRateLimit;
		ofs << verticalSync;
		ofs << contextSettings.antialiasingLevel;
	}
	ofs.close();
}

void	GraphicsSettings::loadFromFile(const std::string path)
{
	//get all the values from config file
	std::ifstream	ifs(path);
	if(ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullscreen;
		ifs >> farmeRateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}
	ifs.close();
}