#include "AlienDrone.h"
#include "../../Game.h"


AlienDrone::AlienDrone(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Drone, last_Alien_Id++, jointime, health, power, attackcapacity)
{

}

void AlienDrone::Attack(Game* gameptr)
{
	if (gameptr->getAlienArmy()->getADCount() < 2)
		return;
	ArrayStack<Unit*>ETtemplist;
	priQueue<Unit*>EGtemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	int i = 0;
	int pri;

	for (i; i < attackCapacity / 2; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Gunnery);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				EGtemplist.enqueue(attackedUnit, pri);
		}
		else
			break;
	}


	for (i; i < attackCapacity; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Tank);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				ETtemplist.pop(attackedUnit);
		}
	}

	if (EGtemplist.getCount() > 0)
	{
		cout << "ED " << getID() << " shots Gunneries ";
		EGtemplist.printlist();
	}
	if (ETtemplist.getCount() > 0)
	{
		cout << "ED " << getID() << " shots Tanks ";
		ETtemplist.printlist();
	}
	while (EGtemplist.dequeue(attackedUnit, pri))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	while (ETtemplist.pop(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);

}
