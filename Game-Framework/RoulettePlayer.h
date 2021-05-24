#ifndef ROULETTEPLAYER_H
#define ROULETTEPLAYER_H

#include "IPlayer.h"
#include "RouletteGame.h"
#include "Utils.h"
#include "RoulettBet.h"
#include <new>
using std::bad_alloc;
using std::cerr;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <iostream>

class RoulettePlayer : public IPlayer{
private:

	IGame* _game;
	int _bankroll;
	int _betCount;

	Menu* menuPlayer;
	vector<string> rouletteMenuItems;
	enum rouletteMenuEnum{ ERROR, CHOOSE_NUMBERS, CHOOSE_COLOUR, BET_AMOUNT, END };

	void newBet();
	void initialize();
	void createRouletteMenu();
	void setMenu();
	bool setSlots(vector<int>*);
	bool isSlotNumberValid(int);
	int setSlotColour();
	int setBetAmount();
	RoulettBet* getBet();
public:
	RoulettePlayer(int);
	~RoulettePlayer();
	bool setGame(IGame* game);// Gives the player a game object to use
	bool play(int numberOfTimes);// Tells player to play the game numberOfTimes times
	int getMoney() const;// Returns the amount of player's money
	int getBetCount() const;// Returns the total number of bets placed during object life time
	bool canPlaceBet();
	void displayInstructions()const;
	void displayHeader()const;
};

#endif // !ROULETTEPLAYER_H