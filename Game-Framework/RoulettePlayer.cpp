/**
* Author: Clive Leddy
* File: RoulettePlayer.cpp
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
#include "RoulettePlayer.h"

/// <summary>
/// Class constructor that initialises the class.
/// </summary>
/// <param name="bankroll">The original amount of money the play has to bet with as type int.</param>
RoulettePlayer::RoulettePlayer(int bankroll) : _bankroll(bankroll), _betCount(0){

	_game = nullptr;
	menuPlayer = nullptr;

	rouletteMenuItems = {"Incorrect menu choice!",
		"Choose a number you want to bet on. You may repeat this step to add additional slots to bet on.",
		"Alternatively, you can choose the colour RED or BLACK instead of a number you want to bet on.",
		"Place bet."
	};

	initialize();
}

/// <summary>
/// Class destructor.
/// </summary>
RoulettePlayer::~RoulettePlayer(){
	delete menuPlayer;

	if(_game != nullptr){
		delete _game;
		_game = nullptr;

	} else{

		_game = nullptr;
	}

	if(!rouletteMenuItems.empty()){
		rouletteMenuItems.clear();
	}
}

/// <summary>
/// Initialize the class. Create and set the menu for the Roulette player.
/// </summary>
void RoulettePlayer::initialize(){

	createRouletteMenu();
	setMenu();
}

/// <summary>
/// Create the menu instance for the Roulette player.
/// </summary>
void RoulettePlayer::createRouletteMenu(){

	try{

		menuPlayer = new Menu();

	} catch(bad_alloc ba){

		cerr << "bad_alloc caught: " << ba.what() << endl;
	}
}

/// <summary>
/// Add the menu text to the Roulette player menu.
/// </summary>
void RoulettePlayer::setMenu(){

	menuPlayer->setTitle("Place you're bets!");
	menuPlayer->setPrompt("Enter your choice: ");
	menuPlayer->setMenuItemsTitle("HOW TO PLAY ROULETTE - STEP BY STEP.");
	menuPlayer->addMenuItem(rouletteMenuItems[CHOOSE_NUMBERS]);
	menuPlayer->addMenuItem(rouletteMenuItems[CHOOSE_COLOUR]);
	menuPlayer->addMenuItem(rouletteMenuItems[END]);
}

/// <summary>
/// A new bet has been placed. Reduce the bankroll with the bet amount.
/// </summary>
/// <param name="betAmount">A bet as type int.</param>
void RoulettePlayer::newBet(const int betAmount){

	_bankroll -= betAmount;
}

/// <summary>
/// Set an instance of the Roulette game. This is the game the player will use to determine winnings on bets.
/// </summary>
/// <param name="game">The Roulette game used in this instance as type IGame*.</param>
/// <returns>True if a valid Roulette game is given other wise false.</returns>
bool RoulettePlayer::setGame(IGame* game){

	if(game != nullptr){

		//Validate the game ID with a acceptable Roulette game.
		if(game->getID() != RouletteGame::getRouletteID()){

			return false;
		}

		_game = game;

		return true;
	}

	return false;
}

/// <summary>
/// The entry point of the Roulette player. Show a menu and the number of rounds played. The player will 
/// play at most an maximum number of times. As long as the player has money (bankroll) to bet with. If 
/// the player wins then the winnings are added to the players bankroll.
/// </summary>
/// <param name="numberOfTimes">Then maximum number of time the Roulette player will place bets.</param>
/// <returns>True if the player played all of the rounds other wise false.</returns>
bool RoulettePlayer::play(int numberOfTimes){
	RouletteBet* rb;//Container containing all of the bets the play makes.
	int payout = 0;//The players winnings.

	displayHeader();
	//Play a round.
	for(int index = 0; index < numberOfTimes; index++){

		setNumberOfRounds(index);//Make a note on how many rounds have been played.

		cout << endl << "\nRound " << index + 1 << " of " << numberOfTimes << "." << endl;

		rb = getBet();//Get all of the players bets.

		//All bets are sent to the Roulette game. The winnings, if any, are saved in the variable payout.
		payout = _game->play((char*)rb, rb->getBetTotal());
		cout << endl;

		if(payout > 0){//Display winnings.

			cout << endl << "->>> Winner <<<-" << endl;
			cout << "Your bankroll was currently " << getMoney() << " SEK." << endl;
			cout << "Your payout is " << payout << " SEK." << endl;

			updateBankroll(payout);

			cout << "Your bankroll is now " << getMoney() << " SEK." << endl;
		} else{

			cout << endl << "No payout in this round." << endl;
			cout << "Your bankroll is currently " << getMoney() << " SEK." << endl;
		}

		if(getMoney() <= 0){//End the game if the player has no money.
			return false;
		}
	}

	return true;
}

/// <summary>
/// Make a not on the number of rounds the game has been played.
/// </summary>
/// <param name="rounds">Round number as type int.</param>
void RoulettePlayer::setNumberOfRounds(int rounds){
	_betCount = rounds + 1;
}

/// <summary>
/// Initialise the bankroll. In other words the initial amount of money the player has to bet with.
/// </summary>
/// <param name="bankroll">Money as type int.</param>
void RoulettePlayer::setBankroll(const int bankroll){

	_bankroll = bankroll;
}

/// <summary>
/// Update the bankroll.
/// </summary>
/// <param name="payout">Potential winnings as type int.</param>
void RoulettePlayer::updateBankroll(const int payout){

	setBankroll(getMoney() + payout);
}

/// <summary>
/// This is the class workhorse. First display a menu on the different types of betting. The player can place 
/// several bets per round. The player can choose to place several bet on different slots and / or one of two 
/// slot colours, black, red. Each bet on a slot is a "inside bet" in European Roulette.
/// </summary>
/// <returns>All the slots with bets on them as type RouletteBet*.</returns>
RouletteBet* RoulettePlayer::getBet(){
	int choice = -1;
	bool ans = false;
	RouletteBet* rb = new RouletteBet();
	SlotAndBet* slots = nullptr;
	vector<SlotAndBet>* tempSlots = new vector<SlotAndBet>();
	int slotColour = -1;
	int colourBet = 0;
	int slot = 0;
	int slotBet = 0;

	do{
		displayInstructions();//Betting instruction per slot type.

		choice = Utils::getInputInt(menuPlayer->getPrompt().c_str(), "Please choose a valid menu option!");
		try{
			switch(choice){
				case CHOOSE_NUMBERS://Inside betting, bet on a single slot.

					if(setSlots(&slot, &slotBet)){//Get slot (0 -- 36) and a bet.

						//Update tempSlots and slots with slot and slotBet if the are valid.
						chooseNunbers(tempSlots, slots, slot, slotBet);

					} else{

						cout << "Previous bet, slot " << slot << " and slot bet " << slotBet << " SEK." << endl;
					}

					//Remind the player on what slots they have betted on.
					displayBetStatus(tempSlots, slotColour, colourBet);
					break;
				case CHOOSE_COLOUR://Bet on a slot colour, red or black.

					if(canPlaceBet()){//The player has enough money to place a bet.

						//Get the slot colour and bet.
						slotColour = setSlotColour();
						colourBet = setColourBetAmount();

						//Make sure that the player only bets with what the can afford.
						if(getMoney() >= colourBet){

							newBet(colourBet);//Make note that a new bet has been made.
						} else{

							cout << "Previous bet, " << slotColour << " and slot bet " << slotBet << " SEK." << endl;

							slotColour = -1;
							slotBet = 0;
						}

					} else{
						cerr << "Your bankroll is empty!" << endl;
					}

					//Remind the player on what slots they have betted on.
					displayBetStatus(tempSlots, slotColour, colourBet);
					break;
				case END:

					rb = new RouletteBet(colourBet, slotColour, tempSlots);
					ans = true;

					break;
				default:
					cout << rouletteMenuItems[ERROR] << endl;
					cout << "Try again!" << endl;
					break;
			}
		} catch(bad_alloc ba){

			cerr << "Fatal error creating SlotAndBet object: " << ba.what() << endl;
			exit(1);
		}

	} while(!ans);

	return rb;
}

/// <summary>
/// Display all the bets the player has made thus far.
/// </summary>
/// <param name="tempSlots">A temporary container of all the bets thus far as type vector<SlotAndBet>*.</param>
/// <param name="slotColour">A slot colour as type int.</param>
/// <param name="colourBet">The bet on a slot colour as type int.</param>
void RoulettePlayer::displayBetStatus(vector<SlotAndBet>* tempSlots, int slotColour, int colourBet)const{
	const int WIDTH = 3;

	cout << endl << "You're bankroll is " << getMoney() << " SEK" << endl;

	if(slotColour >= 0){

		cout << "Slot colour ";

		if(slotColour == RouletteGame::BLACK){

			cout << " black";
		}

		if(slotColour == RouletteGame::RED){

			cout << " red";
		}

		cout << " bet " << colourBet << " SEK" << endl;
	}

	//Iterator through all the inside slot bets and display them.
	for(vector<SlotAndBet>::iterator it = tempSlots->begin(); it < tempSlots->end(); it++){

		cout << "Slot " << setw(WIDTH) << it->getSlot() << " bet " << setw(WIDTH) << it->getBet() << " SEK." << endl;
	}


}

/// <summary>
/// Update tempSlots and slots with slot and slotBet from the referenced parameters slot and slotBet. 
/// However, the updates will only occur if the player has enough money and that the slots, 0 to 36,
/// red or black are valid.
/// </summary>
/// <param name="tempSlots">Reference to a container holding all the bets as type vector<SlotAndBet>*.</param>
/// <param name="slots">A reference to a slot and bet pair as type SlotAndBet*.</param>
/// <param name="slot">Reference to a slot as type int&.</param>
/// <param name="slotBet">Reference to a slot bet as type int&.</param>
void RoulettePlayer::chooseNunbers(vector<SlotAndBet>* tempSlots, SlotAndBet* slots, int& slot, int& slotBet){

	try{
		slots = new SlotAndBet(slot, slotBet);//Update slots with a new instance of SlotAndBet pair.

		//Make sure that the bet can be made.
		if(canPlaceBet() && (getMoney() >= slotBet)){

			if(!hasBet(tempSlots, slots)){//Make sure that no duplicate bets are made.

				newBet(slotBet);//A new bet has been made, update the class.
				tempSlots->push_back(*slots);//Add the bet to the container of bets.

			} else{

				cout << "You have already placed a bet on slot " << slot << "!" << endl;
			}

		} else{

			cout << "Bet rejected!" << endl;
			cout << "Your bankroll is " << getMoney() << " SEK" << endl;
		}
	} catch(bad_alloc ba){

		cerr << "Fatal error creating SlotAndBet object: " << ba.what();
		exit(1);
	}
}

/// <summary>
/// Check to make sure that the player is not betting on the same slot multiple time.
/// </summary>
/// <param name="slots">All the bets made as type vector<SlotAndBet>*.</param>
/// <param name="element">A new slot with bet pair as type SlotAndBet*.</param>
/// <returns>True if the element could be added to the container of bets other wise false.</returns>
bool RoulettePlayer::hasBet(vector<SlotAndBet>* slots, SlotAndBet* element)const{

	//Iterator through all the inside slot bets.
	for(vector<SlotAndBet>::iterator it = slots->begin(); it < slots->end(); it++){

		if(it->getSlot() == element->getSlot()){//Check for duplicates.

			return true;
		}
	}

	return false;
}

/// <summary>
/// Ask the player to place a bet on a slot colour. The bet entered must be greater that 0.
/// </summary>
/// <returns>The bet  as type int.</returns>
int RoulettePlayer::setColourBetAmount(){
	string* helper = new string("Enter the amount to bet on RED or BLACK.");
	string* msg = new string("Enter amount to bet: ");
	string* errMsg = new string("Not a valid bet!");
	int res = -1;

	cout << *helper << endl;

	do{

		cout << *msg;
		res = Utils::getInputInt(msg->c_str(), errMsg->c_str());

		if(res > 0){

			break;

		} else{

			cout << *errMsg << endl;
			res = -1;
		}

	} while(true);

	return res;
}

/// <summary>
/// Ask the player to a slot colour. Red is 0 and black is 1.
/// </summary>
/// <returns>The slot colour RouletteGame::BLACK or RouletteGame::RED as type int.</returns>
int RoulettePlayer::setSlotColour(){
	string* msg = new string("Select a colour (0 = red and 1 = black)? ");
	string* errMsg = new string("Not a valid selection!");
	int res = -1;

	do{

		cout << *msg;
		res = Utils::getInputInt(msg->c_str(), errMsg->c_str());

		if(res == 0){

			res = RouletteGame::RED;
			break;

		} else if(res == 1){

			res = RouletteGame::BLACK;
			break;

		} else{

			cout << *errMsg << endl;
			res = -1;
		}

	} while(true);

	return res;
}

/// <summary>
/// Get a slot number and bet amount from the user. Check to make sure that the slot number and bet are valid.
/// If not display a message informing that either the slot or bet is not valid and that the user should try
/// again.
/// </summary>
/// <param name="slot">A slot as type int*.</param>
/// <param name="bet">A bet on a slot as type int*.</param>
/// <returns>True if both the slot and bet are valid otherwise false.</returns>
bool RoulettePlayer::setSlots(int* slot, int* bet){
	string* slotMsg = new string("Enter a number from 0 to 36: ");
	string* slotBetMsg = new string("Enter bet for slot: ");
	string* errMsg = new string("Not a valid number!");

	if(!canPlaceBet()){//Does not have enough funds in the bankroll.

		cout << "Your bankroll is empty!" << endl;
		return false;
	}

	cout << *slotMsg;
	*slot = Utils::getInputInt(slotMsg->c_str(), errMsg->c_str());

	if(isSlotNumberValid(*slot)){//The entered slot number was not in the 0 to 36 range.

		cout << *slotBetMsg;
		*bet = Utils::getInputInt(slotBetMsg->c_str(), errMsg->c_str());

		if(isSlotBetAmountValid(*bet)){//Check if the bet does not exceed the current bankroll amount.

			return true;

		} else{

			cout << "Your bet =  " << *bet << " SEK is too big. Your bankroll is " << getMoney() << " SEK" << endl;
		}
	} else{

		cerr << "Invalid slot! " << *slot << endl;
	}

	return false;
}

/// <summary>
/// Validate that a given number is within the 0 to 36 range of slots.
/// </summary>
/// <param name="number">A number as type const int.</param>
/// <returns>True if the number is within range otherwise false.</returns>
bool RoulettePlayer::isSlotNumberValid(const int number)const{
	
	if((number >= RouletteGame::LOWEST_SLOT) &&
		(number <= RouletteGame::HIGHEST_SLOT)){
	
		return true;
	}

	return false;
}

/// <summary>
/// Validate that the given amount can be subtracted from the bankroll.
/// </summary>
/// <param name="amount">A bet as type const int.</param>
/// <returns></returns>
bool RoulettePlayer::isSlotBetAmountValid(const int amount)const{
	if(canPlaceBet() && (getMoney() >= amount)){
		return true;
	}
	return false;
}

/// <summary>
/// Get the current sum of the bankroll.
/// </summary>
/// <returns>The sum of the bankroll as type int.</returns>
int RoulettePlayer::getMoney() const{
	return _bankroll;
}

/// <summary>
/// Validate that the bankroll has funds.
/// </summary>
/// <returns>True if the bankroll is greater than 0 otherwise false.</returns>
bool RoulettePlayer::canPlaceBet()const{

	if(_bankroll > 0){

		return true;
	}

	return false;
}

/// <summary>
/// Get the current round of betting.
/// </summary>
/// <returns>A number of rounds as type int.</returns>
int RoulettePlayer::getBetCount() const{
	return _betCount;
}

/// <summary>
/// Display a header for the Roulette player.
/// </summary>
void RoulettePlayer::displayHeader()const{
	system("CLS");
	cout << "In this game, you have a wheel that features red and black slots" << endl;
	cout << "that have the numbers from 1 to 36 on them, and one green zero slot." << endl;
	cout << "Except for the wheel, you have a table which also features the numbers" << endl;
	cout << "and several additional sectors on which you can place bets." << endl;
	cout << "The dealer spins the wheel and reveals the winning number." << endl;
	cout << "Collect your winnings, if you have guessed the number." << endl;
	cout << "Place another bet and try again." << endl;
}

/// <summary>
/// Display the instructions menu with delimiters.
/// </summary>
void RoulettePlayer::displayInstructions()const{
	menuPlayer->displayMenu('-', '-');
}

