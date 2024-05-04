#include "HealingUnit.h"
#include "../../Game.h"

HealingUnit::HealingUnit(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::HealingUnit, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

void HealingUnit::Attack(Game* gameptr)
{
	LinkedQueue<Unit*>templist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	for (int i = 0; i < attackCapacity; i++)
	{
		attackedUnit = gameptr->getEarthArmy()->removeUnit(UnitType::UMLUnit);
		if (attackedUnit)
		{
			if (!attackedUnit->IsAttacked())
			{
				attackedUnit->makeAttacked(true);
			}
			if(gameptr->getCrntTimeStep()-attackedUnit->getUMLJoiningTime()>10)
				gameptr->addToKilledList(attackedUnit);
			else
			{
				int improvement = (this->getPower() * (this->getHealth() / 100)) / sqrt(attackedUnit->getHealth());
				attackedUnit->Heal(improvement);

				if (attackedUnit->getHealth() > attackedUnit->getIntialHealth() * .2)
				{
					gameptr->getEarthArmy()->addUnit(attackedUnit);
				}
				else
					templist.enqueue(attackedUnit);
			}
			
		}
	}
	if (gameptr->getMode() == Mode::Normal) {
		if (templist.getCount() > 0)
		{
			cout << "HU " << getID() << " Heals ";
			templist.printlist();
		}
	}
	while (templist.dequeue(attackedUnit))
	{
		if(int(attackedUnit->getType())== 0)
		gameptr->getEarthArmy()->addToUML(attackedUnit,gameptr->E_ArmyMaxHealth()-attackedUnit->getHealth(),attackedUnit->getUMLJoiningTime());
		else
			gameptr->getEarthArmy()->addToUML(attackedUnit, 0, attackedUnit->getUMLJoiningTime());
	}
	Unit* ptr = this;

	gameptr->addToKilledList(ptr);
}
