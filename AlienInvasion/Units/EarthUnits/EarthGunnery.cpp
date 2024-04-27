#include "EarthGunnery.h"
#include "../../Game.h"

EarthGunnery::EarthGunnery(int jointime, int health, int power, int attackcapacity) :Unit(UnitType::Gunnery, last_Earth_Id++, jointime, health, power, attackcapacity)
{
	setPri(power + health);
}

void EarthGunnery::Attack(Game* gameptr)
{
	arrayADT<Unit*>AMtemplist;
	LinkedQueue<Unit*>ADtemplist;

	int attackcapacity = getAttackCapacity();

	Unit* attackedUnit = nullptr;

	for (int i = 0; i < attackcapacity ; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Monster);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				AMtemplist.add(attackedUnit);
			i++;
		}
	
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Drone);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				ADtemplist.enqueue(attackedUnit);
			i++;
		}

		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Drone);
		if (attackedUnit)
		{
			int damage = (getPower() * getHealth() / 100) / sqrt(attackedUnit->getHealth());
			attackedUnit->decrementHealth(damage);
			if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				ADtemplist.enqueue(attackedUnit);
		}
	}

	if (AMtemplist.getcount() > 0)
	{
		cout << "ES " << getID() << " shots Alien Monsters ";
		AMtemplist.printlist();
	}
	if (ADtemplist.getCount() > 0)
	{
		cout << "ES " << getID() << " shots Drones ";
		ADtemplist.printlist();
	}
	while (AMtemplist.remove(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	while (ADtemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
}

int EarthGunnery::getPri()
{
	return Pri;
}

void EarthGunnery::setPri(int pri)
{
	Pri = pri;
}
