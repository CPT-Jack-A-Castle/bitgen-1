


#include "MnemonicCommandline.h"
#include "GenerationParameters.h"
#include "CommandlineParser.h"
#include "randomUtils.h"
#include "mnemonic.h"
#include "extraInfo.h"
#include "txtGeneration.h"
#include "bitgenVersion.h"
#include "FileUtil.h"
#include "printPS.h"
#include "random.h"

#include <stdlib.h>
#include <iostream>



int calculateNumDiceNeeded(const int numBits)
{
	BigInt<512> val(BigInt<512>::onePattern());
	const int numShift = 512 - numBits;
	BigInt<512> valStart(val >> numShift);
		
	BigInt<512> zero;
	BigInt<512> six(6);
		
	int i = 0;
	for( ; valStart != zero ; i++)
	{
		//std::cout << "Val: " << valStart << std::endl;
		valStart /= six;
	}

	const int numDice(i);
	return numDice;
}





void saveMnemonicResultInternal(const Mnemonic& mnemonic,
						const std::string& thetime,
						const GenerationParameters& params,
						const std::string& genMethod, const std::list<ExtraInfo>& generationExtra,
						const std::string& xpriv,
						const ExtendedPublicKey& extendedPublicKey, //const std::string& xpub,
						const std::string& derivedPubStrWithExtraInfo,
						const std::string& derivedXpub,						
						const bool includedExtendedAddress)
{	
	//std::cout << "Mnemonic: " << mnemonic.toStr() << std::endl;
	
	const std::string privKeyAgain = mnemonic.getAsNumber();

	std::string currencyExtra;
	if(params.getCurrencySpecific())
	{
		currencyExtra += getCurrencyShortName();
		currencyExtra += "_";
	}

	//std::cout << "Taking hash of: \"" << xpub << "\"" << std::endl;
	
	const std::string hash = sha256(extendedPublicKey.toString());		//?????

		
	{	
		
		//Todo: Two object for private parts and public parts
		
		const FilePair content = generateMnemonicFile(genMethod, generationExtra, thetime, params.getAccountName(), mnemonic,
				versionNumber, applicationName, params.getCurrencySpecific(), xpriv, extendedPublicKey.toString(), derivedPubStrWithExtraInfo, derivedXpub, includedExtendedAddress); //, numWords);
	
	

	
		const std::string filename("mnemonic_" + currencyExtra + intToString(mnemonic.numberWords()) + "_" + hexString(hash) + "_private.txt");

		std::cout << std::endl;
		std::cout << "Saving file: " << filename << std::endl;
	
		fileWrite(filename, content.privateFile);
		
		
		if(includedExtendedAddress)
		{
			const std::string publicFilename("mnemonic_" + currencyExtra + intToString(mnemonic.numberWords()) + "_" + hexString(hash) + "_share.txt");

			std::cout << "Saving file: " << publicFilename << std::endl;
	
			fileWrite(publicFilename, content.publicFile);
		}
		
	}
	
	
	
	
	const PostscriptGenerator postscriptGenerator(versionNumber, applicationName, LANG_EN, 
		PostscriptGenerator::ADDRTYPE_NORMAL, params.getCurrencySpecific());
	
	
	
	{
		const std::string postscript = postscriptGenerator.generatePrivateMnemonic(
				mnemonic.toStr(), mnemonic.numberWords(), params.getAccountName(),
				genMethod, thetime, generationExtra, xpriv, extendedPublicKey, derivedXpub);

		const std::string psFilename("mnemonic_" + currencyExtra + intToString(mnemonic.numberWords()) + "_" + hexString(hash) + "_private.ps");

		std::cout << "Saving file: " << psFilename << std::endl;
	
		fileWrite(psFilename, postscript);
	}
	
		
	if(includedExtendedAddress) //!xpub.empty())
	{
		const std::string pubPostscript = postscriptGenerator.generatePublicMnemonic(
			mnemonic.toStr(), mnemonic.numberWords(), params.getAccountName(), 
			genMethod, thetime, generationExtra, xpriv, extendedPublicKey, derivedXpub);

		const std::string pubPsFilename("mnemonic_" + currencyExtra + intToString(mnemonic.numberWords()) + "_" + hexString(hash) + "_share.ps");
	
		std::cout << "Saving file: " << pubPsFilename << std::endl;
	
		fileWrite(pubPsFilename, pubPostscript);
		
	}
	
}






void saveResultForMnemonic(const Mnemonic & mnemonic, const std::string& thetime,
						const GenerationParameters& params, //const std::string& not_used_random,
						const std::string& genMethod, std::list<ExtraInfo>& generationExtra)
{
	const ExtendedPrivateKey extendedPrivate = mnemonic.getExtendedPrivFromMnemonic(params.getPassword());
	const ExtendedPublicKey extendedPublicKey = extendedPrivate.getPub();


	const std::string derivationStr = DerivationPath::getCurrencyDerivationPath();
	std::cout << "DerivationStr: " << derivationStr << std::endl;

	const DerivationPath derivationPath(derivationStr);
	
	const ExtendedPrivateKey derivedPrivateKey = extendedPrivate.derive(derivationPath);
	const ExtendedPublicKey derivedPublicKey = derivedPrivateKey.getPub();
	std::cout << "DERIVED Public Key : " << derivedPublicKey.toString() << std::endl;
	const ExtendedPublicKey canonicalDerivedPublicKey = derivedPublicKey.getWithoutDeptAndParent();
	const std::string derivedPubStrWithExtraInfo = derivedPublicKey.toString();

	const std::string extPrivStr = extendedPrivate.toString();
	const std::string extPubStr = extendedPublicKey.toString();

	const std::string derivedPrivStr = derivedPrivateKey.toString();
	const std::string derivedPubStr = canonicalDerivedPublicKey.toString();

	std::cout << "Mnemonic           : " << mnemonic.toStr() << std::endl;

	
	if(params.getGenerateExtended())
	{
		//std::cout << "Generating extended address" << std::endl;

		std::cout << "Extended privkey   : " << extPrivStr << std::endl;
		std::cout << "Extended pubkey    : " << extPubStr << std::endl;
		
		std::cout << "Derivation for " << getCurrencyName() << " (" << derivationStr << "):" << std::endl; 
		std::cout << "Derived privkey    : " << derivedPrivStr << std::endl;
		
		std::cout << "Derived orig pubkey: " << derivedPubStrWithExtraInfo << std::endl;		
		std::cout << "Derived pubkey     : " << derivedPubStr << std::endl;

		if(!params.getPassword().empty())
		{
			const ExtraInfo extraPass("Password", params.getPassword());
			generationExtra.push_back(extraPass);
		}
	}

	saveMnemonicResultInternal(mnemonic, thetime, params, genMethod,
			generationExtra, extPrivStr, extendedPublicKey /*extPubStr*/, derivedPubStrWithExtraInfo, derivedPubStr, 
			params.getGenerateExtended());			
}





//Returns numBytes
int verifyNumWords(const int numWords)
{
	if(numWords != 12 && numWords != 15 && numWords != 18
		 && numWords != 21 && numWords != 24)
	{
		std::cout << "Incorrect number of words: " << numWords << std::endl;
		std::cout << "Allowed values: " << "12, 15, 18, 21 or 24" << std::endl;
		throw std::string("Incorrect number text words");
	}



	if(numWords < 12)
	{
		std::cout << std::endl;
		std::cout << "WARNING:" << std::endl;		
		std::cout << "WARNING: This random number does not have enough entropy for crypto currency!" << std::endl;
		std::cout << "WARNING:" << std::endl;
		std::cout << std::endl;
	}


	const int num32bit = numWords / 3;
	const int numBytes = 4 * num32bit;
	const int numBits = 8 * numBytes;

	std::cout << "Text words     : " << numWords << std::endl;
	std::cout << "Entropy [bits] : " << numBits << std::endl;
	std::cout << std::endl;
	
	return numBytes;
}







Mnemonic getMnemonicFromGenerationType(const std::string& genType, GenerationParameters& paramsOut, 
	const std::vector<std::string>& args,
	const int commandLineStartPos)
{	
	if(genType == "random")
	{
		paramsOut = parseTheExtraParams(args, commandLineStartPos, true);
		const int numBytes = verifyNumWords(paramsOut.getWords());
				
		std::cout << "Generating " << numBytes << " random bytes" << std::endl;
		
		const std::string random = getFromDevRandom(numBytes);
		std::cout << std::endl;
	
		if(random.size() != numBytes)
		{
			std::cout << "Buf size: " << random.size() << " num bytes: " << numBytes << std::endl;
			throw std::string("Internal error, incorrect number random bytes");
		}
		
		const BigInt<256> privkey(random, 'c');

		const Mnemonic mnemonicObj(privkey, paramsOut.getWords());
		return mnemonicObj;
	}
	else if(genType == "hex")
	{
		std::cout << "HEX CHOOSEN: " << args.size() << " and " << (commandLineStartPos + 2) << std::endl;
		
		if(args.size() < (commandLineStartPos + 2))
		{
			std::cout << "Usage: bitgen genMnemonic numWords hex HEXVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		paramsOut = parseTheExtraParams(args, commandLineStartPos + 1);
		
		const int numBytes = verifyNumWords(paramsOut.getWords());
		
		const std::string hexVal(args[commandLineStartPos + 1]);		
		
		if(hexVal.size() != (numBytes * 2))
		{
			std::cerr << std::endl;
			std::cerr << "Incorrect amount data given. Got " << hexVal.size() << " hex digits, want " << (numBytes * 2) << " hex digits" << std::endl;
			throw std::string("Not enough data");
		}
				
		std::cout << "HexVal:   " << hexVal << std::endl;
		
		const std::string binStr = convertFromHex(hexVal);
		
		const std::string hexValUpper = hexString(binStr);
				
		const BigInt<256> privkey = BigInt<256>::fromHex(hexValUpper);
		//std::cout << "PrivData: " << privkey << std::endl;
		
		const Mnemonic mnemonicObj(privkey, paramsOut.getWords());
		return mnemonicObj;
	}
	else if(genType == "mnemonic")
	{
		std::cout << "Creating from mnemonic" << std::endl;
		
		if(args.size() < (commandLineStartPos + 2))
		{
			std::cout << "Usage: bitgen genMnemonic mnemonic MNEMONICVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		paramsOut = parseTheExtraParams(args, commandLineStartPos + 1);
		
		const int numBytes = verifyNumWords(paramsOut.getWords());
		
		const std::string mnemonicStr(args[commandLineStartPos + 1]);
		std::cout << "Got mnemonic: " << mnemonicStr << std::endl;
		
		const Mnemonic mnemonicObj(mnemonicStr);
		return mnemonicObj;

		//const BigInt<256> privKey = mnemonicObj.toPrivKey();
	}	
	else if(genType == "hash")
	{
		//std::cout << "Creating from hash" << std::endl;
		
		if(args.size() < (commandLineStartPos + 2))
		{
			std::cout << "Usage: bitgen genMnemonic numWords hash HASHVAL ..." << std::endl;
			throw std::string("Incorrect usage");			
		}	
		
		paramsOut = parseTheExtraParams(args, commandLineStartPos + 1);
		
		const int numBytes = verifyNumWords(paramsOut.getWords());
		
		const std::string hashStr(args[commandLineStartPos + 1]);
		
		std::cout << "Got hashStr: " << hashStr << std::endl;
	
		const int minHashSize =  paramsOut.getWords() * 10;
		std::cout << "Minimum permitted hash size: " << minHashSize << ", got: " << hashStr.size() << std::endl;
		if(hashStr.size() < minHashSize)
		{
			std::cerr << "Error, at least " << minHashSize << " characters needed, got: " << hashStr.size() << std::endl;
			
			throw std::string("Need larger hash");
		}
	
		const std::string sha = sha256(hashStr);
		const BigInt<256> privKey(sha, 'c');
	
	
		const std::string priv = privKey.getLastBytes(numBytes);
			
		std::cout << std::endl;
		std::cout << "Generated private data: " << hexString(priv) << std::endl;

		const Mnemonic mnemonicObj(privKey, paramsOut.getWords());
		return mnemonicObj;		
	}
	else if(genType == "dice")
	{
		std::cout << std::endl;
		std::cout << "Creating from dice" << std::endl;
		
		if(args.size() < 3)
		{
			std::cout << "Usage: bitgen genMnemonic [numWords] dice DICEVAL ..." << std::endl;
			throw std::string("Incorrect usage");			
		}	
		
		paramsOut = parseTheExtraParams(args, commandLineStartPos + 1);
		
		const int numBytes = verifyNumWords(paramsOut.getWords());
		
		const std::string diceStr(args[commandLineStartPos + 1]);
		std::cout << "Got diceval: " << diceStr << std::endl;
		
		const int numBits = numBytes * 8;
		
		const int numDice = calculateNumDiceNeeded(numBits);
		
		
		if(diceStr.size() != numDice)
		{
			std::cerr << "Should have exactly " << numDice << " dice values, got: " << diceStr.size() << std::endl;
			std::cerr << "Need " << numDice << " dice values" << std::endl;
			throw std::string("Incorrect num dice");
		}
		
		const BigInt<256> privKey = getRandomNumFrom6SideDice(diceStr, numDice);
		
		const Mnemonic mnemonicObj(privKey, paramsOut.getWords());
		return mnemonicObj;
	}	
	else
	{
		std::cout << "Unknown generation type: " << genType << std::endl;
		throw std::string("Unknown generation type");		
	}
}




std::string genTypeToGenInfo(const std::string& genType)
{
	if(genType == "random")
	{
		return "/dev/random";
	}
	else if(genType == "hex")
	{
		return "hex";
	}
	else if(genType == "mnemonic")
	{
		return "mnemonic";
	}
	else if(genType == "hash")
	{
		return "hash";
	}
	else if(genType == "dice")
	{
		return "dice";
	}
	else
	{
		throw (std::string("Unknown generation type: ") + genType);
	}
		
	
	return ("GenType:" + genType);
}
	
	

void createMnemonicAccount(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen genMnemonic genType..." << std::endl;
		std::cout << "        genType: random, hex, hash, dice, mnemonic, " << std::endl;
		std::cout << " Example: bitgen genMnemonic random" << std::endl;
		return;
	}	
	
	const std::string genTypeStr(args[1]);

	std::string generationInfo;
		
	try
	{
		generationInfo = genTypeToGenInfo(genTypeStr);
	}
	catch(const std::string& err)
	{	
		std::cout << "Incorrect generation type: " << genTypeStr << std::endl;
		std::cout << "Usage: bitgen genMnemonic genType..." << std::endl;
		std::cout << "        genType: random, hex, hash, dice, mnemonic, " << std::endl;
		std::cout << " Example: bitgen genMnemonic random words 24" << std::endl;
		
		throw std::string("Argument error");			
	}
		
	std::cout << std::endl;
		
	std::string not_used_random;
	GenerationParameters params;
	const int commandLineStartPos(1);	
	const Mnemonic mnemonicObj = getMnemonicFromGenerationType(genTypeStr, params, args, commandLineStartPos); 
					
	std::list<ExtraInfo> generationExtra;	//Todo: Used?

	std::string wallet;	//Todo?		
	if(!wallet.empty())
	{
		const ExtraInfo extraInfo("Wallet", genTypeStr);
		generationExtra.push_back(extraInfo);	
	}


	saveResultForMnemonic(mnemonicObj, thetime, params, /*random,*/ generationInfo, generationExtra);
}


