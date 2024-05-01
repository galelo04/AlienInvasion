#include "HealingUnit.h"

HealingUnit::HealingUnit(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::HealingUnit, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void HealingUnit::Attack(Game* gameptr, bool isSilent)
{
}
