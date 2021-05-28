/**
* Author: Clive Leddy
* File: Utils.cpp
* Date: 2021-05-20
* Summary:
* This is a utility class that contains no data. It contains methods that perform a task without saving data
* or a state. There is no constructor or destructor.
*/
#include "Utils.h"

/// <summary>
/// Get input entered from standard in as an integer. The entered integer must be a positive value or the
/// user will be asked to re-enter a new value.
/// </summary>
/// <param name="msg">A message to the user requesting input as a const char*.</param>
/// <param name="errMsg">An error message informing the user that the input was incorrect of type const char*.</param>
/// <returns>The entered value from the user as type int.</returns>
int Utils::getInputInt(const char* msg, const char* errMsg){
	string input;
	bool valid = false;

	input.clear();

	while(!valid){

		cin >> input;
		valid = true;

		for(int index = 0; index < input.length(); index++){

			if(isdigit(input[index]) == false){

				cin.clear();
				cin.ignore(numeric_limits<int>::max(), '\n');
				cout << errMsg << endl << msg;
				valid = false;
				break;
			}
		}
	}

	return stoi(input);
}