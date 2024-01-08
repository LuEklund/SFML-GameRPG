#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font *font, std::string text, unsigned charSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor,
	short unsigned id)
{

	this->id = id;
	//setting up the button (shape) and the text of button
	this->font = font;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idleColor);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outlineIdleColor);


	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(charSize);

	//centers the text within the button
	this->text.setPosition(
		(this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f))
			- (this->text.getGlobalBounds().width / 2.f),
		(this->shape.getPosition().y)
		// + (this->shape.getGlobalBounds().height / 2.f)) 
		// 	- (this->text.getGlobalBounds().height / 2.f
	);

	//defining the colors for the TEXT in the button
	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;
	//defining the colors for the button
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;


	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;

	//giving the button its color and state
	buttonState = IDLE_BTN;
}

gui::Button::~Button()
{

}

const bool gui::Button::isPressed() const
{
	if (buttonState == ACTIVE_BTN)
		return (true);
	return (false);
}

const std::string gui::Button::getText() const
{
	return (text.getString());
}

const short unsigned &gui::Button::getId() const
{
	return (id);
}


void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

void gui::Button::update(const sf::Vector2i &mousePosWindow)
{
	//Update the states for the button

	//Idle
	buttonState = IDLE_BTN;

	//Hover
	if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		buttonState = HOVER_BTN;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = ACTIVE_BTN;
		}
	}

	//applys the appropriate color to the button depending on the state
	switch (buttonState)
	{
	case IDLE_BTN:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		shape.setOutlineColor(outlineIdleColor);
		break;

	case HOVER_BTN:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		break;

	case ACTIVE_BTN:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		shape.setOutlineColor(outlineActiveColor);
		break;
	
	default:
		shape.setFillColor(sf::Color::Red);
		text.setFillColor(sf::Color::Blue);
		shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void gui::Button::render(sf::RenderTarget &target)
{
	target.draw(shape);
	target.draw(text);
}




//=====================================================
//==================[DropDownList]=====================
//=====================================================
gui::DropDownList::DropDownList(float x, float y, float width, float height,
	sf::Font &font, std::string list[],
	unsigned nrOfELements, unsigned default_index)
	:	font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	// unsigned	nrOfELements = sizeof(list) / sizeof(std)

	this->activeElement = new gui::Button(
				x, y, width, height,
				&font, list[default_index], 14,
				sf::Color(255,255,255,150), sf::Color(254,255,254,200), sf::Color(20,20,20,50),
				sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200),
				sf::Color(255,255,255,200), sf::Color(255,255,255,255), sf::Color(20,20,20,50)
				);

	for (unsigned i = 0; i < nrOfELements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i + 1) * height), width, height,
				&font, list[i], 14,
				sf::Color(255,255,255,200), sf::Color(254,254,254,255), sf::Color(20,20,20,50),
				sf::Color(70,70,70,200), sf::Color(150,150,150,200), sf::Color(20,20,20,200),
				sf::Color(255,255,255,0), sf::Color(255,255,255,0), sf::Color(20,20,20,0),
				i
			));
	}
	
}

gui::DropDownList::~DropDownList()
{
	delete activeElement;
	for (size_t i = 0; i < list.size(); i++)
	{
		delete list[i];
	}
}


//Accessors
const bool gui::DropDownList::getKeytime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return true;
	}
	return false;
}

const unsigned short &gui::DropDownList::getActiveElementId()
{
	return (activeElement->getId());
}

//Functions
void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
	updateKeytime(dt);

	activeElement->update(mousePosWindow);

	//SHow and hid ethe list
	if (activeElement->isPressed() && getKeytime())
	{
		if (showList)
			showList = false;
		else
			showList = true;
	}

	//if show the list update each button within the list
	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->update(mousePosWindow);

			if (i->isPressed() && getKeytime())
			{
				showList = false;
				activeElement->setText(i->getText());
				activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
	activeElement->render(target);
	if (showList)
	{
		for (auto &i : this->list)
		{
			i->render(target);
		}
	}

}


void gui::DropDownList::updateKeytime(const float &dt)
{
	if (keytime < keytimeMax)
		keytime += 10.f * dt;
}




//=====================================================
//=================[TextureSelector]===================
//=====================================================
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
	float grid_Size,
	const sf::Texture *texture_sheet, sf::Font &font, std::string text)
	:	keytimeMax(1.f), keytime(0.f)
{
	gridSize = grid_Size;
	active = false;
	hidden = false;
	float	offset = 100.f;

	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x + offset,y);
	bounds.setFillColor(sf::Color(50,50,50,100));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(255,255,255,200));

	sheet.setTexture(*texture_sheet);
	sheet.setPosition(x + offset, y);

	if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
	{
		sheet.setTextureRect(sf::IntRect(0,0, static_cast<int>(bounds.getGlobalBounds().width), static_cast<int>(sheet.getGlobalBounds().height)));
	}
	if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
	{
		sheet.setTextureRect(sf::IntRect(0,0, static_cast<int>(bounds.getGlobalBounds().height), static_cast<int>(sheet.getGlobalBounds().width)));
	}

	selector.setPosition(x + offset,y);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Red);

	textureRect.width = static_cast<int>(grid_Size);
	textureRect.height = static_cast<int>(grid_Size);

	hideBtn = new gui::Button(
		x, y, 50.f, 50.f,
		&font, text, 16,
		sf::Color(255,255,255,200), sf::Color(255,255,255,250), sf::Color(20,20,20,50),
		sf::Color(70,70,70,200), sf::Color(150,150,150,250), sf::Color(20,20,20,50));
}

gui::TextureSelector::~TextureSelector()
{
	delete hideBtn;
}

//Accessors
const bool &gui::TextureSelector::getActive() const
{
	return (active);
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const
{
	return (textureRect);
}

const bool gui::TextureSelector::getKeytime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return true;
	}
	return false;
}

//Functions


void gui::TextureSelector::updateKeytime(const float &dt)
{
	if (keytime < keytimeMax)
		keytime += 10.f * dt;
}

//updates the TextureSelector
void gui::TextureSelector::update(const sf::Vector2i mousePosWindow, const float &dt)
{
	updateKeytime(dt);
	hideBtn->update(mousePosWindow);
	//if hide-button was pressed we update the state for hidden bool by inverting it.
	if (hideBtn->isPressed() && getKeytime())
	{
		hidden = !hidden;
	}

	if (!hidden)
	{
		if (bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			active = true;
		else
			active = false;

		if (active)
		{
			mousePosGrid.x = (mousePosWindow.x - static_cast<int>(bounds.getPosition().x)) / static_cast<unsigned>(gridSize);
			mousePosGrid.y = (mousePosWindow.y - static_cast<int>(bounds.getPosition().y)) / static_cast<unsigned>(gridSize);
			selector.setPosition(
				bounds.getPosition().x + mousePosGrid.x * gridSize,
				bounds.getPosition().y + mousePosGrid.y * gridSize
				);
			//update texture rectangle (sf::IntRect)
			textureRect.left =  static_cast<int>(selector.getPosition().x - bounds.getPosition().x);
			textureRect.top =  static_cast<int>(selector.getPosition().y - bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
	if (!hidden)
	{
		target.draw(bounds);
		target.draw(sheet);

		if (active)
			target.draw(selector);
	}
	hideBtn->render(target);
}





