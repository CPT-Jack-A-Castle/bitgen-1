#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <string>



class Timestamp
{
public:
	explicit Timestamp(int inTimestamp) : timestamp(inTimestamp) {}
	
	
	int numVal() const
	{
		return timestamp;
	}
	
	bool isBlockHeight() const
	{
		return (timestamp < 500000000);
	}
	
	std::string toString() const;
	
private:
	static std::string epochTimeToString(const int timeInt);


	int timestamp;		//Todo: long
};



#endif

