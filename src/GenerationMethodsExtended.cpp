

#include "GenerationMethodsExtended.h"
#include "GenerationMethods.h"

#include "mnemonic.h"
#include "extraInfo.h"
#include "mnemonic.h"
#include "txtGeneration.h"
#include "bitgenVersion.h"
#include "language.h"
#include "printPS.h"
#include "FileUtil.h"
#include "random.h"
#include "randomUtils.h"
#include "keyDerivationFunction.h"


#include <iostream>
#include <list>


void GenerationMethodsExtended::createExtendedSeed(const std::string& thetime, const std::string& seedval, const GenerationParameters& params)
{
	std::cout << "Creating extended key from hex seed" << std::endl;
	
	const std::string seedUpper = toUpper(seedval);

	const std::string seed(convertFromHex(seedUpper));
	const Mnemonic mnemonic(seed);

	const ExtendedPrivateKey extendedPrivate = calculateMasterKey(seed);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();

	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Seed", hexString(seed));
	generationExtra.push_back(extraInfo);


	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "seed", thetime, params, generationExtra,
		extendedPublicKey.extendedData.chainString(), mnemonic);	
}




void GenerationMethodsExtended::createExtendedRandom(const std::string& thetime, const GenerationParameters& params)
{
	const bool useCurrencySpecific = params.getCurrencySpecific();
	//;
	//std::cout << "Creating extended key" << std::endl;
	if(useCurrencySpecific)
	{
		std::cout << "Will use currencyspecific addresses" << std::endl;
	}
	
	std::cout << "Generating random data for private key..." << std::endl;
	const BigInt<256> privKeyInt = getRandomNumber();	
	const PrivKey privKey(privKeyInt, true);

	std::cout << "Generating random data for chain code..." << std::endl;	
	const BigInt<256> chainCode = getRandomNumber();	
	
	const BigInt<32> zero;	
	const ExtendedPrivateKey extendedPrivate(0, zero, zero, chainCode, privKey);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();


	//std::cout << "Created extended" << std::endl << extendedPrivate.toString() << std::endl;
	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	std::list<ExtraInfo> generationExtra;

	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(params.getCurrencySpecific()), 
		extendedPublicKey, "/dev/random", thetime, 
		params, generationExtra, 
		extendedPublicKey.extendedData.chainString(), Mnemonic(MnemonicBase::DUMMY_EMPTY_MNEMONIC));
}




void GenerationMethodsExtended::saveExtendedFiles(const std::string& extPrivate, 
	const ExtendedPublicKey& extPublic, 
	const std::string& generator,
	const std::string& thetime, const GenerationParameters& params, const std::list<ExtraInfo>& generationExtra, 
	const std::string& derivationPath,
	const MnemonicBase& mnemonic,
	const bool isElectrum// = false
	)
{	
	const std::string accountName = params.getAccountName();
	
	const std::string fileId = extPublic.toString().substr(50);
	
	if(params.getGenerateTXT())
	{
		FilePair files = generateExtendedTxtFiles(extPublic.toString(), extPrivate, 
						generator, thetime, accountName, versionNumber, applicationName, generationExtra, derivationPath,
						params.getCurrencySpecific());
		

		saveExtendedTxtFiles(files, fileId, params.getCurrencySpecific(), isElectrum);
	}	
	
	
	if(params.getGeneratePS())
	{
		//std::cout << "Will save ps files" << std::endl;
		
		const Language lang = getLanguage();		
		const PostscriptGenerator postscriptGenerator(versionNumber, applicationName, lang, 
			(isElectrum ? PostscriptGenerator::ADDRTYPE_ELECTRUM : PostscriptGenerator::ADDRTYPE_EXTENDED), 
			params.getCurrencySpecific());
		
		//std::cout << "1" << std::endl;
		const PublicExtendedPostscriptInfo pubInfo(extPublic.toString(), thetime, accountName);
		
		//const std::list<std::string> generationExtra;
		const PrivatePostscriptInfo privInfo(extPrivate, mnemonic.toStr(), generator, true, generationExtra);
		//std::cout << "2" << std::endl;
		
		const PsInfoFile psinfo = postscriptGenerator.generateExtended(privInfo, pubInfo);

		//std::cout << "3" << std::endl;

		std::string currencySpecStr;
		if(params.getCurrencySpecific() || isElectrum)
		{
			currencySpecStr += getCurrencyShortName();
			currencySpecStr += "_";		
		}

		const std::string start = isElectrum ? "electrum" : "extended";

		const std::string privFilename = start + "_" + currencySpecStr + fileId + "_private.ps";
		//const std::string fullPrivPath = (privPath == ".") ? privFilename : (privPath + "/" + privFilename);
	
		std::cout << "Saving privfile: " << privFilename << std::endl;
		fileWrite(privFilename, psinfo.privatePs);
			
		const std::string pubFilename = start + "_" + currencySpecStr + fileId + "_share.ps";
		//const std::string fullPubPath = (pubPath == ".") ? pubFilename : (pubPath + "/" + pubFilename);	
		std::cout << "Saving publfile: " << pubFilename << std::endl;
		fileWrite(pubFilename, psinfo.publicPs);
		
	}

}






//Todo: Move to class GenerationMethodsExtendeds
void GenerationMethodsExtended::createExtendedMnemonic(const std::string& thetime, const std::string& mnemonicRaw, 
	const GenerationParameters& params)
{
	std::cout << "Creating extended key from mnemonic" << std::endl;
	
	const Mnemonic mnemonic(mnemonicRaw);		//Verify the mnemonic
	
	//Make sure we use lower case letters with single spaces.	
	//const std::string mnemonicStr = normalizeMnemonicStr(mnemonicRaw);
	std::cout << "Normalized mnemonic: \"" << mnemonic.toStr() << "\"" << std::endl;
	
	const std::string not_used_privData = mnemonic.getAsNumber();	//Todo???


	const std::string passphrase = params.getPassword();


	const ExtendedPrivateKey extendedPrivate = mnemonic.getExtendedPrivFromMnemonic(passphrase);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();

	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	if(params.getPrintExtendedLegacy())
	{
		std::cout << "Private legacy: " << extendedPrivate.toString(true) << std::endl;
		std::cout << "Public legacy : " << extendedPublicKey.toString(true) << std::endl;
		std::cout << std::endl;		
	}

	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Mnemonic", mnemonic.toStr(), true);
	generationExtra.push_back(extraInfo);

	if(!passphrase.empty())
	{
		const ExtraInfo extraInfo2("Password", passphrase);
		generationExtra.push_back(extraInfo2);
	}

	const ExtraInfo extraInfo3("EntBits", intToString(not_used_privData.size() * 8));
	generationExtra.push_back(extraInfo3);



	saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "BIP 39 seed", thetime, params, generationExtra,
		extendedPublicKey.extendedData.chainString(), mnemonic);	
}






//Todo: Move to class GenerationMethodsExtended
void GenerationMethodsExtended::createExtendedHash(const std::string& thetime, const std::string& hashval, const GenerationParameters& params)
{
	std::cout << "Creating extended hash key" << std::endl;
	
	const int minHashSize(50);
	if(hashval.size() < minHashSize)
	{
		std::cerr << "Hash must be at least " << minHashSize << " characters" << std::endl;
		std::cerr << "Got hashval: \"" << hashval << "\"" << std::endl;
		throw std::string("Hash not long enough");
	}

	const int hashSizeHalf = hashval.size() / 2;
	const std::string hashLeft = hashval.substr(0, hashSizeHalf);
	const std::string hashRight = hashval.substr(hashSizeHalf);

	//std::cout << "L: " << hashLeft << std::endl;
	//std::cout << "R: " << hashRight << std::endl;
	
	const std::string shaleft = sha256(hashLeft);
	const BigInt<256> privKeyInt(shaleft, 'c');
	const PrivKey privKey(privKeyInt, true);
		
		
	const std::string sharight = sha256(hashRight);
	const BigInt<256> chainCode(sharight, 'c');
	
	const BigInt<32> zero;		//Todo: Make zero the default argument
	const ExtendedPrivateKey extendedPrivate(0, zero, zero, chainCode, privKey);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();

	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	std::list<ExtraInfo> generationExtra;

	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "hash", thetime, 
		params, generationExtra,
		extendedPublicKey.extendedData.chainString(), Mnemonic(MnemonicBase::DUMMY_EMPTY_MNEMONIC));	
}






//Todo: Move to class GenerationMethodsExtended
void GenerationMethodsExtended::createExtendedHex(const std::string& thetime, const std::string& hexhval, const GenerationParameters& params)
{
	std::cout << "Creating extended hex key" << std::endl;
	
	const int hexSize(128);
	if(hexhval.size() != hexSize)
	{
		std::cerr << "Hex value must be exactly " << hexSize << " characters" << std::endl;
		std::cerr << "Got hexval: \"" << hexhval << "\" with " << hexhval.size() << " characters" << std::endl;
		throw std::string("Incorrect hex length");
	}


	const int hexSizeHalf = 64;
	const std::string hexLeft = hexhval.substr(0, hexSizeHalf);
	const std::string hexRight = hexhval.substr(hexSizeHalf);

	//std::cout << "L: " << hexLeft << " size: " << hexLeft.size() << std::endl;
	//std::cout << "R: " << hexRight << " size: " << hexRight.size() << std::endl;


	const std::string privKeyStrUpper = toUpper(hexLeft);
	const BigInt<256> privKeyInt = BigInt<256>::fromHex(privKeyStrUpper);	
	const PrivKey privKey(privKeyInt, true);

	const std::string chainCodeStrUpper = toUpper(hexRight);
	const BigInt<256> chainCode = BigInt<256>::fromHex(chainCodeStrUpper);

	//std::cout << "PrivkeyInt: " << privKeyInt << std::endl;
	//std::cout << "ChainCoInt: " << chainCode << std::endl;
	
	
	const BigInt<32> zero;		//Todo: Make zero the default argument
	const ExtendedPrivateKey extendedPrivate(0, zero, zero, chainCode, privKey);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();

	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;


	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Hexval", hexhval);
	generationExtra.push_back(extraInfo);


	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "hex", thetime, params, generationExtra,
		extendedPublicKey.extendedData.chainString(), Mnemonic(MnemonicBase::DUMMY_EMPTY_MNEMONIC));	
}







//Todo: Move to class GenerationMethodsExtended
void GenerationMethodsExtended::createExtendedDice(const std::string& thetime, const std::string& diceval, const GenerationParameters& params)
{
	std::cout << "Creating extended dice key" << std::endl;
	
	const int diceSize(200);
	if(diceval.size() != diceSize)
	{
		std::cerr << "Dice value must be exactly " << diceSize << " characters" << std::endl;
		std::cerr << "Got diceval: \"" << diceval << "\" with " << diceval.size() << " characters" << std::endl;
		throw std::string("Incorrect dice length");
	}


	const int diceSizeHalf = 100;
	const std::string diceLeft = diceval.substr(0, diceSizeHalf);
	const std::string diceRight = diceval.substr(diceSizeHalf);

	std::cout << "L: " << diceLeft << " size: " << diceLeft.size() << std::endl;
	std::cout << "R: " << diceRight << " size: " << diceRight.size() << std::endl;

	const BigInt<256> privKeyInt = getRandomNumFrom6SideDice(diceLeft);		
	const PrivKey privKey(privKeyInt, true);

	const BigInt<256> chainCode = getRandomNumFrom6SideDice(diceRight);		


	//std::cout << "PrivkeyInt: " << privKeyInt << std::endl;
	//std::cout << "ChainCoInt: " << chainCode << std::endl;
	
	
	const BigInt<32> zero;		//Todo: Make zero the default argument
	const ExtendedPrivateKey extendedPrivate(0, zero, zero, chainCode, privKey);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();

	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Diceval", diceval);
	generationExtra.push_back(extraInfo);

	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "dice", thetime, params, generationExtra,
		extendedPublicKey.extendedData.chainString(), Mnemonic(MnemonicBase::DUMMY_EMPTY_MNEMONIC));
}





#ifndef NO_BRAINWALLET_GENERATION


//Todo: Move to class GenerationMethodsExtended
void GenerationMethodsExtended::createExtendedExtBrain(const std::string& thetime, const std::string& salt, const std::string& brainVal, 
	const GenerationParameters& params)
{
	std::cout << "Creating extended brain wallet" << std::endl;
	
	const int brainSize(200);
	if(brainVal.size() < brainSize)
	{
		std::cerr << "Brain size must be at least " << brainSize << " characters" << std::endl;
		std::cerr << "Got " << brainVal.size() << " characters" << std::endl;
		throw std::string("Incorrect brain wallet length");
	}


	const int brainSizeHalf = brainVal.size() / 2;
	const std::string brainLeft = brainVal.substr(0, brainSizeHalf);
	const std::string brainRight = brainVal.substr(brainSizeHalf);

	std::cout << "L: " << brainLeft << " size: " << brainLeft.size() << std::endl;
	std::cout << "R: " << brainRight << " size: " << brainRight.size() << std::endl;

	std::cout << "Generating brainwallet" << std::endl;

	std::cout << "Salt: \"" << salt << "\"" << std::endl;		
	std::cout << "Passphrase: \"" << brainRight << "\"" << std::endl;
		
				
	std::cout << "Calculating privkey, this may take a while..." << std::endl;	
	const std::string kdfStr = bitgenArgon2Kdf(brainRight, salt);
	if(kdfStr.size() != 32)
	{
		throw std::string("KDF error");
	}
	const std::string sha = sha256(kdfStr);
	const BigInt<256> privKeyInt(sha, 'c');
	const PrivKey privKey(privKeyInt, true);


	std::cout << "Calculating chain code, this may take a while..." << std::endl;	
	const std::string kdfStrChainCode = bitgenArgon2Kdf(brainLeft, salt);
	if(kdfStrChainCode.size() != 32)
	{
		throw std::string("KDF error");
	}
	const std::string shaChainCode = sha256(kdfStrChainCode);
	const BigInt<256> chainCode(shaChainCode, 'c');


	//std::cout << "PrivkeyInt: " << privKeyInt << std::endl;
	//std::cout << "ChainCoInt: " << chainCode << std::endl;
	
	
	const BigInt<32> zero;		//Todo: Make zero the default argument
	const ExtendedPrivateKey extendedPrivate(0, zero, zero, chainCode, privKey);

	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();

	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	//std::cout << "Will create gen extra list" << std::endl;
	std::list<ExtraInfo> generationExtra;

	//std::cout << "Will create gen extra 1" << std::endl;

	const ExtraInfo extraInfoSalt("Salt", salt);
	generationExtra.push_back(extraInfoSalt);

	//std::cout << "Will create gen extra 2" << std::endl;
	
	const ExtraInfo extraInfoPassphrase("Passphrase", brainVal);
	generationExtra.push_back(extraInfoPassphrase);
	
	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "brain", thetime, params, generationExtra,
		extendedPublicKey.extendedData.chainString(), Mnemonic(MnemonicBase::DUMMY_EMPTY_MNEMONIC));
	
}
#endif




//Todo: Move to class GenerationMethodsExtended
void GenerationMethodsExtended::createExtendedExtPriv(const std::string& thetime, const std::string& exprivVal, const GenerationParameters& params)
{
	std::cout << "Using extended key from xpriv" << std::endl;
		
	const ExtendedKey extendedKey = decodeHD(exprivVal);
	if(!extendedKey.isPrivate)
	{
		std::cout << "This is not a private extended key" << std::endl;
		throw std::string("Incorrent argument");
	}

	const ExtendedPrivateKey extendedPrivate = decodePrivateHD(extendedKey);	
	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();
	
	std::cout << "Private: " << extendedPrivate.toString() << std::endl;
	std::cout << "Public : " << extendedPublicKey.toString() << std::endl;
	std::cout << std::endl;

	std::list<ExtraInfo> generationExtra;

	GenerationMethodsExtended::saveExtendedFiles(extendedPrivate.toString(), extendedPublicKey, "xprv", thetime, params, generationExtra,
		extendedPublicKey.extendedData.chainString(), Mnemonic(MnemonicBase::DUMMY_EMPTY_MNEMONIC));
}


