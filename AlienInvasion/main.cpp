#include "Game.h"
#include "Armies/AlienArmy/AlienArmy.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	//game.battle();
	while(true)
		game.timeStep();
	
	game.printStatus();
	
}