#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#ifndef ITEMS_H
#define ITEMS_H


struct Items
{
	//Constructor/Destructor
	Items();
	~Items();
	
	//Functions
	void displayItems(sf::RenderWindow&, sf::Event&, sf::Sprite&);
	void loadPaths(std::vector<std::string>&, std::vector<std::string>&);
	void setItems(sf::RenderWindow&);
	void left_slots_initialize(std::map<int,sf::Sprite*>&);
	void thumb_id_initialize(std::vector<sf::Sprite*> items, std::vector<std::string> item_paths, std::map<sf::Sprite*, int>& thumb_id);
	void equip_item(sf::Sprite*);
	//Vector for path to thumbnails
	std::vector<std::string> item_paths;
	//Vector for path to sprites
	std::vector<std::string> sprite_paths;
	
	//Vector for sf::Images to images of the thumbnails
	std::vector<sf::Image*> item_imgs;
	//Vector for sf::Sprites for the actual thumbnails
	std::vector<sf::Sprite*> items;
	//Vector for sf::Images to the images of the sprites
	std::vector<sf::Image*> sprite_items;
	//Vector for sf::Sprites for the actual sprites
	std::vector<sf::Sprite*> sprite_spr;
    //Contains thumbnails as keys, sprites as values
	std::map<sf::Sprite*, sf::Sprite*> thumbspr;
	//position of thumbnails on map
	std::map<sf::Sprite*, std::map<int,int> >item_pos;
	//Inventory sprite representation
	std::vector< std::vector<sf::Sprite*> > slots;
	//Items you pick up to be passed to animation.cpp where it gets drawn ontop of eachother
	std::vector<sf::Sprite*> equipped;
	//Equipped sprite representation
	std::map<int, sf::Sprite*> left_slots;
	//Map to determine ID's of thumbnails for appropriate left_slots
	std::map<sf::Sprite*, int> thumb_id;
	
	//size of thumbnails
	int ITEM_SIZE;
	
	//Inventory objs
	sf::Sprite inventory;
	sf::Image inv_img;
	
	//MouseOver Inventory
	sf::Image mouse_over_img;
	sf::Sprite mouse_over;
	
	//Description text
	sf::String desc;
		
	//Disable assignment/copy constructor
	Items(const Items& other)=delete;
	Items& operator=(const Items& other)=delete;
	
};



#endif
