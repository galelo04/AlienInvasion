#include "Game.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	while (game.battle() != 40);
	game.EndGame();
}
