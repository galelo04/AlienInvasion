#include "AlienDrone.h"



AlienDrone::AlienDrone(int jointime, int health, int power, int attackcapacity)
	:Unit(UnitType::Drone, last_Alien_Id++, jointime, health, power, attackcapacity)
{

}

void AlienDrone::Attack(Game* gameptr)
{
}
