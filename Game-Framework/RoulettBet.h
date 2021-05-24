#ifndef ROULETT_BET_H
#define ROULETT_BET_H

#include <string>
using std::string;
#include <vector>
using std::vector;

class RoulettBet{
private:
	vector<int> *_slots;
	int _slotColour;
	int _betAmount;

public:
	
	RoulettBet(int, int , vector<int>*);
	RoulettBet(int, vector<int>*);
	RoulettBet(int, int);
	~RoulettBet();
	void setSlot(int);
	void setSlotColour(int);
	void setAmount(int);
	vector<int> *getSlots()const;
	int getSlotColour()const;
	int getAmount()const;
};


#endif // !ROULETT_BET_H