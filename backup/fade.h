#include <SFML/Graphics.hpp>

#ifndef FADE_H
#define FADE_H

struct Fade
{
	//Constructors
	Fade(const char*);
	
	//Functions
	int fadeOut(sf::RenderWindow&);
	int fadeIn(sf::RenderWindow&);
	
	//Vars
	int alpha_num_out;
	int alpha_num_in;
	
	sf::Sprite filter;
	sf::Image filter_image;
	sf::Clock clock;
	
};


#endif
