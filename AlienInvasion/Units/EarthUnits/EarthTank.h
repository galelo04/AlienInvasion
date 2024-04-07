#pragma once
#include "../Unit.h".
#include "../../DataStructures/Pri-Queue/priQueue.h".

class EarthTank : public Unit
{
public:
	EarthTank(int jointime, int health, int power, int attackcapacity);
	virtual void Attack();
};

