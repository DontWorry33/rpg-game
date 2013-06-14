#include <SFML/Graphics.hpp>
#include <algorithm>
#include "items.h"
#include "character.h"

#ifndef EVENTS_H
#define EVENTS_H

struct Items;
struct Character;

struct Events
{
	Events();
	void findItem(Items&, Character&);
	void mouseOver(Items&, Character&);
};



#endif
