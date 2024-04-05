#pragma once
#include "../Unit.h".
#include "../../DataStructures/Queue/LinkedQueue.h".

class EarthSoldier : public Unit
{
public:
	EarthSoldier(int jointime, int health, int power, int attackcapacity);
	virtual void Attack();
};

