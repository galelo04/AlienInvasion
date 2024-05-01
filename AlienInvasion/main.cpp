#include "Game.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	char c;
	Mode mode;
	cout << "For Normal Mode press Enter , For Silent Mode press 1 then Enter " << endl;
	cin >> c;
	if (c == '1')
		mode = Mode::Silent;
	else
		mode = Mode::Normal;
	cout << "Simulation starts..." << endl;
	while (game.battle(mode) != 40);
	game.EndGame();
}
