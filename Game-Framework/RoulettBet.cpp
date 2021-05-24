#include "RoulettBet.h"

RoulettBet::RoulettBet(int betAmount, int slotColour, vector<int> *slots) :_betAmount(betAmount), _slotColour(slotColour), _slots(slots){
}
RoulettBet::RoulettBet(int betAmount, vector<int>* slots) : RoulettBet(betAmount, 0, nullptr){
}

RoulettBet::RoulettBet(int betAmount, int slotColour): RoulettBet(betAmount, slotColour, nullptr){
}

RoulettBet::~RoulettBet(){
	delete _slots;
}

void RoulettBet::setSlot(int slotNr){
	_slots->push_back(slotNr);
}

void RoulettBet::setSlotColour(int slotColour){
	_slotColour = slotColour;
}

void RoulettBet::setAmount(int betAmount){
	_betAmount = betAmount;
}

vector<int> *RoulettBet::getSlots()const{
	return _slots;
}

int RoulettBet::getSlotColour()const{
	return _slotColour;
}

int RoulettBet::getAmount()const{
	return _betAmount;
}