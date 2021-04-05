#ifndef VANITY_COMMANDLINE_H
#define VANITY_COMMANDLINE_H


#include <string>


class VanityCommandline
{
public:
	static void generateVanityPoolResult(int argc, char* argv[], const std::string& thetime, const bool usePool);
	static void generateVanity(int argc, char* argv[], const std::string& thetime, const bool usePool);

};


#endif
