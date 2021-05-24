#include "RouletteGame.h"

RouletteGame::RouletteGame(){
	
}


RouletteGame::~RouletteGame(){


}

int RouletteGame::play(char* bet, int amount){
	int choice = 0;
	RoulettBet* rb;
	//void* test = reinterpret_cast<void*>(bet);
	//rb = (RoulettBet*)test;
	rb = (RoulettBet*)bet;
	//rb = new RoulettBet(nullptr);
	//rb = (RoulettBet*)test;
	cout << "success!! amount (0) = " << rb->getAmount() << endl;
	rb->setSlotColour(new string("Leddy"));
	return 0;
}


int RouletteGame::getID() const{

	return GAME_ID;
}


