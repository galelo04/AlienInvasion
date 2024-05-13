#include "AlienSoldier.h"
#include "../../Game.h"

AlienSoldier::AlienSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::AlienSoldier, last_Alien_Id++,jointime,health,power,attackcapacity)
{
}

bool AlienSoldier::Attack(Game* gameptr)
{
	bool didAttack = false;
	LinkedQueue<Unit*>EStemplist;
	LinkedQueue<Unit*>SUtemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
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

			if (attackedUnit->getHealth() <= 0)
			{
				gameptr->addToKilledList(attackedUnit);
				if (attackedUnit->isInfected())
					gameptr->getEarthArmy()->decrementInfES();
			}
			else if (attackedUnit->getHealth() < attackedUnit->getIntialHealth() * .2)
			{
				gameptr->getEarthArmy()->addToUML(attackedUnit, gameptr->getCrntTimeStep());
				if (attackedUnit->isInfected())
					gameptr->getEarthArmy()->decrementInfES();
			}
			else
				EStemplist.enqueue(attackedUnit);
			i++;
		}
		attackedUnit = gameptr->getAllyArmy()->removeUnit(UnitType::SaverUnit);
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

			if (attackedUnit->getHealth() <= 0)
			{
				delete attackedUnit;
			}

			else
				SUtemplist.enqueue(attackedUnit);
		}
	}
	if (gameptr->getMode() == Mode::Normal) {
		if (EStemplist.getCount() > 0)
		{
			cout << "AS " << getID() << " shoots Earth Soldiers ";
			EStemplist.printlist();
		}
		if (SUtemplist.getCount() > 0)
		{
			cout << "AS " << getID() << " shoots Saver Units ";
			SUtemplist.printlist();
		}
	}
	while (EStemplist.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	while (SUtemplist.dequeue(attackedUnit))
		gameptr->getAllyArmy()->addUnit(attackedUnit);

	return didAttack;
}
