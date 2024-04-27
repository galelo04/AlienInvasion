#include "Game.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	while (game.timeStep() != 40);
	game.EndGame();
}
