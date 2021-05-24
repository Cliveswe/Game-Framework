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
private:

public:
	static int getInputInt(const char* msg, const char* errMsg);
};
#endif // !UTILS_H