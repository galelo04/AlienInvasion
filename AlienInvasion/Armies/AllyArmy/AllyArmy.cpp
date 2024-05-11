#include "AllyArmy.h"
#include "../../Game.h"

AllyArmy::AllyArmy()
{
}

void AllyArmy::addUnit(Unit* unit)
{
	if (!unit) return;
	else
	{
		SaverUnits.enqueue(unit);
	}
}

Unit* AllyArmy::removeUnit(UnitType type)
{
	Unit* removedUnit = nullptr;
	SaverUnits.dequeue(removedUnit);
	return removedUnit;
}

void AllyArmy::attack(Game* gameptr)
{
	Unit* unitAttacking = nullptr;

	if (SaverUnits.peek(unitAttacking))
	{
		unitAttacking->Attack(gameptr);
	}
}

void AllyArmy::print()
{
	cout << "==============  Alive Saver Units   =============\n";
	
	cout << SaverUnits.getCount() << " SU ";
	SaverUnits.printlist();
}

int AllyArmy::getSUCount()
{
	return SaverUnits.getCount();
}

bool AllyArmy::withdrawal(Game* gameptr)
{
	if (gameptr->getEarthArmy()->getInfESCount() == 0)
	{
		Unit* SUtobeDestoryed;
		while (SaverUnits.dequeue(SUtobeDestoryed))
			delete SUtobeDestoryed;

		return true;
	}
	else
	{
		return false;
	}
}

AllyArmy::~AllyArmy()
{
	Unit* unittobedeleted;
	while (SaverUnits.dequeue(unittobedeleted))
		delete unittobedeleted;
}

