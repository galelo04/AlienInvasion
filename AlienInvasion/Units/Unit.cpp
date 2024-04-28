#include "Unit.h"
#include "../Game.h"

int Unit::last_Earth_Id = 1;
int Unit::last_Alien_Id = 2000;

Unit::Unit(UnitType type, int id, int jointime, int health, int power, int attackcapacity)
    :ID(id) ,Type(type) , JoinTime(jointime) , Health(health) , Power(power) , AttackCapacity(attackcapacity), numAttacks(0),intialHealth(health)
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

int Unit::getTa() const
{
    return firstAttackTime;
}

void Unit::setTa(int Ta)
{
    firstAttackTime = Ta;
}

int Unit::getTd() const
{
    return DestructionTime;
}

void Unit::setTd(int Td)
{
    DestructionTime = Td;
}

int Unit::getDf() const
{
    return (getTa() - getJoinTime());
}

int Unit::getDd() const
{
    return (getTd() - getTa());
}

int Unit::getDb() const
{
    return (getDf() + getDd());
}

int Unit::getnumAttacks() const
{
    return numAttacks;
}

void Unit::incrementnumAttacks()
{
    numAttacks++;
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

int Unit::getIntialHealth() const
{
    return intialHealth;
}

