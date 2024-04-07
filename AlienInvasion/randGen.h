#ifndef RAND_GEN
#define RAND_GEN

#include "Units/Unit.h"
#include "Game.h"

class randGen
{
private:
	int* params;
public:
	randGen(Game* gameptr);
	Unit* genUnit(Game* gameptr,int EH, int P, int C,bool is_E);
	void createUnit(Game* gameptr);
};

#endif
