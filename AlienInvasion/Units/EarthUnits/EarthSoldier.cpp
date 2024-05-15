#include "EarthSoldier.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::EarthSoldier, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

bool EarthSoldier::Attack(Game* gameptr)
{
	bool didAttack = false;
	LinkedQueue<Unit*>AStemplist;
	LinkedQueue<Unit*>EStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		if (this->isInfected())
		{
			attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::EarthSoldier);

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

					EStemplist.enqueue(attackedUnit);
			}
		}
		else
		{
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
		}
	}
	if (gameptr->getMode() == Mode::Normal)
	{
		if (AStemplist.getCount() > 0)
		{
			cout << "ES " << getID() << " shoots Alien Soldiers ";
			AStemplist.printlist();
		}
		else if (EStemplist.getCount() > 0)
		{
			cout << "ES " << getID() << " shoots Earth Soldiers ";
			EStemplist.printlist();
		}
	}
	while (AStemplist.dequeue(attackedUnit))
	{
		if (attackedUnit->getHealth() <= 0)
			gameptr->addToKilledList(attackedUnit);
		else
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	}
	while (EStemplist.dequeue(attackedUnit))
	{
		if (attackedUnit->getHealth() <= 0)
		{
			gameptr->addToKilledList(attackedUnit);
			if (attackedUnit->isInfected())
				gameptr->getEarthArmy()->decrementInfES();
		}
		else if (attackedUnit->getHealth() < attackedUnit->getIntialHealth() * .2)
		{
			gameptr->getEarthArmy()->addToUML(attackedUnit, gameptr->getCrntTimeStep());
			if (attackedUnit->isInfected());
		}
		else
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	}


	return didAttack;
}

void EarthSoldier::heal(int imp)
{
	decrementHealth(-imp);
}

