#ifndef RAND_GEN
#define RAND_GEN

#include "Game.h"

enum  ArmyType {
	eartharmy=0,
	alienarmy,
	allyarmy
};

class randGen
{
private:
	int* params;
	Game* gameptr;
public:
	randGen(Game* _gameptr);
	void getparameters(int* parameters);
	Unit* createUnit(int EH, int P, int C,bool is_E,int timestep);
	void generateUnits(int timestep);
	void EA_help();
};

#endif
