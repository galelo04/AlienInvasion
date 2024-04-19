#include "Game.h"
//

int main()


{
	Game game;
	game.instantiateGame();
	//game.battle();
	while (game.getTimeStep()!=51)
		game.timeStep();

}