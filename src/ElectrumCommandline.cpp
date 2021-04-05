



#include "ElectrumCommandline.h"
#include "currencySpecific.h"
#include "GenerationParameters.h"
#include "CommandlineParser.h"
//#include "GenerationMethods.h"
#include "GenerationMethodsElectrum.h"



#include <iostream>




void createElectrumAccount(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen-" << getCurrencyShortName() << " electrum genType ..." << std::endl;
		std::cout << " genType: random, hash, mnemonic, hex, dice, brain" << std::endl;
		std::cout << std::endl;
		std::cout << " Options can be added in the end of the command line" << std::endl;
		std::cout << "Example 1:" << std::endl;
		std::cout << "   bitgen electrum random words 13 name \"My test account\"" << std::endl;
		std::cout << "   This will generate a random 13 word mnemonic with the name \"My test account\"" << std::endl;		
		std::cout << std::endl;
		std::cout << "Example 2:" << std::endl;		
		std::cout << "   bitgen electrum hash HASH words 15 name \"My hash test\"" << std::endl;
		std::cout << std::endl;		
		std::cout << "Example 3:" << std::endl;		
		std::cout << "   bitgen electrum mnemonic \"distance curve job orchard riot solve rice regular combine bonus ski beef rail chief coyote material\" name \"My test with 16 words\"" << std::endl;
		std::cout << std::endl;		
		std::cout << "Example 4:" << std::endl;
		std::cout << "   bitgen electrum hex 7289BCF837900FE8788BC78A111678ABB words 12 name \"Hex test\"" << std::endl;
		std::cout << std::endl;		
		std::cout << "Example 5:" << std::endl;	
		std::cout << "   bitgen electrum dice 1231236626256261235123656661616625662656626252661265 words 12 name \"Dice test\"" << std::endl;
		std::cout << std::endl;		
		std::cout << "Example 6:" << std::endl;			
		std::cout << "   bitgen electrum brain me@gmail.com MyBrainwal... words 13 name \"Brainwallet test\"" << std::endl;
		return;
	}	
	
	const std::string genType(args[1]);
	

	if(genType == "random")
	{
#ifndef __linux
		std::cerr << "Random is not supported on Windows. Use \"hash\" instead" << std::endl;
		return;
#endif

		//const int numWords = getNumWords(args, 2);

		const GenerationParameters params = parseTheExtraParams(args, 1, true);

		std::cout << "Generating electrum seed with " << params.getWords() << " words from random" << std::endl;
		GenerationMethodsElectrum::createElectrumRandom(thetime, params.getWords(), params);
	}	
	else if(genType == "hash")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen electrum hash HASHVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		
		//const int numWords = getNumWords(args);
		
		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string hashval(args[2]);
		GenerationMethodsElectrum::createElectrumHash(thetime, params.getWords(), hashval, params);
	}
	else if(genType == "mnemonic")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen electrum mnemonic MNEMONICVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string mnemonic(args[2]);
		
		const std::list<ExtraInfo> extra;
		GenerationMethodsElectrum::createElectrumMnemonic(thetime, mnemonic, params, extra);
	}
	else if(genType == "hex")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended hex HEXVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		//const int numWords = getNumWords(args);


		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string hexval(args[2]);
		GenerationMethodsElectrum::createElectrumHex(thetime, params.getWords(), hexval, params);
	}	
	else if(genType == "dice")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen electrum dice DICEVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		//const int numWords = getNumWords(args);


		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string diceval(args[2]);
		GenerationMethodsElectrum::createElectrumDice(thetime, params.getWords(), diceval, params);
	}
	else if(genType == "brain")
	{		
		if(args.size() < 4)
		{
			std::cerr << "Usage: bitgen electrum brain email/salt BRAINVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		//const int numWords = getNumWords(args, 4);

		const GenerationParameters brainParams = parseTheExtraParams(args, 3);
		
		const std::string saltVal(args[2]);
		const std::string extbrainVal(args[3]);
				
		GenerationMethodsElectrum::createElectrumBrain(thetime, brainParams.getWords(), saltVal, extbrainVal, brainParams);
	}	
	else
	{
		std::cerr << "Unknown electrum option: " << genType << std::endl;
		throw std::string("Unknown electrum option");
	}
}




