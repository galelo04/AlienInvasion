#include "SaverUnit.h"
#include "../../Game.h"

SaverUnit::SaverUnit(int jointime, int health, int power, int attackcapacity) :
	Unit(UnitType::SaverUnit, last_Ally_Id++, jointime, health, power, attackcapacity)
{
}

void SaverUnit::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>AStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
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
	if (gameptr->getMode() == Mode::Normal)
	{
		if (AStemplist.getCount() > 0)
		{
			cout << "SU " << getID() << " shots ";
			AStemplist.printlist();
		}

	}
	while (AStemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
}


