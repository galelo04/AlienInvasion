#include "HealingUnit.h"
#include "../../Game.h"

HealingUnit::HealingUnit(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::HealingUnit, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

bool HealingUnit::Attack(Game* gameptr)
{
	bool didHeal = false;
	LinkedQueue<Unit*>templist_S;
	LinkedQueue<Unit*>templist_T;
	Unit* healedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		healedUnit = gameptr->getEarthArmy()->removefromUML(UnitType::EarthSoldier);
		if (healedUnit)
		{
			if (gameptr->getCrntTimeStep() - healedUnit->getUMLJoiningTime() > 10)
			{
				gameptr->addToKilledList(healedUnit);
			}
			else
			{
				didHeal = true;
				double improvement = ceil(this->getPower() * (this->getHealth() / 100.0)) / sqrt(healedUnit->getHealth());
				if (healedUnit->isInfected())
					healedUnit->heal(improvement/2.0);
				else
					healedUnit->heal(improvement);

				if (healedUnit->getHealth() > healedUnit->getIntialHealth() * .2)
				{
					if (healedUnit->isInfected())
					{
						healedUnit->infect(false);
						healedUnit->immune(true);
					}
					gameptr->getEarthArmy()->addUnit(healedUnit);
				}
				else
					templist_S.enqueue(healedUnit);
			}

		}
		else
		{
			healedUnit = gameptr->getEarthArmy()->removefromUML(UnitType::Tank);
			if (healedUnit)
			{
				if (gameptr->getCrntTimeStep() - healedUnit->getUMLJoiningTime() > 10)
					gameptr->addToKilledList(healedUnit);
				else
				{
					double improvement = ceil(this->getPower() * (this->getHealth() / 100.0)) / sqrt(healedUnit->getHealth());
					healedUnit->heal(improvement);

					if (healedUnit->getHealth() > healedUnit->getIntialHealth() * .2)
					{
						gameptr->getEarthArmy()->addUnit(healedUnit);
					}
					else
						templist_T.enqueue(healedUnit);
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
	while (templist_S.dequeue(healedUnit))
		gameptr->getEarthArmy()->addToUML(healedUnit, healedUnit->getUMLJoiningTime());
	while(templist_T.dequeue(healedUnit))
		gameptr->getEarthArmy()->addToUML(healedUnit, healedUnit->getUMLJoiningTime());
	

	return didHeal;
}

