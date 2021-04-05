#ifndef ROOT_GENERATION_COMMANDLINE_H
#define ROOT_GENERATION_COMMANDLINE_H


#include <string>

class HierarcialRandomCommandline
{
public:
	static void generateRootKey(const std::string& theTime, int argc, char* argv[]);
	static void generatePublicFromRoot(int argc, char* argv[], const std::string& thetime);
	static void generatePrivateFromRoot(int argc, char* argv[], const std::string& thetime);

};

#endif
