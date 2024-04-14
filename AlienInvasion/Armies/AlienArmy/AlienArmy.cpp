#include "AlienArmy.h"



AlienArmy::AlienArmy()
{
	addDroneDirection = Direction::Back;
	removeDroneDirection = Direction::Front;
}


void AlienArmy::addUnit(Unit* unit , UnitType type )
{
	switch (type)
	{
	case(UnitType::AlienSoldier):
	{
		AlienSoldiers.enqueue(unit);
		break;
	}
	case(UnitType::Monster):
	{
		AlienMonsters[MonstersCount++] = unit;
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
		int randomindex = rand() % MonstersCount;
		removedUnit = AlienMonsters[randomindex];
		AlienMonsters[randomindex] = AlienMonsters[MonstersCount - 1];
		MonstersCount--;
		break;
	}
	case (UnitType::Drone):
	{
		switch (removeDroneDirection)
		{
		case Direction::Front:
		{
			if (AlienDrones.getCount() >= 2)
				AlienDrones.dequeue(removedUnit);
			removeDroneDirection = Direction::Back;
			break;
		}
		case Direction::Back:
		{
			if (AlienDrones.getCount() >= 1)
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

void AlienArmy::attack()
{
}

void AlienArmy::print()
{
	cout << "==============  Alien Army Alive Units =============\n";
	cout << AlienSoldiers.getCount() << " AS ";
	AlienSoldiers.printlist();
	cout << MonstersCount << " AM [";
	for (int i = 0; i < MonstersCount; i++)
	{
		cout << AlienMonsters[i]->getID();
		if (i != MonstersCount - 1)
			cout << ", ";
	}
	cout << "]" << endl;
	cout << AlienDrones.getCount() << " AD ";
	AlienDrones.printlist();
}
