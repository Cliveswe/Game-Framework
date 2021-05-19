#include "RoulettePlayer.h"

RoulettePlayer::RoulettePlayer(int purse): _purse(purse){
	_game = new RouletteGame();
}

RoulettePlayer::~RoulettePlayer(){
	delete _game;
}


bool RoulettePlayer::setGame(IGame* game){
	if(game != nullptr){
		_game = game;
		return true;
	}
	return false;
}

bool RoulettePlayer::play(int numberOfTimes){
	_game->play(nullptr, 10);
	return false;
}

int RoulettePlayer::getMoney() const{
	return _purse;
}

int RoulettePlayer::getBetCount() const{
	return 0;
}
