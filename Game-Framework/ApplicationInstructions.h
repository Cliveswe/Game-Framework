/*
* Name: Clive Leddy
* File: ApplicationInstructions.h
* Date: 2021-05-15
*
* Summary:
* Gather data from the user. Start by displaying a menu of choices and prompt for a choice. Thus set the 
* games bankroll and the number of rounds the game will be played. After a valid choice has been selected 
* it is then executed.
*/
#ifndef APPLICATION_INSTRUCTIONS_H
#define APPLICATION_INSTRUCTIONS_H


#include "Menu.h"
#include "utils.h"
#include <string>
using std::cin;
using std::cerr;
#include <new>
using std::bad_alloc;

/// <summary>
/// Gather data from the user. Start by displaying a menu of choices and prompt for a choice. Thus set the 
/// games bankroll and the number of rounds the game will be played. After a valid choice has been selected 
/// it is then executed.
/// </summary>
class ApplicationInstructions{

private:
	int bankroll;
	int rounds;
	Menu* menu;
	//Manage the menu items before they are added to the menu.
	vector<string> applicationMenuItems;
	enum MenuEnum{ ERROR, BANKROLL, ROUNDS, PLAY_GAME, END };

	/// <summary>
	/// Initialise the class by creating and populating a menu.
	/// </summary>
	void initialize();
	
	/// <summary>
	/// Populate the menu.
	/// </summary>
	void setMenu();
	
	/// <summary>
	/// Create a new menu.
	/// </summary>
	void createGameMenu();
	
	/// <summary>
	/// Display the menu with delimiters.
	/// </summary>
	void displayMenu();
	
	/// <summary>
	/// Set the bankroll by requesting a sum to be entered by the user.
	/// </summary>
	/// <returns>True if the entered sum is positive otherwise false.</returns>
	bool setBankroll();

	/// <summary>
	/// Set the number of rounds by requesting the number of rounds to play by the user.
	/// Note: There is no upper limit on how many rounds a game should have!
	/// </summary>
	/// <returns>True if the entered sum is positive otherwise false.</returns>
	bool setNumberOfRounds();
public:
	
	/// <summary>
	/// Class constructor. Initialises the class fields bankroll and rounds to 0.
	/// </summary>
	ApplicationInstructions();
	
	/// <summary>
	/// Class destructor.
	/// </summary>
	~ApplicationInstructions();
	
	/// <summary>
	/// Check if the entered data is valid to play a game of Roulette.
	/// </summary>
	/// <returns>True if can play a game otherwise false.</returns>
	bool canPlayGame()const;
	
	/// <summary>
	/// Gather data from the user. Start by displaying a menu of choices and prompt for a choice. After a valid 
	/// choice has been selected it is then executed.
	/// </summary>
	/// <returns>1 end the game, -1 as for a new choice, 0 to continue as type int.</returns>
	int gatherData();
	
	/// <summary>
	/// Get the current bankroll.
	/// </summary>
	/// <returns>The bankroll as type int.</returns>
	int getBankroll()const;
	
	/// <summary>
	/// Get the number of rounds to play in this game.
	/// </summary>
	/// <returns>The number of rounds to play as type int.</returns>
	int getNumberOfRounds()const;
};

#endif // !APPLICATION_INSTRUCTIONS_H
