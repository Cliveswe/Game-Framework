#ifndef ROULETTEPLAYER_H
#define ROULETTEPLAYER_H

#include "IPlayer.h"
#include "RouletteGame.h"


class RoulettePlayer : public IPlayer{
private:
	int _purse;
	IGame* _game;
public:
	RoulettePlayer(int);
	~RoulettePlayer();
	bool setGame(IGame* game);// Gives the player a game object to use
	bool play(int numberOfTimes);// Tells player to play the game numberOfTimes times
	int getMoney() const;// Returns the amount of player's money
	int getBetCount() const;// Returns the total number of bets placed during object life time
};

#endif // !ROULETTEPLAYER_H