#ifndef RAND_GEN
#define RAND_GEN

#include "Game.h"

enum  ArmyType {
	eartharmy = 0,
	alienarmy,
	allyarmy
};

class randGen
{
private:

	int params[29];
	bool earth_limit;
	bool alien_limit;
	bool allyLimit;
	bool generateSU;
	Game* gameptr;

public:
	randGen(Game* _gameptr);
	void getparameters(int parameters[], int size);
	Unit* createUnit(int EH, int P, int C, ArmyType type, int timestep);
	void generateUnits(int timestep);
	void EA_help();
};

#endif