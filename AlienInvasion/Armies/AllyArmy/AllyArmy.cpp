#include "AllyArmy.h"
#include "../../Game.h"
#include "Windows.h"
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

bool AllyArmy::attack(Game* gameptr)
{
	bool didSUAttack = false;
	Unit* unitAttacking = nullptr;

	if (SaverUnits.peek(unitAttacking))
	{
		unitAttacking->Attack(gameptr);
	}
	return didSUAttack;
}

void AllyArmy::print()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console_color, 14);
	cout << "==============  Alive Saver Units   =============\n";
	SetConsoleTextAttribute(console_color, 15);
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

