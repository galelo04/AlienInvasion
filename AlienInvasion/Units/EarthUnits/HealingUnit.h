#pragma once
#include "../Unit.h"
class HealingUnit :
    public Unit
{
public:
    HealingUnit(int jointime, int health, int power, int attackcapacity);
    virtual bool Attack(Game* gameptr);
    virtual void heal(int imp) {}
};

