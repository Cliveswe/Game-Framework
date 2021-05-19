/*
* Name: Clive Leddy
* File: Menu.cpp
* Date: 2021-04-15
*
* Summary: This is a reusable menu. The menu has a title. You can choose to have the title combined
* with a delimiter below it. The rest of the menu is a vector of strings. The vector position 0, is
* reserved for a menu items title. This title can be used as an instruction on how to use the menu
* items.
*/
#include "Menu.h"

Menu::Menu(){
	_menuItems = { };
	_title = "->No title<-\n use setTitle(string title)";
	_prompt = "Make your choice: ";
	setMenuItemsTitle("->No items<-\n Use setMenuItemsTitle(string menuTitle) to set a menu title.\n Use addMenuItem(string menuItem) to add menu items.");
}

Menu::~Menu(){
	_menuItems.clear();
}

/// <summary>
/// Display a delimiter by the value in length.
/// </summary>
/// <param name="length">Number of times a delimiter is displayed as type integer.</param>
/// <param name="delimiter">A delimiter as type char*.</param>
void Menu::displayDelimiter(const int length, const char delimiter){

	for(int i = 0; i < length; i++){
		cout << delimiter;
	}
}

/// <summary>
/// Set the title of the menu.
/// </summary>
/// <param name="title">Menu title as type string.</param>
void Menu::setTitle(string title){
	_title = title;
}

/// <summary>
/// Set the menu prompt.
/// </summary>
/// <param name="prompt">Menu title as type string.</param>
void Menu::setPrompt(string prompt){
	_prompt = prompt;
}

/// <summary>
/// Display the title.
/// </summary>
void Menu::displayTitle(){

	cout << endl << _title << endl;
}

/// <summary>
/// Display the prompt.
/// </summary>
void Menu::displayPrompt(){

	cout << endl << _prompt;
}

/// <summary>
/// Display the title with a delimiter.
/// </summary>
/// <param name="delimiter">A delimiter as type char*.</param>
void Menu::displayTitle(const char delimiter){

	displayTitle();
	displayDelimiter((int)_title.size(), delimiter);
	cout << endl;
}

/// <summary>
/// Display the all menu items. Each item is preceded with a number that is used
/// as an index. The first menu item is an menu instruction with a delimiter displayed
/// below it.
/// </summary>
/// <param name="delimiter">A delimiter as type char*.</param>
void Menu::displayMenuItems(const char delimiter){

	cout << _menuItems[0] << endl;
	displayDelimiter((int)_menuItems[0].size(), delimiter);

	for(int i = 1; i < (int)_menuItems.size(); i++){

		cout << endl << i << ") " << _menuItems[i];
	}

	cout << endl;
}

/// <summary>
/// Display the all menu items. Each item is preceded with a number that is used
/// as an index. The first menu item is an menu instruction.
/// </summary>
void Menu::displayMenuItems(){
	displayMenuItems(' ');
}

/// <summary>
/// Add title to the menu items. This title may include a short instruction about 
/// the menu itself.
/// </summary>
/// <param name="menuTitle">A menu title as type string.</param>
void Menu::setMenuItemsTitle(string menuTitle){

	if(_menuItems.size() == 0){

		_menuItems.push_back(menuTitle);

	} else{

		_menuItems[0] = menuTitle;
	}
}

/// <summary>
/// Add a menu item to the vector list of items.
/// </summary>
/// <param name="menuItem">A menu item as type string.</param>
/// <returns>True if the menu item is added otherwise false.</returns>
bool Menu::addMenuItem(string menuItem){

	if(_menuItems.size() > 0){

		_menuItems.push_back(menuItem);
		return true;
	}

	return false;
}

/// <summary>
/// Display Menu.
/// </summary>
/// <param name="titleDelimiter">A delimiter used when displaying the menu title.</param>
/// <param name="menuItemsDelimiter">A delimiter used when displaying the menu prompt.</param>
void Menu::displayMenu(const char titleDelimiter, const char menuItemsDelimiter){
	displayTitle(titleDelimiter);
	displayMenuItems(menuItemsDelimiter);
	displayPrompt();
}

/// <summary>
/// Display Menu.
/// </summary>
void Menu::displayMenu(){
	displayTitle();
	displayMenuItems();
	displayPrompt();
}