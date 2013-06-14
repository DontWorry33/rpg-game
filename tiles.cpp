#include "tiles.h"

Tiles::Tiles()
{
	grass_tile_image.LoadFromFile("mattgfx/grass_tile.png");
	grass_tile_image.SetSmooth(false);
	grass_tile.SetImage(grass_tile_image);

	gravel_tile_image.LoadFromFile("mattgfx/gravel_tile.png");
	gravel_tile_image.SetSmooth(false);
	gravel_tile.SetImage(gravel_tile_image);
	
	tree_tile_image.LoadFromFile("mattgfx/tree.png");
	tree_tile_image.SetSmooth(false);
	tree_tile.SetImage(tree_tile_image);
	
	sand_tile_image.LoadFromFile("mattgfx/sand_tile.png");
	sand_tile_image.SetSmooth(false);
	sand_tile.SetImage(sand_tile_image);
	
}

void Tiles::addTile(sf::RenderWindow& App, int xNum, int yNum, int tileType)
{
	if (tileType==0)
	{
		gravel_tile.SetPosition(xNum*32, yNum*32);
		App.Draw(gravel_tile);
	}
	if (tileType==1)
	{
		grass_tile.SetPosition(xNum*32, yNum*32);
		App.Draw(grass_tile);
	}
	if (tileType==2)
	{
		tree_tile.SetPosition(xNum*32,yNum*32);
		App.Draw(tree_tile);
	}
	if (tileType==3)
	{
		sand_tile.SetPosition(xNum*32,yNum*32);
		App.Draw(sand_tile);
	}
}

void Tiles::loadMap(const char* map_file, sf::RenderWindow& App)
{
	int y=0;
	std::string cords;
	std::ifstream map(map_file);
	if (map.is_open())
	{
		while (map.good())
		{
			getline(map,cords);

			for (unsigned int horz=0; horz<cords.length(); horz++) 
			{
				if (cords[horz]=='0')
				{
					this->addTile(App,horz,y, 0);
					gravel_tiles.insert(std::pair<int,int>(horz,y));
				}
				if (cords[horz]=='1') 
				{
					this->addTile(App,horz,y, 1);
					grass_tiles.insert(std::pair<int,int>(horz,y));
				}
				if (cords[horz]=='2')
				{
					this->addTile(App,horz,y, 2);
					tree_tiles.insert(std::pair<int,int>(horz,y));
				}
				if (cords[horz]=='3')
				{
					this->addTile(App,horz,y, 3);
					sand_tiles.insert(std::pair<int,int>(horz,y));
				}
			}
			y+=1;
		}	
		map.close();
	}
	else std::cout << "Unable to open file" << std::endl;
}
