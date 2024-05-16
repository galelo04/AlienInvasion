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
	if (loadParams(filename))
	{
		char c;
		Mode mode;
		SetConsoleTextAttribute(console_color, 8);
		cout << "Choose your favourite mode:" << endl;
		SetConsoleTextAttribute(console_color, 7);
		cout << " 1)Normal Mode" << endl;
		cout << " 2)Silent Mode" << endl;

		cin >> c;
		while (c!='2'&&c!='1')
		{
			SetConsoleTextAttribute(console_color, 12);
			cout << "Please Choose Only Mode\"1\" or Mode\"2\"\n";
			SetConsoleTextAttribute(console_color, 7);
			cin >> c;
		
		}
		if (c == '2')
			mode = Mode::Silent;

		else
			mode = Mode::Normal;
		system("cls");
		cout << "Simulation starts..." << endl;
		setMode(mode);
	}
}

bool Game::loadParams(string filename)
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
		inFile >> Params[21];   // number of saver units
		inFile >> Params[22] >> Params[23] >> Params[24] >> Params[25] >> Params[26] >> Params[27];  //[21,22]=>SU_P, [23,24]=>SU_H, [25,26]=>SU_C
		inFile >> Params[28]; //[Monster infection prop ]
		inFile >> Params[29]; //[Infection Threshold]

		Params[10] = Params[10] * -1;
		Params[12] = Params[12] * -1;
		Params[14] = Params[14] * -1;

		Params[16] = Params[16] * -1;
		Params[18] = Params[18] * -1;
		Params[20] = Params[20] * -1;

		Params[23] = Params[23] * -1;
		Params[25] = Params[25] * -1;
		Params[27] = Params[27] * -1;

		inFile.close();
		generator->getparameters(Params , 30);
		
		return true;
	}
	else
	{
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(console_color, 12);
		system("cls");
		cout << "make sure of the name of the file and don't put .txt\n";
		instantiateGame();
		return false;
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

bool Game::battle()
{
	bool earthAttack = false;
	bool alienAttack = false;
	bool allyAttack = false;
	generator->generateUnits(TimeStep);
	if (_mode == Mode::Normal)
	{
		HANDLE console_color;
		console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		printStatus();

		SetConsoleTextAttribute(console_color, 13);
		cout << "==============  Units fighting at current step ===============\n";
		SetConsoleTextAttribute(console_color, 15);
		
		earthAttack=earthArmy->attack(this);
		alienAttack=alienArmy->attack(this);
		allyAttack=allyArmy->attack(this);

		earthArmy->infES_P();
		
		printKilledlist();
		SetConsoleTextAttribute(console_color, 9);
		system("pause");
		//system("cls");
	}
	else
	{
		earthAttack = earthArmy->attack(this);
		alienAttack = alienArmy->attack(this);
		allyAttack = allyArmy->attack(this);
	}
	
	if (TimeStep >= 40)
	{
		int ES_Total = earthArmy->getESCount();
		int EG_Total = earthArmy->getEGCount();
		int ET_Total = earthArmy->getETCount();
		int AS_Total = alienArmy->getASCount();
		int AD_Total = alienArmy->getADCount();
		int AM_Total = alienArmy->getAMCount();
		int E_Total = ES_Total + EG_Total + ET_Total;
		int A_Total = AS_Total + AD_Total + AM_Total;


		if (A_Total == 0 && E_Total != 0)
		{
			result = Result::Win;
			return false;
		}
		else if (E_Total == 0 && A_Total != 0)
		{
			result = Result::Loss;
			return false;
		}
		//else if ((E_Total == 0 && A_Total == 0) || (ES_Total!=0 && EG_Total==0 && ET_Total==0 && AS_Total==0 && AD_Total!=0 && AM_Total==0) || (ES_Total == 0 && EG_Total != 0 && ET_Total == 0 && AS_Total != 0 && AD_Total == 0 && AM_Total == 0))
		else if(!earthAttack && !alienAttack && !allyAttack)
		{
			result = Result::Drawn;
			return false;
		}
	}
	TimeStep++;
	return true;
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
	cout << "==============  Killed/Destructed Units ======================\n";
	SetConsoleTextAttribute(console_color, 15);
	cout << killedlist.getCount() << " Units ";
	killedlist.printlist();
}



void Game::addToKilledList(Unit*& unit)
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
	outFile.open("OutputFile\\outputfile.txt");
	if (outFile.is_open())
	{
		outFile << "Td\t" << "ID\t" << "Tj\t" << "Df\t" << "Dd\t" << "Db\t" << endl;
		Unit* unit;int pri = 0;
		int killedES = 0, killedEG = 0, killedET = 0;
		int killedAS = 0, killedAD = 0, killedAM = 0;
		int EtotalDf = 0, EtotalDd = 0, EtotalDb = 0;
		int AtotalDf = 0, AtotalDd = 0, AtotalDb = 0;
		int killedlistcount = killedlist.getCount();
		int i = 0;
		while (i < killedlistcount)
		{
			killedlist.dequeue(unit);
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
			killedlist.enqueue(unit);
			i++;
		}

		outFile << endl;

		outFile << "Battle result: \t";
		
		if (result == Result::Win)
			outFile << "Win" << endl;
		else if (result == Result::Loss)
			outFile << "Loss" << endl;
		else
			outFile << "Drawn" << endl;

		outFile << endl;

		int ES_Total = earthArmy->getESCount() + killedES;
		int EG_Total = earthArmy->getEGCount() + killedEG;
		int ET_Total = earthArmy->getETCount() + killedET;
		int TotalKilledE = killedES + killedEG + killedET;


		outFile << "For Earth Army:" << endl;
		
		outFile << "\t - ES_Total : " << ES_Total << " , ET_Total : "<< ET_Total << " , EG_Total : " << EG_Total << endl;
		
		if (ES_Total == 0)
			outFile << "\t - DestructedES % is Undefined";
		else 
			outFile << "\t - DestructedES % : " << killedES * 100.0 / ES_Total << "%";

		if (ET_Total == 0)
			outFile << " , DestructedET % is Undefined";
		else
			outFile << " , DestructedET %: " << killedET * 100.0 / ET_Total << "%";

		if (EG_Total == 0)
			outFile << " , DestructedEG % is Undefined" << endl;
		else
			outFile << " , DestructedEG % : " << killedEG * 100.0 / EG_Total << "%" << endl;
		
		if ((ES_Total + EG_Total + ET_Total) == 0)
			outFile << "\t - DestructedEU % is Undefined" << endl;
		else
			outFile << "\t - DestructedEU % : " << (TotalKilledE) * 100.0 / (ES_Total + EG_Total + ET_Total) << "%" << endl;

		if (TotalKilledE == 0)
			outFile << "\t - Av_Df is Undefined , Av_Dd is Undefined , Av_Db is Undefined" << endl;
		else
		{
			outFile << "\t - Av_Df : " << EtotalDf * 1.0/ TotalKilledE;
			outFile << " , Av_Dd : " << EtotalDd * 1.0 / TotalKilledE;
			outFile << " , Av_Db : " << EtotalDb * 1.0 / TotalKilledE << endl;
		}
		
		if(EtotalDb == 0)
			outFile << "\t - Df/Db % is Undefined , Dd/Db % is Undefined" << endl;
		else
			outFile << "\t - Df/Db % : " << EtotalDf * 100.0 / EtotalDb << "%" << " , Dd/Db % : " << EtotalDd * 100.0 / EtotalDb << "%" << endl;

		outFile << "\t - Total Healed Units : " << earthArmy->getTotalHealedES() + earthArmy->getTotalFixedET() << endl;
		outFile << "\t - Healed Soldiers : " << earthArmy->getTotalHealedES();
		outFile << "\t , Fixed Tanks : " << earthArmy->getTotalFixedET() << endl;

		if ((ES_Total + EG_Total + ET_Total) == 0)
			outFile << "\t - Healing % is Undefined" << endl;
		else
			outFile << "\t - Healing % : " << (earthArmy->getTotalHealedES() + earthArmy->getTotalFixedET()) * 100.0 / (ES_Total + EG_Total + ET_Total) << "%" << endl;

		if (ES_Total == 0)
			outFile << "\t - Infection % is Undefined";
		else
			outFile << "\t - Infection % : " << earthArmy->getTotalinfES() * 100.0 / ES_Total << "%"<<endl;
		


		outFile << endl;
		
		int AS_Total = alienArmy->getASCount() + killedAS;
		int AD_Total = alienArmy->getADCount() + killedAD;
		int AM_Total = alienArmy->getAMCount() + killedAM;
		int TotalKilledA = killedAS + killedAD + killedAM;

		outFile << "For Alien Army:" << endl;

		outFile << "\t - AS_Total : " << AS_Total << " , AM_Total : " << AM_Total << " , AD_Total : " << AD_Total << endl;
		
		if (AS_Total == 0)
			outFile << "\t - DestructedAS % is Undefined";
		else
			outFile << "\t - DestructedAS % : " << killedAS * 100.0 / AS_Total << "%";

		if (AM_Total == 0)
			outFile << " , DestructedAM % is Undefined";
		else
			outFile << " , DestructedAM %: " << killedAM * 100.0 / AM_Total << "%";

		if (AD_Total == 0)
			outFile << " , DestructedAD % is Undefined" << endl;
		else
			outFile << " , DestructedAD % : " << killedAD * 100.0 / AD_Total << "%" << endl;

		if ((AS_Total + AD_Total + AM_Total) == 0)
			outFile << "\t - DestructedAU % is Undefined" << endl;
		else
			outFile << "\t - DestructedAU % : " << (TotalKilledA) * 100.0 / (AS_Total + AD_Total + AM_Total) << "%" << endl;
		
		if (TotalKilledA == 0)
			outFile << "\t - Av_Df is Undefined , Av_Dd is Undefined , Av_Db is Undefined" << endl;
		else
		{
			outFile << "\t - Av_Df : " << AtotalDf * 1.0 / TotalKilledA;
			outFile << " , Av_Dd : " << AtotalDd * 1.0 / TotalKilledA;
			outFile << " , Av_Db : " << AtotalDb * 1.0 / TotalKilledA << endl;
		}
		
		if (AtotalDb == 0)
			outFile << "\t - Df/Db % is Undefined , Dd/Db % is Undefined" << endl;
		else
			outFile << "\t - Df/Db % : " << AtotalDf * 100.0 / AtotalDb << "%" << " , Dd/Db % : " << AtotalDd * 100.0 / AtotalDb << "%" << endl;

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

void Game::EndGame()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, 7);
	earthArmy->destroyUML(this);
	loadOutputs();
	cout << "Simulation ends, Output file is created" << endl;
	SetConsoleTextAttribute(console_color, 8);
	if (result == Result::Win)
	{
		SetConsoleTextAttribute(console_color, 10);
		cout << "\n\n\n\n\n\n\n";
		cout << "			 _____           _   _          _                         \n";
		cout << "			| ____|__ _ _ __| |_| |__      / \\   _ __ _ __ ___  _   _ \n";
		cout << "			|  _| / _` | '__| __| '_ \\    / _ \\ | '__| '_ ` _ \\| | | |\n";
		cout << "			| |__| (_| | |  | |_| | | |  / ___ \\| |  | | | | | | |_| |\n";
		cout << "			|_____\\__,_|_|   \\__|_| |_| /_/   \\_\\_|  |_| |_| |_|\\__, |\n";
		cout << "			\\ \\      / (_)_ __  ___                             |___/ \n";
		cout << "			 \\ \\ /\\ / /| | '_ \\/ __|                                   \n";
		cout << "			  \\ V  V / | | | | \\__ \\                                    \n";
		cout << "			   \\_/\\_/  |_|_| |_|___/                                     \n";
		cout << "\n\n\n\n\n\n\n";
	}
	else if(result==Result::Loss)
	{
		SetConsoleTextAttribute(console_color, 11);
		cout << "\n\n\n\n\n\n\n";
		cout << "			    _    _ _                 _                          \n";
		cout << "			   / \\  | (_) ___ _ __      / \\   _ __ _ __ ___  _   _\n";
		cout << "			  / _ \\ | | |/ _ \\ '_  \\   / _ \\ | '__| '_ ` _ \\| | | |\n";
		cout << "			 / ___ \\| | |  __/ | | |  / ___ \\| |  | | | | | | |_| |\n";
		cout << "			/_/   \\_\\_|_|\\___|_| |_| /_/   \\_\\_|  |_| |_| |_|\\__, |\n";
		cout << "			\\ \\      / (_)_ __  ___                          |___/ \n";
		cout << "			 \\ \\ /\\ / /| | '_ \\/ __|                                   \n";
		cout << "			  \\ V  V / | | | | \\__ \\                                    \n";
		cout << "			   \\_/\\_/  |_|_| |_|___/                                     \n";
		cout << "\n\n\n\n\n\n\n";

	}
	else
	{
		SetConsoleTextAttribute(console_color, 12);
		cout << "\n\n\n\n\n\n\n";
		cout << "           ____                                 \n";
		cout << "          |  _ \\ _ __ __ ___      ___ __ \n";
		cout << "          | | | | '__/ _` \\ \\ /\\ / / '_ \\ \n";
		cout << "          | |_| | | | (_| |\\ V  V /| | | |\n";
		cout << "          |____/|_|  \\__,_| \\_/\\_/ |_| |_|\n";
		cout << "\n\n\n\n\n\n\n";

	}

}

Game::~Game()
{
	Unit* unittobedeleted;

	while (killedlist.dequeue(unittobedeleted))
		delete unittobedeleted;

	delete generator;
	delete alienArmy;
	delete earthArmy;
}

