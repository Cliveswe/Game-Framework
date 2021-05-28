/**
* Author: Clive Leddy
* File: RoulettePlayer.h
* Date: 2021-04-13
* Summary:
* European Roulette with inside bets only.
* This class is an interface between the user and the game Roulette. The user is asked to select one or
* more slots and to bet on each slot. This class makes use of a class SlotAndBet and RouletteBet when
* passing all bets to the class RouletteGame. By using both SlotAndBet and RouletteBet classes we can cast
* the class RouletteBet to char* and avoid slicing when programming to a base class. The method play(int)
* is the entry point of this class. The user will play a number of rounds of Roulette or as long as the
* player has money to bet with.
* The players bankroll is reduced with every bet the player places on a slot. When the player is done betting
* all his bets are sent to the RouletteGame class as a gamble. If the gamble pays off the winnings are 
* returned to the player and in turn used to update the players bankroll.
* If the players bankroll becomes empty the player cannot place any more bets even if there are rounds to play. 
* Thus the game ends for the player.
*/
#ifndef ROULETTEPLAYER_H
#define ROULETTEPLAYER_H

#include "IPlayer.h"
#include "RouletteGame.h"
#include "Utils.h"
#include "RouletteBet.h"
#include "SlotAndBet.h"
#include <new>
using std::bad_alloc;
using std::cerr;
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <iostream>
#include <algorithm>
using std::find;

/// <summary>
/// This class implements the virtual class IPlayer and is used to hot swap games in the application.
/// This class is an interface between the user and the game Roulette. The user is asked to select one 
/// or more slots and to bet on each slot. This class makes use of a class SlotAndBet and RouletteBet when
/// passing all bets to the class RouletteGame. By using both SlotAndBet and RouletteBet classes we can cast
/// the class RouletteBet to char* and avoid slicing when programming to a base class.
/// The method play(int) is the entry point of this class. However, all the heavy lifting is performed 
/// by the method getBet().
/// <inheritdoc/>
/// </summary>
class RoulettePlayer : public IPlayer{
private:

	IGame* _game;
	int _bankroll;
	int _betCount;

	Menu* menuPlayer;
	vector<string> rouletteMenuItems;
	enum rouletteMenuEnum{ ERROR, CHOOSE_NUMBERS, CHOOSE_COLOUR, END };

	/// <summary>
	/// Initialize the class. Create and set the menu for the Roulette player.
	/// </summary>
	void initialize();
	
	/// <summary>
	/// A new bet has been placed. Reduce the bankroll with the bet amount.
	/// </summary>
	/// <param name="betAmount">A bet as type int.</param>
	void newBet(const int);
	
	/// <summary>
	/// Create the menu instance for the Roulette player.
	/// </summary>
	void createRouletteMenu();
	
	/// <summary>
	/// Add the menu text to the Roulette player menu.
	/// </summary>
	void setMenu();
	
	/// <summary>
	/// Get a slot number and bet amount from the user. Check to make sure that the slot number and bet are valid.
	/// If not display a message informing that either the slot or bet is not valid and that the user should try
	/// again.
	/// </summary>
	/// <param name="slot">A slot as type int*.</param>
	/// <param name="bet">A bet on a slot as type int*.</param>
	/// <returns>True if both the slot and bet are valid otherwise false.</returns>
	bool setSlots(int*, int*);
	
	/// <summary>
	/// Validate that a given number is within the 0 to 36 range of slots.
	/// </summary>
	/// <param name="number">A number as type const int.</param>
	/// <returns>True if the number is within range otherwise false.</returns>
	bool isSlotNumberValid(const int)const;
	
	/// <summary>
	/// Ask the player to a slot colour. Red is 0 and black is 1.
	/// </summary>
	/// <returns>The slot colour RouletteGame::BLACK or RouletteGame::RED as type int.</returns>
	int setSlotColour();
	
	/// <summary>
	/// Ask the player to place a bet on a slot colour. The bet entered must be greater that 0.
	/// </summary>
	/// <returns>The bet  as type int.</returns>
	int setColourBetAmount();
	
	/// <summary>
	/// Update the bankroll.
	/// </summary>
	/// <param name="payout">Potential winnings as type int.</param>
	void updateBankroll(int);
	
	/// <summary>
	/// Initialise the bankroll. In other words the initial amount of money the player has to bet with.
	/// </summary>
	/// <param name="bankroll">Money as type int.</param>
	void setBankroll(int);
	
	/// <summary>
	/// This is the class workhorse. First display a menu on the different types of betting. The player can place 
	/// several bets per round. The player can choose to place several bet on different slots and / or one of two 
	/// slot colours, black, red. Each bet on a slot is a "inside bet" in European Roulette.
	/// </summary>
	/// <returns>All the slots with bets on them as type RouletteBet*.</returns>
	RouletteBet* getBet();
	
	/// <summary>
	/// Display all the bets the player has made thus far.
	/// </summary>
	/// <param name="tempSlots">A temporary container of all the bets thus far as type vector<SlotAndBet>*.</param>
	/// <param name="slotColour">A slot colour as type int.</param>
	/// <param name="colourBet">The bet on a slot colour as type int.</param>
	void displayBetStatus(vector<SlotAndBet>* tempSlots, int slotColour, int colourBet)const;
	
	/// <summary>
	/// Check to make sure that the player is not betting on the same slot multiple time.
	/// </summary>
	/// <param name="slots">All the bets made as type vector<SlotAndBet>*.</param>
	/// <param name="element">A new slot with bet pair as type SlotAndBet*.</param>
	/// <returns>True if the element could be added to the container of bets other wise false.</returns>
	bool hasBet(vector<SlotAndBet>*, SlotAndBet*)const;
	
	/// <summary>
	/// Validate that the given amount can be subtracted from the bankroll.
	/// </summary>
	/// <param name="amount">A bet as type const int.</param>
	/// <returns></returns>
	bool isSlotBetAmountValid(const int)const;

	/// <summary>
	/// Update tempSlots and slots with slot and slotBet from the referenced parameters slot and slotBet. 
	/// However, the updates will only occur if the player has enough money and that the slots, 0 to 36,
	/// red or black are valid.
	/// </summary>
	/// <param name="tempSlots">Reference to a container holding all the bets as type vector<SlotAndBet>*.</param>
	/// <param name="slots">A reference to a slot and bet pair as type SlotAndBet*.</param>
	/// <param name="slot">Reference to a slot as type int&.</param>
	/// <param name="slotBet">Reference to a slot bet as type int&.</param>
	void chooseNunbers(vector<SlotAndBet>*, SlotAndBet*, int&, int&);

	/// <summary>
	/// Make a not on the number of rounds the game has been played.
	/// </summary>
	/// <param name="rounds">Round number as type int.</param>
	void setNumberOfRounds(int);

public:
	/// <summary>
	/// Class constructor that initialises the class.
	/// </summary>
	/// <param name="bankroll">The original amount of money the play has to bet with as type int.</param>
	RoulettePlayer(int);
	
	/// <summary>
	/// Class destructor.
	/// </summary>
	~RoulettePlayer();
	
	/// <summary>
	/// Set an instance of the Roulette game. This is the game the player will use to determine winnings on bets.
	/// </summary>
	/// <param name="game">The Roulette game used in this instance as type IGame*.</param>
	/// <returns>True if a valid Roulette game is given other wise false.</returns>
	bool setGame(IGame* game);// Gives the player a game object to use
	
	/// <summary>
	/// The entry point of the Roulette player. Show a menu and the number of rounds played. The player will 
	/// play at most an maximum number of times. As long as the player has money (bankroll) to bet with. If 
	/// the player wins then the winnings are added to the players bankroll.
	/// </summary>
	/// <param name="numberOfTimes">Then maximum number of time the Roulette player will place bets.</param>
	/// <returns>True if the player played all of the rounds other wise false.</returns>
	bool play(int numberOfTimes);// Tells player to play the game numberOfTimes times
	
	/// <summary>
	/// Get the current sum of the bankroll.
	/// </summary>
	/// <returns>The sum of the bankroll as type int.</returns>
	int getMoney() const;// Returns the amount of player's money
	
	/// <summary>
	/// Get the current round of betting.
	/// </summary>
	/// <returns>A number of rounds as type int.</returns>
	int getBetCount() const;// Returns the total number of bets placed during object life time
	
	/// <summary>
	/// Validate that the bankroll has funds.
	/// </summary>
	/// <returns>True if the bankroll is greater than 0 otherwise false.</returns>
	bool canPlaceBet()const;

	/// <summary>
	/// Display the instructions menu with delimiters.
	/// </summary>
	void displayInstructions()const;
	
	/// <summary>
	/// Display a header for the Roulette player.
	/// </summary>
	void displayHeader()const;
};

#endif // !ROULETTEPLAYER_H