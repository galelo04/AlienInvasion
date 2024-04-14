#ifndef GAME
#define GAME
#include "Armies/AlienArmy/AlienArmy.h"
#include "Armies/EarthArmy/EarthArmy.h"

class randGen;
class Game
{
private:
	int Params[20];
	int TimeStep;
	EarthArmy EArmyTempList;
	AlienArmy aliensTempList;
	AlienArmy * alienArmy;
	EarthArmy * earthArmy;
	randGen * generator;
	LinkedQueue <Unit* > killedlist;
public:
	Game();
	AlienArmy* getAlienArmy() ;
	EarthArmy* getEarthArmy() ;
	void instantiateGame();
	void loadParams(string filename);
	int* getParams();
	int getTimeStep();
	void timeStep();
	void battle();
	void printStatus();
	void addToKilledList(Unit* unit);
};

#endif 
