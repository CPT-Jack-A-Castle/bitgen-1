
#include "GenerationMethodsElectrum.h"
#include "GenerationMethodsExtended.h"

#include "randomUtils.h"
#include "random.h"
#include "keyDerivationFunction.h"


void GenerationMethodsElectrum::saveElectrumMnemonic(const std::string& thetime,
	const ElectrumMnemonic& mnemonic, 
	const std::string& genMethod, 
	const GenerationParameters& params,
	const std::list<ExtraInfo>& extra)
{	
	//if(!mnemonic.electrum())
	//{
	//	throw std::string("Internal error, mnemonic not electrum type");
	//}
	
	
	
	std::cout << "Found seed: " << mnemonic.toStr() << std::endl;	
	std::cout << std::endl;

	const ExtendedPrivateKey extendedPrivate = mnemonic.getPrivateFromElectrumMnemonic();	
	
	std::cout << "Extended private: " << extendedPrivate.toString() << std::endl;
	
	const ExtendedPublicKey extendedPub = extendedPrivate.getPub();	

	std::cout << "Extended pub: " << extendedPub.toString() << std::endl;
	std::cout << std::endl;
	

	std::list<ExtraInfo> generationExtra;
		
	const ExtraInfo extraInfo("Mnemonic", mnemonic.toStr(), true);
	generationExtra.push_back(extraInfo);

	generationExtra.insert(generationExtra.end(), extra.begin(), extra.end());

	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPub/*.toString()*/, genMethod, thetime, params, generationExtra,
		extendedPub.extendedData.chainString(), mnemonic, true);
}



void GenerationMethodsElectrum::generateElectrumMnemonicInfo(const std::string& thetime,
	const BigInt<256>& randomNum, 
	const int numWords, 
	const std::string& genMethod, 
	const GenerationParameters& params,
	const std::list<ExtraInfo>& extra)
{
	const ElectrumMnemonic mnemonic = ElectrumMnemonic::generateElectrum(randomNum, numWords);
		
	saveElectrumMnemonic(thetime, mnemonic, genMethod, params, extra);
	
}




void GenerationMethodsElectrum::createElectrumDice(const std::string& thetime,
	const int numWords,
	const std::string& diceStr, 
	const GenerationParameters& params)
{
	std::cout << "Creating electrum seed with " << numWords << " words from dice" << std::endl;
	
	const double numWordsDouble(numWords);
	
	const int numDiceNeeded = ((numWordsDouble * 11.0) / 2.63);
	
	if(diceStr.size() != numDiceNeeded)
	{
		std::cout << "Number dice needed: " << numDiceNeeded << ", got: " << diceStr.size() << std::endl;
		throw std::string("Not correct number dice digits");
	}
	
	const BigInt<256> randomNum = getRandomNumFrom6SideDice(diceStr, numDiceNeeded);		
	//std::cout << "Random: " << hexString(randomNum.getBinaryLong())	<< std::endl;
	//std::cout << "Non-zero digits: " << randomNum.numberBitsNeeded() << std::endl;
	
	
	std::list<ExtraInfo> extra;
	const ExtraInfo extraInfo("Dice", diceStr);	
	extra.push_back(extraInfo);
	generateElectrumMnemonicInfo(thetime, randomNum, numWords, "dice", params, extra);	
}





void GenerationMethodsElectrum::createElectrumHex(const std::string& thetime,
	const int numWords,
	const std::string& hex, 
	const GenerationParameters& params)
{
	std::cout << "Creating electrum seed from hex" << std::endl;
	
	const int numWordsBound = (numWords * 11) * 2 / 8;
	const int numHexCharsNeeded = min(numWordsBound, 64);
	
	if(hex.size() < numHexCharsNeeded)
	{
		std::cout << "Num hex digits needed: " << numHexCharsNeeded << ", got: " << hex.size() << std::endl;
		throw std::string("Not enough hex digits");
	}
	else if(hex.size() > numHexCharsNeeded)
	{
		std::cout << "Num hex digits needed: " << numHexCharsNeeded << ", got: " << hex.size() << std::endl;
		throw std::string("Too many hex digits");
	}
	
	const std::string hexUpper = toUpper(hex);
		
	const BigInt<256> randomNum = BigInt<256>::fromHex(hexUpper);
	
	std::list<ExtraInfo> extra;
	const ExtraInfo extraInfo("Hex", hexUpper);	
	extra.push_back(extraInfo);
	
	generateElectrumMnemonicInfo(thetime, randomNum, numWords, "hex", params, extra);	
}





void GenerationMethodsElectrum::createElectrumBrain(const std::string& thetime,
	const int numWords,
	const std::string& salt, const std::string& brainVal,	
	const GenerationParameters& params)
{
	const int minBrainStrSize(100);
	
	if(brainVal.size() < minBrainStrSize)
	{
		std::cout << "Brain string size: " << brainVal.size() << ", need: " << minBrainStrSize << std::endl;
		throw std::string("Brain string too short");
	}
	
	std::cout << "Creating electrum seed from brain string" << std::endl;
	
	std::cout << "Calculating privkey, this may take a while..." << std::endl;	
	const std::string kdfStr = bitgenArgon2Kdf(brainVal, salt);
	if(kdfStr.size() != 32)
	{
		throw std::string("KDF error");
	}
	const std::string sha = sha256(kdfStr);
	const BigInt<256> randomNum(sha, 'c');
		
			
	std::list<ExtraInfo> extra;
	const ExtraInfo extraInfo("Brain", brainVal, true);	
	extra.push_back(extraInfo);
	
	generateElectrumMnemonicInfo(thetime, randomNum, numWords, "brain", params, extra);	
}





void GenerationMethodsElectrum::createElectrumHash(const std::string& thetime,
	const int numWords,
	const std::string& hash, 
	const GenerationParameters& params)
{
	std::cout << "Creating electrum seed from hash" << std::endl;
	
	const BigInt<256> randomNum = hashStringToBigInt(hash);

	const std::list<ExtraInfo> extra;
	generateElectrumMnemonicInfo(thetime, randomNum, numWords, "hash", params, extra);	
}




void GenerationMethodsElectrum::createElectrumRandom(const std::string& thetime,
	const int numWords, 
	const GenerationParameters& params)
{
	std::cout << "Creating electrum seed from /dev/random" << std::endl;
	
	BigInt<256> randomNum = getRandomNumber();		//Todo: Only get as much entropy that is needed with numWords
	//std::cout << "Random num: " << hexString(randomNum.getBinaryLong()) << std::endl;
	
	const std::list<ExtraInfo> extra;
	generateElectrumMnemonicInfo(thetime, randomNum, numWords, "random", params, extra);
}




void GenerationMethodsElectrum::createElectrumMnemonic(const std::string& thetime, const std::string& mnemonicRaw, 
	const GenerationParameters& params, const std::list<ExtraInfo>& extra)
{
	std::cout << "Creating extended key from mnemonic" << std::endl;
	
	//Make sure we use lower case letters with single spaces.	
	//const std::string mnemonicStr = normalizeMnemonicStr(mnemonicRaw);
	const ElectrumMnemonic mnemonic(mnemonicRaw);
	const int numWords = mnemonic.numberWords();
	
	if(numWords > 24)
	{
		std::cout << "Number words incorrent, got: " << numWords << " words" << std::endl;
		throw std::string("Incorrect num words");
	}
	
	std::cout << "Normalized mnemonic: \"" << mnemonic.toStr() << "\"" << std::endl;

	saveElectrumMnemonic(thetime, mnemonic, "mnemonic", params, extra);	
}









