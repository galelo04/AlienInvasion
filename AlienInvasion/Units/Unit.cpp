#include "Unit.h"

int Unit::last_Earth_Id = 1;
int Unit::last_Alien_Id = 2000;

Unit::Unit(UnitType type, int id, int jointime, int health, int power, int attackcapacity)
    :ID(id) ,Type(type) , JoinTime(jointime) , Health(health) , Power(power) , AttackCapacity(attackcapacity)
{
}

//UnitType Unit::getType() const
//{
//    return Type;
//}
//
//int Unit::getID() const
//{
//    return ID;
//}
//
//void Unit::setID(int id)
//{
//    ID = id;
//}
//
