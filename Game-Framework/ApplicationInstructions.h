#ifndef APPLICATION_INSTRUCTIONS_H
#define APPLICATION_INSTRUCTIONS_H


#include "Menu.h"
#include "utils.h"
#include <string>
using std::cin;
using std::cerr;
#include <new>
using std::bad_alloc;

class ApplicationInstructions{

private:
	int bankroll;
	int rounds;
	Menu* menu;
	vector<string> applicationMenuItems;
	enum MenuEnum{ ERROR, BANKROLL, ROUNDS, PLAY_GAME, END };

	void initialize();
	void setMenu();
	void createGameMenu();
	void displayMenu();
	bool setBankroll();
	bool setNumberOfRounds();
public:
	
	ApplicationInstructions();
	~ApplicationInstructions();
	bool canPlayGame()const;
	int gatherData();
	int getBankroll()const;
	int getNumberOfRounds()const;
};

#endif // !APPLICATION_INSTRUCTIONS_H
