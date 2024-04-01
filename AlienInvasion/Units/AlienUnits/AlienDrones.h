#pragma once
#include "../Unit.h"
#include "../../DataStructures/Queue/LinkedQueue.h"
class AlienDrones :
    public Unit
{
public:
    virtual void Attack();
};

