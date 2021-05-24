#include "Utils.h"

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