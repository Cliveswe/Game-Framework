/**
* Author: Clive Leddy
* File: RoulettePlayer.h
* Date: 2021-04-13
* Summary:
* Play a round of Roulette. Generate a random number. Using the random number as the winning slot number.
* If the player placed a bet on the winning slot calculate the winnings and give them to the player. Display
* the winning number and all the slots that player betted on.
* In this version, the char* bet has to be type cast from char* to the type RouletteBet*.
*/

#ifndef ROULETTEGAME_H
#define ROULETTEGAME_H

#include "IGame.h"
#include "RouletteBet.h"
#include "Menu.h"
using std::cin;
#include <ctime>
using std::time;

/// <summary>
/// Play a round of Roulette. Generate a random number. Using the random number as the winning slot number.
/// If the player placed a bet on the winning slot calculate the winnings and give them to the player. Display
/// the winning number and all the slots that player betted on.
/// In this version, the char* bet has to be type cast from char* to the type RouletteBet*.
/// </summary>
class RouletteGame : public IGame{
private:
	static const int GAME_ID = 12345;
	static const int SINGLE_NUMBER = 35;
	static const int BLACK_RED = 2;

	/// <summary>
	/// Generate a random number from 0 to 36.
	/// </summary>
	/// <returns>A random number as type int.</returns>
	int rouletteNumber();

	/// <summary>
	/// Get the colour of a slot.
	/// </summary>
	/// <param name="rouletteNr">The slot number as type int.</param>
	/// <returns>The colour code for black or red as type int.</returns>
	int getSlotColour(int)const;
	
	/// <summary>
	/// Display the slot colour.
	/// </summary>
	/// <param name="slot">The slot as type int.</param>
	void printSlotColourAsText(int)const;

public:
	/*None is 0 RED R = 18, E = 5 & D = 4 RED = 1854
	BLACK B = 2, L = 12, A = 1, C = 3 & K = 11 BLACK = 2121311 */
	static enum SLOT_COLOURS{ NONE = 0, RED = 1854, BLACK = 2121311 };
	static const int LOWEST_SLOT = 0;//0 is the lowest slot number on the roulette wheel.
	static const int HIGHEST_SLOT = 36;//0 is the highest slot number on the roulette wheel.

	RouletteGame();
	~RouletteGame();

	/// <summary>
	/// Get the unique class ID.
	/// </summary>
	/// <returns>The class ID as type int.</returns>
	static int getRouletteID(){
		return GAME_ID;
	}

	/*IGame virtual methods.*/
	/// <summary>
	/// Play a round of Roulette. Generate a random number. Using the random number as the winning slot number.
	/// If the player placed a bet on the winning slot calculate the winnings and give them to the player. Display
	/// the winning number and all the slots that player betted on.
	/// In this version, the char* bet has to be type cast from char* to the type RouletteBet*.
	/// </summary>
	/// <param name="bet">A bet as type char*.</param>
	/// <param name="amount">The bet amount as type int.</param>
	/// <returns>The winnings if the player won else 0 as type int.</returns>
	int play(char* bet, int amount);// Place amount money on position bet and return winnings

	/// <summary>
	/// Get the unique class ID.
	/// </summary>
	/// <returns>The class ID as type int.</returns>
	int getID() const;// Returns a unique ID for the actual game type
};
#endif // !ROULETTEGAME_H
