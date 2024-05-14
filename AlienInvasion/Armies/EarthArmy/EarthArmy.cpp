#include "EarthArmy.h"
#include <Windows.h>
#include "../../Game.h"

EarthArmy::EarthArmy()
{
	srand((unsigned)time(NULL));
	InfectedSoldiers = 0;
	TotalinfES = 0;
	totalHealedES = 0;
	totalFixedET = 0;
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
		EarthGunneries.enqueue(unit, unit->getHealth() + unit->getPower());
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
	default:
		break;
	}
	return removedUnit;
}

Unit* EarthArmy::removefromUML(UnitType type)
{
	Unit* removedUnit = nullptr;
	int pri;

	switch (type)
	{
	case(UnitType::EarthSoldier):
	{
		UMLsoldiers.dequeue(removedUnit,pri);
		break;
	}
	case(UnitType::Tank):
	{
		UMLtanks.dequeue(removedUnit);
		break;
	}
	default: break;
	}
	return removedUnit;
}

bool EarthArmy::attack(Game* gameptr)
{
	bool didSoldiersAttack = false;
	bool didTanksAttack = false;
	bool didGunneriesAttack = false;
	bool didHUHeal = false;
	Unit* unitAttacking = nullptr;
	int pri = 0;
	
	if (EarthSoldiers.dequeue(unitAttacking))
	{
		didSoldiersAttack=unitAttacking->Attack(gameptr);
		EarthSoldiers.enqueue(unitAttacking);
	}

	if (EarthTanks.peek(unitAttacking))
	{
		didTanksAttack=unitAttacking->Attack(gameptr);
	}

	if (EarthGunneries.peek(unitAttacking, pri))
	{
		didGunneriesAttack=unitAttacking->Attack(gameptr);
	}
	if (HealingList.peek(unitAttacking)&&(UMLsoldiers.getCount()>0||UMLtanks.getCount()>0))
	{
		unitAttacking->Attack(gameptr);

		didHUHeal=HealingList.pop(unitAttacking);
		if(didHUHeal)
			gameptr->addToKilledList(unitAttacking);
	}
	infectionSpread();
	return (didSoldiersAttack || didTanksAttack || didGunneriesAttack || didHUHeal);
}


void EarthArmy::infectionSpread()
{
	LinkedQueue<Unit*> templist;
	Unit* removed = nullptr;
	if (InfectedSoldiers > 0)
	{
		int A = 1 + (rand() % 100);
		if (A <= 2)
		{
			int size = getESCount();
			int index = 1 + (rand() % size);
			int i = 0;
			while(EarthSoldiers.dequeue(removed))
			{
				if (i == index)
				{
					if (!removed->isInfected())
					{
						removed->infect(true);
						incrementInfES();
					}
				}
				templist.enqueue(removed);
				i++;
			}
			while (templist.dequeue(removed))
				EarthSoldiers.enqueue(removed);
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
	cout << HealingList.getCount() << " HU ";
	HealingList.printlist();
	cout << "ES inf% " << infES_P()<<endl;

}

void EarthArmy::addToUML(Unit* unit,int UT)
{
	switch (unit->getType())
	{
	case UnitType::EarthSoldier:
	{
		UMLsoldiers.enqueue(unit,-unit->getHealth());
		unit->setUMLJoiningTime(UT);
		break;
	}
	case UnitType::Tank:
	{
		UMLtanks.enqueue(unit);
		unit->setUMLJoiningTime(UT);
		break;
	}
	default:
		break;
	}
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

int EarthArmy::getInfESCount()
{
	return InfectedSoldiers;
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

void EarthArmy::destroyUML(Game* gameptr)
{
	Unit* removeUnit;
	int pri = 0;
	while (UMLsoldiers.dequeue(removeUnit, pri))
	{
		removeUnit->decrementHealth(removeUnit->getHealth());
		gameptr->addToKilledList(removeUnit);
	}
	while (UMLtanks.dequeue(removeUnit))
	{
		removeUnit->decrementHealth(removeUnit->getHealth());
		gameptr->addToKilledList(removeUnit);
	}
}

int EarthArmy::getTotalFixedET()
{
	return totalFixedET;
}

void EarthArmy::incrementFixedET()
{
	totalFixedET++;
}

int EarthArmy::getTotalHealedES()
{
	return totalHealedES;
}

void EarthArmy::incrementHealedES()
{
	totalHealedES++;
}

int EarthArmy::getTotalinfES()
{
	return TotalinfES;
}


void EarthArmy::incrementInfES()
{
	InfectedSoldiers++;
	TotalinfES++;
}

void EarthArmy::decrementInfES()
{
	InfectedSoldiers--;
}

int EarthArmy::infES_P()
{
	if (EarthSoldiers.getCount() == 0) return 0;
	return ((getInfESCount()*100)/EarthSoldiers.getCount());

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
	while(UMLsoldiers.dequeue(unittobedeleted, pri))
		delete unittobedeleted;
	while (UMLtanks.dequeue(unittobedeleted))
		delete unittobedeleted;
}
