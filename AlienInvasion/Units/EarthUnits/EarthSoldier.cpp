#include "EarthSoldier.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::EarthSoldier, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthSoldier::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>templist;
	Unit* attackedUnit;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		attackedUnit=gameptr->getAlienArmy()->removeUnit(UnitType::AlienSoldier);
		int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
		attackedUnit->decrementHealth(damage);
		if (attackedUnit->getHealth() <= 0)
			gameptr->addToKilledList(attackedUnit);
		else if(attackedUnit)
			templist.enqueue(attackedUnit);
	}
	while (templist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
}

