#include "characterstats.h"

CharacterStats::CharacterStats()
{
	health=100;
	mana=50;
	strength=10;
	defence=10;
	dexterity=10;	
	
	all_stats.push_back(health);
	all_stats.push_back(mana);
	all_stats.push_back(strength);
	all_stats.push_back(defence);
	all_stats.push_back(dexterity);
	
}
