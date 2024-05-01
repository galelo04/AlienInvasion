#include "Game.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	char c;
	Mode mode;
	cout << "For Normal Mode enters 1 , For Silent Mode enters 2 " << endl;
	cin >> c;
	if (c == '2')
		mode = Mode::Silent;
	else
		mode = Mode::Normal;
	cout << "Simulation starts..." << endl;
	while (game.battle(mode) != 40);
	game.EndGame();
}
