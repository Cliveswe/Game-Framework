/**
* Author: Clive Leddy
* File: Utils.h
* Date: 2021-05-20
* Summary:
* This is a utility class that contains no data. It contains methods that perform a task without saving data
* or a state. There is no constructor or destructor.
*/

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>
using std::numeric_limits;
using std::streamsize;
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class Utils{

public:

	/// <summary>
	/// Get input entered from standard in as an integer. The entered integer must be a positive value or the
	/// user will be asked to re-enter a new value.
	/// </summary>
	/// <param name="msg">A message to the user requesting input as a const char*.</param>
	/// <param name="errMsg">An error message informing the user that the input was incorrect of type const char*.</param>
	/// <returns>The entered value from the user as type int.</returns>
	static int getInputInt(const char* msg, const char* errMsg);
};
#endif // !UTILS_H