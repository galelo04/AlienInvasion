#include "EarthSoldier.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::EarthSoldier, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthSoldier::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>AStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::AlienSoldier);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				AStemplist.enqueue(attackedUnit);
		}
	}
	if (AStemplist.getCount() > 0)
	{
		cout << "ES " << getID() << " shots ";
		AStemplist.printlist();
	}
	while (AStemplist.dequeue(attackedUnit))
	gameptr->getAlienArmy()->addUnit(attackedUnit);
}

