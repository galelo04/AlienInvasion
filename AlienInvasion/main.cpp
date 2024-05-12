#include "Game.h"
//

int main()
{
	Game game;
	game.instantiateGame();
	char c;
	Mode mode;
	cout << "Choose your favourite mode:" << endl;
	cout << " 1)Normal Mode" << endl;
	cout << " 2)Silent Mode" << endl;
	cin >> c;
	if (c == '2')
		mode = Mode::Silent;
	else
		mode = Mode::Normal;
	cout << "Simulation starts..." << endl;
	game.setMode(mode);



	while (game.battle());


	game.EndGame();
}
