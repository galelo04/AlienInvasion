#pragma once
#include "../Unit.h"
class AlienDrone :
    public Unit
{
public:
    AlienDrone(int jointime, int health, int power, int attackcapacity);
    virtual bool Attack(Game* gameptr);
    virtual void heal(int imp) {};
};

