#include "AlienDrone.h"
#include "../../Game.h"


AlienDrone::AlienDrone(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Drone, last_Alien_Id++, jointime, health, power, attackcapacity)
{

}

bool AlienDrone::Attack(Game* gameptr)
{
	bool didAttack = false;
	ArrayStack<Unit*>ETtemplist;
	priQueue<Unit*>EGtemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	int i = 0;
	int pri = 0;
	while (i < attackCapacity && (gameptr->getEarthArmy()->getEGCount() > 0 || gameptr->getEarthArmy()->getETCount() > 0))
	{
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::Tank);
		if (attackedUnit)
		{
			didAttack = true;
			if (!attackedUnit->IsAttacked())
			{
				attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
				attackedUnit->makeAttacked(true);
			}
			double damage = (getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else if (attackedUnit->getHealth() < .2 * attackedUnit->getIntialHealth())
			{
				gameptr->getEarthArmy()->addToUML(attackedUnit,gameptr->getCrntTimeStep());
			}
			else
				ETtemplist.push(attackedUnit);
			i++;
		}
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::Gunnery);
		if (attackedUnit)
		{
			didAttack = true;
			if (!attackedUnit->IsAttacked())
			{
				attackedUnit->setFirstAttackTime(gameptr->getCrntTimeStep());
				attackedUnit->makeAttacked(true);
			}
			double damage = (getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				EGtemplist.enqueue(attackedUnit, pri);
			i++;
		}
	}
	
	if (gameptr->getMode()==Mode::Normal) {
		if (EGtemplist.getCount() > 0)
		{
			cout << "AD " << getID() << " shots Gunneries ";
			EGtemplist.printlist();
		}
		if (ETtemplist.getCount() > 0)
		{
			cout << "AD " << getID() << " shots Tanks ";
			ETtemplist.printlist();
		}
	}
	while (EGtemplist.dequeue(attackedUnit, pri))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	while (ETtemplist.pop(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);


	return didAttack;

}

//
//for (i; i < attackCapacity / 2; i++)
//{
//	attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Gunnery);
//	if (attackedUnit)
//	{
//		int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
//		attackedUnit->decrementHealth(damage);
//		if (attackedUnit->getHealth() <= 0)
//			gameptr->addToKilledList(attackedUnit);
// else if (attackedUnit->getHealth() < .2 * attackedUnit->getIntialHealth())
//{
//	gameptr->getEarthArmy()->addToUML(attackedUnit);
//}
//		else
//		{
//			pri = attackedUnit->getHealth() + attackedUnit->getPower();
//			EGtemplist.enqueue(attackedUnit, pri);
//		}
//	}
//	else
//		break;
//}
//
//
//for (i; i < attackCapacity; i++)
//{
//	attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Tank);
//	if (attackedUnit)
//	{
//		int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
//		attackedUnit->decrementHealth(damage);
//		if (attackedUnit->getHealth() <= 0)
//			gameptr->addToKilledList(attackedUnit);
//		else
//			ETtemplist.pop(attackedUnit);
//	}
//}