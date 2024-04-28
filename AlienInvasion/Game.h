#ifndef GAME
#define GAME
#include "Armies/AlienArmy/AlienArmy.h"
#include "Armies/EarthArmy/EarthArmy.h"

class randGen;
class Game
{
private:
	int Params[21];
	int TimeStep;
	AlienArmy * alienArmy;
	EarthArmy * earthArmy;
	randGen * generator;
	LinkedQueue <Unit* > killedlist;
public:
	Game();
	AlienArmy*& getAlienArmy() ;
	EarthArmy*& getEarthArmy() ;
	void instantiateGame();
	void loadParams(string filename);
	int battle();
	void printStatus();
	void printKilledlist();
	void addToKilledList(Unit* unit);
	void loadOutputs(string filename);
	int getCrntTimeStep();
	void EndGame();
	~Game();
};

#endif 
