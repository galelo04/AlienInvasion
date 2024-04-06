#ifndef GAME
#define GAME

class Game
{
private:
	int Params[20];
	int TimeStep;
public:
	Game();
	void loadParams();
	int* getParams();
	int getTimeStep();
	void SetTimeStep();
};

#endif 
