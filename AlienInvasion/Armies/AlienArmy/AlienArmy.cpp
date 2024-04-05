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

removedUnits AlienArmy::removeUnit(UnitType type)
{
	removedUnits removed;
	switch (type)
	{
	case (UnitType::AlienSoldier):
	{
		AlienSoldiers.dequeue(removed.unit1);
		break;
	}
	case (UnitType::Monster):
	{
		int randomindex = rand() % MonstersCount;
		removed.unit1 = AlienMonsters[randomindex];
		AlienMonsters[randomindex] = AlienMonsters[MonstersCount - 1];
		MonstersCount--;
		break;
	}
	case (UnitType::Drone):
	{
		if(AlienDrones.dequeue(removed.unit1) && AlienDrones.dequeuerear(removed.unit2))
			break;
		else
			removed.unit1 = nullptr;
		break;
	}
	default:
		break;
	}
	return removed;
}

