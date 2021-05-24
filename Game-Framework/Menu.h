/*
* Name: Clive Leddy
* File: Menu.h
* Date: 2021-04-15
*
* Summary: This is a reusable menu. The menu has a title. You can choose to have the title combined
* with a delimiter below it. The rest of the menu is a vector of strings. The vector position 0, is
* reserved for a menu items title. This title can be used as an instruction on how to use the menu
* items.
*/

#ifndef MENU_H
#define MENU_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

/// <summary>
/// This is a reusable menu. The menu has a title. You can choose to have the title combined
/// with a delimiter below it.The rest of the menu is a vector of strings.The vector position 0, is
/// reserved for a menu items title.This title can be used as an instruction on how to use the menu
/// items.
/// </summary>
class Menu{

private:
	string _title;
	string _prompt;
	vector<string> _menuItems;

public:
	Menu();
	~Menu();

	/// <summary>
	/// The menu has a number of menu choices.
	/// </summary>
	/// <returns>Number of menu items as type integer.</returns>
	int numberOfMenuItems(){

		if(_menuItems.size() > 1){

			return (int)_menuItems.size() - 1;
		}

		return 0;
	}

	/// <summary>
	/// Display a delimiter by the value in length.
	/// </summary>
	/// <param name="length">Number of times a delimiter is displayed as type integer.</param>
	/// <param name="delimiter">A delimiter as type char*.</param>
	void displayDelimiter(const int length, const char delimiter);

	/// <summary>
	/// Set the menu prompt.
	/// </summary>
	/// <param name="title">Menu title as type string.</param>
	void setPrompt(string prompt);

	/// <summary>
	/// Get the prompt.
	/// </summary>
	/// <returns>The prompt text as a string.</returns>
	string getPrompt()const;

	/// <summary>
	/// Display the prompt.
	/// </summary>
	void displayPrompt();

	/// <summary>
	/// Display the title.
	/// </summary>
	void displayTitle();

	/// <summary>
	/// Set the title of the menu.
	/// </summary>
	/// <param name="title">Menu title as type string.</param>
	void setTitle(string title);

	/// <summary>
	/// Display the title with a delimiter.
	/// </summary>
	/// <param name="delimiter">A delimiter as type char*.</param>
	void displayTitle(const char delimiter);

	/// <summary>
	/// Display the all menu items. Each item is preceded with a number that is used
	/// as an index. The first menu item is an menu instruction with a delimiter displayed
	/// below it.
	/// </summary>
	/// <param name="delimiter">A delimiter as type char*.</param>
	void displayMenuItems(const char delimiter);

	/// <summary>
	/// Display the all menu items. Each item is preceded with a number that is used
	/// as an index. The first menu item is an menu instruction.
	/// </summary>
	void displayMenuItems();

	/// <summary>
	/// Add title to the menu items. This title may include a short instruction about 
	/// the menu itself.
	/// </summary>
	/// <param name="menuTitle">A menu title as type string.</param>
	void setMenuItemsTitle(string menuTitle);

	/// <summary>
	/// Add a menu item to the vector list of items.
	/// </summary>
	/// <param name="menuItem">A menu item as type string.</param>
	/// <returns>True if the menu item is added otherwise false.</returns>
	bool addMenuItem(string menuItem);

	/// <summary>
	/// Display Menu.
	/// </summary>
	/// <param name="titleDelimiter">A delimiter used when displaying the menu title.</param>
	/// <param name="menuItemsDelimiter">A delimiter used when displaying the menu prompt.</param>
	void displayMenu(const char dilimiter, const char menuItemsDilimiter);

	/// <summary>
	/// Display Menu.
	/// </summary>
	void displayMenu();
};

#endif // !MENU_H
