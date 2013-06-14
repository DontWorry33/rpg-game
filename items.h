#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include "character.h"
#include "equipment.cpp"
#include "slotitems.cpp"

#ifndef ITEMS_H
#define ITEMS_H
struct Character;
struct Items
{
	
	//Constructor/Destructor
	Items();
	~Items();
	
	//Functions
	void displayItems(sf::RenderWindow&, sf::Event&, sf::Sprite&, sf::Vector2f&, Character&);
	void displayStats(sf::RenderWindow&,Character&);
	void loadPaths(std::vector<Equip*>&);
	void setItems(sf::RenderWindow&);
	void left_slots_initialize();
	void equip_item(sf::Sprite*);
	
	
	//Vector for path to thumbnails
	std::vector<Equip*> item_paths;
	
    //Contains thumbnails as keys, sprites as values
	std::map<sf::Sprite*, sf::Sprite*> thumbspr;
	//position of thumbnails on map
	std::map<Equip*, std::map<int,int> >item_pos;
	//Inventory sprite representation
	std::vector< std::vector<Slot_Items*> > slots;
	//Items you pick up to be passed to animation.cpp where it gets drawn ontop of eachother
	std::vector<sf::Sprite*> equipped;
	//Equipped sprite representation
	std::map<int, sf::Sprite*> left_slots;
	//Map to determine ID's of thumbnails for appropriate left_slots
	std::map<sf::Sprite*, int> thumb_id;

	//Stats objs
	sf::Sprite stats;
	sf::Image stats_img;

	//Inventory objs
	sf::Sprite inventory;
	sf::Image inv_img;
	
	//MouseOver Inventory
	sf::Image mouse_over_img;
	sf::Sprite mouse_over;

	//top description bar
	sf::Sprite desc_bar;
	sf::Image desc_bar_img;
	
	//Description text
	sf::String desc;
	
	//blankimg
	sf::Image blank;
	int ITEM_SIZE;
	bool inventory_isopen;
	bool last_I;
	bool stats_isopen;
	bool last_S;
	//Disable assignment/copy constructor
	Items(const Items& other)=delete;
	Items& operator=(const Items& other)=delete;
	
};


#endif
