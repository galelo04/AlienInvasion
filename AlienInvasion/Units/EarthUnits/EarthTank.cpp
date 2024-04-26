#include "EarthTank.h"
#include "../../Game.h"

EarthTank::EarthTank(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::Tank, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthTank::Attack(Game* gameptr)
{	
	LinkedQueue<Unit*>AMtemplist;
	LinkedQueue<Unit*>AStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	int i = 0;

	if (gameptr->getEarthArmy()->getESCount() < 0.3 * gameptr->getAlienArmy()->getASCount())
	{
		
		for (i; i < attackCapacity / 2; i++)
		{
			if (gameptr->getEarthArmy()->getESCount() >= 0.8 * gameptr->getAlienArmy()->getASCount())
				break;

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
			else
				break;
		}
	}

	for (i; i < attackCapacity; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Monster);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				AMtemplist.enqueue(attackedUnit);
		}
	}

	if (AStemplist.getCount() > 0)
	{
		cout << "ET " << getID() << " shots Soldiers ";
		AStemplist.printlist();
	}
	if (AMtemplist.getCount() > 0)
	{
		cout << "ET " << getID() << " shots Monsters ";
		AStemplist.printlist();
	}
	while (AStemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	while (AMtemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);

}


