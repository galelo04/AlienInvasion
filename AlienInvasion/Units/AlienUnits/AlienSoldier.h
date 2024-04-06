#pragma once
#include "../Unit.h"
#include "../../DataStructures/Queue/LinkedQueue.h"

class AlienSoldier : public Unit
{
public:
	AlienSoldier(int id,int jointime , int health , int power , int attackcapacity);
	virtual void Attack();
};