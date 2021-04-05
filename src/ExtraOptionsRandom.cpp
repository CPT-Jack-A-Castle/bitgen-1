
#include "ExtraOptionsRandom.h"


#include <iostream>



bool ExtraOptionsRandom::useArg(const std::string &arg)
{
	if(arg == "urandom")
	{
		if(longbuf)
		{
			throw std::string("Can not combine urandom and long");
		}
		useURandom = true;
		return true;		
	}
	else if(arg == "long")
	{
		if(useURandom)
		{
			throw std::string("Can not combine urandom and long");
		}

		std::cout << "Using 128 bytes from /dev/random" << std::endl;
		longbuf = true;
		return true;				
	}
	else if(arg == "encrypt")
	{
		if(onlyIndicatedUsage)
		{
			throw std::string("Error, only one usage indication permitted");
		}
			
		onlyIndicatedUsage = true;
		signVerify = false;
		return true;				
	}
	else if(arg == "verify")
	{
		if(onlyIndicatedUsage)
		{
			throw std::string("Error, only one usage indication permitted");
		}
			
		onlyIndicatedUsage = true;
		signVerify = true;
		return true;				
	}		
	
	return false;
}

