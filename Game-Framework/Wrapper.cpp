#include "Wrapper.h"

int Wrapper::play(char* bet, int amount){
	return game.play(bet, amount);
}

int Wrapper::getID(){
	return game.getID();
}
