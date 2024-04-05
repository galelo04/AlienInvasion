#pragma once
#include "../Units/Unit.h"

enum class Direction
{
	Front,
	Back
};
class Army
{
public:
	virtual void addUnit(Unit* unit , UnitType type , Direction dir ) = 0;
	virtual Unit* removeUnit(UnitType type , Direction dir ) =0;
	virtual void attack() = 0;
	virtual void print() = 0;
};

