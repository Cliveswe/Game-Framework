
#include "RouletteGAme.h"
#include "RoulettePlayer.h"
#include "ApplicationInstructions.h"

#include <iostream>
using std::cout;
using std::endl;

ApplicationInstructions AppInc;
RoulettePlayer* player;//(AppInc.getBankroll()); // Start with a player that has 1000 Kr
RouletteGame* game;

class App{
public:
	App(IPlayer* player, IGame* game) : _player(player), _game(game){ }
	int run();
private:
	IPlayer* _player;
	IGame* _game;
};

int App::run(){
	
	if(!_player->setGame(_game)){
		delete _player;
		delete _game;
		return 1;
	}
	
	_player->play(AppInc.getNumberOfRounds());
	cout << "After " << _player->getBetCount() << " number of rounds, the player has " << _player->getMoney() << " SEK left!" << endl;

	return 0;
}

int main(){

	do{
		int ctr = AppInc.gatherData();
		
		if(ctr == 1){
			return 0;

		} else if(ctr == -1){
			continue;

		} else if(ctr == 0){
			break;
		}

	} while(true);

	if(AppInc.canPlayGame()){

		
		player = new RoulettePlayer(AppInc.getBankroll()); // Start with a player that has 1000 Kr
		game = new RouletteGame();

		App app(player, game);

		return app.run();

	} else{

		cout << "The game did not run!" << endl;
		return 1;
	}

	return 0;
}