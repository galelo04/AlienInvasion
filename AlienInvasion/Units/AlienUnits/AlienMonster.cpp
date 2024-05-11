#include "AlienMonster.h"
#include "../../Game.h"



AlienMonster::AlienMonster(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Monster, last_Alien_Id++, jointime, health, power, attackcapacity)
{

}

void AlienMonster::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>EStemplist;
	ArrayStack<Unit*>ETtemplist;
	int attackcapacity = getAttackCapacity();
	Unit* attackedUnit = nullptr;
	int i = 0;
	while (i < attackcapacity && (gameptr->getEarthArmy()->getESCount() >0 || gameptr->getEarthArmy()->getETCount() > 0))
	{
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::Tank);
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
			else if(attackedUnit->getHealth()<.2*attackedUnit->getIntialHealth())
			{
				gameptr->getEarthArmy()->addToUML(attackedUnit,gameptr->getCrntTimeStep());
			}
			else
				ETtemplist.push(attackedUnit);
			i++;
		}
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::EarthSoldier);
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
			else if (attackedUnit->getHealth() < .2 * attackedUnit->getIntialHealth())
			{
				gameptr->getEarthArmy()->addToUML(attackedUnit,gameptr->getCrntTimeStep());
			}
			else
				EStemplist.enqueue(attackedUnit);
			i++;
		}
	}
	if (gameptr->getMode() == Mode::Normal) {
		if (EStemplist.getCount() > 0)
		{
			cout << "AM " << getID() << " shots Earth Soldiers ";
			EStemplist.printlist();
		}
		if (ETtemplist.getCount() > 0)
		{
			cout << "AM " << getID() << " shots Tanks ";
			ETtemplist.printlist();
		}
	}
	while (ETtemplist.pop(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	while (EStemplist.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
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