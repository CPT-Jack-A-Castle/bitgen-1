#ifndef ENTITY_INFORMATION_COMMANDLINE_H
#define ENTITY_INFORMATION_COMMANDLINE_H


#include <vector>
#include <string>

class EntityInformationCommandline
{
public:
	static void informationAboutEntity(const std::vector<std::string>& args, const std::string& thetime);
	static void verifyWif(int argc, char* argv[], const std::string& thetime);

};


#endif

