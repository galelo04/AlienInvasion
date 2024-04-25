#include "EarthSoldier.h"

EarthSoldier::EarthSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::EarthSoldier, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthSoldier::Attack(Game* gameptr)
{
}

