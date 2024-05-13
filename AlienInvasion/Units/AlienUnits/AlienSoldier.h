#pragma once
#include "../Unit.h"

class AlienSoldier : public Unit
{
public:
	AlienSoldier(int jointime , int health , int power , int attackcapacity);
	virtual bool Attack(Game* gameptr);
	virtual void heal(int imp) {};
};