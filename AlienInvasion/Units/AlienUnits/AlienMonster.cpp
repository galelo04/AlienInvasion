#include "AlienMonster.h"
#include "../../Game.h"



AlienMonster::AlienMonster(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Monster, last_Alien_Id++, jointime, health, power, attackcapacity)
{

}

void AlienMonster::Attack(Game* gameptr)
{

}
