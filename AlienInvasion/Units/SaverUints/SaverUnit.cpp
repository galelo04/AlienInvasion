#include "SaverUnit.h"
#include "../../Game.h"

SaverUnit::SaverUnit(int jointime, int health, int power, int attackcapacity) :
	Unit(UnitType::SaverUnit, last_Ally_Id++, jointime, health, power, attackcapacity)
{
}

bool SaverUnit::Attack(Game* gameptr)
{
	bool didAttack = false;
	LinkedQueue<Unit*>AStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{

		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::AlienSoldier);
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
			else
				AStemplist.enqueue(attackedUnit);
		}

	}
	if (gameptr->getMode() == Mode::Normal)
	{
		if (AStemplist.getCount() > 0)
		{
			cout << "SU " << getID() << " shoots Alien Soldiers";
			AStemplist.printlist();
		}

	}
	while (AStemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);

	return didAttack;
}


