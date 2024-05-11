#ifndef GAME
#define GAME
#include "Armies/AlienArmy/AlienArmy.h"
#include "Armies/EarthArmy/EarthArmy.h"
#include "Armies/AllyArmy/AllyArmy.h"

class randGen;
enum class Mode {
	Normal,
	Silent
};
class Game
{
private:
	int Params[29];
	int TimeStep;
	AlienArmy * alienArmy;
	EarthArmy * earthArmy;
	AllyArmy* allyArmy;
	randGen * generator;
	priQueue <Unit* > killedlist;
	

	Mode _mode;
public:
	Game();
	AlienArmy*& getAlienArmy() ;
	EarthArmy*& getEarthArmy() ;
	AllyArmy*& getAllyArmy();
	void instantiateGame();
	void loadParams(string filename);
	int battle();
	Mode getMode() const;
	void setMode(Mode mode);
	void printStatus();
	void printKilledlist();
	void addToKilledList(Unit*& unit);
	void loadOutputs();
	int getCrntTimeStep();
	void EndGame();
	~Game();
};

#endif 
