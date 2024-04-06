#include "AlienMonster.h"



AlienMonster::AlienMonster(int id,int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Monster, id, jointime, health, power, attackcapacity)
{

}

void AlienMonster::Attack()
{
}
