#include "AlienArmy.h"
#include <Windows.h>


AlienArmy::AlienArmy():ASCount(0)
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
		ASCount++;
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
		ASCount--;
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
	/*AlienSoldiers.peek(unitAttacking);
	if (unitAttacking)
		unitAttacking->Attack(gameptr);
	if (AlienDrones.getCount() >= 2)
	{
		AlienDrones.peek(unitAttacking);
		if (unitAttacking)
			unitAttacking->Attack(gameptr);
		AlienDrones.peekrear(unitAttacking);
		if (unitAttacking)
			unitAttacking->Attack(gameptr);
	}*/
	AlienMonsters.peekRandomly(unitAttacking);
	if (unitAttacking)
		unitAttacking->Attack(gameptr);
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
	return ASCount;
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
