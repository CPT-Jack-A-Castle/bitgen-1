/**
 * bitgencli.cpp - Bitcoin address generator
 *
 * Copyright (C)2015 The bitgen developers <bitgen@openmailbox.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
 
/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
*/
 



#include "miniPriv.h"
#include "test/unittest.h"
#include "privKey.h"
#include "pubKey.h"
#include "bitgenVersion.h"

#include "commandLine.h"
#include "keyDerivationFunction.h"
#include "RangeSearcher.h"
#include "HierarchialRandom.h"
#include "txtGeneration.h"
#include "currencySpecific.h"
#include "license.h"
#include "GenerationParameters.h"
#include "usagePrintout.h"
#include "GenerationMethods.h"
#include "bitlibVersion.h"
#include "StaticXor.h"
#include "MnemonicCommandline.h"
#include "CommandlineParser.h"
#include "ExtendedAddressCommandline.h"
#include "TransactionCommandline.h"
#include "RootGenerationCommandline.h"
#include "EntityInformationCommandline.h"
#include "MiscCommandline.h"
#include "ElectrumCommandline.h"
#include "FileUtil.h"
#include "bitgenConfig.h"
#include "currencySpecific.h"

#include <time.h>

#include <iostream>


void printCompleteVersion()
{
	std::cout << "bitgen version " << versionNumber << std::endl;
	std::cout << std::endl;
	std::cout << "using bigint " << BigInt<0>::version() << std::endl;
	std::cout << "using bitlib version " << bitlibVersionNumber << std::endl;
	std::cout << std::endl;

	std::cout << "Currency: " << getCurrencyName() << " (" << getCurrencyShortName() << ")" << std::endl;
	std::cout << std::endl;
		
	std::cout << "http://www.bitgen.org/" << std::endl;		
}










void removeOtpFolders(std::vector<std::string>& args)
{
	removeFolderConfig();
}


void setNextNumToUse(std::vector<std::string>& args)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen setnextnum NUMBER" << std::endl;
		return;
	}
	
	const std::string numStr = args[1];
	
	const int num = atoi(numStr.c_str());
	
	std::cout << "Setting next number to use: " << num << std::endl;
	
	setConfiguredNum(num);
}



std::string canonFileName(const std::string& folder)
{
#ifdef __linux
	char* absolutePathRaw = realpath(folder.c_str(), NULL);
	if(absolutePathRaw == NULL)
	{
		std::string errMsg("Folder does not exist: ");
		errMsg += folder;
		
		std::cout << errMsg << std::endl;
		
		throw errMsg;
	}
	
	const std::string absPath(absolutePathRaw);
	free(absolutePathRaw);
	
	return absPath;
#else
	throw std::string("realpath is not supported on windows");
	return "not_supported_on_windows";	
#endif
}


void setOtpFolders(std::vector<std::string>& args)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen otpdir PUBFOLDER DIR1 ... DIRN" << std::endl;
		
		std::cout << std::endl;
	
		std::string confPublicFolder;
		const std::list<std::string> folders = getPublicAndOtpFolders(confPublicFolder);
		
		std::cout << "Configured folders: " << std::endl;
		std::cout << "Public: " << confPublicFolder << std::endl;
		std::cout << std::endl;
		for(std::list<std::string>::const_iterator it = folders.begin() ;
			it != folders.end() ;
			++it)
		{
			const std::string& folder = (*it);
			std::cout << folder << std::endl;
		}
		
		return;
	}	


	std::cout << "Setting OTP folders" << std::endl;
	
	std::list<std::string> folders;
	for(int i = 1 ; i < args.size() ; i++)
	{
		const std::string canonName = canonFileName(args[i]);
		folders.push_back(canonName); //args[i]);
	}
	
	
	
	
	addFoldersToConfig(folders);
	
	for(std::list<std::string>::const_iterator it = folders.begin() ;
		it != folders.end() ;
		++it)
	{
		const std::string& folder = (*it);
		std::cout << "Folder: " << folder << std::endl;
	}
	
}



void getNextNumToUse()
{
	const int nextNum = getConfiguredNum(false);
	
	std::cout << "nextNum: " << nextNum << std::endl;
}




void doBitgenWork(int argc, char* argv[])
{			
	time_t t = time(0);
	const std::string thetime = removeNewline(asctime(localtime(&t)));
	
	std::vector<std::string> args;
	for(int i = 1 ; i < argc ; i++)
	{
		args.push_back(argv[i]);		
	}

	if(argc < 2)
	{
		std::cout << "For help, use \"bitgen-" << getCurrencyShortName() << " help\"" << std::endl;
		throw std::string("Missing argument");
		return;
	}

	const std::string firstArg(argv[1]);


	if(firstArg == "version" || firstArg == "-v")
	{
		printCompleteVersion();
	}
	else if(firstArg == "setlang")
	{
		setLanguage(argc, argv, thetime);
	}	
	else if(firstArg == "brainwallet")
	{
		GenerationMethods::generateBrainWallet(args, thetime);
	}
	//Private key generation
	else if(firstArg == "bulk")
	{
		GenerationMethods::generateBulk(args, thetime);
	}	
	else if(firstArg == "dice")
	{
		GenerationMethods::generateWithDice(args, thetime);
	}
	else if(firstArg == "hash")
	{
		GenerationMethods::generateHash(args, thetime);	
	}
	else if(firstArg == "hex")
	{
		GenerationMethods::generateHex(args, thetime);
	}
	else if(firstArg == "mnemonic")
	{
		GenerationMethods::generateFromMnemonic(args, thetime);		
	}		
	else if(firstArg == "random")
	{
		GenerationMethods::generateRandom(args, thetime);
	}
	//One time pad
	else if(firstArg == "otpgen")
	{
		GenerationMethods::generateOtpParts(args, thetime);
	}
	else if(firstArg == "otp")
	{
		GenerationMethods::generateOtpTotal(args, thetime);
	}			
	else if(firstArg == "otpdir")
	{
		setOtpFolders(args); //, thetime);
	}
	else if(firstArg == "removeotpdir")
	{
		removeOtpFolders(args); //, thetime);
	}					
	//Static xor
	else if(firstArg == "addxor")
	{
		addStaticXor(args, thetime);
	}	
	else if(firstArg == "removexor")
	{
		removeStaticXor(args, thetime);
	}	
	else if(firstArg == "readxor")
	{
		readStaticXor(args, thetime);
	}
	//Raw random number generation
	else if(firstArg == "binary")
	{
		GenerationMethods::generateBinaryRandomNumber(args, thetime);
	}	
	else if(firstArg == "wif")
	{
		GenerationMethods::generateFromWif(args, thetime);
	}
	
	//Mini key commands
	else if(firstArg == "mini")
	{
		miniKeyGenerate(argc, argv, thetime);
	}
	else if(firstArg == "miniToWif")
	{
		generateWifFromMiniPrivKey(argc, argv, thetime);
	}	
	
	//else if(firstArg == "infoPrivate")
	//{	
	//	std::cout << "This command is deprecated. Use \"info\" instead" << std::endl;
	//	std::cout << std::endl;
	//	validatePrivateWif(argc, argv, thetime);		
	//}
	else if(firstArg == "info")
	{
		EntityInformationCommandline::informationAboutEntity(args, thetime);
	}	
	else if(firstArg == "verifyWIF") //Todo: Remove??
	{
		std::cout << "This command is deprecated. Use \"info\" instead" << std::endl;		
		std::cout << std::endl;		
		EntityInformationCommandline::verifyWif(argc, argv, thetime);		
	}	
	//else if(firstArg == "infoAddress")
	//{
	//	std::cout << "This command is deprecated. Use \"info\" instead" << std::endl;
	//	std::cout << std::endl;		
	//	verifyAddress(argc, argv, thetime);
	//}
		
	//Commands for Hierarcial random addresses
	else if(firstArg == "genRoot")
	{
		HierarcialRandomCommandline::generateRootKey(thetime, argc, argv);
	}
	else if(firstArg == "genPub")
	{
		HierarcialRandomCommandline::generatePublicFromRoot(argc, argv, thetime);
	}
	else if(firstArg == "genPriv")
	{
		HierarcialRandomCommandline::generatePrivateFromRoot(argc, argv, thetime);
	}
	
	//Commands that display a public address
	else if(firstArg == "pub")
	{
		generatePublicPart(args, argc, argv, thetime);
	}
	else if(firstArg == "invoice")
	{
		generatePaymentRequest(argc, argv, thetime);
	}
	
	//Commands for public keys
	
	//else if(firstArg == "keypair")	//Generates the pub-priv keypair from wif
	//{
	//	generatePostscriptKeypair(argc, argv, thetime);
	//}	
	else if(firstArg == "uncompress")	//Uncompresses the public key in hex format
	{
		uncompressPublicKey(argc, argv, thetime);
	}
	else if(firstArg == "compress")		//Compresses the public key in hex format
	{
		//std::cout << "Will compress public key" << std::endl;
		compressPublicKey(argc, argv, thetime);
	}
	else if(firstArg == "help")
	{
		printUsage();	
	}
	else if(firstArg == "license")
	{
		printLicense();
	}
	else if(firstArg == "intsize")
	{
		printIntSize();
	}
	//Transactions
	else if(firstArg == "savetrans")
	{
		TransactionCommandline::saveTheTransaction(args);
	}	
	else if(firstArg == "decodetrans")
	{
		TransactionCommandline::decodeTransaction(args);
	}
	else if(firstArg == "parsetrans")		//Redundant?
	{
		TransactionCommandline::parseTransaction(args);
	}
	else if(firstArg == "transinputhashes")	//Redundant?
	{
		TransactionCommandline::getTransactionInputHashes(args);
	}	
	else if(firstArg == "savescript")
	{
		TransactionCommandline::saveScript(args);
	}	
	else if(firstArg == "decodescript")
	{
		TransactionCommandline::decodeScript(args);
	}
	else if(firstArg == "runtrans")
	{
		TransactionCommandline::runTrans(args);
	}
	else if(firstArg == "transaction")
	{
		TransactionCommandline::createTransaction(args);
	}
	//Extended keys
	else if(firstArg == "genMnemonic")
	{
		createMnemonicAccount(args, thetime);
	}			
	else if(firstArg == "hmacsha512")
	{
		std::cout << "Moved to unit tests" << std::endl;
		//testHmacSha512(args);
	}	
	else if(firstArg == "derivation")
	{
		calcDerivation(args);
	}
	else if(firstArg == "addressderivation")
	{
		calcAddressDerivation(args);
	}
	else if(firstArg == "firsthdaddress")
	{
		calcFirstHdAddress(args);
	}
	
	
	//else if(firstArg == "testderivation")
	//{
	//	testPerormDerivation(args);
	//}	
	
	//Electrum	
	else if(firstArg == "electrum")
	{
		createElectrumAccount(args, thetime);
	}
	else if(firstArg == "getnextnum")
	{
		std::cout << "Getting next num" << std::endl;
		getNextNumToUse();
	}
	else if(firstArg == "setnextnum")
	{		
		std::cout << "Setting next num" << std::endl;
		setNextNumToUse(args);
	}
	
/*
	else if(firstArg == "extended")
	{
		createExtendedAccount(args, thetime);
	}
	else if(firstArg == "mnemonicInfo")
	{
		getMnemonicInformation(args, thetime);
	}	
	else if(firstArg == "listMnemonic")
	{
		listMnemonicSize(args, thetime);
	}
*/
	//else if(firstArg == "pbkdf2")
	//{
	//	testPbKdb2(args, thetime);
	//}	


/*	
	else if(firstArg == "timelock")
	{
		createTimelock(args);
	}
	else if(firstArg == "multisig")
	{
		createMultisig(args);
	}
	else if(firstArg == "signmultisig")	
	{
		partSignMultisig(args);
	}
	else if(firstArg == "combinemultisig")
	{
		combineMultisigSignatures(args);
	}
	else if(firstArg == "not_used_combinesig")	//Todo: Remove
	{
		not_used_combineNormalSignatures(args);
	}		
	else if(firstArg == "signatureinfo")	
	{
		signatureInfo(args);
	}	
	else if(firstArg == "showascii")
	{
		showAscii(args);
	}
	else if(firstArg == "fixlowstrans")
	{
		fixLowSTransaction(args);
	}
	else if(firstArg == "getcpp")
	{
		getCppString(args);
	}
	else if(firstArg == "outscript")
	{
		createOutScript(args);
	}
	else if(firstArg == "inscript")		//Todo: Remove, same function as outscript
	{
		createInScript(args);
	}	
*/
	//else if(firstArg == "not_used_partialsignmultisig")	//Todo: Remove???
	//{
	//	not_used_signMultisig(args, false);
	//}	
	else
	{
		std::cerr << "Unknown command: " << argv[1] << std::endl;
	}
	
}







	/*
	for(std::vector<std::string>::const_iterator it = args.begin() ;
		it != args.end() ;
		++it)
	{
		const std::string& a = (*it);
		std::cout << "arg: " << a << std::endl;	
	}
	*/
	
	

