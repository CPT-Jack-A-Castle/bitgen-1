

#include "ExtendedAddressCommandline.h"
#include "mnemonic.h"
#include "FileUtil.h"
#include "GenerationParameters.h"
#include "CommandlineParser.h"
#include "GenerationMethods.h"
#include "randomUtils.h"
#include "MnemonicCommandline.h"
#include "GenerationMethods.h"
#include "GenerationMethodsExtended.h"

#include <iostream>
#include <stdlib.h>

#include <time.h>



void calcDerivation(const std::vector<std::string>& args)
{	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen derivation extPriv derivationPath ..." << std::endl;
		return;
	}	
	
	std::string xpriv(args[1]);
	std::string givenPath;
	bool useLegacy(false);
	
	if(xpriv == "mnemonic")
	{
		if(args.size() < 4)
		{
			std::cout << "Usage: bitgen derivation mnemonic MNEMONIC derivationPath ..." << std::endl;
			return;
		}	
		
		std::cout << "Got private as mnemonic" << std::endl;
		const std::string mnemonicStr(args[2]);
		const Mnemonic mnemonic(mnemonicStr);
		
		//Todo: Passphrase????
		const ExtendedPrivateKey extendedPrivate = mnemonic.getExtendedPrivFromMnemonic("");
		
		const std::string extendedPriv = extendedPrivate.toString();
		std::cout << "Extended private: " << extendedPriv << std::endl;
		xpriv = extendedPriv;
		
		
		givenPath = (args[3]);		
		
		if(args.size() >= 5)
		{
			//std::cout << "Got extra arg" << std::endl;
			const std::string extra(args[4]);
			if(extra == "printextendedlegacy")
			{
				std::cout << "Using Legacy format for extended keys for currency: " << getCurrencyName() << std::endl;
				useLegacy = true;
			}
			else
			{
				std::cout << "Unknown argument: " << extra << std::endl;
				throw std::string("Unknown argument");
			}
		}		
	}
	else
	{
		givenPath = args[2];
		
		if(args.size() >= 4)
		{
			//std::cout << "Got extra arg" << std::endl;
			const std::string extra(args[3]);
			if(extra == "printextendedlegacy")
			{
				std::cout << "Using Legacy format for extended keys for currency: " << getCurrencyName() << std::endl;
				useLegacy = true;
			}
			else
			{
				std::cout << "Unknown argument: " << extra << std::endl;
				throw std::string("Unknown argument");
			}
		}
		
	}
	
	
	//std::cout << "Original path: " << givenPath << std::endl;	
	const std::string mypath = DerivationPath::expandShorthands(givenPath);
	//std::cout << "Expanded path: " << mypath << std::endl;	
	
	
	const DerivationPath derivationPath(mypath); //DerivationPath::getDerivationPath(mypath));
	
	std::cout << "Derivation path: " << derivationPath.toString() << std::endl;



	const ExtendedKey extendedKey = decodeHD(xpriv, true);
	
	//std::cout << "READY DECODING HD key" << std::endl;
	
	if(extendedKey.isPrivate)
	{
		//throw std::string("Internal error, not extended private");
		const ExtendedPrivateKey privKey = decodePrivateHD(extendedKey);


		//std::cout << "Extended priv key: \n" << privKey.toString() << std::endl;
		//std::cout << "Start priv key : " << privKey.toExtFormat() << std::endl;
		//std::cout << std::endl;
	

		//std::cout << "Derivation path: " << derivationPath.toString() << std::endl;
		//std::cout << std::endl;

		const ExtendedPrivateKey resultKey = privKey.derive(derivationPath);

		const ExtendedPublicKey pubKey = resultKey.getPub();
		const ExtendedPublicKey pubKeyClean = pubKey.getWithoutDeptAndParent();


		std::cout << "Result priv key : " << resultKey.toString() << std::endl;
		std::cout << "Result pub key  : " << pubKey.toString() << std::endl;
		std::cout << "Clean pub key   : " << pubKeyClean.toString() << std::endl;
		//std::cout << "Result pub clean info: " << std::endl << pubKeyClean.infoString() << std::endl;
		
		if(useLegacy)
		{
			std::cout << std::endl;
			std::cout << "Priv key legacy: " << resultKey.toString(true) << std::endl;
			std::cout << "Pub key legacy : " << pubKey.toString(true) << std::endl;
		}
		
		
		if(false)
		{
			std::cout << std::endl;
			std::cout << "Result priv key info: \n" << resultKey.infoString() << std::endl;
		}
	}
	else
	{
		const ExtendedPublicKey pubKey = decodePublicHD(extendedKey);

		std::cout << "Start public key : " << pubKey.toString() << std::endl;

		const ExtendedPublicKey derived = pubKey.derive(derivationPath);

		std::cout << "Result pub key: " << derived.toString() << std::endl;
		std::cout << std::endl;
		std::cout << "Result pub key info: \n" << derived.infoString() << std::endl;	
	}
}





void infoForAnyExtended(const std::vector<std::string>& args)
{	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen extended infopriv PRIVEXT" << std::endl;	

		return;
	}	
	
	
	const std::string extended(args[2]);
		
	const ExtendedKey extendedKey = decodeHD(extended);
	
	if(extendedKey.isPrivate)
	{
		const ExtendedPrivateKey getExtendedPrivateKey = decodePrivateHD(extendedKey);	
		const ExtendedPublicKey extendedPublicKey = getExtendedPrivateKey.getPub();

		std::cout << "Extended info:\n" << getExtendedPrivateKey.infoString() << std::endl;
		std::cout << "Extended priv: " << getExtendedPrivateKey.toString() << std::endl;	
		std::cout << "Extended pub : " << extendedPublicKey.toString() << std::endl;			
	}
	else
	{
		//const ExtendedPrivateKey getExtendedPrivateKey = decodePrivateHD(extendedKey);	
		//std::cout << "Extended priv: " << getExtendedPrivateKey.toExtFormat() << std::endl;	
		
		const ExtendedPublicKey extendedPublicKey = decodePublicHD(extendedKey);
		std::cout << "Extended pub : " << extendedPublicKey.toString() << std::endl;			
		std::cout << std::endl;

		std::cout << "Extended info:\n" << extendedPublicKey.infoString() << std::endl;
	}

}



//Todo: REMOVE, use infoForAnyExtended() instead
void infoForPrivateExtended(const std::vector<std::string>& args)
{	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen extended infopriv PRIVEXT" << std::endl;	

		return;
	}	
	
	
	const std::string xpriv(args[2]);
		
	const ExtendedKey extendedKey = decodeHD(xpriv);
	if(!extendedKey.isPrivate)
	{
		std::cout << "This is not a private extended key" << std::endl;
		return;
	}

	const ExtendedPrivateKey getExtendedPrivateKey = decodePrivateHD(extendedKey);	
	const ExtendedPublicKey extendedPublicKey = getExtendedPrivateKey.getPub();

	std::cout << "Extended info:\n" << getExtendedPrivateKey.infoString() << std::endl;
	std::cout << "Extended priv: " << getExtendedPrivateKey.toString() << std::endl;	
	std::cout << "Extended pub : " << extendedPublicKey.toString() << std::endl;	
}


//Todo: REMOVE, use infoForAnyExtended() instead
void infoForPublicExtended(const std::vector<std::string>& args)
{	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen extended infopublic PUBEXT" << std::endl;	

		return;
	}	
	
	
	const std::string xpub(args[2]);
	
	
	const ExtendedKey extendedKey = decodeHD(xpub);
	if(extendedKey.isPrivate)
	{
		std::cout << "This is not a public extended key" << std::endl;
		return;
	}

	const ExtendedPrivateKey getExtendedPrivateKey = decodePrivateHD(extendedKey);	
	const ExtendedPublicKey extendedPublicKey = decodePublicHD(extendedKey);

	std::cout << "Extended info:\n" << getExtendedPrivateKey.infoString() << std::endl;
	//std::cout << "Extended priv: " << getExtendedPrivateKey.toExtFormat() << std::endl;	
	std::cout << "Extended pub : " << extendedPublicKey.toString() << std::endl;	
}







PrivKey getFirstReceivePrivkeyFromExtendedPrivate(const ExtendedPrivateKey& extendedPrivate, std::string& path)
{
	path = DerivationPath::expandShorthands("receive");

	const DerivationPath derivationPath(path);
			
	const ExtendedPrivateKey leaf = extendedPrivate.derive(derivationPath);
	
	const PrivKey privKey = leaf.privKey;
	
	return privKey;
}




PrivKey mnemonicToFirstPrivateKey(const Mnemonic& mnemonicObj, std::string& path)
{
	const ExtendedPrivateKey extendedPrivate = mnemonicObj.getExtendedPrivFromMnemonic();
	const std::string extPrivStr = extendedPrivate.toString();
		
	const PrivKey privKey = getFirstReceivePrivkeyFromExtendedPrivate(extendedPrivate, path);
	
	return privKey;
}





void calcFirstHdAddress(const std::vector<std::string>& args)
{
	const int words = 24;
	const int numBytes = 32; //256 bit
			
	std::cout << "Generating " << numBytes << " random bytes" << std::endl;
	std::cout << std::endl;
	
	const std::string random = getFromDevRandom(numBytes);
	
	if(random.size() != numBytes)
	{
		std::cout << "Buf size: " << random.size() << " num bytes: " << numBytes << std::endl;
		throw std::string("Internal error, incorrect number random bytes");
	}
	

	const BigInt<256> privkey(random, 'c');


	const Mnemonic mnemonicObj(privkey, words);
	
	const std::string mnemonic = mnemonicObj.toStr();		
	std::cout << "Generated mnemonic: " << std::endl << mnemonic << std::endl;


	std::string path;
	const PrivKey privKey = mnemonicToFirstPrivateKey(mnemonicObj, path);
	std::cout << "The path: " << path << std::endl;
	std::cout << std::endl;
	
	const BitcoinEllipticCurve ec;

	const PubAddress pubAddress = privKey.getAddress(ec);

	std::cout << "Calculating first HD address" << std::endl;

	std::cout << "First receive keypair for this xpriv: " << std::endl;
		
	std::cout << "Private: " << privKey.toString() << std::endl;
	std::cout << "Public : ";
	if(usesCashAddress())
	{
		std::cout << pubAddress.toFullCashAddrString();
	}
	else
	{
		std::cout << pubAddress.toString();
	}
	std::cout << std::endl;			
		
	time_t t = time(0);
	const std::string thetime = removeNewline(asctime(localtime(&t)));


	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Info", "The BIP39 mnemonic can be used as seed in a HD wallet");	
	generationExtra.push_back(extraInfo);

	const ExtraInfo extraInfo2("Derivation path", path);	
	generationExtra.push_back(extraInfo2);
	
	const std::string generator = "Random with HD first address derivation";
	const GenerationParameters params;
	
	GenerationMethods::saveAllFiles(pubAddress, privKey.toString(), generator, generationExtra, 
		thetime, params, mnemonicObj);
}


void calcAddressDerivation(const std::vector<std::string>& args)
{	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen addressderivation extAddr path [endnum] ..." << std::endl;
		std::cout << " extAddr is an extended address, starting with \"xprv\" or \"xpub\"" << std::endl;
		std::cout << " path is the derivation path, for example \"m/0/0\"" << std::endl;
		std::cout << " The path may be specified by shorthands, such as \"receive\" or \"change\"" << std::endl;
		std::cout << " The following shorthands exist:" << std::endl;
		std::cout << "  receive     - receive addresses (Aliases: coinomiRec, copayRec, jaxxRec exodus)" << std::endl;
		std::cout << "  change      - change addresses (Aliases: coinomiCha, copayCha, jaxxCha)" << std::endl;
		std::cout << "  electrumRec - Electrum receive addresses" << std::endl;
		std::cout << "  electrumCha - Electrum change addresses" << std::endl;
		std::cout << std::endl;
		std::cout << " Example: bitgen addressderivation xprv9s21ZrQH143K3Gq13ThqwLogxZAMeBHrvXwWPK3uVWh23nY295AQawgFW9mSQQdNymRdDGztaXQBxoBMrHbDceuj4fAQXzz9YgU6sSCVTwt change 10" << std::endl;
		
		return;
	}	
	
	const std::string givenxpriv(args[1]);
	
	
	std::string xpriv(givenxpriv);
	std::string givenpath;
	std::string endNumStr;
	
	bool printExtendedLegacy(false);
	
	//std::cout << "XPRIV: " << xpriv << std::endl;
	
	if(xpriv == "mnemonic" || xpriv == "electrummnemonic")
	{
		if(args.size() < 4)
		{
			std::cout << "Usage: bitgen addressderivation mnemonic MNEMONIC path [endnum] ..." << std::endl;
			return;
		}	
		
		
		const std::string mnemonicStr(args[2]);
		
		givenpath = args[3];		
		
		if(args.size() > 4)
		{
			endNumStr = args[4];
		}

		if(args.size() > 5)
		{
			std::cout << "Got extra arg" << std::endl;
			const std::string extra(args[5]);
			if(extra == "printextendedlegacy")
			{
				std::cout << "PRINTING EXTENDED LEGACY" << std::endl;
				printExtendedLegacy = true;				
			}
			else
			{
				std::cout << "Unknown arg: " << extra << std::endl;
				throw std::string("Unknown command line arg");
			}
		}
		
		
		if(xpriv == "mnemonic")
		{
			const Mnemonic mnemonic(mnemonicStr);
		
			//Todo: Passphrase????
			const ExtendedPrivateKey extendedPrivate = mnemonic.getExtendedPrivFromMnemonic("");
			const ExtendedPublicKey extendedPublic = extendedPrivate.getPub();
		
			const std::string extendedPriv = extendedPrivate.toString();
			std::cout << "Extended private: " << extendedPriv << std::endl;
			std::cout << "Extended public : " << extendedPublic.toString() << std::endl;
			
			if(printExtendedLegacy)
			{
				std::cout << "Ext priv legacy: " << extendedPrivate.toString(true) << std::endl;
				std::cout << "Ext pub legacy : " << extendedPublic.toString(true) << std::endl;			
			}
			
			xpriv = extendedPriv;
		}
		else
		{
			std::cout << "Using electrum mnemonic" << std::endl;
			const ElectrumMnemonic mnemonic(mnemonicStr);
		
			const ExtendedPrivateKey extendedPrivate = mnemonic.getPrivateFromElectrumMnemonic();	
			const ExtendedPublicKey extendedPublic = extendedPrivate.getPub();

			//Todo: Passphrase????
			//const ExtendedPrivateKey extendedPrivate = getExtendedPrivFromMnemonic(mnemonic.toStr(), "");
		
			const std::string extendedPriv = extendedPrivate.toString();
			std::cout << "Extended private: " << extendedPriv << std::endl;
			std::cout << "Extended public : " << extendedPublic.toString() << std::endl;
			
			xpriv = extendedPriv;
			
		}
		
		
		
	}
	else
	{
		givenpath = args[2];
		
		if(args.size() > 3)
		{
			endNumStr = args[3];
		}
		
		if(args.size() > 4)
		{
			//std::cout << "Got extra arg" << std::endl;
			const std::string extra(args[4]);
			if(extra == "printextendedlegacy")
			{
				std::cout << "PRINTING EXTENDED LEGACY" << std::endl;
				printExtendedLegacy = true;
			}
			else
			{
				std::cout << "Unknown arg: " << extra << std::endl;
				throw std::string("Unknown command line arg");
			}
		}
		
	}
	
	const ExtendedKey extendedKey = decodeHD(xpriv, true);
	
	
	
	const std::string path = DerivationPath::expandShorthands(givenpath);

	std::cout << "Got pathstring: " << givenpath << " Endnumstr: " << endNumStr << std::endl;

	int endNum(-1);
	if(!endNumStr.empty())
	{
		endNum = atoi(endNumStr.c_str());
	}
	

	std::cout << "Performning address derivation" << std::endl;

	const DerivationPath origDerivationPath(path); //  = DerivationPath::getDerivationPath(path);

	if(!extendedKey.isPrivate)	//Public
	{
		std::cout << "Converting path to public" << std::endl;
	}	

	const DerivationPath derivationPath = extendedKey.isPrivate ? (origDerivationPath 
																	/*DerivationPath::getDerivationPath(path)*/) : 
																	origDerivationPath.getPub();
	
	
	
	std::cout << std::endl;
	std::cout << "Derivation path: " << derivationPath.toString();

	std::string content;
	content += derivationPath.toString();


	if(endNum == -1)
	{
		endNum = derivationPath.getLast().val.intVal();
	}
	else
	{
		std::cout << " to " << endNum;
		content += " to ";
		content += intToString(endNum);		
	}
	
	std::cout << std::endl;
	content += "\n\n";


	const ChildNum startItem = derivationPath.getLast();
	const DerivationPath derivationPathShort = derivationPath.withoutLast();
	const BigInt<32> finalNum(endNum + 1);
	
	//std::cout << "Last: " << last.toString() << std::endl;		
	//std::cout << "Derivation without last: " << derivationPathShort.toString() << std::endl;

	const std::string filenameStart = std::string("derddr_") +  getCurrencyShortName() + "_" + 
			startItem.toString() + "_" + intToString(endNum) + "_";

	if(extendedKey.isPrivate)
	{
		const ExtendedPrivateKey extendedPrivKey = decodePrivateHD(extendedKey);

		const ExtendedPrivateKey derived = extendedPrivKey.derive(derivationPathShort);
		std::cout << "Derived private key: " << derived.toString() << std::endl;
		
		const ExtendedPublicKey myderivedPub = derived.getPub();
		std::cout << "Derived public key : " << myderivedPub.toString() << std::endl;
		
		if(printExtendedLegacy)
		{
			std::cout << "Private key legacy: " << derived.toString(true) << std::endl;
			std::cout << "public key legacy : " << myderivedPub.toString(true) << std::endl;			
		}
		
		std::cout << std::endl;
		
		const BitcoinEllipticCurve ec;
		

		for(BigInt<32> i = startItem.val ; i < finalNum ; i++)
		{
			std::list<ChildNum> thisPath;
			thisPath.push_back(i);
			const DerivationPath thisDerPath(thisPath, false);
			
			const ExtendedPrivateKey leaf = derived.derive(thisDerPath);				

			const PrivKey privKey = leaf.privKey;

			const PubAddress pubAddress = privKey.getAddress(ec);
		
			std::cout << i.strDec() << " Private: " << privKey.toString() << " ";
			std::cout << "Public: ";
			if(usesCashAddress())
			{
				std::cout << pubAddress.toCashAddrString();
			}
			else
			{
				std::cout << pubAddress.toString();
			}
			std::cout << std::endl;
			
			
			content += i.strDec();
			content += " ";
			content += privKey.toString();
			content += " ";			
			content += pubAddress.toString();
			content += "\n";
			
		}
		
		const ExtendedPublicKey derivedPub = derived.getPub();
		
		const std::string contentHash = sha256(content).substr(0, 10);
		
		const std::string filename = filenameStart + hexString(contentHash) + "_" + derivedPub.toString().substr(60) + "_private.txt";
		
		std::cout << std::endl;
		std::cout << "Saving file: " << filename << std::endl;
		fileWrite(filename, content);
	}
	else
	{
		const ExtendedPublicKey extendedPubKey = decodePublicHD(extendedKey);
		
		const ExtendedPublicKey derived = extendedPubKey.derive(derivationPathShort);
		
		std::cout << std::endl;

		for(BigInt<32> i = startItem.val ; i < finalNum ; i++)
		{
			std::list<ChildNum> thisPath;
			thisPath.push_back(i);
			
			const DerivationPath thisDerPath(thisPath, true);
			const ExtendedPublicKey leaf = derived.derive(thisDerPath);				
				
			const PubKey pubKey = leaf.pubKey;
			const PubAddress pubAddress = pubKey.getAddress();
				
			std::cout << i.strDec() << " Public: " << pubAddress.toString();
			if(getCurrencyShortName() == "bch" || getCurrencyShortName() == "bch_slp")
			{
				std::cout << " " << pubAddress.toFullCashAddrString();
			}
			std::cout << std::endl;

			content += i.strDec();
			content += " ";
			content += pubAddress.toString();
			content += "\n";
			
		}
		
		
		const std::string filename = filenameStart + derived.toString().substr(60) +  "_public.txt";
		
		std::cout << std::endl;
		std::cout << "Saving file: " << filename << std::endl;
		fileWrite(filename, content);
	}

}











void createExtendedAccount(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen extended genType ..." << std::endl;
		std::cout << " genType: random, mnemonic, seed, hash, dice, hex, brain" << std::endl;
		
		return;
	}	
	
	const std::string genType(args[1]);
	
	if(genType == "random")
	{
#ifndef __linux
		std::cerr << "Random is not supported on Windows. Use \"hash\" instead" << std::endl;
		return;
#endif
		
		//std::cout << "Will parse all extra params" << std::endl;
		const GenerationParameters params = parseTheExtraParams(args, 1, true);

		std::cout << "Generating random" << std::endl;
		GenerationMethodsExtended::createExtendedRandom(thetime, params);
	}
	else if(genType == "hash")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended hash HASHVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string hashval(args[2]);
		GenerationMethodsExtended::createExtendedHash(thetime, hashval, params);
	}
	else if(genType == "seed")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended seed SEEDVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string seedval(args[2]);
		GenerationMethodsExtended::createExtendedSeed(thetime, seedval, params);
	}
	else if(genType == "mnemonic")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended mnemonic MNEMONICVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string mnemonic(args[2]);
		GenerationMethodsExtended::createExtendedMnemonic(thetime, mnemonic, params);
	}		
	else if(genType == "hex")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended hex HEXVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string hexval(args[2]);
		GenerationMethodsExtended::createExtendedHex(thetime, hexval, params);
	}
	else if(genType == "dice")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended dice DICEVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string diceval(args[2]);
		GenerationMethodsExtended::createExtendedDice(thetime, diceval, params);
	}
	else if(genType == "priv")
	{
		if(args.size() < 3)
		{
			std::cerr << "Usage: bitgen extended extpriv EXTPRIVVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	
		const GenerationParameters params = parseTheExtraParams(args, 2);
		
		std::string extprivVal(args[2]);
		GenerationMethodsExtended::createExtendedExtPriv(thetime, extprivVal, params);
	}
	else if(genType == "brain")
	{
		//std::cout << "OK, brain choosen" << std::endl;
		
		if(args.size() < 4)
		{
			std::cerr << "Usage: bitgen extended brain email/salt BRAINVAL ..." << std::endl;
			throw std::string("Incorrect usage");
		}	

		//std::cout << "Will parse extra params" << std::endl;
		const GenerationParameters brainParams = parseTheExtraParams(args, 3);
		
		
		std::string saltVal(args[2]);
		std::string extbrainVal(args[3]);
		
		//std::cout << "Will call createExtendedExtBrain" << std::endl;
		
		GenerationMethodsExtended::createExtendedExtBrain(thetime, saltVal, extbrainVal, brainParams);
	}
	else if(genType == "infopriv")	//Todo: REMOVE, use "info" instead
	{
		infoForPrivateExtended(args);
	}
	else if(genType == "infopub")	//Todo: REMOVE, use "info" instead
	{
		infoForPublicExtended(args);
	}	
	else if(genType == "info")
	{
		infoForAnyExtended(args);	//Todo
	}		
	else
	{
		std::cerr << "Unknown extended option: " << genType << std::endl;
		throw std::string("Unknown extended option");
	}
}




