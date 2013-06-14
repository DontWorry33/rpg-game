#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#ifndef TILES_H
#define TILES_H

struct Animation;

struct Tiles
{
	//Constructors
	Tiles();
	
	//Functions
	void addTile(sf::RenderWindow&, int, int, int);
	void loadMap(const char*, sf::RenderWindow&);
	
	//Tiles
	sf::Sprite gravel_tile;
	sf::Image gravel_tile_image;
	
	sf::Sprite grass_tile;
	sf::Image grass_tile_image;
	
	sf::Sprite tree_tile;
	sf::Image tree_tile_image;
	
	sf::Sprite sand_tile;
	sf::Image sand_tile_image;
	
	//Tile Containers
	std::multimap<int,int> gravel_tiles;
	std::multimap<int,int> grass_tiles;
	std::multimap<int,int> tree_tiles;
	std::multimap<int,int> sand_tiles;
	
};

#endif
