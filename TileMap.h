#ifndef TILEMAP_H
# define TILEMAP_H

#include "Tile.h"
#include "Entity.h"

class TileMap
{
private:
	float			gridSizeF;
	int				gridSizeI;
	sf::Vector2i	maxSizeWorldGrid;
	sf::Vector2f	maxSizeWorldF;
	int				layers;

	//Conatins all the tiles
	std::vector <std::vector <std::vector <std::vector<Tile *> > > > map;

	//Post-tiles render (on top of player)
	std::stack<Tile *>	deferredRenderStack;

	//Texture file path where we get the textures from when loading the tilemap
	std::string	textureFile;

	//Texture for the tilemap
	sf::Texture	tileSheet;

	//collisionbox for collidable tiles
	sf::RectangleShape		collisionBox;

	//Culling
	int		fromX;
	int		toX;
	int		fromY;
	int		toY;
	int		layer;

	void	clear();

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	~TileMap();

	//Accessors
	const sf::Texture	*getTileSheet() const;
	const int			getLayerSize(const int x, const int y, const int layer) const;


	//Functions
	void	addTile(const int x, const int y, const int z,
					const sf::IntRect &texture_rect,
					const bool &collision, const short &type);
	void	removeTile(const int x, const int y, const int z);

	void	saveToFile(const std::string file_name);
	void	loadFromFile(const std::string file_name);

	void	updateColision( const float &dt, Entity *entity = NULL);

	void	update();
	void	render(sf::RenderTarget &target, const sf::Vector2i &gridPosiiton);
	void	renderDeferred(sf::RenderTarget &target);
};



#endif