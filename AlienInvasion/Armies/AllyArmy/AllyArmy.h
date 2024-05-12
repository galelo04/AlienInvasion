#pragma once
#include "../Army.h"
#include "../../DataStructures/Queue/LinkedQueue.h"
class AllyArmy:public Army
{
private:
	LinkedQueue<Unit*>SaverUnits;
public:
	AllyArmy();
	virtual void addUnit(Unit* unit);
	virtual Unit* removeUnit(UnitType type);
	virtual void attack(Game* gameptr);
	virtual void print();
	int getSUCount();
	bool withdrawal(Game* gameptr);
	~AllyArmy();


};

