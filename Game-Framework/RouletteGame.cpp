/**
* Author: Clive Leddy
* File: RoulettePlayer.cpp
* Date: 2021-04-13
* Summary:
* Play a round of Roulette. Generate a random number. Using the random number as the winning slot number.
* If the player placed a bet on the winning slot calculate the winnings and give them to the player. Display
* the winning number and all the slots that player betted on.
* In this version, the char* bet has to be type cast from char* to the type RouletteBet*.
*/

#include "RouletteGame.h"

RouletteGame::RouletteGame(){
	/*Seed the random generator with time(0) the number of ticks since Jan 1, 1970 UTC*/
	srand(time(0));
}

RouletteGame::~RouletteGame(){
}

/// <summary>
/// Play a round of Roulette. Generate a random number. Using the random number as the winning slot number.
/// If the player placed a bet on the winning slot calculate the winnings and give them to the player. Display
/// the winning number and all the slots that player betted on.
/// In this version, the char* bet has to be type cast from char* to the type RouletteBet*.
/// </summary>
/// <param name="bet">A bet as type char*.</param>
/// <param name="amount">The bet amount as type int.</param>
/// <returns>The winnings if the player won else 0 as type int.</returns>
int RouletteGame::play(char* bet, int amount){
	int rouletteNr = rouletteNumber();
	RouletteBet* rb;
	int payout = 0;

	rb = (RouletteBet*)bet;//Un-boxing from char* to RouletteBet*.

	cout << endl;
	cout << "Your bet is " << amount << " SEK." << endl;
	cout << "The winning slot number is ";
	printSlotColourAsText(rouletteNr);//Display the winning slot colour, black or red.
	cout << " " << rouletteNr << "." << endl;//Display the winning slot number.

	//Check if the player placed a bet on the winning slot.
	if(rb->getSlotBet(rouletteNr) > 0){

		payout += rb->getSlotBet(rouletteNr) * SINGLE_NUMBER_MULTIPLIER;//Calculate the winnings.
	}

	//Check if the player paced a bet on a slot colour i.e. red or black.
	if(rb->getSlotColour() == getSlotColour(rouletteNr)){

		payout += rb->getSlotColourAmount() * BLACK_RED;//Calculate the winnings.
	}

	//Display all the bets made by the player.
	cout << endl << rb << endl;

	return payout;
}

/// <summary>
/// Generate a random number from 0 to 36.
/// </summary>
/// <returns>A random number as type int.</returns>
int RouletteGame::rouletteNumber(){

	return Utils::randomNumberGenerator(LOWEST_SLOT, HIGHEST_SLOT);
}

/// <summary>
/// Get the unique class ID.
/// </summary>
/// <returns>The class ID as type int.</returns>
int RouletteGame::getID() const{

	return GAME_ID;
}

/// <summary>
/// Display the slot colour.
/// </summary>
/// <param name="slot">The slot as type int.</param>
void RouletteGame::printSlotColourAsText(int slot)const{
	if(getSlotColour(slot) == BLACK){
		cout << "BLACK";
	} else if(getSlotColour(slot) == RED){
		cout << "RED";
	}
}

/// <summary>
/// Get the colour of a slot.
/// </summary>
/// <param name="rouletteNr">The slot number as type int.</param>
/// <returns>The colour code for black or red as type int.</returns>
int RouletteGame::getSlotColour(int rouletteNr)const{
	//Even numbers are Black.
	if((rouletteNr % 2) == 0){
		return BLACK;
	}
	//Odd numbers are Red.
	return RED;
}
