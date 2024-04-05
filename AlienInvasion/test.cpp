
#include "Armies/AlienArmy/AlienArmy.h"
//

int main()
{
	AlienArmy ARmy;
	LinkedQueue<Unit*> killedlist;
	AlienDrone* d1 = new AlienDrone(1,1,1,1);
	AlienDrone* d2 = new AlienDrone(1, 1, 1, 1);
	AlienDrone* d3 = new AlienDrone(1, 1, 1, 1);
	AlienDrone* d4 = new AlienDrone(1, 1, 1, 1);
	AlienSoldier* s1 = new AlienSoldier(1, 1, 1, 1);
	AlienMonster* m1 = new AlienMonster(1, 1, 1, 1);
	ARmy.addUnit(d1,UnitType::Drone);
	ARmy.addUnit(d2, UnitType::Drone);
	ARmy.addUnit(d3, UnitType::Drone);
	ARmy.addUnit(d4, UnitType::Drone);
	ARmy.addUnit(s1, UnitType::AlienSoldier);
	ARmy.addUnit(m1, UnitType::Monster);
	ARmy.print();
	removedUnits removed;
	removed = ARmy.removeUnit(UnitType::Drone);
	if(removed.unit1)
		killedlist.enqueue(removed.unit1);
	if (removed.unit2)
		killedlist.enqueue(removed.unit2);
	removed = ARmy.removeUnit(UnitType::Monster);
	if (removed.unit1)
		killedlist.enqueue(removed.unit1);
	if (removed.unit2)
		killedlist.enqueue(removed.unit2);
		ARmy.print();
		cout << "==================================================\nkilledlist\n";
		killedlist.printlist();
}