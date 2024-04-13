#ifndef GAME
#define GAME
#include "Armies/AlienArmy/AlienArmy.h"
class randGen;
class Game
{
private:
	int Params[20];
	int TimeStep;
	AlienArmy aliens;
	randGen * generator;
	LinkedQueue <Unit* > killedlist;
public:
	Game();
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
