


#include "VanityCommandline.h"


#include "wif.h"
#include "privKey.h"
#include "extraInfo.h"
#include "mnemonic.h"
#include "GenerationParameters.h"
#include "GenerationMethods.h"
#include "VanitySearcher.h"


#include <iostream>
#include <list>



void VanityCommandline::generateVanityPoolResult(int argc, char* argv[], const std::string& thetime, const bool usePool)
{
	if(argc < 4)
	{
		std::cout << "Usage: bitgen vanityPoolResult wif1 wif2 [Name]" << std::endl;
		throw std::string("Incorrect usage");
	}

	const std::string wifStr1 = argv[2];
	const std::string wifStr2 = argv[3];


	std::string accountName;
	if(argc > 4)
	{
		accountName = argv[4];
	}
	
	const Wif wif1(wifStr1);
	const Wif wif2(wifStr2);

	const PrivKey privKey1 = wif1.getPriv();

	const BigInt<1024> N(BitcoinEllipticCurve::Nval());

	const PrivKey pk1 = wif1.getPriv();
	const PrivKey pk2 = wif2.getPriv();
	
	const BigInt<1024> priv1(BigInt<1024>::asPositive(pk1.key));
	const BigInt<1024> priv2(BigInt<1024>::asPositive(pk2.key));

	
	const BigInt<1024> sum = priv1 + priv2;
	const BigInt<1024> modsum = sum % N;
	
	const BigInt<256> privKey(modsum);
				
	const PrivKey myPrivKey(privKey, privKey1.compressed);
	const Wif wif = myPrivKey.getWif();
	
	BitcoinEllipticCurve ec;
	
	const PubAddress address = myPrivKey.getAddress(ec);
	
	std::cout << std::endl;
	std::cout << "Wif: " << wif << std::endl;	
	std::cout << "Address: " << address << std::endl;
	
	std::list<ExtraInfo> generationExtra;
				
	const Mnemonic myMnemonicObj(privKey);

				
	GenerationParameters params(myPrivKey.compressed, true, true);
	GenerationMethods::saveAllFiles(address, wif.toString(), "vanity pool", 
		generationExtra, thetime, 
		params,
		myMnemonicObj
		);				
}















//Todo: Move to separate file for vanity generation
void VanityCommandline::generateVanity(int argc, char* argv[], const std::string& thetime, const bool usePool)
{
#ifndef __linux
	std::cerr << "Vanity is not supported on Windows." << std::endl;
	return;
#endif
	
	bool printAll(false);
		
	std::string searchPatternRaw;
	if(argc < 3)
	{
		std::cout << "Usage: bitgen vanity pattern [Name]" << std::endl;
		throw std::string("Pattern must be given (eg 1PR)");
	}

	searchPatternRaw = argv[2];


	std::string accountName;
	if(argc > 3)
	{
		accountName = argv[3];
		std::cout << "Account name: " << accountName << std::endl;
	}

	std::string pkifStr;
	if(argc > 3)
	{
		pkifStr = argv[3];
		std::cout << "Pkif: " << pkifStr << std::endl;
	}

	if(usePool)
	{
		if(pkifStr.empty())
		{
			std::cout << "Usage: bitgen vanityPool pattern pkif [Name]" << std::endl;
			
			throw std::string("Pkif must be given");
		}
	}


	VanitySearcher::searchForVanityAddress(searchPatternRaw, usePool, pkifStr, thetime, accountName);
}




/*
void handleVanityFound(const long int startTime, const int i)
{
			const long int endTime = time(NULL);
			const long int totalTime = (endTime - startTime);
			const int iterationsPerSec = (totalTime == 0) ? 0 : (i / totalTime);
			
			std::cout << std::endl;
			std::cout << "Found solution: " << pub << std::endl;
			std::cout << " while searching for: " << searchPattern << std::endl;
			if(iterationsPerSec != 0)
			{
				std::cout << "Iterations per second: " << iterationsPerSec << std::endl;
			}
			std::cout << std::endl;

			const BigInt<257> N(BitcoinEllipticCurve::N());
				
			const BigInt<257> privKeyRLarger(privKeyR);
			const BigInt<257> privKeyTotal = privKeyRLarger + i;
			const BigInt<257> privKeyMod = privKeyTotal % N; 	//Modulus
			const BigInt<256> privKey(privKeyMod);
				
			const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(privKey, compressed);

			std::cout << "PRIV: " << keypair.privaddr << std::endl;			
			std::cout << "PUB : " << keypair.pubaddr << std::endl;
				
			std::list<std::string> generationExtra;
				
			const std::string mnemonic = generateMnemonic(privKey);
				
				
			saveAllFiles(keypair.pubaddr.address, keypair.privaddr.address, "vanity", 
				generationExtra, thetime, accountName, mnemonic, compressed);			
}
*/



