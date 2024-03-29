#ifndef PAUSEMENU_H
# define PAUSEMENU_H

# include <iostream>
# include <map>

# include "SFML/Graphics.hpp"
#include "Gui.h"

class PauseMenu
{
private:
	sf::Font						font;
	sf::Text						menuText;

	sf::RectangleShape				background;
	sf::RectangleShape				container;

	std::map<std::string, gui::Button *>	buttons;


public:
	PauseMenu(sf::RenderWindow &window, sf::Font &font);
	~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button *>	&getButtons();

	//Functions
	const bool	isButtonPrerssed(const std::string key);
	void		addButton(const std::string key, float y, const std::string text);
	void		update(const sf::Vector2i &mousePosWindow);
	void		render(sf::RenderTarget &target);
};


#endif