#ifndef COMMANDLINE_PARSER_H
#define COMMANDLINE_PARSER_H


#include "GenerationParameters.h"


GenerationParameters parseTheExtraParams(const std::vector<std::string>& args, const int startPos, 
	const bool useCurrencySpecific = false);



#endif

