#include "EarthArmy.h"
#include <Windows.h>

EarthArmy::EarthArmy()
{
}

void EarthArmy::addUnit(Unit* unit)
{
	if (!unit) return;
	UnitType type = unit->getType();
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
		EarthGunnery* gunnery = dynamic_cast <EarthGunnery*> (unit);
		if (gunnery)
		{
			gunnery->setPri(unit->getHealth() + unit->getPower());
			EarthGunneries.enqueue(gunnery, gunnery->getPri());
		}
			break;
	}
	default:
		break;
	}
}

Unit* EarthArmy::removeUnit(UnitType type)
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
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console_color, 10);
	cout << "==============  Earth Army Alive Units =============\n";
	SetConsoleTextAttribute(console_color, 15);
	cout << EarthSoldiers.getCount() << " ES ";
	EarthSoldiers.printlist();
	cout << EarthTanks.getCount() << " ET ";
	EarthTanks.printlist();
	cout << EarthGunneries.getCount() << " EG ";
	EarthGunneries.printlist();
}

EarthArmy::~EarthArmy()
{
	Unit* unittobedeleted;
	int pri;
	while (EarthSoldiers.dequeue(unittobedeleted))
		delete unittobedeleted;
	while (EarthGunneries.dequeue(unittobedeleted,pri))
		delete unittobedeleted;
	while (EarthTanks.pop(unittobedeleted))
		delete unittobedeleted;
}