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
	int i = 0;
	while (i < attackCapacity && (gameptr->getEarthArmy()->getESCount() > 0 || gameptr->getAllyArmy()->getSUCount() > 0))
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

		
				SUtemplist.enqueue(attackedUnit);
			i++;
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
		}
		else
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	}
	while (SUtemplist.dequeue(attackedUnit))
	{
		if (attackedUnit->getHealth() <= 0)
		{
			gameptr->addToKilledList(attackedUnit);
		}
		else
		gameptr->getAllyArmy()->addUnit(attackedUnit);
	}

	return didAttack;
}
