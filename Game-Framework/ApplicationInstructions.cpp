#include "ApplicationInstructions.h"

ApplicationInstructions::ApplicationInstructions() : bankroll(0), rounds(0){
	menu = nullptr;

	applicationMenuItems = {"Incorrect menu choice!",
		"Enter the players bankroll.",
		"Enter the total number of rounds to play.",
		"Play the game then display your results.",
		"End the program."
	};

	initialize();
}

ApplicationInstructions::~ApplicationInstructions(){
	applicationMenuItems.clear();
	delete menu;
}

void ApplicationInstructions::initialize(){

	createGameMenu();
	setMenu();
}

void ApplicationInstructions::createGameMenu(){

	try{

		menu = new Menu();

	} catch(bad_alloc ba){

		cerr << "bad_alloc caught: " << ba.what() << endl;
	}
}

void ApplicationInstructions::setMenu(){

	menu->setTitle("Roulette");
	menu->setPrompt("Enter your choice: ");
	menu->setMenuItemsTitle("In order to play the game, menu item 3, you first must enter data in menu items 1 & 2!");
	menu->addMenuItem(applicationMenuItems[BANKROLL]);
	menu->addMenuItem(applicationMenuItems[ROUNDS]);
	menu->addMenuItem(applicationMenuItems[PLAY_GAME]);
	menu->addMenuItem(applicationMenuItems[END]);
}

int ApplicationInstructions::gatherData(){
	int choice = 0;
	bool ans = false;
	string prompt = menu->getPrompt();
	const char* errMsg = applicationMenuItems[ERROR].c_str();
	const char* msg = prompt.c_str();

	displayMenu();

	choice = Utils::getInputInt(prompt.c_str(), errMsg);

	switch(choice){
		case BANKROLL:
			ans = setBankroll();
			break;
		case ROUNDS:
			ans = setNumberOfRounds();
			break;
		case PLAY_GAME:
			if(canPlayGame()){
				return 0;
			} else{
				cout << "Both the bankroll and number of rounds must be entered before a game can be played." << endl;
			}
			break;
		case END:
			return 1;
			break;
		default:
			ans = false;
			break;
	}
	if(!ans){
		cerr << "The value you entered is not valid. Try again." << endl << endl;
	}

	return -1;
}

bool ApplicationInstructions::canPlayGame()const{
	int lines = 15;

	if(!(getNumberOfRounds() > 0)){
		system("CLS");
		cout << applicationMenuItems[ROUNDS] << endl;
		return false;
	}

	if(!(getBankroll() > 0)){
		system("CLS");
		cout << applicationMenuItems[BANKROLL] << endl;
		return false;
	}

	return true;
}

void ApplicationInstructions::displayMenu(){

	menu->displayMenu('-', '-');
}

int ApplicationInstructions::getBankroll()const{
	return bankroll;
}

bool ApplicationInstructions::setBankroll(){
	const char* msg = "Enter bankroll (example 123): ";
	const char* errMsg = "\nIncorrect input! Try again.";
	
	cout << msg;
	bankroll = Utils::getInputInt(msg, errMsg);
	
	if(bankroll > 0){

		return true;
	}

	return false;
}

int ApplicationInstructions::getNumberOfRounds()const{
	return rounds;
}

bool ApplicationInstructions::setNumberOfRounds(){
	const char *msg= "Number of rounds to play: ";
	const char* errMsg = "\nUnrecognised number of rounds! Try again.";

	cout << msg;
	rounds = Utils::getInputInt(msg, errMsg);

	if(rounds > 0){

		return true;
	}

	return false;
}

