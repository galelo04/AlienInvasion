#include "EarthSoldier.h"
#include "../../Game.h"

EarthSoldier::EarthSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::EarthSoldier, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void EarthSoldier::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>AStemplist;
	LinkedQueue<Unit*>EStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		if (this->isInfected())
		{
			attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::EarthSoldier);
			if (attackedUnit && attackedUnit->getID() != this->getID())
			{
				if (!attackedUnit->IsAttacked())
				{
					attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
					attackedUnit->makeAttacked(true);
				}
				int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
				attackedUnit->decrementHealth(damage);

				if ((attackedUnit->getHealth() > 0) && (attackedUnit->getHealth() < attackedUnit->getIntialHealth() * .2))
					gameptr->getEarthArmy()->addToUML(attackedUnit, gameptr->getCrntTimeStep());

				else if (attackedUnit->getHealth() <= 0)
					gameptr->addToKilledList(attackedUnit);
				else
					EStemplist.enqueue(attackedUnit);
			}
		}
		else
		{
			attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::AlienSoldier);
			if (attackedUnit)
			{
				if (!attackedUnit->IsAttacked())
				{
					attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
					attackedUnit->makeAttacked(true);
				}
				int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
				attackedUnit->decrementHealth(damage);
				if (attackedUnit->getHealth() <= 0)
					gameptr->addToKilledList(attackedUnit);
				else
					AStemplist.enqueue(attackedUnit);
			}
		}
	}
	if (gameptr->getMode() == Mode::Normal) 
	{
		if (AStemplist.getCount() > 0)
		{
			cout << "ES " << getID() << " shots ";
			AStemplist.printlist();
		}
		else if (EStemplist.getCount() > 0)
		{
			cout << "ES " << getID() << " shots ";
			EStemplist.printlist();
		}
	}
	while (AStemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	while (EStemplist.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
}

void EarthSoldier::heal(int imp)
{
	decrementHealth(-imp);
}

