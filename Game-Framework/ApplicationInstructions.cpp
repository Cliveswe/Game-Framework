/*
* Name: Clive Leddy
* File: ApplicationInstructions.cpp
* Date: 2021-05-15
*
* Summary:
* Gather data from the user. Start by displaying a menu of choices and prompt for a choice. Thus set the
* games bankroll and the number of rounds the game will be played. After a valid choice has been selected
* it is then executed.
*/

#include "ApplicationInstructions.h"

/// <summary>
/// Class constructor. Initialises the class fields bankroll and rounds to 0.
/// </summary>
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

/// <summary>
/// Class destructor.
/// </summary>
ApplicationInstructions::~ApplicationInstructions(){
	applicationMenuItems.clear();
	delete menu;
}

/// <summary>
/// Initialise the class by creating and populating a menu.
/// </summary>
void ApplicationInstructions::initialize(){

	createGameMenu();
	setMenu();
}

/// <summary>
/// Create a new menu.
/// </summary>
void ApplicationInstructions::createGameMenu(){

	try{

		menu = new Menu();

	} catch(bad_alloc ba){

		cerr << "bad_alloc caught: " << ba.what() << endl;
	}
}

/// <summary>
/// Populate the menu.
/// </summary>
void ApplicationInstructions::setMenu(){

	menu->setTitle("Game");
	menu->setPrompt("Enter your choice: ");
	menu->setMenuItemsTitle("In order to play the game, menu item 3, you first must enter data in menu items 1 & 2!");
	menu->addMenuItem(applicationMenuItems[BANKROLL]);
	menu->addMenuItem(applicationMenuItems[ROUNDS]);
	menu->addMenuItem(applicationMenuItems[PLAY_GAME]);
	menu->addMenuItem(applicationMenuItems[END]);
}

/// <summary>
/// Gather data from the user. Start by displaying a menu of choices and prompt for a choice. After a valid 
/// choice has been selected it is then executed.
/// </summary>
/// <returns>1 end the game, -1 ask for a new choice, 0 to continue as type int.</returns>
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

/// <summary>
/// Check if the entered data is valid to play a game of Roulette.
/// </summary>
/// <returns>True if can play a game otherwise false.</returns>
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

/// <summary>
/// Display the menu with delimiters.
/// </summary>
void ApplicationInstructions::displayMenu(){

	menu->displayMenu('-', '-');
}

/// <summary>
/// Get the current bankroll.
/// </summary>
/// <returns>The bankroll as type int.</returns>
int ApplicationInstructions::getBankroll()const{
	return bankroll;
}

/// <summary>
/// Set the bankroll by requesting a sum to be entered by the user.
/// </summary>
/// <returns>True if the entered sum is positive otherwise false.</returns>
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

/// <summary>
/// Get the number of rounds to play in this game.
/// </summary>
/// <returns>The number of rounds to play as type int.</returns>
int ApplicationInstructions::getNumberOfRounds()const{
	return rounds;
}

/// <summary>
/// Set the number of rounds by requesting the number of rounds to play by the user.
/// Note: There is no upper limit on how many rounds a game should have!
/// </summary>
/// <returns>True if the entered sum is positive otherwise false.</returns>
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

