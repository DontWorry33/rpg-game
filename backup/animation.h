#include <SFML/Graphics.hpp>
#include "strings.h"
#include "tiles.h"
#ifndef ANIMATION_H
#define ANIMATION_H

struct Strings;
struct Tiles;
struct Inventory;

struct Animation
{

	//Basic
	int ani_movements[4]; //down,left,right,up
	sf::Image ani_img;
	sf::Sprite ani_spr;
	
	//Speed and position for animation
	double speed;
	double xpos;
	double ypos;	
	double velx;
	double vely;
	
	//Pos for picture
	int ani_ypos;
	int ani_xpos;
	int st;
	
	//Animation image dimensions
	double ani_img_full_width;
	double ani_img_full_height;
	double ani_img_width;
	double ani_img_height;
	
	//Methods
	Animation(){}
	Animation(const char*);
	void swapImage(std::vector<sf::Sprite*>);
	void Update(sf::RenderWindow&, Tiles&, sf::View&, int&, Strings&);
	
	std::vector<sf::Sprite> to_draw;
	
	sf::Clock clock;
	
	
};

#endif

