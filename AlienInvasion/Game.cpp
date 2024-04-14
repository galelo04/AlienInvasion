#include "Game.h"
#include "randGen.h"
#include "fstream"
using namespace std;

Game::Game() 
{
	earthArmy = new EarthArmy;
	alienArmy = new AlienArmy;
	generator = new randGen(this);
	TimeStep = 0;
}

AlienArmy* Game::getAlienArmy() 
{
	return  alienArmy;
}

EarthArmy* Game::getEarthArmy()
{
	return earthArmy;
}

void Game::instantiateGame()
{
	cout << "please enter the file name " << endl;
	string filename;
	cin >> filename;
	loadParams(filename);
}

void Game::loadParams(string filename)
{
	
	ifstream inFile;
	inFile.open("InputFiles\\"+filename+".txt");

	if (inFile.is_open())
	{
		inFile >> Params[0];                            // [0]=>N
		inFile >> Params[1] >> Params[2] >> Params[3];  // [1]=>ES%, [2]=>ET%, [3]=>EG%
		inFile >> Params[4] >> Params[5] >> Params[6];  // [4]=>AS%, [5]=>AM%, [6]=>AD%
		inFile >> Params[7];                            // [7]=>Prob
		inFile >> Params[8] >> Params[9] >> Params[10] >> Params[11] >> Params[12] >> Params[13];    //[8,9]=>ES_R, [10,11]=>ET_R, [12,13]=>EG_R
		inFile >> Params[14] >> Params[15] >> Params[16] >> Params[17] >> Params[18] >> Params[19];  //[14,15]=>AS_R, [16,17]=>AM_R, [18,19]=>AD_R

		Params[9] = Params[9] * -1;
		Params[11] = Params[11] * -1;
		Params[13] = Params[13] * -1;

		Params[15] = Params[15] * -1;
		Params[17] = Params[17] * -1;
		Params[19] = Params[19] * -1;
	}
	else
		cout << "make sure of the name of the file and dont put .txt\n";
	generator->getparameters(Params);
}

int* Game::getParams() 
{
	return Params;
}

void Game::battle()
{
	generator->generateUnits(TimeStep);
}

void Game::printStatus()
{
	cout << "\nCurrent TimeStep " << TimeStep << endl;
	earthArmy->print();
	alienArmy->print();
	cout << "==============  Killed/Destructed Units =============\n";
	cout << killedlist.getCount() << " Units ";
	killedlist.printlist();
}

void Game::addToKilledList(Unit* unit)
{
	killedlist.enqueue(unit);
}


int Game::getTimeStep() 
{
	return TimeStep;
}

void Game::timeStep()
{
	printStatus();
	cout << "Press Enter to move to next timestep ...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	generator->generateUnits(TimeStep);
	TimeStep++;
}

