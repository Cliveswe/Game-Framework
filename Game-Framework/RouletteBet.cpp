/*
* Name: Clive Leddy
* File: RouletteBet.cpp
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
#include "RouletteBet.h"

/// <summary>
/// Class constructor.
/// </summary>
/// <param name="betAmount">Set a bet on a slot colour as type int.</param>
/// <param name="slotColour">Set a selected slot colour as type int.</param>
/// <param name="slots">Add a list of bets on a variety of slots as type vector<SlotAndBet>*.</param>
RouletteBet::RouletteBet(int betAmount, int slotColour, vector<SlotAndBet>* slots) :
	_betAmount(betAmount), _slotColour(slotColour), _slots(slots){
}

/// <summary>
/// Class constructor that creates an instance of the class that is empty.
/// </summary>
RouletteBet::RouletteBet() : RouletteBet(0, 0, NULL){ }

/// <summary>
/// Class destructor.
/// </summary>
RouletteBet::~RouletteBet(){
	_slots->clear();
	delete _slots;
}

/// <summary>
/// Get the list of slots and bet per slot.
/// </summary>
/// <returns>Add a list of bets on a variety of slots as type vector<SlotAndBet>*.</returns>
vector<SlotAndBet>* RouletteBet::getSlots()const{
	return _slots;
}

/// <summary>
/// Get a bet that was placed on a slot.
/// </summary>
/// <param name="slotNr">The slot as type int.</param>
/// <returns>If the requested slot is found return the bet otherwise return 0, as type int.</returns>
int RouletteBet::getSlotBet(int slotNr)const{

	//Iterate through the list of bets per slot.
	for(vector<SlotAndBet>::iterator it = _slots->begin(); it < _slots->end(); it++){

		if(slotNr == it->getSlot()){//Find the requested slot.

			return it->getBet();
		}
	}

	return 0;
}

/// <summary>
/// Get the colour of the slot.
/// </summary>
/// <returns>The slot colour as type int.</returns>
int RouletteBet::getSlotColour()const{
	return _slotColour;
}

/// <summary>
/// Get the bet that was placed on the slot colour.
/// </summary>
/// <returns>The bet placed on the slot colour as type int.</returns>
int RouletteBet::getSlotColourAmount()const{
	return _betAmount;
}

/// <summary>
/// Is there any slots with bets.
/// </summary>
/// <returns>True if there is a list of slots otherwise false.</returns>
bool RouletteBet::hasSlots()const{

	if((_slots != NULL) && !_slots->empty()){//There is a list of slots with bets.

		return true;
	}
	return false;
}

/// <summary>
/// Get the total sum of bet on all the slots.
/// </summary>
/// <returns>The bet total as type int.</returns>
int RouletteBet::getBetTotal()const{
	int res = 0;

	if(getSlotColourAmount() != 0){//Add the bet on a slot colour.
	
		res += getSlotColourAmount();
	}

	if(hasSlots()){//Sum up all the bets on the slots.

		//Iterate through the list of bets per slot.
		for(vector<SlotAndBet>::iterator it = _slots->begin(); it < _slots->end(); it++){
			
			res += it->getBet();
		}
	}

	return res;
}

/// <summary>
/// Format the class data for printing. Think of this method as a toSting() method in for example Java.
/// This a overloaded operator "<<".
/// </summary>
/// <param name="os">The stream to write to as type iostream.</param>
/// <param name="rb">The source to display as type RouletteBet*.</param>
/// <returns>A stream of type ostream.</returns>
ostream& operator<<(ostream& os, const RouletteBet* rb){
	const int WIDTH = 3;

	os << "Bets per slot!" << endl;

	if(rb != NULL){

		if(rb->hasSlots()){

			//Iterate through the list of bets per slot.
			for(vector<SlotAndBet>::iterator it = rb->getSlots()->begin(); it < rb->getSlots()->end(); it++){

				os << "slot " << setw(WIDTH) << it->getSlot() << " bet " << setw(WIDTH) << it->getBet() << endl;
			}
		}
		//The slot colour has a bet.
		if((rb->getSlotColour() != 0) && (rb->getSlotColourAmount() > 0)){

			os << "slot colour: ";

			if(rb->getSlotColour() == RouletteGame::RED){//The slot colour is RED.

				os << "RED";

			} else if(rb->getSlotColour() == RouletteGame::BLACK){//The slot colour is BLACK.

				os << "BLACK";
			}

			os << " bet: " << rb->getSlotColourAmount() << " SEK." << endl;
		}

		os << "Total bet: " << rb->getBetTotal() << " SEK." << endl;

	} else{

		os << "No bets placed!" << endl;
	}


	return os;
}