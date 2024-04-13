#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int jointime, int health, int power, int attackcapacity, int pri) :Unit(UnitType::Gunnery, last_Earth_Id++, jointime, health, power, attackcapacity), Pri(pri)
{
}

void EarthGunnery::Attack()
{
}

int EarthGunnery::getPri()
{
	return Pri;
}
