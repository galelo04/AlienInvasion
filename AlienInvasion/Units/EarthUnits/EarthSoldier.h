#pragma once
#include "../Unit.h".

class EarthSoldier : public Unit
{
public:
	EarthSoldier(int jointime, int health, int power, int attackcapacity);
	virtual bool Attack(Game* gameptr);
	virtual void heal(int imp);
};

