#include "AlienArmy.h"



AlienArmy::AlienArmy()
{

}


void AlienArmy::addUnit(Unit* unit , UnitType type ,Direction dir)
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
		switch (dir)
		{
		case Direction::Front:
			AlienDrones.enqueuefront(unit);
			break;
		case Direction::Back:
			AlienDrones.enqueue(unit);
			break;
		default:
			break;
		}
	}
	default:
		break;
	}
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
		cout << AlienMonsters[i];
		if (i != MonstersCount - 1)
			cout << ", ";
	}
	cout << "]" << endl;
	cout << AlienDrones.getCount() << " AD ";
	AlienDrones.printlist();
}

Unit* AlienArmy::removeUnit(UnitType type , Direction dir)
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
		if (AlienDrones.getCount() < 2)
			break;
		switch (dir)
		{
		case Direction::Front:
			AlienDrones.dequeue(removedUnit);
			break;
		case Direction::Back:
			AlienDrones.dequeuerear(removedUnit);
			break;
		default:
			break;
		}
	}
	default:
		break;
	}
	return removedUnit;
}

