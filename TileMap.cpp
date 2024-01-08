#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < maxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < layers; z++)
			{
				for (int k = 0; k < map[x][y][z].size(); k++)
				{
					delete map[x][y][z][k];
					map[x][y][z][k] = NULL;
				}
			}
			map[x][y].clear();
		}
		map[x].clear();
	}
	map.clear();
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	gridSizeF = gridSize;
	gridSizeI = static_cast<int>(gridSizeF);
	maxSizeWorldGrid.x = width;
	maxSizeWorldGrid.y = height;
	maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	layers = 1;
	textureFile = texture_file;

	//Culling
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	map.resize(maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile *> > >());
	for (int x = 0; x < maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < maxSizeWorldGrid.y; y++)
		{
			map[x].resize(maxSizeWorldGrid.y, std::vector<std::vector<Tile *>>());
			for (int z = 0; z < layers; z++)
			{
				map[x][y].resize(layers, std::vector<Tile *>());
			}
		}
	}

	if (!tileSheet.loadFromFile(textureFile))
		std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << textureFile << std::endl;
	collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	collisionBox.setFillColor(sf::Color(255,0,0,50));
	collisionBox.setOutlineColor(sf::Color::Red);
	collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	clear();
}

//Accessors
const sf::Texture *TileMap::getTileSheet() const
{
	return (&tileSheet);
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x > 0 && x < map.size())
	{
		if (y >= 0 && y < map[x].size())
		{
			if (layer >= 0 && layer < map[x][y].size())
			{
				return (static_cast<int>(map[x][y][layer].size()));
			}
		}
	}
	return (-1);
}

//Functions
void TileMap::addTile(const int x, const int y, const int z,
				const sf::IntRect &texture_rect,
				const bool &collision, const short &type)
{
	//takes three indicies from the mouse postion.
	//and add a tile to that position in the grid.
	if (x < maxSizeWorldGrid.x && x >= 0 &&
		y < maxSizeWorldGrid.y && y >= 0 &&
		z < layers && z >= 0)
	{
		//OK to add tile
		map[x][y][z].push_back(new Tile(x, y, gridSizeF, tileSheet, texture_rect, collision, type));
		std::cout << "ADDED TILE" << std::endl;
	}

}

void TileMap::removeTile(const int x, const int y, const int z)
{
	//takes three indicies from the mouse postion.
	//and removes the tile from that position in the grid.
	if (x < maxSizeWorldGrid.x && y < maxSizeWorldGrid.y && z < layers)
	{
		if (!map[x][y][z].empty())
		{
			//OK to remove tile
			delete map[x][y][z][map[x][y][z].size() - 1];
			map[x][y][z].pop_back();
			std::cout << "REMOVED TILE" << std::endl;

		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tileMap to an file
	Format: 
	basics:
	Size x y
	gridSize
	layers
	textureFile

	All tiles
	gridPos x y z, Texture rect x y, collision, type
	*/

	std::ofstream outFile;
	outFile.open(file_name);
	if (outFile.is_open())
	{
		outFile << maxSizeWorldGrid.x << " " << maxSizeWorldGrid.y << "\n"
			<< gridSizeI << "\n"
			<< layers << "\n"
			<< textureFile << "\n";

		for (int x = 0; x < maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					if (!map[x][y][z].empty())
					{
						for (int k = 0; k < map[x][y][z].size(); k++)
						{
							outFile << x << " " << y << " " << z << " " <<
							map[x][y][z][k]->getAsString() << " ";
						}
						
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << std::endl;
	}
	outFile.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream inFile;
	inFile.open(file_name);
	if (inFile.is_open())
	{
		sf::Vector2i	size;
		int				gridSize = 0;
		int				layers = 0;
		std::string		texture_file;
		int				x = 0;
		int				y = 0;
		int				z = 0;
		int				trX = 0;
		int				trY = 0;
		bool			collision = false;
		short			type = 0;

		//Basics
		inFile >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		clear();

		map.resize(maxSizeWorldGrid.x, std::vector<std::vector<std::vector<Tile *> > >());
		for (int x = 0; x < maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				map[x].resize(maxSizeWorldGrid.y, std::vector<std::vector<Tile *> >());
				for (int z = 0; z < layers; z++)
				{
					map[x][y].resize(layers, std::vector<Tile *>());
				}
			}
		}

		if (!tileSheet.loadFromFile(textureFile))
			std::cout << "ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET::FILENAME: " << textureFile << std::endl;
		//Load all Tiles
		while(inFile >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			map[x][y][z].push_back(new Tile(x, y,
				this->gridSizeF,
				this->tileSheet,
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
				collision, type));
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << std::endl;
	}
	inFile.close();
}

void TileMap::updateColision(const float &dt, Entity *entity)
{
	//World bounds check. Preventing the entity from exiting
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > maxSizeWorldF.x)
	{
		entity->setPosition(maxSizeWorldF.x -  entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	/* TILES */
	/*	Render the tiles close to the entity
		And ensuring the tiles are valid to render*/
	layer = 0;
	fromX = entity->getGridPosition(gridSizeI).x - 1;
	if (fromX < 0)
		fromX = 0;
	else if (fromX > maxSizeWorldGrid.x)
		fromX = maxSizeWorldGrid.x;

	toX = entity->getGridPosition(gridSizeI).x + 3;
	if (toX < 0)
		toX = 0;
	else if (toX > maxSizeWorldGrid.x)
		toX = maxSizeWorldGrid.x;

	fromY = entity->getGridPosition(gridSizeI).y - 1;
	if (fromY < 0)
		fromY = 0;
	else if (fromY > maxSizeWorldGrid.y)
		fromY = maxSizeWorldGrid.y;

	toY = entity->getGridPosition(gridSizeI).y + 3;
	if (toY < 0)
		toY = 0;
	else if (toY > maxSizeWorldGrid.y)
		toY = maxSizeWorldGrid.y;

	sf::FloatRect	playerBounds = entity->getGlobalBounds();
	sf::FloatRect	nextPositionBounds = entity->getNextPositionBounds(dt);

	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{
			for (int k = 0; k < map[x][y][layer].size(); k++)
			{
				sf::FloatRect	tileBounds = map[x][y][layer][k]->getGlobalBounds();
				if (map[x][y][layer][k]->getCollision()
					&& map[x][y][layer][k]->intersects(nextPositionBounds))
				{
					//Bottom collision of entity with tile
					if (playerBounds.top < tileBounds.top
						&& playerBounds.top + playerBounds.height < tileBounds.top + tileBounds.height
						&& playerBounds.left < tileBounds.left + tileBounds.width
						&& playerBounds.left + playerBounds.width > tileBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, tileBounds.top - playerBounds.height);
					}
					//Top collision of entity with tile
					if (playerBounds.top > tileBounds.top
						&& playerBounds.top + playerBounds.height > tileBounds.top + tileBounds.height
						&& playerBounds.left < tileBounds.left + tileBounds.width
						&& playerBounds.left + playerBounds.width > tileBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, tileBounds.top + tileBounds.height);
					}

					//Right collision of entity with tile
					if (playerBounds.left < tileBounds.left
						&& playerBounds.left + playerBounds.width < tileBounds.left + tileBounds.width
						&& playerBounds.top < tileBounds.top + tileBounds.height
						&& playerBounds.top + playerBounds.height > tileBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(tileBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision of entity with tile
					if (playerBounds.left > tileBounds.left
						&& playerBounds.left + playerBounds.width > tileBounds.left + tileBounds.width
						&& playerBounds.top < tileBounds.top + tileBounds.height
						&& playerBounds.top + playerBounds.height > tileBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(tileBounds.left + tileBounds.width, playerBounds.top);
					}
				}
			
			}
		}
	}
}

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget &target, const sf::Vector2i &gridPosiiton)
{

	layer = 0;
	fromX = gridPosiiton.x - 4;
	if (fromX < 0)
		fromX = 0;
	else if (fromX > maxSizeWorldGrid.x)
		fromX = maxSizeWorldGrid.x;

	toX = gridPosiiton.x + 8;
	if (toX < 0)
		toX = 0;
	else if (toX > maxSizeWorldGrid.x)
		toX = maxSizeWorldGrid.x;

	fromY = gridPosiiton.y - 3;
	if (fromY < 0)
		fromY = 0;
	else if (fromY > maxSizeWorldGrid.y)
		fromY = maxSizeWorldGrid.y;

	toY = gridPosiiton.y + 8;
	if (toY < 0)
		toY = 0;
	else if (toY > maxSizeWorldGrid.y)
		toY = maxSizeWorldGrid.y;

	for (int x = fromX; x < toX; x++)
	{
		for (int y = fromY; y < toY; y++)
		{
			for (int k = 0; k < map[x][y][layer].size(); k++)
			{
				if (map[x][y][layer][k]->getType() == TileTypes::DOODAD)
				{
					deferredRenderStack.push(map[x][y][layer][k]);
				}
				else
					map[x][y][layer][k]->render(target);
				if (map[x][y][layer][k]->getCollision())
				{
					collisionBox.setPosition(map[x][y][layer][k]->getPosition());
					target.draw(collisionBox);
				}
			}
			
		}
	}
}

void TileMap::renderDeferred(sf::RenderTarget &target)
{
	while (!deferredRenderStack.empty())
	{
		deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}
