#include "Game.h"
int main()
{
	Game game;
	game.instantiateGame();
	

	while (game.battle());
	
	game.EndGame();
	cout << "The game ended after " << game.getCrntTimeStep() << " timesteps\n";
}
