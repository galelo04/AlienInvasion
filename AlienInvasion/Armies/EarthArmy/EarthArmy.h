#pragma once
#include "../Army.h"
#include "../../Units/EarthUnits/EarthSoldier.h"
#include "../../Units/EarthUnits/EarthGunnery.h"
#include "../../Units/EarthUnits/EarthTank.h"
#include "../../DataStructures/Stack/ArrayStack.h"
#include "../../DataStructures/Queue/LinkedQueue.h"
#include "../../DataStructures/Pri-Queue/priQueue.h"

class EarthArmy : public Army
{
private:
	LinkedQueue<Unit*>EarthSoldiers;
	ArrayStack<Unit*>EarthTanks;
	priQueue<Unit*>EarthGunneries;
	ArrayStack<Unit*>HealingList;
	priQueue <Unit*> UML;
public:
	EarthArmy();
	virtual void addUnit(Unit* unit);
	void addToUML(Unit*& unit, int priority,int JT);
	virtual Unit* removeUnit(UnitType type);
	virtual void attack(Game* gameptr);
	virtual void print();
	int getESCount();
	int getETCount();
	int getEGCount();
	int getTotalEDf();
	~EarthArmy();
};

