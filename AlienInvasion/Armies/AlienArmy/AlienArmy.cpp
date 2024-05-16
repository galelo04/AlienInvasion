#include "AlienArmy.h"
#include <Windows.h>
#include "../../Game.h"


AlienArmy::AlienArmy()
{
	addDroneDirection = Direction::Back;
	removeDroneDirection = Direction::Front;
}


void AlienArmy::addUnit(Unit* unit)
{
	if (!unit) return;
	UnitType type = unit->getType();
	switch (type)
	{
	case(UnitType::AlienSoldier):
	{
		AlienSoldiers.enqueue(unit);
		break;
	}
	case(UnitType::Monster):
	{
		AlienMonsters.add(unit);
		break;
	}
	case(UnitType::Drone):
	{
		switch (addDroneDirection)
		{
		case Direction::Front:
		{
			AlienDrones.enqueuefront(unit);
			addDroneDirection = Direction::Back;
			break;
		}
		case Direction::Back:
		{
			AlienDrones.enqueue(unit);
			addDroneDirection = Direction::Front;
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
}

Unit* AlienArmy::removeUnit(UnitType type)
{
	Unit* removedUnit = nullptr;
	switch (type)
	{
	case (UnitType::AlienSoldier):
	{
		AlienSoldiers.dequeue(removedUnit);
		break;
	}
	case (UnitType::Monster):
	{
		AlienMonsters.remove(removedUnit);
		break;
	}
	case (UnitType::Drone):
	{
		switch (removeDroneDirection)
		{
		case Direction::Front:
		{
			AlienDrones.dequeue(removedUnit);
			removeDroneDirection = Direction::Back;
			break;
		}
		case Direction::Back:
		{
			AlienDrones.dequeuerear(removedUnit);
			removeDroneDirection = Direction::Front;
			break;
		}
		default:
			break;
		}
	}
	default:
		break;
	}
	return removedUnit;
}

bool AlienArmy::attack(Game* gameptr)
{
	bool didSoldiersAttack = false;
	bool didMonstersAttack = false;
	bool didDronesAttack = false;
	Unit* unitAttacking = nullptr;

	if (AlienSoldiers.peek(unitAttacking))
	{
		didSoldiersAttack=unitAttacking->Attack(gameptr);
	}
	if (AlienDrones.getCount() >= 2)
	{
		if (AlienDrones.peek(unitAttacking))
		{
			didDronesAttack=unitAttacking->Attack(gameptr);
		}

		if (AlienDrones.peekrear(unitAttacking))
		{
			unitAttacking->Attack(gameptr);
		}
	}

	if (AlienMonsters.peekRandomly(unitAttacking))
	{
		didMonstersAttack=unitAttacking->Attack(gameptr);
	}
	return (didDronesAttack || didMonstersAttack || didSoldiersAttack);
}

void AlienArmy::print()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 11);

	cout << "==============  Alien Army Alive Units =======================\n";
	SetConsoleTextAttribute(console_color, 15);
	cout << AlienSoldiers.getCount() << " AS ";
	AlienSoldiers.printlist();
	cout << AlienMonsters.getcount() << " AM ";
	AlienMonsters.printlist();
	cout << AlienDrones.getCount() << " AD ";
	AlienDrones.printlist();
}

int AlienArmy::getASCount()
{
	return AlienSoldiers.getCount();
}

int AlienArmy::getADCount()
{
	return AlienDrones.getCount();
}

int AlienArmy::getAMCount()
{
	return AlienMonsters.getcount();
}

int AlienArmy::getTotalADf(int& totalAlivegotAttacked)
{
	int Df = 0;
	Unit* unit;

	while (AlienSoldiers.dequeue(unit))
	{
		if (unit->IsAttacked())
		{
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
			totalAlivegotAttacked++;
		}
	}
	while (AlienDrones.dequeue(unit))
	{
		if (unit->IsAttacked())
		{
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
			totalAlivegotAttacked++;
		}
	}
	while (AlienMonsters.remove(unit))
	{
		if (unit->IsAttacked())
		{
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
			totalAlivegotAttacked++;
		}
	}

	return Df;
}

AlienArmy::~AlienArmy()
{
	Unit* unittobedeleted;
	while (AlienSoldiers.dequeue(unittobedeleted))
		delete unittobedeleted;
	while (AlienMonsters.remove(unittobedeleted))
		delete unittobedeleted;
	while (AlienDrones.dequeue(unittobedeleted))
		delete unittobedeleted;
}
