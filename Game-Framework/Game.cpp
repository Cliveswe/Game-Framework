#include "IGame.h"
#include "IPlayer.h"
#include "CrapPlayer.h"

#include <iostream>
using std::cout;
using std::endl;

class App{
public:
	App(IPlayer* player, IGame* game) : _player(player), _game(game){ }
	int run();
private:
	IPlayer* _player;
	IGame* _game;
};
int App::run(){
	_player->setGame(_game);
	_player->play(10000);
	cout << "After " << _player->getBetCount() << " number of rounds, the player has " << _player->getMoney() << " SEK left!" << endl;
	return 0;
}
int main(){
	RoulettePlayer player(1000); // Start with a player that has 1000 Kr
	RouletteGame game;
	App app(&player, &game);
	return app.run();
}