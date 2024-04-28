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

void AlienArmy::attack(Game* gameptr)
{
	Unit* unitAttacking = nullptr;
	AlienSoldiers.peek(unitAttacking);
	if (unitAttacking)
	{
		unitAttacking->Attack(gameptr);
		if (!unitAttacking->getmakeAttack())
		{
			unitAttacking->setFirstAttackTime(gameptr->getCrntTimeStep());
			unitAttacking->setmakeAttack(true);
		}
	}
	if (AlienDrones.getCount() >= 2)
	{
		AlienDrones.peek(unitAttacking);
		if (unitAttacking) 
		{
			unitAttacking->Attack(gameptr);
			if (!unitAttacking->getmakeAttack())
			{
				unitAttacking->setFirstAttackTime(gameptr->getCrntTimeStep());
				unitAttacking->setmakeAttack(true);
			}
		}
		AlienDrones.peekrear(unitAttacking);
		if (unitAttacking) 
		{
			unitAttacking->Attack(gameptr);
			if (!unitAttacking->getmakeAttack())
			{
				unitAttacking->setFirstAttackTime(gameptr->getCrntTimeStep());
				unitAttacking->setmakeAttack(true);
			}
		}
	}
	AlienMonsters.peekRandomly(unitAttacking);
	if (unitAttacking) 
	{
		unitAttacking->Attack(gameptr);
		if (!unitAttacking->getmakeAttack())
		{
			unitAttacking->setFirstAttackTime(gameptr->getCrntTimeStep());
			unitAttacking->setmakeAttack(true);
		}
	}
}

void AlienArmy::print()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 11);

	cout << "==============  Alien Army Alive Units =============\n";
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

int AlienArmy::getTotalADf()
{
	int Df = 0;
	Unit* unit;

	while (AlienSoldiers.dequeue(unit))
	{
		if (unit->getmakeAttack())
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
	}
	while (AlienDrones.dequeue(unit))
	{
		if (unit->getmakeAttack())
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
	}
	while (AlienMonsters.remove(unit))
	{
		if (unit->getmakeAttack())
			Df += unit->getFirstAttackTime() - unit->getJoinTime();
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
