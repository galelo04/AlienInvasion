#pragma once
#include "../Unit.h".

class EarthTank : public Unit
{
public:
	EarthTank(int jointime, int health, int power, int attackcapacity);
	virtual void Attack(Game* gameptr, bool isSilent);
};

