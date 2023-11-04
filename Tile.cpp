#include "Tile.h"

Tile::Tile()
{
	colision = false;
	type = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF,
	const sf::Texture &texture, const sf::IntRect &texture_rect,
	bool colision, short type)
{
	shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	shape.setFillColor(sf::Color::White);
	// shape.setOutlineThickness(1.f);
	// shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	shape.setTexture(&texture);
	shape.setTextureRect(texture_rect);

	this->colision = colision;
	this->type = type;
}

Tile::~Tile()
{
}

//Accessors
short const &Tile::getType() const
{
	return (type);
}

const sf::Vector2f & Tile::getPosition() const
{
	return(shape.getPosition());
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return (shape.getGlobalBounds());
}

const bool & Tile::getCollision() const
{
	return(colision);
}

const bool Tile::intersects(const sf::FloatRect bounds)
{
	return(shape.getGlobalBounds().intersects(bounds));
}

//Accessors
const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << shape.getTextureRect().left << " " << shape.getTextureRect().top
		<< " " << colision << " " << type;
	return (ss.str());
}

//Functions
void Tile::update()
{
}

void Tile::render(sf::RenderTarget &target)
{
	target.draw(shape);
}
