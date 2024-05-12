#include "HealingUnit.h"
#include "../../Game.h"

HealingUnit::HealingUnit(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::HealingUnit, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void HealingUnit::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>templist_S;
	LinkedQueue<Unit*>templist_T;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		attackedUnit = gameptr->getEarthArmy()->removefromUML(UnitType::EarthSoldier);
		if (attackedUnit)
		{

			if (gameptr->getCrntTimeStep() - attackedUnit->getUMLJoiningTime() > 10)
			{
				gameptr->addToKilledList(attackedUnit);
				
			}
			else
			{
				int improvement = (this->getPower() * (this->getHealth() / 100)) / sqrt(attackedUnit->getHealth());
				attackedUnit->heal(improvement);

				if (attackedUnit->getHealth() > attackedUnit->getIntialHealth() * .2)
				{
					gameptr->getEarthArmy()->addUnit(attackedUnit);
				}
				else
					templist_S.enqueue(attackedUnit);

			}

		}
		else
		{
			attackedUnit = gameptr->getEarthArmy()->removefromUML(UnitType::Tank);
			if (attackedUnit)
			{

				if (gameptr->getCrntTimeStep() - attackedUnit->getUMLJoiningTime() > 10)
					gameptr->addToKilledList(attackedUnit);
				else
				{
					int improvement = (this->getPower() * (this->getHealth() / 100)) / sqrt(attackedUnit->getHealth());
					attackedUnit->heal(improvement);

					if (attackedUnit->getHealth() > attackedUnit->getIntialHealth() * .2)
					{
						gameptr->getEarthArmy()->addUnit(attackedUnit);
					}
					else
						templist_T.enqueue(attackedUnit);
				}
			}
		}

	}
	if (gameptr->getMode() == Mode::Normal) {
		if (templist_S.getCount() > 0)
		{
			cout << "HU " << getID() << " Heals Soldiers ";
			templist_S.printlist();
		}
		if (templist_T.getCount() > 0)
		{
			cout << "HU " << getID() << " Fixes Tanks ";
			templist_T.printlist();
		}
	}
	while (templist_S.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addToUML(attackedUnit, attackedUnit->getUMLJoiningTime());
	while(templist_T.dequeue(attackedUnit))
		gameptr->getEarthArmy()->addToUML(attackedUnit, attackedUnit->getUMLJoiningTime());
	
}

