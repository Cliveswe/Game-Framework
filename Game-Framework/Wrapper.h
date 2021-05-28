/*
* Name: Clive Leddy
* File: Wrapper.h
* Date: 2021-05-28
* Summary:
* This is a wrapper class that wraps the class CrapGame with the base class IGame. This enables the class
* CrapGame to be use in the application. 
* Other names for this technique from design patterns are the Adapter or Decorator class.
*/

#ifndef WRAPPER_H
#define WRAPPER_H

#include "IGame.h"
#include "CrapGame.h"

/// <summary>
/// This is a wrapper class that wraps the class CrapGame with the base class IGame. This enables the class
/// CrapGame to be use in the application.
/// Other names for this technique from design patterns are the Adapter or Decorator class.
/// </summary>
class Wrapper : public IGame, private CrapGame{
private:
	CrapGame game;

public:
	/// <summary>
	/// Play the CrapGame.
	/// </summary>
	/// <param name="bet">Not used in the game of Craps.</param>
	/// <param name="amount">Amount of money as a bet as type int.</param>
	/// <returns>The winnings as type int.</returns>
	int play(char* bet, int amount);

	/// <summary>
	/// Get the ID of the Craps game.
	/// </summary>
	/// <returns>Game id as type int.</returns>
	int getID()const;
};

#endif // !WRAPPER_H
