#ifndef RAND_GEN
#define RAND_GEN

#include "Game.h"

class randGen
{
private:
	int params[21];
	Game* gameptr;
	bool earth_limit;
	bool alien_limit;

public:
	randGen(Game* _gameptr);
	void getparameters(int parameters[], int size);
	Unit* createUnit(int EH, int P, int C,bool is_E,int timestep);
	void generateUnits(int timestep);
};

#endif
