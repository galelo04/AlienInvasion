#include "AlienMonster.h"
#include "../../Game.h"



AlienMonster::AlienMonster(int jointime, int health, int power, int attackcapacity, int infprob)
	:Unit(UnitType::Monster, last_Alien_Id++, jointime, health, power, attackcapacity), infection_probability(infprob)
{
	srand((unsigned)time(NULL));
}

bool AlienMonster::Attack(Game* gameptr)
{
	bool didAttack = false;
	LinkedQueue<Unit*>EStemplist;
	ArrayStack<Unit*>ETtemplist;
	LinkedQueue<Unit*>SUtemplist;
	Unit* attackedUnit = nullptr;

	int attackcapacity = getAttackCapacity();

	int i = 0;
	while (i < attackcapacity && (gameptr->getEarthArmy()->getESCount() > 0 || gameptr->getEarthArmy()->getETCount() > 0
		|| gameptr->getAllyArmy()->getSUCount() >0 ))
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
			int prob = 1 + (rand() % 100);
			if (prob <= infection_probability && !attackedUnit->isImmuned() && !attackedUnit->isInfected())
			{
				attackedUnit->infect(true);
				gameptr->getEarthArmy()->incrementInfES();
			}
			else
			{
				double damage = ceil((getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth()));
				attackedUnit->decrementHealth(damage);
			}
			if (attackedUnit->getHealth() <= 0)
			{
				gameptr->addToKilledList(attackedUnit);
				if (attackedUnit->isInfected())
					gameptr->getEarthArmy()->decrementInfES();
			}
			else if (attackedUnit->getHealth() < .2 * attackedUnit->getIntialHealth())
			{
				gameptr->getEarthArmy()->addToUML(attackedUnit, gameptr->getCrntTimeStep());
				if (attackedUnit->isInfected())
					gameptr->getEarthArmy()->decrementInfES();
			}
			else
				EStemplist.enqueue(attackedUnit);
			i++;
		}
	

		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::Tank);
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
				gameptr->addToKilledList(attackedUnit);
			else if (attackedUnit->getHealth() < .2 * attackedUnit->getIntialHealth())
			{
				gameptr->getEarthArmy()->addToUML(attackedUnit, gameptr->getCrntTimeStep());
			}
			else
				ETtemplist.push(attackedUnit);
			i++;
		}


		attackedUnit = gameptr->getAllyArmy()->removeUnit(UnitType::SaverUnit);
		if (attackedUnit)
		{
			didAttack = true;
			double damage = ceil((getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth()));
			attackedUnit->decrementHealth(damage);

			if (attackedUnit->getHealth() <= 0)
			{
				delete attackedUnit;
			}

			else
				SUtemplist.enqueue(attackedUnit);
			i++;
		}

	}
	if (gameptr->getMode() == Mode::Normal) {
		if (EStemplist.getCount() > 0)
		{
			cout << "AM " << getID() << " shoots Earth Soldiers ";
			EStemplist.printlist();
		}
		if (ETtemplist.getCount() > 0)
		{
			cout << "AM " << getID() << " shoots Tanks ";
			ETtemplist.printlist();
		}
		if (SUtemplist.getCount() > 0)
		{
			cout << "AM " << getID() << " shoots Saver Units ";
			SUtemplist.printlist();
		}

	}
	while (ETtemplist.pop(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	while (EStemplist.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	while (SUtemplist.dequeue(attackedUnit))
		gameptr->getAllyArmy()->addUnit(attackedUnit);


	return didAttack;
}











//int attackedSoldiers = min(getAttackCapacity() / 2, gameptr->getEarthArmy()->getESCount());
//int attackedTanks = getAttackCapacity() - attackedSoldiers;
//attackedSoldiers = getAttackCapacity() - attackedTanks;
//for (int i = 0; i < attackedTanks; i++)
//{
//	attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::Tank);
//	if (attackedUnit)
//	{
//		int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
//		attackedUnit->decrementHealth(damage);
//		if (attackedUnit->getHealth() <= 0)
//			gameptr->addToKilledList(attackedUnit);
//		else
//			ETtemplist.push(attackedUnit);
//	}
//}
//for (int i = 0; i < attackedSoldiers; i++)
//{
//	attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::EarthSoldier);
//	if (attackedUnit)
//	{
//		int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
//		attackedUnit->decrementHealth(damage);
//		if (attackedUnit->getHealth() <= 0)
//			gameptr->addToKilledList(attackedUnit);
//		else
//			EStemplist.enqueue(attackedUnit);
//	}
//}