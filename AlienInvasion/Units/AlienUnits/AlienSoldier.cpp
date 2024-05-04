#include "AlienSoldier.h"
#include "../../Game.h"

AlienSoldier::AlienSoldier(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::AlienSoldier, last_Alien_Id++,jointime,health,power,attackcapacity)
{
}

void AlienSoldier::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>EStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
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

			if ((attackedUnit->getHealth() > 0) && (attackedUnit->getHealth() < attackedUnit->getIntialHealth() * .2))
				gameptr->getEarthArmy()->addToUML(attackedUnit, gameptr->E_ArmyMaxHealth() - attackedUnit->getHealth(),gameptr->getCrntTimeStep());

			else if (attackedUnit->getHealth() <= 0)
				gameptr->addToKilledList(attackedUnit);
			else
				EStemplist.enqueue(attackedUnit);
		}
	}
	if (gameptr->getMode() == Mode::Normal) {
		if (EStemplist.getCount() > 0)
		{
			cout << "AS " << getID() << " shots ";
			EStemplist.printlist();
		}
	}
	while (EStemplist.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addUnit(attackedUnit);
}
