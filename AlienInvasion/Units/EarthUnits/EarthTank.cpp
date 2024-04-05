#include "EarthTank.h"

EarthTank::EarthTank(int jointime, int health, int power, int attackcapacity) :Unit(UnitType::Tank, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthTank::Attack()
{
}
