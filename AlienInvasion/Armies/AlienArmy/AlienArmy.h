#pragma once
#include "../../DataStructures/Queue/LinkedQueue.h"
#include "../Army.h"
#include "../../Units/Unit.h"
#include "../../Units/AlienUnits/AlienMonster.h"
#include "../../Units/AlienUnits/AlienDrone.h"
#include "../../Units/AlienUnits/AlienSoldier.h"
#include"../../DataStructures/arrayADT/arrayADT.h"

class AlienArmy : public Army
{
	int ASCount;
private:
	LinkedQueue<Unit*>AlienSoldiers;
	LinkedQueue<Unit*> AlienDrones;
	arrayADT<Unit*> AlienMonsters;
	Direction addDroneDirection;
	Direction removeDroneDirection;
public:
	AlienArmy();
	virtual void addUnit(Unit* unit);
	virtual Unit* removeUnit(UnitType type );
	virtual void attack(Game* gameptr);
	virtual void print();
	int getASCount();
	~AlienArmy();
};
