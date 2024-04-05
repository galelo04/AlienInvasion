#pragma once
#include "../Units/Unit.h"

struct removedUnits
{
	Unit* unit1 = nullptr;
	Unit* unit2 = nullptr;
};
class Army
{
public:
	virtual void addUnit(Unit* unit , UnitType type) = 0;
	virtual removedUnits removeUnit(UnitType type) =0;
	virtual void attack() = 0;
	virtual void print() = 0;
};

