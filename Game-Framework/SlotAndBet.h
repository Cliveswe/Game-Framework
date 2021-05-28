/*
* Author: Clive Leddy
* File: SlotAndBet.h
* Date: 2021-05-25
* Summary:
* A container that holds a slot number and a bet on that slot in the game of Roulette.
*/
#ifndef SLOTANDBET_H
#define SLOTANDBET_H

class SlotAndBet{
private:
	int _slot;
	int _bet;
public:
	SlotAndBet(int, int);
	~SlotAndBet();

	/// <summary>
	/// Get the slot number.
	/// </summary>
	/// <returns>Slot number as int.</returns>
	int getSlot()const;

	/// <summary>
	/// Get the slot bet.
	/// </summary>
	/// <returns>Slot bet as int.</returns>
	int getBet()const;
};

#endif // !SLOTANDBET_H
