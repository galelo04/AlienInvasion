#ifndef GAME
#define GAME
#include "Armies/AlienArmy/AlienArmy.h"
#include "Armies/EarthArmy/EarthArmy.h"

class randGen;
enum class Mode {
	Normal,
	Silent
};
enum class Result {
	Win,
	Loss,
	Drawn
};
class Game
{
private:
	int Params[21];
	int TimeStep;
	AlienArmy * alienArmy;
	EarthArmy * earthArmy;
	randGen * generator;
	priQueue <Unit* > killedlist;
	Result result;
	Mode _mode;
public:
	Game();
	AlienArmy*& getAlienArmy() ;
	EarthArmy*& getEarthArmy() ;
	void instantiateGame();
	void loadParams(string filename);
	bool battle();
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
