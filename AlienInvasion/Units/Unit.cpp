#include "Unit.h"
#include "../Game.h"

int Unit::last_Earth_Id = 1;
int Unit::last_Alien_Id = 2000;
int Unit::last_Ally_Id = 4000;
Unit::Unit(UnitType type, int id, int jointime, int health, int power, int attackcapacity)
    :ID(id) ,Type(type) , JoinTime(jointime) , Health(health) , Power(power) , AttackCapacity(attackcapacity), Attacked(false), intialHealth(health) , infected(false) , immuned(false)
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

int Unit::getFirstAttackTime() const
{
    return firstAttackTime;
}

void Unit::setFirstAttackTime(int Ta)
{
    firstAttackTime = Ta;
}

int Unit::getDestructionTime() const
{
    return DestructionTime;
}

void Unit::setDestructionTime(int Td)
{
    DestructionTime = Td;
}

int Unit::getUMLJoiningTime() const
{
    return UMLJoiningTime;
}

void Unit::setUMLJoiningTime(int TU)
{
    UMLJoiningTime = TU;
}

bool Unit::IsAttacked() const
{
    return Attacked;
}

void Unit::makeAttacked(bool makeatt)
{
    Attacked = makeatt;
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

void Unit::infect(bool state)
{
    infected = state;
}

bool Unit::isInfected()
{
    return infected;
}

void Unit::immune(bool state)
{
    immuned = state;
}

bool Unit::isImmuned()
{
    return immuned;
}

