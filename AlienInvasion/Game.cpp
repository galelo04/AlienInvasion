#include "Game.h"
#include "randGen.h"
#include "fstream"
#include <Windows.h>
using namespace std;



Game::Game() 
{

	srand((unsigned)time(NULL));
	earthArmy = new EarthArmy;
	alienArmy = new AlienArmy;
	generator = new randGen(this);
	TimeStep = 1;
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
	
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 8);

	cout << "please enter the file name " << endl;
	string filename;
	SetConsoleTextAttribute(console_color, 7);
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
		inFile.close();

		generator->getparameters(Params);
	}
	else
	{
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 12);
		system("cls");
		cout << "make sure of the name of the file and dont put .txt\n";
		instantiateGame();
	}
	
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
	system("cls");
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 6);
	cout << "\nCurrent TimeStep " << TimeStep << endl;

	SetConsoleTextAttribute(console_color, 15);
	earthArmy->print();
	alienArmy->print();

	
	SetConsoleTextAttribute(console_color, 12);
	cout << "==============  Killed/Destructed Units =============\n";
	SetConsoleTextAttribute(console_color, 15);
	cout << killedlist.getCount() << " Units ";
	killedlist.printlist();
}

void Game::addToKilledList(Unit* unit)
{
	if(unit)
	killedlist.enqueue(unit);
}


int Game::getTimeStep() 
{
	return TimeStep;
}

void Game::timeStep()
{
	generator->generateUnits(TimeStep);

	int X = 1 + (rand() % 100);
	if (X > 0 && X < 10)
	{
		/*EArmyTempList.addUnit(EArmy.removeUnit(UnitType::EarthSoldier));
		EArmy.addUnit(EArmyTempList.removeUnit(UnitType::EarthSoldier));*/
		earthArmy->addUnit(earthArmy->removeUnit(UnitType::EarthSoldier));
	}
	else if (X > 10 && X < 20)
	{
		addToKilledList(earthArmy->removeUnit(UnitType::Tank));
	}
	else if (X > 20 && X < 30)
	{
		/*Unit* removedGunnery = EArmy.removeUnit(UnitType::Gunnery);
		removedGunnery->decrementHealth(removedGunnery->getHealth() / 2);
		EArmyTempList.addUnit(removedGunnery);
		EArmy.addUnit(EArmyTempList.removeUnit(UnitType::Gunnery));*/

		Unit* removedGunnery = earthArmy->removeUnit(UnitType::Gunnery);
		if (removedGunnery)
		{
			removedGunnery->decrementHealth(removedGunnery->getHealth() / 2);
			earthArmy->addUnit(removedGunnery);
		}
	}
	else if (X > 30 && X < 40)
	{
		LinkedQueue<Unit*>AlienSoldiersTempList;
		
		for (int i = 0; i < 5; i++)
		{
			Unit* removedAS = alienArmy->removeUnit(UnitType::AlienSoldier);
			if (removedAS)
			{
				removedAS->decrementHealth(removedAS->getHealth() / 2);
				AlienSoldiersTempList.enqueue(removedAS);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			Unit* removedASTP;
			AlienSoldiersTempList.dequeue(removedASTP);
			alienArmy->addUnit(removedASTP);
		}
	}
	else if (X > 40 && X < 50)
	{
		arrayMonsterADT<Unit*> AlienMonstersTempList;

		for (int i = 0; i < 5; i++)
		{
			Unit* removedAM= alienArmy->removeUnit(UnitType::Monster);
			AlienMonstersTempList.add(removedAM);
		}
		for (int i = 0; i < 5; i++)
		{
			Unit* removedAMTP;
			AlienMonstersTempList.remove(removedAMTP);
			alienArmy->addUnit(removedAMTP);
		}
	}
	else if (X > 50 && X < 60)
	{
		for (int i = 0; i < 6; i++)
		{
			addToKilledList(alienArmy->removeUnit(UnitType::Drone));
		}
	}
	printStatus();
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 9);
	cout << "Press Enter to move to next timestep ...";
	system("pause");
	//system("cls");
	generator->generateUnits(TimeStep++);
}

