#ifndef WRAPPER_H
#define WRAPPER_H

#include "IGame.h"
#include "CrapGame.h"

class Wrapper : public IGame, private CrapGame{
private:
	CrapGame game;
public:
	virtual int play(char* bet, int amount);
	virtual int getID();
};

#endif // !WRAPPER_H
