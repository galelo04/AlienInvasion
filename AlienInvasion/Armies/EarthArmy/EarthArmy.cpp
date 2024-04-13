#include "EarthArmy.h"

EarthArmy::EarthArmy()
{
}

void EarthArmy::addUnit(Unit* unit, UnitType type, Direction dir)
{
	switch (type)
	{
	case(UnitType::EarthSoldier):
	{
		EarthSoldiers.enqueue(unit);
		break;
	}
	case(UnitType::Tank):
	{
		EarthTanks.push(unit);
		break;
	}
	case(UnitType::Gunnery):
	{
		EarthGunneries.enqueue(unit, unit->getHealth() + unit->getPower());
		break;
	}
	default:
		break;
	}
}

Unit* EarthArmy::removeUnit(UnitType type, Direction dir)
{
	Unit* removedUnit = nullptr;
	int pri;

	switch (type)
	{
	case (UnitType::EarthSoldier):
	{
		EarthSoldiers.dequeue(removedUnit);
		break;
	}
	case (UnitType::Tank):
	{
		EarthTanks.pop(removedUnit);
		break;
	}
	case (UnitType::Gunnery):
	{
		EarthGunneries.dequeue(removedUnit, pri);
		break;
	}
	default:
		break;
	}
	return removedUnit;
}

void EarthArmy::attack()
{
}

void EarthArmy::print()
{
	cout << "==============  Earth Army Alive Units =============\n";
	cout << EarthSoldiers.getCount() << " ES ";
	EarthSoldiers.printlist();
	cout << EarthTanks.getCount() << " ET ";
	EarthSoldiers.printlist();
	cout << EarthGunneries.getCount() << " EG ";
	//EarthGunneries.printlist();
}
