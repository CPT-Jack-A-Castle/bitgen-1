
#ifndef GENERATION_METHODS_ELECTRUM_H
#define GENERATION_METHODS_ELECTRUM_H


#include "GenerationParameters.h"
#include "ExtendedKey.h"
#include "extraInfo.h"
#include "mnemonic.h"


#include <string>

class GenerationMethodsElectrum
{
public:

	static void createElectrumMnemonic(const std::string& thetime, const std::string& mnemonicRaw, const GenerationParameters& params, const std::list<ExtraInfo>& extra);
	static void createElectrumRandom(const std::string& thetime, const int numWords, const GenerationParameters& params);
	static void createElectrumHash(const std::string& thetime, const int numWords, const std::string& hash, const GenerationParameters& params);
	static void createElectrumHex(const std::string& thetime, const int numWords, const std::string& hex, const GenerationParameters& params);
	static void createElectrumDice(const std::string& thetime, const int numWords, const std::string& diceStr, const GenerationParameters& params);
	static void createElectrumBrain(const std::string& thetime, const int numWords, const std::string& salt, const std::string& brainVal, const GenerationParameters& params);

private:
	static void generateElectrumMnemonicInfo(const std::string& thetime, const BigInt<256>& randomNum, 
		const int numWords, const std::string& genMethod, const GenerationParameters& params, 
		const std::list<ExtraInfo>& extra);

	static void saveElectrumMnemonic(const std::string& thetime,const ElectrumMnemonic& mnemonic, 
		const std::string& genMethod, const GenerationParameters& params,
		const std::list<ExtraInfo>& extra);

};



#endif
