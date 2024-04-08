#ifndef RAND_GEN
#define RAND_GEN

#include "Game.h"

class randGen
{
private:
	int* params;
public:
	randGen();
	void getparameters(int* parameters);
	Unit* createUnit(int EH, int P, int C,bool is_E,AlienArmy * aliens,int timestep);
	void generateUnits( AlienArmy* aliens,int timestep);
};

#endif
