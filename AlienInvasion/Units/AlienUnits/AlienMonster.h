#pragma once
#include "../Unit.h"
class AlienMonster :
    public Unit
{
public:
    AlienMonster(int jointime , int health , int power , int attackcapacity);
    virtual void Attack(Game* gameptr, bool isSilent);
};

