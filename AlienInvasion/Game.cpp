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
	allyArmy = new AllyArmy;
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

AllyArmy*& Game::getAllyArmy()
{
	return allyArmy;
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
		inFile >> Params[9] >> Params[10] >> Params[11] >> Params[12] >> Params[13] >> Params[14];    //[9,10]=>E_P, [11,12]=>E_H, [13,14]=>E_C
		inFile >> Params[15] >> Params[16] >> Params[17] >> Params[18] >> Params[19] >> Params[20];  //[15,16]=>A_P, [17,18]=>A_H, [19,20]=>A_C
		inFile >> Params[21] >> Params[22] >> Params[23] >> Params[24] >> Params[25] >> Params[26];  //[21,22]=>SU_P, [23,24]=>SU_H, [25,26]=>SU_C
		inFile >> Params[27]; //[Monster infection prop ]
		inFile >> Params[28]; //[Infection Threshold]

		Params[10] = Params[10] * -1;
		Params[12] = Params[12] * -1;
		Params[14] = Params[14] * -1;

		Params[16] = Params[16] * -1;
		Params[18] = Params[18] * -1;
		Params[20] = Params[20] * -1;

		Params[22] = Params[22] * -1;
		Params[24] = Params[24] * -1;
		Params[26] = Params[26] * -1;

		inFile.close();
		generator->getparameters(Params);
	}
	else
	{
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 12);
		system("cls");
		cout << "make sure of the name of the file and don't put .txt\n";
		instantiateGame();
	}
}


Mode Game::getMode() const
{
	return _mode;
}

void Game::setMode(Mode mode)
{
	_mode = mode;
}

int Game::battle()
{
	generator->generateUnits(TimeStep);
	if (_mode == Mode::Normal)
	{
		printStatus();
		cout << "==============  Units fighting at current step ===============\n";
	
		earthArmy->attack(this);
		alienArmy->attack(this);
		allyArmy->attack(this);
		
		printKilledlist();
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 9);
		system("pause");
		//system("cls");
	}
	else
	{
		earthArmy->attack(this);
		alienArmy->attack(this);
		allyArmy->attack(this);
	}
	
	//generator->generateUnits(TimeStep++);
	TimeStep++;
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
	allyArmy->print();
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



void Game::addToKilledList(Unit*& unit)
{
	if (unit)
	{
		unit->setDestructionTime(TimeStep);
		killedlist.enqueue(unit,-TimeStep);
	}
}


void Game::loadOutputs()
{
	ofstream outFile;
	outFile.open("OutputFile\\outputfile.txt");
	if (outFile.is_open())
	{
		outFile << "Td\t" << "ID\t" << "Tj\t" << "Df\t" << "Dd\t" << "Db\t" << endl;
		Unit* unit;int pri = 0;
		int killedES = 0, killedEG = 0, killedET = 0;
		int killedAS = 0, killedAD = 0, killedAM = 0;
		int EtotalDf = 0, EtotalDd = 0, EtotalDb = 0;
		int AtotalDf = 0, AtotalDd = 0, AtotalDb = 0;
		
		while (killedlist.dequeue(unit, pri))
		{
			UnitType type = unit->getType();
			if (type != UnitType::HealingUnit) {
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

		int ETotalgotAttacked = 0;
		EtotalDf += earthArmy->getTotalEDf(ETotalgotAttacked);
		ETotalgotAttacked += killedES + killedEG + killedET;

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
			outFile << "\t - DestructedEU % is Undefined" << endl;
		else
			outFile << "\t - DestructedEU % : " << (killedES + killedEG + killedET) * 100 / (ES_Total + EG_Total + ET_Total) << "%" << endl;
		
		if(ETotalgotAttacked == 0)
			outFile << "\t - Av_Df is Undefined";
		else
			outFile << "\t - Av_Df : " << EtotalDf / ETotalgotAttacked;
		
		if ((killedES + killedEG + killedET) == 0)
			outFile << " , Av_Dd is Undefined , Av_Db is Undefined" << endl;
		else
		{
			outFile << " , Av_Dd : " << EtotalDd / (killedES + killedEG + killedET);
			outFile << " , Av_Db : " << EtotalDb / (killedES + killedEG + killedET) << endl;
		}
		
		if(EtotalDb == 0)
			outFile << "\t - Df/Db % is Undefined , Dd/Db % is Undefined" << endl;
		else
			outFile << "\t - Df/Db % : " << EtotalDf * 100 / EtotalDb << "%" << " , Dd/Db % : " << EtotalDd * 100 / EtotalDb << "%" << endl;

		if (ES_Total == 0)
			outFile << "\t - Infection % is Undefined";
		else
			outFile << "\t - Infection % : " << earthArmy->getTotalinfES() * 100 / ES_Total << "%";



		outFile << endl;
		
		int AS_Total = alienArmy->getASCount() + killedAS;
		int AD_Total = alienArmy->getADCount() + killedAD;
		int AM_Total = alienArmy->getAMCount() + killedAM;

		int ATotalgotAttacked = 0;
		AtotalDf += earthArmy->getTotalEDf(ATotalgotAttacked);
		ATotalgotAttacked += killedAS + killedAD + killedAM;

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
			outFile << "\t - DestructedAU % is Undefined" << endl;
		else
			outFile << "\t - DestructedAU % : " << (killedAS + killedAD + killedAM) * 100 / (AS_Total + AD_Total + AM_Total) << "%" << endl;
		
		if (ATotalgotAttacked == 0)
			outFile << "\t - Av_Df is Undefined";
		else
			outFile << "\t - Av_Df : " << AtotalDf / ATotalgotAttacked;

		if ((killedAS + killedAD + killedAM) == 0)
			outFile << " , Av_Dd is Undefined , Av_Db is Undefined" << endl;
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
		cout << "make sure of the name of the file and don't put .txt\n";
		EndGame();
	}
	outFile.close();
}

int Game::getCrntTimeStep()
{
	return TimeStep;
}

//void Game::battleResult()
//{
//	int ES_Count = earthArmy->getESCount();
//	int EG_Count = earthArmy->getEGCount();
//	int ET_Count = earthArmy->getETCount();
//	int AS_Count = alienArmy->getASCount();
//	int AD_Count = alienArmy->getADCount();
//	int AM_Count = alienArmy->getAMCount();
//
//	if (ES_Count > 0 && EG_Count == 0 && ET_Count == 0)
//	{
//		if (AM_Count > 0)
//		{
//			cout << "Loss";
//			return;
//		}
//		else if(AS_Count == 0 && AD_Count == 0)
//		{
//			cout << "Win";
//			return;
//		}
//		else
//		{
//			cout << "Drawn";
//			return;
//		}
//	}
//	else if (ES_Count > 0 && EG_Count > 0 && ET_Count == 0)
//	{
//		if (AD_Count <= 1  && AS_Count == 0)
//		{
//			cout << "Win";
//			return;
//		}
//		else
//		{
//			cout << "Drawn";
//			return;
//		}
//	}
//	else if (ES_Count > 0 && EG_Count == 0 && ET_Count > 0)
//	{
//		if (AD_Count <= 1 && AS_Count == 0)
//		{
//			cout << "Win";
//			return;
//		}
//		else
//		{
//			cout << "Drawn";
//			return;
//		}
//	}
//}

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

