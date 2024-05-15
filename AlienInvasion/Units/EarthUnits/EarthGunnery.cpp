#include "EarthGunnery.h"
#include "../../Game.h"

EarthGunnery::EarthGunnery(int jointime, int health, int power, int attackcapacity) :Unit(UnitType::Gunnery, last_Earth_Id++, jointime, health, power, attackcapacity)
{
	setPri(power + health);
}

bool EarthGunnery::Attack(Game* gameptr)
{
	bool didAttack = false;
	arrayADT<Unit*>AMtemplist;
	LinkedQueue<Unit*>ADtemplist;

	int attackcapacity = getAttackCapacity();
	Unit* attackedUnit = nullptr;
	//////////////////////////////////////////////////////////////////////////////
	int monsters, drones;
	if (gameptr->getAlienArmy()->getADCount() > gameptr->getAlienArmy()->getAMCount())
	{
		if ((attackcapacity / 2) > gameptr->getAlienArmy()->getAMCount())
		{
			monsters = gameptr->getAlienArmy()->getAMCount();
		}
		else
		{
			monsters = attackcapacity / 2;
		}
		drones = attackcapacity - monsters;
	}
	else
	{
		if ((attackcapacity / 2) > gameptr->getAlienArmy()->getADCount())
		{
			drones = gameptr->getAlienArmy()->getADCount();
		}
		else
		{
			drones = attackcapacity / 2;
		}
		monsters = attackcapacity - drones;

		if (monsters > gameptr->getAlienArmy()->getAMCount())
			monsters = gameptr->getAlienArmy()->getAMCount();
	}
	////////////////////////////////////////////////////////////////////
	for (int i = 0; i < monsters; i++)
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
			double damage = ceil((getPower() * getHealth() / 100.0) / sqrt(attackedUnit->getHealth()));
			attackedUnit->decrementHealth(damage);
			
				AMtemplist.add(attackedUnit);
		}
	}



	for (int i = 0; i < drones; i++)
	{

		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Drone);
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
			
				ADtemplist.enqueue(attackedUnit);
			i++;
		}

		attackedUnit = gameptr->getAlienArmy()->removeUnit(UnitType::Drone);
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
		
				ADtemplist.enqueue(attackedUnit);
		}
	}
	
	if (gameptr->getMode() == Mode::Normal) {
		if (AMtemplist.getcount() > 0)
		{
			cout << "EG " << getID() << " shoots Monsters ";
			AMtemplist.printlist();
		}
		if (ADtemplist.getCount() > 0)
		{
			cout << "EG " << getID() << " shoots Drones ";
			ADtemplist.printlist();
		}
	}
	while (AMtemplist.remove(attackedUnit))
	{
		if (attackedUnit->getHealth() <= 0)
			gameptr->addToKilledList(attackedUnit);
		else
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	}
	while (ADtemplist.dequeue(attackedUnit))
	{
		if (attackedUnit->getHealth() <= 0)
			gameptr->addToKilledList(attackedUnit);
		else
		gameptr->getAlienArmy()->addUnit(attackedUnit);
	}


	return didAttack;
}

int EarthGunnery::getPri()
{
	return Pri;
}

void EarthGunnery::setPri(int pri)
{
	Pri = pri;
}





