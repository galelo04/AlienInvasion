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
	virtual void addUnit(Unit* unit) = 0;
	virtual Unit* removeUnit(UnitType type ) =0;
	virtual bool attack(Game * gameptr) = 0;
	virtual void print() = 0;
};

