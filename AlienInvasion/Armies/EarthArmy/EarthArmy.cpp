#include "EarthArmy.h"
#include <Windows.h>
#include "../../Game.h"

EarthArmy::EarthArmy()
{}

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
	case(UnitType::HealingUnit):
	{
		HealingList.push(unit);
		break;
	}
	default:
		break;
	}
}

void EarthArmy::addToUML(Unit*& unit,int priority,int JT)
{
	if (unit)
	{
		unit->setUMLJoiningTime(JT);
		UML.enqueue(unit, priority);

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
	case(UnitType::HealingUnit):
	{
		HealingList.pop(removedUnit);
		break;
	}
	case(UnitType::UMLUnit):
	{
		UML.dequeue(removedUnit,pri);
		break;
	}
	default:
		break;
	}
	return removedUnit;
}

void EarthArmy::attack(Game* gameptr)
{
	Unit* unitAttacking = nullptr;
	int pri = 0;
	EarthSoldiers.peek(unitAttacking);
	if (unitAttacking) 
	{
		unitAttacking->Attack(gameptr);
	}
	EarthTanks.peek(unitAttacking);
	if (unitAttacking) 
	{
	unitAttacking->Attack(gameptr);
	}
	EarthGunneries.peek(unitAttacking, pri);
	if (unitAttacking) 
	{
		unitAttacking->Attack(gameptr);
	}
	if (HealingList.pop(unitAttacking))
	{
		if (unitAttacking)
		{
			unitAttacking->Attack(gameptr);
			gameptr->addToKilledList(unitAttacking);
		}
	}
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



int EarthArmy::getESCount()
{
	return EarthSoldiers.getCount();
}

int EarthArmy::getETCount()
{
	return EarthTanks.getCount();
}

int EarthArmy::getEGCount()
{
	return EarthGunneries.getCount();
}

int EarthArmy::getTotalEDf(int& totalAlivegotAttacked)
{
	int Df = 0;
	int pri = 0;
	Unit* unit;

	while (EarthSoldiers.dequeue(unit))
	{
		if (unit->IsAttacked())
		{
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
			totalAlivegotAttacked++;
		}
	}
	while (EarthGunneries.dequeue(unit, pri))
	{
		if (unit->IsAttacked())
		{
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
			totalAlivegotAttacked++;
		}
	}
	while (EarthTanks.pop(unit))
	{
		if (unit->IsAttacked())
		{
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
			totalAlivegotAttacked++;
		}
	}

	return Df;
}

EarthArmy::~EarthArmy()
{
	Unit* unittobedeleted;
	int pri = 0;
	while (EarthSoldiers.dequeue(unittobedeleted))
		delete unittobedeleted;
	while (EarthGunneries.dequeue(unittobedeleted, pri))
		delete unittobedeleted;
	while (EarthTanks.pop(unittobedeleted))
		delete unittobedeleted;
	while(HealingList.pop(unittobedeleted))
		delete unittobedeleted;
	while(UML.dequeue(unittobedeleted, pri))
		delete unittobedeleted;
}
