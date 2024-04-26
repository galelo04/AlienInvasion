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
	for (int i = 0; i < attackcapacity/2; i++)
	{
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::Tank);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				ETtemplist.push(attackedUnit);
		}
	}
	for (int i = 0; i < attackcapacity / 2; i++)
	{
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::EarthSoldier);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				EStemplist.enqueue(attackedUnit);
		}
	}
	if (EStemplist.getCount() > 0)
	{
		cout << "AM " << getID() << " shots Soldiers ";
		EStemplist.printlist();
	}
	if (ETtemplist.getCount() > 0)
	{
		cout << " and shots Tanks ";
		ETtemplist.printlist();
	}
	while (ETtemplist.pop(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
	while (EStemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
}
