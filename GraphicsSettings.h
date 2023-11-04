#ifndef GRAPHICSSETTINGS_H
# define GRAPHICSSETTINGS_H

# include <iostream>
# include <fstream>

# include "SFML/Graphics.hpp"

class GraphicsSettings
	{
	private:
	public:
		GraphicsSettings();
		~GraphicsSettings();
		//Variables
		std::string					title;
		sf::VideoMode				resolution;
		bool						fullscreen;
		bool						verticalSync;
		unsigned					farmeRateLimit;
		sf::ContextSettings			contextSettings;
		std::vector<sf::VideoMode>	videoModes;

		//Functions
		void	saveToFile(const std::string path);

		void	loadFromFile(const std::string path);

	};

	#endif