#pragma once
#include "../Unit.h"
class AlienMonster :
    public Unit
{
    int infection_probability;
public:
    AlienMonster(int jointime, int health, int power, int attackcapacity, int infprob);
    virtual void Attack(Game* gameptr);
    virtual void heal(int imp) {};
};

