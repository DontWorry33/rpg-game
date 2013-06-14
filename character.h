#include <SFML/Graphics.hpp>
#include "animation.h"
#include "strings.h"
#include "characterstats.h"

#ifndef CHARACTER_H
#define CHARACTER_H

struct Animation;
struct CharacterStats;

struct Character
{
	Character(Animation&, CharacterStats&);
	Animation player;
	CharacterStats stats;
	
};



#endif
