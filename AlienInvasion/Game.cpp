#include "Game.h"
#include "randGen.h"
#include "fstream"
#include <Windows.h>
using namespace std;



Game::Game() :killedAD(0),killedAM(0),killedAS(0),killedEG(0),killedES(0),killedET(0)
{
	srand((unsigned)time(NULL));
	earthArmy = new EarthArmy;
	alienArmy = new AlienArmy;
	generator = new randGen(this);
	TimeStep = 1;
}

AlienArmy*& Game::getAlienArmy() 
{
	return  alienArmy;
}

EarthArmy*& Game::getEarthArmy()
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
		inFile >> Params[1] >> Params[2] >> Params[3] >> Params[4];  // [1]=>ES%, [2]=>ET%, [3]=>EG% , [4]=>HU%
		inFile >> Params[5] >> Params[6] >> Params[7];  // [5]=>AS%, [6]=>AM%, [7]=>AD%
		inFile >> Params[8];                            // [8]=>Prob
		inFile >> Params[9] >> Params[10] >> Params[11] >> Params[12] >> Params[13] >> Params[14];    //[9,10]=>ES_R, [11,12]=>ET_R, [13,14]=>EG_R
		inFile >> Params[15] >> Params[16] >> Params[17] >> Params[18] >> Params[19] >> Params[20];  //[15,16]=>AS_R, [17,18]=>AM_R, [19,20]=>AD_R

		Params[10] = Params[10] * -1;
		Params[12] = Params[12] * -1;
		Params[14] = Params[14] * -1;

		Params[16] = Params[16] * -1;
		Params[18] = Params[18] * -1;
		Params[20] = Params[20] * -1;
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
	//system("cls");
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 6);
	cout << "\nCurrent TimeStep " << TimeStep << endl;

	SetConsoleTextAttribute(console_color, 15);
	earthArmy->print();
	alienArmy->print();

	
	
}

void Game::printKilledlist()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 6);
	SetConsoleTextAttribute(console_color, 12);
	cout << "==============  Killed/Destructed Units =============\n";
	SetConsoleTextAttribute(console_color, 15);
	cout << killedlist.getCount() << " Units ";
	killedlist.printlist();
}

void Game::addToKilledList(Unit* unit)
{
	if (unit)
	{
		unit->setTd(getCrntTimeStep());
		killedlist.enqueue(unit);

		switch (unit->getType())
		{
		case UnitType::EarthSoldier:
		{
			killedES++;
			break;
		}
		case UnitType::Gunnery:
		{
			killedEG++;
			break;
		}
		case UnitType::Tank:
		{
			killedET++;
			break;
		}
		case UnitType::AlienSoldier:
		{
			killedAS++;
			break;
		}
		case UnitType::Drone:
		{
			killedAD++;
			break;
		}
		case UnitType::Monster:
		{
			killedAM++;
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void Game::loadOutputs(string filename)
{
	ofstream outFile;
	outFile.open("InputFiles\\" + filename + ".txt");
	if (outFile.is_open())
	{
		Unit* unit;
		while (killedlist.dequeue(unit))
		{
			outFile << "Td\t" << "ID\t" << "Tj\t" << "Df\t" << "Dd\t" << "Db\t" << endl;
			outFile << unit->getTd() << "\t" << unit->getID() << "\t" << unit->getJoinTime() << "\t" << unit->getDf() << "\t" << unit->getDd() << "\t" << unit->getDb() << "\t";
		}
		outFile << "Battle result: \t";
		int EArmyCount = earthArmy->getEGCount() + earthArmy->getESCount() + earthArmy->getETCount();
		int AArmyCount = alienArmy->getADCount() + alienArmy->getAMCount() + alienArmy->getASCount();
		if (EArmyCount > AArmyCount)
			outFile << "Win" << endl;
		else if (EArmyCount < AArmyCount)
			outFile << "Loss" << endl;
		else
			outFile << "Drawn" << endl;

		outFile << "For Earth Army:" << endl;
		outFile << "\t - ( ES_Total : " << earthArmy->getESCount() + killedES;
		outFile << " , EG_Total : " << earthArmy->getEGCount() + killedEG ;
		outFile << " , ET_Total : " << earthArmy->getETCount() + killedET <<" )"<< endl;
		

	}
	else
	{
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 12);
		system("cls");
		cout << "make sure of the name of the file and dont put .txt\n";
		EndGame();
	}
	outFile.close();
}

int Game::getCrntTimeStep()
{
	return TimeStep;
}

void Game::EndGame()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 8);

	cout << "please enter the Output file name " << endl;
	string filename;
	SetConsoleTextAttribute(console_color, 7);
	cin >> filename;
	loadParams(filename);
}

Game::~Game()
{
	delete generator;
	delete alienArmy;
	delete earthArmy;
}

int Game::timeStep()
{
	generator->generateUnits(TimeStep);
	printStatus();
	cout << "==============  Units fighting at current step ===============\n";
	earthArmy->attack(this);
	alienArmy->attack(this);
	printKilledlist();
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 9);
	system("pause");
	//system("cls");
	generator->generateUnits(TimeStep++);
	return TimeStep;
}

