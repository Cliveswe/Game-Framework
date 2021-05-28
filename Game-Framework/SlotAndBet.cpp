/*
* Author: Clive Leddy
* File: SlotAndBet.cpp
* Date: 2021-05-25
* Summary:
* A container that holds a slot number and a bet on that slot in the game of Roulette.
*/
#include "SlotAndBet.h"

SlotAndBet::SlotAndBet(int slot, int bet): _slot(slot), _bet(bet){
}

SlotAndBet::~SlotAndBet(){
}

/// <summary>
/// Get the slot number.
/// </summary>
/// <returns>Slot number as int.</returns>
int SlotAndBet::getSlot()const{
	return _slot;
}

/// <summary>
/// Get the slot bet.
/// </summary>
/// <returns>Slot bet as int.</returns>
int SlotAndBet::getBet()const{
	return _bet;
}