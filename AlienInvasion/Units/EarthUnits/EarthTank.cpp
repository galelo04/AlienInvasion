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
	int attacedUnits = 0;

	if (gameptr->getEarthArmy()->getESCount() < 0.3 * gameptr->getAlienArmy()->getASCount())
	{

		for (attacedUnits; attacedUnits < attackCapacity / 2; attacedUnits++)
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
			if ((gameptr->getEarthArmy()->getESCount() >= 0.8 * gameptr->getAlienArmy()->getASCount()) || !attackedUnit)
				break;
		}
	}

	for (attacedUnits; attacedUnits < attackCapacity; attacedUnits++)
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

}


