
#include "RouletteGame.h"
#include "RoulettePlayer.h"
#include "ApplicationInstructions.h"
#include "Wrapper.h"
#include "CrapPlayer.h"
#include "Menu.h"
#include <iostream>
using std::cout;
using std::endl;

ApplicationInstructions AppInc;
Menu* gameMenu;
vector<string> gameMenuItems;
IGame* game;
IPlayer* player;

const enum menuEnum{
	ERROR, CRAPS, ROULETTE, EXIT
};

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
	cout << endl << "After " << _player->getBetCount() << " number of rounds, the player has " << _player->getMoney() << " SEK left!" << endl;

	return 0;
}

/// <summary>
/// Create an instance of a menu.
/// </summary>
void createMenu(){
	try{

		gameMenu = new Menu();

	} catch(bad_alloc ba){

		cerr << "bad_alloc caught: " << ba.what() << endl;
	}

}

/// <summary>
/// Initialise the menu.
/// </summary>
void setupMenu(){
	gameMenuItems = {"Incorrect choice!", "Crap's", "Roulette", "Exit"};

	gameMenu->setTitle("Game App");
	gameMenu->setPrompt("Enter your choice: ");
	gameMenu->setMenuItemsTitle("In order to play a game, you must first select the number adjacent to the name of a game!");
	gameMenu->addMenuItem(gameMenuItems[CRAPS]);
	gameMenu->addMenuItem(gameMenuItems[ROULETTE]);
	gameMenu->addMenuItem(gameMenuItems[EXIT]);
}

/// <summary>
/// Initialise the Game.
/// </summary>
void initialise(){
	createMenu();
	setupMenu();
}

/// <summary>
/// Select a game to play or exit.
/// </summary>
/// <returns>A number representing a specific game as type int.</returns>
int selectGame(){
	int ctr = -1;

	do{
		gameMenu->displayMenu('-', '-');
		ctr = Utils::getInputInt(gameMenu->getPrompt().c_str(), "Incorrect choice!");

		switch(ctr){
			case CRAPS:
			case ROULETTE:
			case EXIT:
				return ctr;
				break;
			default:
				cout << gameMenuItems[ERROR] << endl;
				continue;
				break;
		}
	} while(true);

	return ctr;
}

/// <summary>
/// Select a game to play or exit the application.
/// </summary>
/// <returns>0 indicating exiting the application or 1 the game did not run as type int.</returns>
int runGame(){
	bool choice = true;
	do{
		if(AppInc.canPlayGame()){

			switch(selectGame()){
				case CRAPS:
					game = new Wrapper();
					player = new CrapPlayer(AppInc.getBankroll());
					break;
				case ROULETTE:
					game = new RouletteGame();
					player = new RoulettePlayer(AppInc.getBankroll());
					break;
				case EXIT:
					choice = false;
					break;
				default:
					cout << gameMenuItems[ERROR] << endl;
					break;
			}

			if(choice){

				App app(player, game);
				app.run();
			}
		} else{

			cout << "The game did not run!" << endl;
			return 1;
		}
	} while(choice);

	return 0;
}

int main(){

	initialise();

	do{
		int ctr = AppInc.gatherData();

		if(ctr == 1){
			return 0;//End the game.

		} else if(ctr == -1){//Try again!
			continue;

		} else if(ctr == 0){//Play game.
			return runGame();
			break;
		}

	} while(true);


	return 0;
}