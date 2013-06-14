#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#ifndef SLOTITEMS_H
#define SLOTITEMS_H

struct Slot_Items
{
	Slot_Items()
	{
		equipped=false;	
		equipped_over_img.LoadFromFile("inventory/equipped_over.png");
		equipped_over.SetImage(equipped_over_img);
		slot = new sf::Sprite;
		description_text.SetSize(14);
		actual_sprite = new sf::Sprite;
	}
	Slot_Items(sf::Image* thumbnail)
	{
		tnail_img=thumbnail;
		equipped=false;	
		equipped_over_img.LoadFromFile("inventory/equipped_over.png");
		equipped_over.SetImage(equipped_over_img);
		slot = new sf::Sprite;
		actual_sprite = new sf::Sprite;
	}
	sf::Image* tnail_img;
	sf::Sprite* slot;
	
	sf::Image equipped_over_img;
	sf::Sprite equipped_over;
	
	bool equipped;
	
	sf::String description_text;
	
	sf::Sprite* actual_sprite;
};

#endif
