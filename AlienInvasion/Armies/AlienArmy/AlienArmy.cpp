#include "AlienArmy.h"



AlienArmy::AlienArmy()
{

}

void AlienArmy::addUnit(Unit* unit , UnitType type)
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
		AlienDrones.enqueue(unit);
		break;
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

Unit* AlienArmy::removeUnit(UnitType type)
{
	Unit* removedUnit;
	switch (type)
	{
	case (UnitType::AlienSoldier):
	{
		if(AlienSoldiers.dequeue(removedUnit));
			return removedUnit;
			return nullptr;
	}
	case (UnitType::Monster):
	{
		int randomindex = rand() % MonstersCount;
		removedUnit = AlienMonsters[randomindex];
		AlienMonsters[randomindex] = AlienMonsters[MonstersCount - 1];
		MonstersCount--;
		return removedUnit;
	}
	case (UnitType::Drone):
	{
		if(AlienDrones.dequeue(removedUnit));
		return removedUnit;
		return nullptr;
	}
	default:
		return nullptr;
	}
}
