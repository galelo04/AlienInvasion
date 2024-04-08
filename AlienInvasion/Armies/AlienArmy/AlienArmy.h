#pragma once
#include "../../DataStructures/Queue/LinkedQueue.h"
#include "../Army.h"
#include "../../Units/Unit.h"
#include "../../Units/AlienUnits/AlienMonster.h"
#include "../../Units/AlienUnits/AlienDrone.h"
#include "../../Units/AlienUnits/AlienSoldier.h"

class AlienArmy : public Army
{
private:
	LinkedQueue<Unit*>AlienSoldiers;
	LinkedQueue<Unit*> AlienDrones;
	Unit* AlienMonsters[1000];
	int MonstersCount ;
	Direction addDroneDirection;
	Direction removeDroneDirection;
public:
	AlienArmy();
	virtual void addUnit(Unit* unit, UnitType type);
	virtual Unit* removeUnit(UnitType type );
	virtual void attack();
	virtual void print();
};
