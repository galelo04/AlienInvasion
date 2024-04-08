#include "Game.h"
#include "Armies/AlienArmy/AlienArmy.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	game.battle();
	while (true)
		game.timeStep();
	/*AlienArmy ARmy;
	LinkedQueue<Unit*> killedlist;
	AlienDrone* d1 = new AlienDrone(1,1,1,1);
	AlienDrone* d2 = new AlienDrone(1, 1, 1, 1);
	AlienDrone* d3 = new AlienDrone(1, 1, 1, 1);
	AlienDrone* d4 = new AlienDrone(1, 1, 1, 1);
	AlienSoldier* s1 = new AlienSoldier(1, 1, 1, 1);
	AlienMonster* m1 = new AlienMonster(1, 1, 1, 1);
	ARmy.addUnit(d1,UnitType::Drone , Direction::Front);
	ARmy.addUnit(d2, UnitType::Drone,Direction::Back);
	ARmy.addUnit(d3, UnitType::Drone, Direction::Front);
	ARmy.addUnit(d4, UnitType::Drone, Direction::Back);
	ARmy.addUnit(s1, UnitType::AlienSoldier, Direction::Front);
	ARmy.addUnit(m1, UnitType::Monster, Direction::Front);
	ARmy.print();
	killedlist.enqueue(ARmy.removeUnit(UnitType::Monster, Direction::Back));
	killedlist.enqueue(ARmy.removeUnit(UnitType::Drone, Direction::Front));
	ARmy.print();
	cout << "==================================================\nkilledlist\n";
	killedlist.printlist();*/
}