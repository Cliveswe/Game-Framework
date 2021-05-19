#include "RouletteGame.h"

RouletteGame::RouletteGame(){ 
	menu = new Menu();
	this->initialize();
}


RouletteGame::~RouletteGame(){
	delete menu;
}

void RouletteGame::initialize(){
	menu->setTitle("Roulette");
	menu->setPrompt("Enter your choice: ");
	menu->setMenuItemsTitle("In order to play the game, menu item 3, you first must enter data in menu items 1 & 2!");
	menu->addMenuItem("Enter the players bankroll.");
	menu->addMenuItem("Enter the total number of rounds to play.");
	menu->addMenuItem("Play the game.");
	menu->addMenuItem("Game instructions.");
	menu->addMenuItem("End the program.");
}

int RouletteGame::play(char* bet, int amount){
	
	menu->displayMenu('-', '-');
	return 0;
}

int RouletteGame::getID() const{
	return 0;
}
