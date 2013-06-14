#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#ifndef TESTITEMS_H
#define TESTITEMS_H

struct Equip
{
	int id;
	sf::String description;
	bool drawable;
	
	std::string pt_description; //plain_text_description
	std::map<std::string, int> stats;
	sf::Sprite* usable;
	sf::Image* u_img;
	
	sf::Sprite* thumb;
	sf::Image* thumb_img;
	
	void set_thumbnail(const char* path)
	{
		thumb_img = new sf::Image;
		thumb = new sf::Sprite;
		thumb_img->LoadFromFile(path);
		thumb->SetImage(*thumb_img);
	}
	
	bool operator<(const Equip &other) const
	{
		//return true;
		return u_img < other.u_img;
	}
	
	virtual ~Equip(){};

};

struct Head : public Equip
{
	Head(const char* path)
	{
		u_img = new sf::Image;
		usable = new sf::Sprite;
		u_img->LoadFromFile(path);
		usable->SetImage(*u_img);
		id=0;
		drawable=true;
	}
	
	~Head()
	{
		delete usable;
		delete u_img;
		delete thumb_img;
		delete thumb;
	}

};

struct Weapon : public Equip
{
	Weapon(const char* path)
	{
		u_img = new sf::Image;
		usable = new sf::Sprite;
		u_img->LoadFromFile(path);
		usable->SetImage(*u_img);
		id=1;
		drawable=true;
	}
	
	~Weapon()
	{
		delete usable;
		delete u_img;
		delete thumb_img;
		delete thumb;		
	}
};

struct Body : public Equip
{
	Body(const char* path)
	{
		u_img = new sf::Image;
		usable = new sf::Sprite;
		u_img->LoadFromFile(path);
		usable->SetImage(*u_img);
		id=2;
		drawable=true;
	}
	~Body()
	{
		delete usable;
		delete u_img;
		delete thumb_img;
		delete thumb;	
	}
	
};

struct Secondary : public Equip
{
	Secondary(const char* path)
	{
		u_img = new sf::Image;
		usable = new sf::Sprite;
		u_img->LoadFromFile(path);
		usable->SetImage(*u_img);
		id=3;
		drawable=true;
	}
	
	~Secondary()
	{
		delete usable;
		delete u_img;
		delete thumb_img;
		delete thumb;	
	}
};

struct Legs : public Equip
{
	Legs(const char* path)
	{
		u_img = new sf::Image;
		usable = new sf::Sprite;
		u_img->LoadFromFile(path);
		usable->SetImage(*u_img);
		id=4;
		drawable=true;
	}
	
	~Legs()
	{
		delete usable;
		delete u_img;
		delete thumb_img;
		delete thumb;	
	}
};
#endif
