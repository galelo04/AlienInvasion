#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int jointime, int health, int power, int attackcapacity) :Unit(UnitType::Gunnery, last_Earth_Id++, jointime, health, power, attackcapacity)
{
	setPri(power + health);
}

void EarthGunnery::Attack()
{
}

int EarthGunnery::getPri()
{
	return Pri;
}

void EarthGunnery::setPri(int pri)
{
	Pri = pri;
}
