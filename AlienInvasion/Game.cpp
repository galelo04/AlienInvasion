#include "Game.h"
#include "randGen.h"
#include "fstream"
using namespace std;

Game::Game()
{
	TimeStep = 0;
}

void Game::loadParams()
{
	
	ifstream inFile;
	inFile.open("InputFiles\\file.txt");

	if (inFile.is_open())
	{
		inFile >> Params[0];
		inFile >> Params[1] >> Params[2] >> Params[3];
		inFile >> Params[4] >> Params[5] >> Params[6];
		inFile >> Params[7];
		inFile >> Params[8] >> Params[9] >> Params[10] >> Params[11] >> Params[12] >> Params[13];
		inFile >> Params[14] >> Params[15] >> Params[16] >> Params[17] >> Params[18] >> Params[19];

		Params[9] = Params[9] * -1;
		Params[11] = Params[11] * -1;
		Params[13] = Params[13] * -1;

		Params[15] = Params[15] * -1;
		Params[17] = Params[17] * -1;
		Params[19] = Params[19] * -1;
	}
}

int* Game::getParams() 
{
	return Params;
}

void Game::SetTimeStep()
{
	TimeStep++;
}


int Game::getTimeStep() 
{
	return TimeStep;
}
