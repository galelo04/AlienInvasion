#include "EarthGunnery.h"

EarthGunnery::EarthGunnery(int jointime, int health, int power, int attackcapacity) :Unit(UnitType::Gunnery, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthGunnery::Attack()
{
}
