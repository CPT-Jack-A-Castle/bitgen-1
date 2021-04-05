
#ifndef GENERATION_METHODS_EXTENDED_H
#define GENERATION_METHODS_EXTENDED_H


#include "GenerationParameters.h"
#include "ExtendedKey.h"
#include "extraInfo.h"
#include "mnemonic.h"


#include <string>

class GenerationMethodsExtended
{
public:
	static void createExtendedMnemonic(const std::string& thetime, const std::string& mnemonicRaw, 
		const GenerationParameters& params);

	static void saveExtendedFiles(const std::string& extPrivate, 
		const ExtendedPublicKey& extPublic, const std::string& generator,
		const std::string& thetime, const GenerationParameters& params, const std::list<ExtraInfo>& generationExtra, 
		const std::string& derivationPath, const MnemonicBase& mnemonic, const bool isElectrum = false);

	static void createExtendedDice(const std::string& thetime, const std::string& diceval, const GenerationParameters& params);

	static void createExtendedHash(const std::string& thetime, const std::string& hashval, const GenerationParameters& params);
	
	static void createExtendedHex(const std::string& thetime, const std::string& hexhval, const GenerationParameters& params);

	static void createExtendedRandom(const std::string& thetime, const GenerationParameters& params);

	static void createExtendedExtBrain(const std::string& thetime, const std::string& salt, const std::string& brainVal, 
		const GenerationParameters& params);
	static void createExtendedExtPriv(const std::string& thetime, const std::string& exprivVal, const GenerationParameters& params);
	static void createExtendedSeed(const std::string& thetime, const std::string& hashval, const GenerationParameters& params);


};



#endif
