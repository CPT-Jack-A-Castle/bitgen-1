

#include "util.h"

#include "Timestamp.h"

#include <time.h>

#include <ctime>


std::string Timestamp::toString() const
{
	return epochTimeToString(timestamp);
}



std::string Timestamp::epochTimeToString(const int timeInt)
{	
	time_t t = timeInt;
	const std::string thetime = removeNewline(asctime(localtime(&t)));
	std::cout << "ASCTIME: " << thetime << std::endl;
	
	return thetime;	
}




