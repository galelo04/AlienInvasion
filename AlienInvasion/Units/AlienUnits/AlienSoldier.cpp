#include "AlienSoldier.h"


AlienSoldier::AlienSoldier( int id,int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::AlienSoldier, id,jointime,health,power,attackcapacity)
{
}

void AlienSoldier::Attack()
{
}
