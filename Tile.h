
#ifndef TILE_H
# define TILE_H

# include <vector>
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>

# include "SFML/Graphics.hpp"


enum TileTypes
{
	DEFAULT,
	DAMAGING,
	DOODAD
};

class Tile
{
private:

protected:
	sf::RectangleShape	shape;
	bool				colision;
	short				type;
public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF,
	const sf::Texture &texture, const sf::IntRect &texture_rect,
	bool colision = false, short type = TileTypes::DEFAULT);
	virtual ~Tile();

	//Accessors
	short const			&getType() const;

	//Accessors
	const sf::Vector2f	&getPosition() const;
	const sf::FloatRect	getGlobalBounds() const;
	const bool			&getCollision() const;
	const bool			intersects(const sf::FloatRect bounds);

	//Functions
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget &target);
};

#endif