#include "EarthTank.h"
#include "../../Game.h"

EarthTank::EarthTank(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::Tank, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

bool EarthTank::Attack(Game* gameptr)
{	
	bool didAttack = false;
	arrayADT<Unit*>AMtemplist;
	LinkedQueue<Unit*>AStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	int i = 0;

	for (i; i < attackCapacity/2; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Monster);
		if (attackedUnit)
		{
			didAttack = true;
			if (!attackedUnit->IsAttacked())
			{
				attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
				attackedUnit->makeAttacked(true);
			}
			double damage = ceil((getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth()));
			attackedUnit->decrementHealth(damage);
			AMtemplist.add(attackedUnit);
		}
		else
			break;
	}


	if (gameptr->getEarthArmy()->getESCount() < 0.3 * gameptr->getAlienArmy()->getASCount())
	{
		
		for (i; i < attackCapacity; i++)
		{
			if (gameptr->getEarthArmy()->getESCount() >= 0.8 * gameptr->getAlienArmy()->getASCount())
				break;

			attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::AlienSoldier);
			if (attackedUnit)
			{
				didAttack = true;
				if (!attackedUnit->IsAttacked())
				{
					attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
					attackedUnit->makeAttacked(true);
				}
				double damage = ceil((getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth()));
				attackedUnit->decrementHealth(damage);
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
			didAttack = true;
			if (!attackedUnit->IsAttacked())
			{
				attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
				attackedUnit->makeAttacked(true);
			}
			double damage = ceil((getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth()));
			attackedUnit->decrementHealth(damage);
			AMtemplist.add(attackedUnit);
		}
		else
			break;
	}

	
	if (gameptr->getMode() == Mode::Normal) {
		if (AStemplist.getCount() > 0)
		{
			cout << "ET " << getID() << " shoots Alien Soldiers ";
			AStemplist.printlist();
		}
		if (AMtemplist.getcount() > 0)
		{
			cout << "ET " << getID() << " shoots Monsters ";
			AMtemplist.printlist();
		}
	}
	while (AStemplist.dequeue(attackedUnit)) 
	{
		if (attackedUnit->getHealth() <= 0)
			gameptr->addToKilledList(attackedUnit);
		else
			gameptr->getAlienArmy()->addUnit(attackedUnit);
	}
		
	while (AMtemplist.remove(attackedUnit))
	{
		if (attackedUnit->getHealth() <= 0)
			gameptr->addToKilledList(attackedUnit);
		else
			gameptr->getAlienArmy()->addUnit(attackedUnit);
	}

	return didAttack;
}

void EarthTank::heal(int imp)
{
	decrementHealth(-imp);
}


