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

int Game::battle(Mode mode)
{
	bool isSilent = true;
	generator->generateUnits(TimeStep);
	if (mode == Mode::Normal)
	{
		isSilent = false;
		printStatus();
		cout << "==============  Units fighting at current step ===============\n";
	}
	earthArmy->attack(this, isSilent);
	alienArmy->attack(this, isSilent);
	if (mode == Mode::Normal)
	{
		printKilledlist();
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 9);
		system("pause");
		//system("cls");
	}
	generator->generateUnits(TimeStep++);
	return TimeStep;
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
		unit->setDestructionTime(TimeStep);
		killedlist.enqueue(unit);
	}
}

void Game::loadOutputs()
{
	ofstream outFile;
	outFile.open("OutputFile\\outfile.txt");
	if (outFile.is_open())
	{
		outFile << "Td\t" << "ID\t" << "Tj\t" << "Df\t" << "Dd\t" << "Db\t" << endl;
		Unit* unit;
		int killedES = 0, killedEG = 0, killedET = 0;
		int killedAS = 0, killedAD = 0, killedAM = 0;
		int EtotalDf = 0, EtotalDd = 0, EtotalDb = 0;
		int AtotalDf = 0, AtotalDd = 0, AtotalDb = 0;
		
		while (killedlist.dequeue(unit) && unit->getType() != UnitType::HealingUnit)
		{
			UnitType type = unit->getType();
			if (type == UnitType::EarthSoldier || type == UnitType::Tank || type == UnitType::Gunnery)
			{
				EtotalDf += unit->getFirstAttackTime() - unit->getJoinTime();
				EtotalDd += unit->getDestructionTime() - unit->getFirstAttackTime();
				EtotalDb += unit->getDestructionTime() - unit->getJoinTime();
			}
			if (type == UnitType::AlienSoldier || type == UnitType::Monster || type == UnitType::Drone)
			{
				AtotalDf += unit->getFirstAttackTime() - unit->getJoinTime();
				AtotalDd += unit->getDestructionTime() - unit->getFirstAttackTime();
				AtotalDb += unit->getDestructionTime() - unit->getJoinTime();
			}
			switch (type)
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
			outFile << unit->getDestructionTime() << "\t" << unit->getID() << "\t" << unit->getJoinTime() << "\t" << unit->getFirstAttackTime() - unit->getJoinTime() << "\t" << unit->getDestructionTime() - unit->getFirstAttackTime() << "\t" << unit->getDestructionTime() - unit->getJoinTime() << endl;

		}

		outFile << endl;

		outFile << "Battle result: \t";
		int EArmyCount = earthArmy->getEGCount() + earthArmy->getESCount() + earthArmy->getETCount();
		int AArmyCount = alienArmy->getADCount() + alienArmy->getAMCount() + alienArmy->getASCount();
		if (EArmyCount > AArmyCount)
			outFile << "Win" << endl;
		else if (EArmyCount < AArmyCount)
			outFile << "Loss" << endl;
		else
			outFile << "Drawn" << endl;

		outFile << endl;

		int ES_Total = earthArmy->getESCount() + killedES;
		int EG_Total = earthArmy->getEGCount() + killedEG;
		int ET_Total = earthArmy->getETCount() + killedET;
		outFile << "For Earth Army:" << endl;
		outFile << "\t - ES_Total : " << ES_Total << " , EG_Total : " << EG_Total << " , ET_Total : "<< ET_Total << endl;
		if (ES_Total == 0)
			outFile << "\t - DestructedES % is Undefined";
		else 
			outFile << "\t - DestructedES % : " << killedES * 100 / ES_Total << "%";
		if (EG_Total == 0)
			outFile << " , DestructedEG % is Undefined";
		else
			outFile << " , DestructedEG % : " << killedEG * 100 / EG_Total << "%";
		if (ET_Total == 0)
			outFile << " , DestructedET % is Undefined" << endl;
		else
			outFile << " , DestructedET %: " << killedET * 100 / ET_Total << "%" << endl;
		if ((ES_Total + EG_Total + ET_Total) == 0)
		{
			outFile << "\t - DestructedEU % is Undefined" << endl;
			outFile << "\t - Av_Df is Undefined";
		}
		else
		{
			outFile << "\t - DestructedEU % : " << (killedES + killedEG + killedET) * 100 / (ES_Total + EG_Total + ET_Total) << "%" << endl;
			outFile << "\t - Av_Df : " << (EtotalDf + earthArmy->getTotalEDf()) / (ES_Total + EG_Total + ET_Total);
		}
		if ((killedES + killedEG + killedET) == 0)
		{
			outFile << " , Av_Dd is Undefined , Av_Db is Undefined" << endl;
		}
		else
		{
			outFile << " , Av_Dd : " << EtotalDd / (killedES + killedEG + killedET);
			outFile << " , Av_Db : " << EtotalDb / (killedES + killedEG + killedET) << endl;
		}
		if(EtotalDb == 0)
			outFile << "\t - Df/Db % is Undefined , Dd/Db % is Undefined" << endl;
		else
			outFile << "\t - Df/Db % : " << EtotalDf * 100 / EtotalDb << "%" << " , Dd/Db % : " << EtotalDd * 100 / EtotalDb << "%" << endl;


		outFile << endl;
		
		int AS_Total = alienArmy->getASCount() + killedAS;
		int AD_Total = alienArmy->getADCount() + killedAD;
		int AM_Total = alienArmy->getAMCount() + killedAM;
		outFile << "For Alien Army:" << endl;
		outFile << "\t - AS_Total : " << AS_Total << " , AD_Total : " << AD_Total << " , AM_Total : " << AM_Total << endl;
		if (AS_Total == 0)
			outFile << "\t - DestructedAS % is Undefined";
		else
			outFile << "\t - DestructedAS % : " << killedAS * 100 / AS_Total << "%";
		if (AD_Total == 0)
			outFile << " , DestructedAD % is Undefined";
		else
			outFile << " , DestructedAD % : " << killedAD * 100 / AD_Total << "%";
		if (AM_Total == 0)
			outFile << " , DestructedAM % is Undefined" << endl;
		else
			outFile << " , DestructedAM %: " << killedAM * 100 / AM_Total << "%" << endl;
		if ((AS_Total + AD_Total + AM_Total) == 0)
		{
			outFile << "\t - DestructedAU % is Undefined" << endl;
			outFile << "\t - Av_Df is Undefined";
		}
		else
		{
			outFile << "\t - DestructedAU % : " << (killedAS + killedAD + killedAM) * 100 / (AS_Total + AD_Total + AM_Total) << "%" << endl;
			outFile << "\t - Av_Df : " << (AtotalDf + alienArmy->getTotalADf()) / (AS_Total + AD_Total + AM_Total);
		}
		if ((killedAS + killedAD + killedAM) == 0)
		{
			outFile << " , Av_Dd is Undefined , Av_Db is Undefined" << endl;
		}
		else
		{
			outFile << " , Av_Dd : " << AtotalDd / (killedAS + killedAD + killedAM);
			outFile << " , Av_Db : " << AtotalDb / (killedAS + killedAD + killedAM) << endl;
		}
		if (AtotalDb == 0)
			outFile << "\t - Df/Db % is Undefined , Dd/Db % is Undefined" << endl;
		else
			outFile << "\t - Df/Db % : " << AtotalDf * 100 / AtotalDb << "%" << " , Dd/Db % : " << AtotalDd * 100 / AtotalDb << "%" << endl;

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
	SetConsoleTextAttribute(console_color, 7);
	loadOutputs();
	cout << "Simulation ends, Output file is created" << endl;
	SetConsoleTextAttribute(console_color, 8);

}

Game::~Game()
{
	delete generator;
	delete alienArmy;
	delete earthArmy;
}

