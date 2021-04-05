
#include "CommandlineParser.h"

#include "commandLine.h"
#include "ExtraOptionsRandom.h"

#include <iostream>




GenerationParameters parseTheExtraParams(const std::vector<std::string>& args, const int startPos, 
	const bool useCurrencySpecific)
{
	//std::cout << "In parseTheExtraParams" << std::endl;
	GenerationParameters params;	

	const std::vector<std::string> allExtraArgs = getExtraArgs(args, startPos);

	ExtraOptionsRandom extraOptions;
	
		
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		
		if(params.useArg(arg))
		{
			//Nothing
		}
		else if(extraOptions.useArg(arg))
		{
			//Nothing			
		}
		else if(useCurrencySpecific && params.useCurrencySpecific(arg))
		{
			//Nothing			
		}		
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();
	return params;
}


