#ifndef ROULETTEGAME_H
#define ROULETTEGAME_H

#include "IGame.h"
#include "Menu.h"

class RouletteGame: public IGame{
private:
	Menu *menu;
public:
	RouletteGame();
	~RouletteGame();
	void initialize();
	int play(char* bet, int amount);	// Place amount money on position bet and return winnings
	int getID() const;					// Returns a unique ID for the actual game type
};
#endif // !ROULETTEGAME_H
