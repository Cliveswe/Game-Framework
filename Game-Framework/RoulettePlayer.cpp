#include "RoulettePlayer.h"

RoulettePlayer::RoulettePlayer(int bankroll) : _bankroll(bankroll), _betCount(0){

	_game = nullptr;
	menuPlayer = nullptr;

	rouletteMenuItems = {"Incorrect menu choice!",
		"Choose a number you want to bet on. You may repeat this step to add additional slots to bet on.",
		"Alternatively, you can choose the colour RED or BLACK instead of a number you want to bet on.",
		"Choose a bet amount that is suitable for your bankroll.",
		"Place bet."
	};

	initialize();
}

RoulettePlayer::~RoulettePlayer(){
	delete menuPlayer;

	if(_game != nullptr){

		_game = nullptr;

	} else{

		_game = nullptr;
	}
}



bool RoulettePlayer::setGame(IGame* game){

	if(game != nullptr){

		if(game->getID() != RouletteGame::getRouletteID()){

			return false;
		}

		_game = game;

		return true;
	}

	return false;
}

bool RoulettePlayer::play(int numberOfTimes){
	RoulettBet* rb;
	displayHeader();
	displayInstructions();

	for(int index = 0; index < numberOfTimes; index++){


		cout << endl << "\nRound " << index + 1 << " of " << numberOfTimes << "." << endl;

		rb = getBet();
		//rb = new RoulettBet();
		//void* test = rb;
		//_game->play(reinterpret_cast<char*>(test), 12);
		_game->play((char*)rb, 12);
		cout << "res " << *rb->getSlotColour() << endl;
	}

	return false;
}

RoulettBet* RoulettePlayer::getBet(){
	int choice = 0;
	bool ans = false;
	RoulettBet* rb = nullptr;
	vector<int>* slots;
	int slotColour = -1;
	int bet;

	try{
		slots = new vector<int>();
	} catch(bad_alloc ba){
		cerr << "bad_alloc caught: " << ba.what() << endl;
		exit(1);
	}

	do{
		displayInstructions();

		choice = Utils::getInputInt(menuPlayer->getPrompt().c_str(), "Unknown input!");

		switch(choice){
			case CHOOSE_NUMBERS:
				setSlots(slots);
				break;
			case CHOOSE_COLOUR:
				 slotColour = setSlotColour();
				break;
			case BET_AMOUNT:
				bet = setBetAmount();
				break;
			case END:
				ans = true;
			default:
				cout << "Wrong choice, try again!" << endl;
				break;
		}
	} while(!ans);

	return rb;
}


int RoulettePlayer::setBetAmount(){
	string* helper = new string("Example. If you have chosen 5 slots and you bet 1 SEK,\nthen your bet total is 5 x 1 = 5 SEK!");
	string* msg = new string("Enter amount to bet per slot and colour: ");
	string* errMsg = new string("Not a valid selection!");
	int res = -1;

	cout << *helper << endl;
	do{
		cout << *msg;
		res = Utils::getInputInt(msg->c_str(), errMsg->c_str());

		if(res> 0){
			break;
		} else{
			res = -1;
		}

	} while(true);

	return res;
}

int RoulettePlayer::setSlotColour(){
	string* msg = new string("Select a colour (0 = red && 1 = black)? ");
	string* errMsg = new string("Not a valid selection!");
	int res = -1;
	
	do{
		cout << *msg;
		res = Utils::getInputInt(msg->c_str(), errMsg->c_str());
		
		if((res == 0) || (res == 1)){
			break;
		} else{
			res = -1;
		}

	} while(true);

	return res;
}

bool RoulettePlayer::setSlots(vector<int>* slots){
	string* msg = new string("Enter a number from 0 to 36? ");
	string* errMsg = new string("Not a valid number!");
	int res;

	cout << *msg;
	res = Utils::getInputInt(msg->c_str(), errMsg->c_str());

	if(isSlotNumberValid(res)){

		slots->push_back(res);
		return true;

	} else{

		cerr << "Invalid input! " << res << endl;
	}

	return false;
}

bool RoulettePlayer::isSlotNumberValid(int number){
	if((number >= RouletteGame::LOWEST_SLOT) &&
		(number <= RouletteGame::HIGHEST_SLOT)){
		return true;
	}
	return false;
}

int RoulettePlayer::getMoney() const{
	return _bankroll;
}

bool RoulettePlayer::canPlaceBet(){
	if(_bankroll > 0){
		return true;
	}

	return false;
}

void RoulettePlayer::newBet(){
	_betCount++;
}

int RoulettePlayer::getBetCount() const{
	return _betCount;
}

void RoulettePlayer::initialize(){
	createRouletteMenu();
	setMenu();
}

void RoulettePlayer::setMenu(){
	menuPlayer->setTitle("Place you're bets!");
	menuPlayer->setPrompt("Enter your choice: ");
	menuPlayer->setMenuItemsTitle("HOW TO PLAY ROULETTE - STEP BY STEP.");
	menuPlayer->addMenuItem(rouletteMenuItems[CHOOSE_NUMBERS]);
	menuPlayer->addMenuItem(rouletteMenuItems[CHOOSE_COLOUR]);
	menuPlayer->addMenuItem(rouletteMenuItems[BET_AMOUNT]);
	menuPlayer->addMenuItem(rouletteMenuItems[END]);
}


void RoulettePlayer::createRouletteMenu(){
	try{
		menuPlayer = new Menu();
	} catch(bad_alloc ba){
		cerr << "bad_alloc caught: " << ba.what() << endl;
	}
}

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

void RoulettePlayer::displayInstructions()const{
	menuPlayer->displayMenu('-', '-');
}

