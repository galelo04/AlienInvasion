#include "Unit.h"

int Unit::last_Earth_Id = 1;
int Unit::last_Alien_Id = 2000;

Unit::Unit(UnitType type, int id, int jointime, int health, int power, int attackcapacity)
    :ID(id) ,Type(type) , JoinTime(jointime) , Health(health) , Power(power) , AttackCapacity(attackcapacity)
{
}

UnitType Unit::getType() const
{
    return Type;
}

int Unit::getID() const
{
    return ID;
}

int Unit::getJoinTime() const
{
    return JoinTime;
}

int Unit::getHealth() const
{
    return Health;
}

int Unit::getPower() const
{
    return Power;
}

int Unit::getAttackCapacity() const
{
    return AttackCapacity;
}

void Unit::decrementHealth(int damage)
{
    Health -= damage;
}

