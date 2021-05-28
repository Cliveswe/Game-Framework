/*
* Name: Clive Leddy
* File: Wrapper.cpp
* Date: 2021-05-28
* Summary:
* This is a wrapper class that wraps the class CrapGame with the base class IGame. This enables the class
* CrapGame to be use in the application.
* Other names for this technique from design patterns are the Adapter or Decorator class.
*/

#include "Wrapper.h"

/// <summary>
/// Play the CrapGame.
/// </summary>
/// <param name="bet">Not used in the game of Craps.</param>
/// <param name="amount">Amount of money as a bet as type int.</param>
/// <returns>The winnings as type int.</returns>
int Wrapper::play(char* bet, int amount){
	return game.play(bet, amount);
}

/// <summary>
/// Get the ID of the Craps game.
/// </summary>
/// <returns>Game id as type int.</returns>
int Wrapper::getID()const{
	return game.getID();
}
