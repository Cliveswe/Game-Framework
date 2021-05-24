#ifndef ROULETTEGAME_H
#define ROULETTEGAME_H

#include "IGame.h"
#include "RoulettBet.h"
#include "Menu.h"
using std::cin;

class RouletteGame : public IGame{
private:
	static const int GAME_ID = 12345;

public:
	/*None is 0 RED R = 18, E = 5 & D = 4 RED = 1854
	BLACK B = 2, L = 12, A = 1, C = 3 & K = 11 BLACK = 2121311 */
	static const enum SLOT_COLOURS{ NONE = 0, RED = 1854, BLACK = 2121311 };
	static const int LOWEST_SLOT = 0;//0 is the lowest slot number on the roulette wheel.
	static const int HIGHEST_SLOT = 36;//0 is the highest slot number on the roulette wheel.

	RouletteGame();
	~RouletteGame();
	
	static int getRouletteID(){
		return GAME_ID;
	}

	/*IGame virtual methods.*/
	int play(char* bet, int amount);// Place amount money on position bet and return winnings
	int getID() const;// Returns a unique ID for the actual game type
};
#endif // !ROULETTEGAME_H
