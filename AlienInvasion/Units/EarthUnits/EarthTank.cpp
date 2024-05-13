#include "EarthTank.h"
#include "../../Game.h"

EarthTank::EarthTank(int jointime, int health, int power, int attackcapacity) 
	:Unit(UnitType::Tank, last_Earth_Id++, jointime, health, power, attackcapacity)
{
}

bool EarthTank::Attack(Game* gameptr)
{	
	bool didAttack = false;
	arrayADT<Unit*>AMtemplist;
	LinkedQueue<Unit*>AStemplist;
	Unit* attackedUnit = nullptr;
	int attackCapacity = getAttackCapacity();
	int i = 0;

	if (gameptr->getEarthArmy()->getESCount() < 0.3 * gameptr->getAlienArmy()->getASCount())
	{
		
		for (i; i < attackCapacity / 2; i++)
		{
			if (gameptr->getEarthArmy()->getESCount() >= 0.8 * gameptr->getAlienArmy()->getASCount())
				break;

			attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::AlienSoldier);
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
					AStemplist.enqueue(attackedUnit);
			}
			else
				break;
		}
	}

	for (i; i < attackCapacity; i++)
	{
		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Monster);
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
				AMtemplist.add(attackedUnit);
		}
	}
	if (gameptr->getMode() == Mode::Normal) {
		if (AStemplist.getCount() > 0)
		{
			cout << "ET " << getID() << " shoots Alien Soldiers ";
			AStemplist.printlist();
		}
		if (AMtemplist.getcount() > 0)
		{
			cout << "ET " << getID() << " shoots Monsters ";
			AMtemplist.printlist();
		}
	}
	while (AStemplist.dequeue(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	while (AMtemplist.remove(attackedUnit))
		gameptr->getAlienArmy()->addUnit(attackedUnit);

	return didAttack;
}

void EarthTank::heal(int imp)
{
	decrementHealth(-imp);
}


