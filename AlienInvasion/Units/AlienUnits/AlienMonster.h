#pragma once
#include "../Unit.h"
class AlienMonster :
    public Unit
{
public:
    AlienMonster(int id,int jointime , int health , int power , int attackcapacity);
    virtual void Attack();
};

