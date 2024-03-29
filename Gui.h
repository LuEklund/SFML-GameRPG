#ifndef GUI_H
# define GUI_H

# include "SFML/Graphics.hpp"
# include <vector>
# include <iostream>
enum buttons_states
{
	IDLE_BTN,
	HOVER_BTN,
	ACTIVE_BTN
};


namespace gui
{
	class Button
	{
	private:

		buttons_states		buttonState;
		short unsigned		id;

		sf::RectangleShape	shape;
		sf::Font			*font;
		sf::Text			text;

		sf::Color			textIdleColor;
		sf::Color			textHoverColor;
		sf::Color			textActiveColor;

		sf::Color			idleColor;
		sf::Color			hoverColor;
		sf::Color			activeColor;

		sf::Color			outlineIdleColor;
		sf::Color			outlineHoverColor;
		sf::Color			outlineActiveColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font *font,std::string text, unsigned charSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
			sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent,
			short unsigned id = 0);
		~Button();


		//Accessors
		const bool	isPressed() const;
		const std::string	getText() const;
		const short unsigned &getId() const;

		//Modifiers
		void	setText(const std::string text);
		void	setId(const short unsigned id);

		//Functions
		void	update(const sf::Vector2i &mousePos);
		void	render(sf::RenderTarget &target);
	};
	
	class DropDownList
	{
	private:
		float						keytime;
		float						keytimeMax;

		sf::Font					&font;
		gui::Button					*activeElement;
		std::vector<gui::Button *>	list;
		bool						showList;
	public:
		DropDownList(float x, float y, float width, float height, sf::Font &font, std::string list[],  unsigned nrOfELements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const bool				getKeytime();
		const unsigned short	&getActiveElementId();

		//Functions
		void	updateKeytime(const float &dt);
		void	update(const sf::Vector2i &mousePosWindow, const float &dt);
		void	render(sf::RenderTarget &target);
	};

	class TextureSelector
	{
	private:
		float				keytime;
		const float			keytimeMax;
		float 				gridSize;
		bool				active;
		bool				hidden;
		gui::Button			*hideBtn;
		sf::RectangleShape	bounds;
		sf::Sprite			sheet;
		sf::RectangleShape	selector;
		sf::Vector2u		mousePosGrid;
		sf::IntRect			textureRect;
	public:
		TextureSelector(float x, float y, float width, float height, float grid_Size, const sf::Texture *texture_sheet, sf::Font &font, std::string text);
		~TextureSelector();

		//Accessors
		const bool			&getActive() const;
		const sf::IntRect	&getTextureRect() const;
		const bool 			getKeytime();

		//Functions
		void	updateKeytime(const float &dt);
		void	update(const sf::Vector2i mousePosWindow, const float &dt);
		
		void	render(sf::RenderTarget &target);
	};
}
#endif