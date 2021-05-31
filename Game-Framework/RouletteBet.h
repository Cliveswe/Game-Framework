/*
* Name: Clive Leddy
* File: RouletteBet.h
* Date: 2021-05-22
*
* Summary: 
* This class is a container of various bets per slot in a Roulette game. The class can only be created,
* destroyed or read. Thus a player sends an instance of this class to the Roulette game. The Roulette game
* in turn can read the bets placed by the user to determine the winnings on one or more bets.
* The class has overridden the "<<" ostream to display all the bets. The bets are formatted by first displaying
* all the bets per slot (inside bets) then the bet on the coloured slot and finally the total sum of all the
* bets.
*/

#ifndef ROULETTE_BET_H
#define ROULETTE_BET_H

#include "SlotAndBet.h"
#include "RouletteGame.h"
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::endl;
#include <ostream>
using std::ostream;
#include <iomanip>
using std::setw;

/// <summary>
/// This class is a container of various bets per slot in a Roulette game. The class can only be created,
/// destroyed or read.Thus a player sends an instance of this class to the Roulette game.The Roulette game
/// in turn can read the bets placed by the user to determine the winnings on one or more bets.
/// The class has overridden the "<<" ostream to display all the bets.The bets are formatted by first displaying
/// all the bets per slot(inside bets) then the bet on the coloured slot and finally the total sum of all the
/// bets.
/// </summary>
class RouletteBet{
private:
	vector<SlotAndBet> *_slots;
	int _slotColour;
	int _betAmount;
	
	/// <summary>
	/// Get the list of slots and bet per slot.
	/// </summary>
	/// <returns>Add a list of bets on a variety of slots as type vector<SlotAndBet>*.</returns>
	vector<SlotAndBet>* getSlots()const;

public:
	
	/// <summary>
	/// Class constructor.
	/// </summary>
	/// <param name="betAmount">Set a bet on a slot colour as type int.</param>
	/// <param name="slotColour">Set a selected slot colour as type int.</param>
	/// <param name="slots">Add a list of bets on a variety of slots as type vector<SlotAndBet>*.</param>
	RouletteBet(int betAmount, int slotColour, vector<SlotAndBet>* slots);
	
	/// <summary>
	/// Class constructor that creates an instance of the class that is empty.
	/// </summary>
	RouletteBet();
	
	/// <summary>
	/// Class destructor.
	/// </summary>
	~RouletteBet();
	
	/// <summary>
	/// Is there any slots with bets.
	/// </summary>
	/// <returns>True if there is a list of slots otherwise false.</returns>
	bool hasSlots()const;
	
	/// <summary>
	/// Get a bet that was placed on a slot.
	/// </summary>
	/// <param name="slotNr">The slot as type int.</param>
	/// <returns>If the requested slot is found return the bet otherwise return 0, as type int.</returns>
	int getSlotBet(int)const;
	
	/// <summary>
	/// Get the colour of the slot.
	/// </summary>
	/// <returns>The slot colour as type int.</returns>
	int getSlotColour()const;

	/// <summary>
	/// Get the bet that was placed on the slot colour.
	/// </summary>
	/// <returns>The bet placed on the slot colour as type int.</returns>
	int getSlotColourAmount()const;
	
	/// <summary>
	/// Get the total sum of bet on all the slots.
	/// </summary>
	/// <returns>The bet total as type int.</returns>
	int getBetTotal()const;
	
	/// <summary>
	/// Format the class data for printing. Think of this method as a toSting() method in for example Java.
	/// This a overloaded operator "<<".
	/// </summary>
	/// <param name="os">The stream to write to as type iostream.</param>
	/// <param name="rb">The source to display as type RouletteBet*.</param>
	/// <returns>A stream of type ostream.</returns>
	friend ostream& operator<<(std::ostream& , const RouletteBet*);
};


#endif // !ROULETTE_BET_H