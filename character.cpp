#include "character.h"

Character::Character(Animation& player, CharacterStats& stats)
{
	this->stats=stats;
	this->player=player;
}
