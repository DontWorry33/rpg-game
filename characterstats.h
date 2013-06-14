#include <SFML/Graphics.hpp>
#include <vector>


#ifndef CHARACTERSTATS_H
#define CHARACTERSTATS_H
struct CharacterStats
{
	CharacterStats();
	int health;
	int mana;
	int strength;
	int defence;
	int dexterity;
	
	std::vector<int> all_stats;
	
};


#endif
