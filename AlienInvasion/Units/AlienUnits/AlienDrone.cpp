#include "AlienDrone.h"



AlienDrone::AlienDrone(int id,int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Drone, id, jointime, health, power, attackcapacity)
{

}

void AlienDrone::Attack()
{
}
