#include "AlienSoldier.h"


AlienSoldier::AlienSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::AlienSoldier, last_Alien_Id++,jointime,health,power,attackcapacity)
{
}

void AlienSoldier::Attack()
{
}
