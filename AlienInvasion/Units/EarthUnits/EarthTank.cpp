#include "EarthTank.h"

EarthTank::EarthTank(int id,int jointime, int health, int power, int attackcapacity) :Unit(UnitType::Tank, id, jointime, health, power, attackcapacity)
{
}

void EarthTank::Attack()
{
}
