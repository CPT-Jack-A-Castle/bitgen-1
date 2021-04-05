/**
 * GenerationMethods.cpp - Bitcoin address generator
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
 

#include "GenerationMethods.h"
#include "GenerationMethodsExtended.h"
#include "GenerationMethodsElectrum.h"

#include "GenerationParameters.h"
#include "commandLine.h"
#include "util.h"
#include "random.h"
#include "privKey.h"
#include "bitcoinKeyPair.h"
#include "mnemonic.h"
#include "SaveFolderHandler.h"
#include "txtGeneration.h"
#include "qrenc.h"
#include "randomUtils.h"
#include "FileUtil.h"
#include "currencySpecific.h"
#include "keyDerivationFunction.h"
#include "bitgenVersion.h"
#include "printPS.h"
#include "ExtendedKey.h"
#include "hmac.h"
#include "bitgenConfig.h"
#include "StaticXor.h"

#include <iostream>
#include <list>
#include <stdlib.h>
#include <algorithm> 
#include <iterator>


void GenerationMethods::splitPassphrase(const std::string& passphrase, std::list<std::string>& generationExtra)
{	
	int lastNewlinePos(0);
	for(int i = 0 ; i < passphrase.size() ; i++)
	{
		const char c = passphrase[i];
		
		const int rowLength = i - lastNewlinePos;
				
		if(rowLength > 40 && c == ' ')
		{
			const std::string row = passphrase.substr(lastNewlinePos, i - lastNewlinePos);
			generationExtra.push_back(row);
			
			lastNewlinePos = i + 1;
		}
		else if(rowLength > 50)
		{
			const std::string row = passphrase.substr(lastNewlinePos, i - lastNewlinePos);
			generationExtra.push_back(row);
			
			lastNewlinePos = i;
		}
	}
	
	const std::string row = passphrase.substr(lastNewlinePos);
	generationExtra.push_back(row);
	
}








void GenerationMethods::printRandomSourceWarning(const std::string generator)
{
	std::cout << "Generating root key information" << std::endl << std::endl;
		
	std::cout << "Warning: Random number generated outside of bitgen with ";
	
#ifdef __linux	
	std::cout << generator << ".";
#else
	std::cout << "CryptGenRandom().";
#endif
	
	std::cout << std::endl;
	std::cout << "         Ensure that your random number generator gives good random numbers." << std::endl;
	std::cout << "         Flaws in the random number generation " << std::endl;
	std::cout << "         might make the private key possible to guess." << std::endl;
	std::cout << "         Consider other random number generators, such as dice." << std::endl;				
}





void GenerationMethods::generateBinaryRandomNumber(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen binary METHOD [extra1] [extra2]" << std::endl;
		std::cout << "    Method: random, dice, hex, hash, brain" << std::endl;
		
		throw std::string("Not enough arguments");
	}
	
	const std::string method = args[1];

	const std::string extra = ((args.size() > 2) ? args[2] : "");
	const std::string extra2 = ((args.size() > 3) ? args[3] : "");
	
	std::cout << "Generating 256 bit random number" << std::endl;
	
	const BigInt<256> privkey = generateRandomWithMethod(method, extra, extra2);

	std::cout << std::endl;
	std::cout << "Generated number: " << hexString(privkey.getBinaryLong()) << std::endl;
}







void GenerationMethods::saveTheOTPPublicFilesInFolders(const PubAddress& pubaddr, 
	const std::string& thetime, 
	const GenerationParameters& params,
	const int newNum, 
	const std::string& pubPath)
{
		
	const std::string filenameBase = getCurrencyShortName() + "_address_" + intToString(newNum) + "_pad";
	
	if(params.getGenerateTXT())
	{		
		savePubOtpTxtFiles(filenameBase, pubaddr, 
			thetime, 
			params.getAccountName(),
			pubPath,
			versionNumber, 
			applicationName);
	}
	
	if(params.getGeneratePS())
	{		
		const Language lang = getLanguage();		
		const PostscriptGenerator postscriptGenerator(versionNumber, applicationName, lang);
		
		const PublicPostscriptInfo pubInfo(pubaddr, thetime, params.getAccountName());
		
		const std::string privaddr("DummyPrivAddr");
		const std::list<ExtraInfo> generationExtra;
		const std::string mnemonicDummy;
		const std::string genMethod("GenerationDummy");
		
		const PrivatePostscriptInfo privInfo(privaddr, mnemonicDummy, genMethod, params.getCompressed(), generationExtra);
		
		const PsInfoFile psinfo = postscriptGenerator.generate(privInfo, pubInfo);

		const std::string pubFilename = filenameBase + "_share.ps";
		
		const std::string fullPubPath = (pubPath == ".") ? pubFilename : (pubPath + "/" + pubFilename);	
		std::cout << "Saving publfile: " << fullPubPath << std::endl;
		fileWrite(fullPubPath, psinfo.publicPs);	
	}
}



void GenerationMethods::saveTheFilesInFolders(const PubAddress& pubaddr, const std::string& privaddr, const std::string& genMethod,
	const std::list<ExtraInfo>& generationExtra, const std::string& thetime, const GenerationParameters& params,
	const Mnemonic& mnemonic, const int newNum, const bool isPad, const BigInt<256> staticXor,
	const std::string& privPath, const std::string& pubPath)
{
	
	if(params.getGenerateTXT())
	{
		saveTxtFiles(newNum, pubaddr, privaddr, genMethod, generationExtra, thetime, 
			params.getAccountName(), 
			mnemonic.toStr(), 
			params.getCompressed(), 
			pubPath, privPath, versionNumber, applicationName, isPad, staticXor);
	}
	
	if(params.getGeneratePS())
	{		
		const Language lang = getLanguage();		
		const PostscriptGenerator postscriptGenerator(versionNumber, applicationName, lang);
		
		const PublicPostscriptInfo pubInfo(pubaddr, thetime, params.getAccountName());
		const PrivatePostscriptInfo privInfo(privaddr, mnemonic.toStr(), genMethod, params.getCompressed(), generationExtra);
		
		const PsInfoFile psinfo = postscriptGenerator.generate(privInfo, pubInfo);
			
		const std::string padExtra = (isPad ? "_pad" : "");
		const std::string addressStr = (getCurrencyShortName() == "bch_slp" || getCurrencyShortName() == "bch") ? pubaddr.toCashAddrString() : pubaddr.toString();

		const std::string numStr = (newNum == 0) ? "" : (intToString(newNum) + "_");


		const std::string filenameStart = getCurrencyShortName() + "_address_" + numStr + addressStr + padExtra;

		
		const std::string privFilename = filenameStart + "_private.ps";
		const std::string fullPrivPath = (privPath == ".") ? privFilename : (privPath + "/" + privFilename);
	
		if(!isPad)
		{
			std::cout << "Saving privfile: " << fullPrivPath << std::endl;
			fileWrite(fullPrivPath, psinfo.privatePs);
		}

		const std::string pubFilename = filenameStart + "_share.ps";
		const std::string fullPubPath = (pubPath == ".") ? pubFilename : (pubPath + "/" + pubFilename);	
		std::cout << "Saving publfile: " << fullPubPath << std::endl;
		fileWrite(fullPubPath, psinfo.publicPs);
		
	}
}




void GenerationMethods::saveAllFiles(const PubAddress& pubaddr, const std::string& privaddr, const std::string& genMethod,
	const std::list<ExtraInfo>& generationExtra, const std::string& thetime, const GenerationParameters& params,
	const Mnemonic& mnemonic, const int newNum, const bool isPad, const BigInt<256> staticXor)
{	
	std::string privPath(".");
	std::string pubPath(".");
	
	if(params.getUseFolder())
	{		
		const bool doCreateFolder = !isPad;
		std::list<std::string> confFolders;
		confFolders.push_back("");
		const std::pair<std::string, std::vector<std::string> > folders = SaveFolderHandler::createNewFolders(newNum, confFolders, doCreateFolder);
		
		privPath = folders.second.front();
		pubPath = folders.first;
	}
	
	saveTheFilesInFolders(pubaddr, privaddr, genMethod,
		generationExtra, thetime, params,
		mnemonic, newNum, isPad, staticXor, privPath, pubPath);	
}



int GenerationMethods::getNextNumberIfConfigured(GenerationParameters& params)
{
	if(params.getUseFolder())
	{
		const int newFolderNum = getConfiguredNum();
		params.setAccountNameforFolder(params.getUseFolder(), newFolderNum);
		return newFolderNum;
	}
	else if(params.useConter())
	{
		return SaveFolderHandler::getNextNumber();
	}
	
	return 0;
}



void GenerationMethods::generateWithDice(const std::vector<std::string>& args, 
					const std::string& thetime)
{
	GenerationParameters params;
			
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen dice digits(1-6) [AccountName]" << std::endl;
		std::cout << " or" << std::endl;
		std::cout << "       bitgen dice - [AccountName]" << std::endl;
			
		return;
	}

	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 1);
	//std::cout << "Extra args: " << allExtraArgs.size() << std::endl;
	
	params.parseArgs(allExtraArgs);	
	params.finally();
	
		
	std::string dice(args[1]);
	if(dice == "-")
	{
		std::cout << "Enter the 100 dice values at one row as digits 1-6" << std::endl;
		std::cout << "Press enter when all digits are entered" << std::endl;
		
		dice = readStdinLine(100, true, oneToSix);
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;			
		std::cout << std::endl;
	}
		
	if(dice.size() != 100)
	{
		std::string errMsg("Need exactly 100 dice throws, got: ");
		errMsg += intToString(dice.size());
		errMsg += " throws";
			
		throw errMsg;
		
		//std::cerr << "Need exactly 100 dice throws, got: " << dice.size() << " throws" << std::endl;
		//return;
	}

	
	const int newFolderNum = getNextNumberIfConfigured(params);

	std::cout << "Generating bitcoin address from dice, got " << dice.size() << " throws" << std::endl;
	std::cout << "Dice result (1-6): " << dice << std::endl;
		
	const BigInt<256> privkey = getRandomNumFrom6SideDice(dice);		
		
	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Dice val (1-6)", dice);
	generationExtra.push_back(extraInfo);

	const PrivKey myPrivKey(privkey, params.getCompressed());
		
	const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(myPrivKey);

	std::cout << "PUB: " << keypair.pubaddr << std::endl;
	std::cout << "PRIV: " << keypair.privaddr << std::endl;

	const Mnemonic mnemonicObj(privkey);

	saveAllFiles(keypair.pubaddr, keypair.privaddr.toString(), "dice", 
					generationExtra, thetime, params, mnemonicObj, newFolderNum);
}




void savePadFile(const PubAddress& pubAddr, const std::string& generator, std::list<ExtraInfo> generationExtra, 
	const std::string& thetime, const BigInt<256>& pad, const int numPad, const int totalPads, const GenerationParameters& params,
	const Mnemonic& mnemonicPad, const std::string& privPath, const BigInt<256>& staticXor, const int newNum,
	const std::string& privFilename)
{	
	if(params.getGenerateTXT())
	{	
		const std::string txtFilename = privFilename + ".txt";
		//std::cout << "Will save txt" << std::endl;
		saveOtpFile(pubAddr, pad.getBinaryLong(), numPad, totalPads, thetime, privPath, versionNumber, 
			applicationName, generationExtra, params.getAccountName(), mnemonicPad.toStr(), generator, staticXor, newNum, 
			txtFilename);
	}
	
	
	if(params.getGeneratePS())
	{		
		const Language lang = getLanguage();		
		const PostscriptGenerator postscriptGenerator(versionNumber, applicationName, lang);
		
		//Pubaddr is not displayed, instead a hash of the pubaddr is used.
		const std::string emptyPubAddr;
		
		const bool useHashOfTimeInsteadOfAddress(true);		//Use hash of time instead of address?
		const PublicPostscriptInfo pubInfo(pubAddr, thetime, params.getAccountName(), useHashOfTimeInsteadOfAddress);	
		
		const PrivatePostscriptInfo privInfo(hexString(pad.getBinaryLong()), mnemonicPad.toStr(), generator,
			true, generationExtra, true, (numPad + 1), totalPads, staticXor);
		
		const PsInfoFile psinfo = postscriptGenerator.generate(privInfo, pubInfo);
			
		const std::string privFilenamePs = privFilename + ".ps";
		const std::string fullPrivPath = (privPath == ".") ? privFilenamePs : (privPath + "/" + privFilenamePs);
	
		std::cout << "Saving priv pad: " << withoutLeadingDot(fullPrivPath) << std::endl;
		fileWrite(fullPrivPath, psinfo.privatePs);
		
		//std::cout << "Save OK" << std::endl;	
		//const std::string pubFilename = pubaddr + "_share.ps";
		//const std::string fullPubPath = (pubPath == ".") ? pubFilename : (pubPath + "/" + pubFilename);	
		//std::cout << "Saving publfile: " << fullPubPath << std::endl;
		//fileWrite(fullPubPath, psinfo.publicPs);
		
	}
}






std::string parse256BitHexString(const std::string& hexVal)
{
	const int numBytes = 32;
	
	if(hexVal.size() != (numBytes * 2))
	{
		std::cerr << std::endl;
		std::cerr << "Incorrect amount of data given. Got " << hexVal.size() << " hex digits, want " << (numBytes * 2) << " hex digits" << std::endl;
		throw std::string("Not enough data");
	}
		
	const std::string binStr = convertFromHex(hexVal);
	return binStr;
}




std::list<BigInt<256> > getPadsFromCommandline(const std::vector<std::string>& args, bool& useStaticXorIfPresent)
{
	std::list<BigInt<256> > pads;
	
	const int numArgs = args.size() - 1;
	
	for(int i = 0 ; i < numArgs ; i++)
	{
		const std::string padHex = args[i + 1];
		
		if(padHex == "nostatic")
		{
			useStaticXorIfPresent = false;
			return pads;
		}
	
		const std::string padBin = parse256BitHexString(padHex);	
	
		const BigInt<256> padInt(padBin,'c');
		//std::cout << "FOUND PAD: " << hexString(padInt.getBinaryLong()) << std::endl;
		pads.push_back(padInt);
	}

	return pads;
}




void GenerationMethods::generateOtpTotal(const std::vector<std::string>& args, const std::string& thetime)
{
	std::cout << "Generating OTP total" << std::endl;
	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen otp OTP1 ... OTPn" << std::endl;
		return;
	}
	
	//Todo: Extra options
	
	GenerationParameters params;	
	params.setAccountName("From OTP do not use");


	bool useStaticXorIfPresent(true);
	std::list<BigInt<256> > padList = getPadsFromCommandline(args, useStaticXorIfPresent);

	const int numPads = padList.size();
	
	std::cout << "Num pads: " << numPads << std::endl;

	const BigInt<256> staticXor = getStaticXor(useStaticXorIfPresent);
	
	const BigInt<256> zero;
	if(staticXor != zero)
	{
		const std::string hash = staticXorHash(staticXor);		
		std::cout << "Using static pad: " <<  hexString(staticXor.getBinaryLong()) << " ";
		std::cout << "(" << hexString(hash) << ")" << std::endl;	
	}
	

	BigInt<256> privKey;
	
	for(std::list<BigInt<256> >::const_iterator it = padList.begin() ;
		it != padList.end() ;
		++it)
	{		
		const BigInt<256> padInt = (*it);
		
		std::cout << "PAD: " << hexString(padInt.getBinaryLong()) << std::endl;

		privKey = padInt ^ privKey;
	}
		
	privKey = staticXor ^ privKey;

	
	std::cout << std::endl;
	std::cout << "Privkey: " << hexString(privKey.getBinaryLong()) << std::endl;
		
	const PrivKey myPrivKey(privKey, true);
		
	const std::string hexStr = hexString(privKey.getBinaryLong());

	std::list<ExtraInfo> generationExtra;
	
	const ExtraInfo extraInfo("Raw hex", hexStr);
	generationExtra.push_back(extraInfo);
	
	const ExtraInfo extraInfoParts("OTP parts", intToString(numPads));
	generationExtra.push_back(extraInfoParts);

	
	BitcoinEllipticCurve ec;

	const Wif wif = myPrivKey.getWif();
	const PubKey pubKey = myPrivKey.getPubkey(ec);
	const Pkif pkif = pubKey.getPkif();
	const PubAddress pubAddr = pubKey.getAddress();
	
	std::cout << "PUB : " << pubAddr << std::endl;
	if(usesCashAddress())
	{
		std::cout << "PUBC: " << pubAddr.toCashAddrString() << std::endl;				
	}
	
	std::cout << "PKIF: " << pkif.toString() << std::endl;	
	std::cout << "PRIV: " << wif.toString() << std::endl;
		
	const Mnemonic mnemonicObj(privKey);

	const std::string generator = "OTP";
	
	const int newNum(0);
		
	std::cout << std::endl;
	
	saveAllFiles(pubAddr, wif.toString(), generator, generationExtra, thetime, 
		params, mnemonicObj, newNum, false, staticXor);
}



std::list<std::string> splitHashStr(const int totNum, const std::string& totalHashVal)
{
	//std::cout << "Will get hash num" << std::endl;
	const int totSize = totalHashVal.size();
	const int partSize = totSize / totNum;	//Rounded down
	const int useSize = partSize * totNum;

	std::list<std::string> ret;
	
	for(int i = 0 ; i < totNum ; i++)
	{
		//size must be a multiple of num, remove last characters if needed
		const std::string useHash = totalHashVal.substr(0, useSize);
	
		const int startPos = i * partSize;
	
		const std::string hashStr = useHash.substr(startPos, partSize);
		ret.push_back(hashStr); 
	}
	
	return ret;
}




BigInt<256> getPartHash(const std::string& part)
{
	const std::string hash = sha256(part);

	const BigInt<256> ret(hash, 'c');
	
	return ret;	
}



const BigInt<256> getPartDice(const std::string& part)
{
	const BigInt<256> ret = getRandomNumFrom6SideDice(part);
		
	return ret;		
}




std::list<BigInt<256> > generatePadRandom(const int totalPads, const std::string& method, const std::string& extraVal)
{
	std::list<BigInt<256> > pads;
	
	if(method == "random")
	{	
		for(int i = 0 ; i < totalPads ; i++)
		{
			const BigInt<256> pad = getRandomNumber(false);
			pads.push_back(pad);
		}
	}
	else if(method == "hash")
	{
		const int minLen = totalPads * 50;
		if(extraVal.size() < minLen)
		{
			std::cout << "Needs at least " << minLen << " character hash, got: " << extraVal.size() << std::endl;
			throw std::string("Hash too short");
		}
		
		const std::list<std::string> parts = splitHashStr(totalPads, extraVal);

		for(std::list<std::string>::const_iterator it = parts.begin() ;
			it != parts.end() ;
			++it)
		{
			const std::string& part = (*it);
			std::cout << "Hash part: " << part << std::endl;
			const BigInt<256> pad = getPartHash(part);
			pads.push_back(pad);
			
		}
	}
	else if(method == "dice")
	{
		const int neededLen = totalPads * 100;
		if(extraVal.size() != neededLen)
		{
			std::cout << "Num dice should be " << neededLen << ", got: " << extraVal.size() << std::endl;
			throw std::string("Incorrect num dice");
		}
		
		const std::list<std::string> parts = splitHashStr(totalPads, extraVal);	//Todo: Rename

		for(std::list<std::string>::const_iterator it = parts.begin() ;
			it != parts.end() ;
			++it)
		{
			const std::string& dicePart = (*it);
			std::cout << "Dice part: " << dicePart << std::endl;
			const BigInt<256> pad = getPartDice(dicePart);
			pads.push_back(pad);
			
		}
	}
	else if(method == "hex")
	{
		const int neededLen = totalPads * 64;
		if(extraVal.size() != neededLen)
		{
			std::cout << "Num hex digits should be " << neededLen << ", got: " << extraVal.size() << std::endl;
			throw std::string("Incorrect num hex digits");
		}
		
		const std::list<std::string> parts = splitHashStr(totalPads, extraVal);	//Todo: Rename

		for(std::list<std::string>::const_iterator it = parts.begin() ;
			it != parts.end() ;
			++it)
		{
			const std::string& hexPart = (*it);
			//std::cout << "Hex part: " << hexPart << std::endl;
			const std::string binStr = convertFromHex(hexPart);
		
			const std::string hexValUpper = hexString(binStr);
		
		
			const BigInt<256> pad = BigInt<256>::fromHex(hexValUpper);
			//std::cout << "PrivData: " << pad << std::endl;
			
			pads.push_back(pad);
			
		}
	}
	else
	{
		std::cout << "Internal error, no such method: " << method << std::endl;
		throw std::string("No such method");
	}


	return pads;
}






void GenerationMethods::savePublicPadPart(const PubAddress& pubAddr, const std::string& thetime,
	const GenerationParameters& params, const int newNum, const std::string& pubPath)
{		
	saveTheOTPPublicFilesInFolders(pubAddr, thetime, params, newNum, pubPath);
}







void GenerationMethods::savePrivatePadPart(const std::list<BigInt<256> >& pads, const std::string method,
	const std::list<std::string>& hashParts, std::vector<std::string>& privatePaths, const PubAddress& pubAddr,
	const std::string generator, const std::string& thetime, const int totalPads, const GenerationParameters& params,
	const BigInt<256>& staticXor, const int newNum)
{
	std::list<std::string>::const_iterator jt = hashParts.begin();
	
	
	int thisNum(0);
	for(std::list<BigInt<256> >::const_iterator it = pads.begin() ;
		it != pads.end() ;
		++it)
	{
		//std::cout << "Next pad" << std::endl;
		const BigInt<256>& pad = (*it);
		std::list<ExtraInfo> padGenerationExtra;
		
		if(method == "hash")
		{
			const std::string& hashVal = (*jt);
			++jt;
			const ExtraInfo extraInfoNum("Hashval", hashVal);	//Todo: Needed?
			padGenerationExtra.push_back(extraInfoNum);
		}
	
		const Mnemonic mnemonicPad(pad);

		//std::cout << "Will get private path: " << thisNum << std::endl;
		const std::string privPath = privatePaths[thisNum];
	
		//std::cout << "WILL SAVE FILES FOR A PAD: " << privPath << std::endl;
		
		const std::string privFilename = getCurrencyShortName() + "_address_"+ intToString(newNum)+ 
			"_private_pad" + intToString(thisNum + 1);

		
		savePadFile(pubAddr, generator, padGenerationExtra, thetime, pad, thisNum, 
			totalPads, params, mnemonicPad, privPath, staticXor, newNum, privFilename);
		//std::cout << "AFTER!" << std::endl;
		
		thisNum++;
	}
}







void GenerationMethods::generateOtpParts(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen otpgen [NUMPAD/useconf] METHOD [extraOptions]" << std::endl;
		std::cout << "  Methods: random, dice, hash, hex" << std::endl;
		
		throw std::string("Incorrect usage");
	}
	
	const std::string numStr = args[1];
	std::list<std::string> folders;
	
	int totalPads(0);
	if(numStr == "useconf")
	{
		std::cout << "Using configured folders for num pads" << std::endl;
		std::string publicFolder;
		folders = getPublicAndOtpFolders(publicFolder);
		
		checkFoldersExist(folders);
		std::cout << "OK, configured folders exist" << std::endl;
		
		totalPads = folders.size();
	}
	else
	{
		totalPads = atoi(numStr.c_str());
		
		for(int i = 0 ; i < totalPads ; i++)
		{
			folders.push_back(".");
		}
	}
	
	
	
	if(totalPads < 2)
	{
		std::cout << "Num pads given: " << totalPads << " (" << numStr << ")" << std::endl;
		std::cout << "Num pads must be at least 2" << std::endl;
		throw std::string("Incorrect number of pads");
	}
	
	std::cout << "Total pads: " << totalPads << std::endl;

	const std::string method = args[2];
	
	if(method != "random" && method != "hash" && method != "dice" && method != "hex")
	{
		std::cout << "Unknown method: " << method << std::endl;
		throw std::string("Unknown method");
	}
	
	std::string extraVal;


	if(method == "random")
	{
		//Nothing
	}
	else if(method == "hash")
	{
		if(args.size() < 4)
		{
			std::cout << "Usage: bitgen otpgen NUMPAD hash HASHVAL [extraOptions]" << std::endl;
		
			throw std::string("Incorrect usage");
		}
		
		extraVal = args[3];		//Todo: Rename to paramVal
	}
	else if(method == "dice")
	{
		if(args.size() < 4)
		{
			std::cout << "Usage: bitgen otpgen NUMPAD dice DICEVAL [extraOptions]" << std::endl;
		
			throw std::string("Incorrect usage");
		}
		
		extraVal = args[3];		//Todo: Rename to paramVal
	}
	else if(method == "hex")
	{
		if(args.size() < 4)
		{
			std::cout << "Usage: bitgen otpgen NUMPAD hex HEXVAL [extraOptions]" << std::endl;
		
			throw std::string("Incorrect usage");
		}
		
		extraVal = args[3];		//Todo: Rename to paramVal
	}
	else
	{
		std::cout << "Internal error, no such method: " << method << std::endl;
		throw std::string("No such method");
	}
	
	GenerationParameters params;	

	const int paramStartPos = (method == "random") ? 2 : 3;

	const std::vector<std::string> allExtraArgs = getExtraArgs(args, paramStartPos);

	ExtraOptionsRandom extraOptions;
	
		
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		
		if(params.useArg(arg))
		{
			//Nothing
		}
		else if(extraOptions.useArg(arg))
		{
			//Nothing			
		}
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();

	
	bool useFolder = params.getUseFolder();
	bool useConfiguredFolderPaths(false);
	
	if(numStr == "useconf")		//Using folder conf implies that folders are used
	{
		useFolder = true;
		useConfiguredFolderPaths = true;
	}

	

	const std::list<BigInt<256> > pads = generatePadRandom(totalPads, method, extraVal);


	std::cout << std::endl;

		
	BigInt<256> privKey;
	for(std::list<BigInt<256> >::const_iterator it = pads.begin() ;
		it != pads.end() ;
		++it)
	{
		const BigInt<256>& pad = (*it);
		std::cout << "Pad: " << hexString(pad.getBinaryLong()) << std::endl;
		
		privKey = privKey ^ pad;
	}

	//Check if a static pad is defined
	const BigInt<256> staticXor = getStaticXor();
	//std::cout << "Static xor: " << hexString(staticXor.getBinaryLong()) << std::endl;
	
	const BigInt<256> zero;
	
	const bool useStaticPad = (staticXor != zero);
	
	if(useStaticPad)
	{
		const std::string hash = staticXorHash(staticXor);		
		
		std::cout << "Using static pad: " <<  hexString(staticXor.getBinaryLong()) << " (" <<
			hexString(hash) << ")" << std::endl;
	}


	privKey = privKey ^ staticXor;
	
	
	std::cout << "Privkey: " << hexString(privKey.getBinaryLong()) << std::endl;
		
	const PrivKey myPrivKey(privKey, true);	

		
	const std::string hexStr = hexString(privKey.getBinaryLong());

	BitcoinEllipticCurve ec;

	const Wif wif = myPrivKey.getWif();
	const PubKey pubKey = myPrivKey.getPubkey(ec);
	const Pkif pkif = pubKey.getPkif();
	const PubAddress pubAddr = pubKey.getAddress();
	
	std::cout << "PUB : " << pubAddr << std::endl;
	
	if(usesCashAddress())
	{
		std::cout << "PUBC: " << pubAddr.toCashAddrString() << std::endl;		
	}
	//std::cout << "PKIF: " << pkif.toString() << std::endl;	
	std::cout << "PRIV: " << wif.toString() << std::endl;
		

	const std::string generator = ((method == "random") ? "OTP /dev/random" : ("OTP " + method));
	
	std::cout << std::endl;

	std::vector<std::string> privatePaths;	
	std::string pubPath;
	
	const int newNum = SaveFolderHandler::getNextNumber();
	//std::cout << "The new number: " << newNum << std::endl;
	params.setAccountNameforFolder(true, newNum);
	
	if(useFolder)
	{
		
		//params.setAccountNameforFolder(true, newNum);
		
		//std::cout << "Account name: " << params.getAccountName() << std::endl;
		
		
		const std::string firstFolder = folders.front();


		const std::pair<std::string, std::vector<std::string> > fullFolders = 
			SaveFolderHandler::createNewFolders(newNum, folders, true, useConfiguredFolderPaths);
		
		privatePaths = fullFolders.second;
		pubPath = fullFolders.first;
	}
	else
	{
		for(int i = 0 ; i < totalPads ; i++)
		{
			privatePaths.push_back(".");
		}
		
		pubPath = ".";
	}

	std::cout << std::endl;
	

	const std::list<std::string> hashParts = splitHashStr(totalPads, extraVal);

	savePrivatePadPart(pads, method, hashParts, privatePaths, pubAddr,
		generator, thetime, totalPads, params, staticXor, newNum);

	std::cout << std::endl;
		
	savePublicPadPart(pubAddr, thetime, params, newNum, pubPath);
	
				
	if(useStaticPad)
	{
		std::cout << std::endl;
		std::cout << "NOTE: STATIC PAD USED. THE PAD MUST BE SECURELY STORED" << std::endl;
		std::cout << "Without knowledge of the static pad, the private key can not be recovered" << std::endl;
	}	
}











void GenerationMethods::generateRandom(const std::vector<std::string>& args, const std::string& thetime)
{
	GenerationParameters params;	
#ifndef __linux
	std::cerr << "Random is not supported on Windows. Use \"hash\" instead" << std::endl;
	return;
#endif
	

	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 0);

	ExtraOptionsRandom extraOptions;
	
		
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		
		if(params.useArg(arg))
		{
			//Nothing
		}
		else if(extraOptions.useArg(arg))
		{
			//Nothing			
		}
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();
	
	
	if(extraOptions.useURandom)
	{
		std::cout << "Using /dev/urandom with hash of buffer" << std::endl;		
	}


	const int newNum = getNextNumberIfConfigured(params);
	
	const std::string generator = extraOptions.useURandom ? "/dev/urandom" : "/dev/random";

	printRandomSourceWarning(generator);
		
	std::cout << "Generating random address" << std::endl;
	if(!extraOptions.useURandom)
	{
		std::cout << "Press random keys or move the mouse if needed" << std::endl;
	}
	
	const BigInt<256> privKey = extraOptions.useURandom ? getBlockCalcRandomNumber() : getRandomNumber(extraOptions.longbuf);
		
	const PrivKey myPrivKey(privKey, params.getCompressed());

		
	const std::string hexStr = hexString(privKey.getBinaryLong());

	std::list<ExtraInfo> generationExtra;
	
	const ExtraInfo extraInfo("Raw hex", hexStr);
	generationExtra.push_back(extraInfo);
	
	BitcoinEllipticCurve ec;

	const Wif wif = myPrivKey.getWif();
	const PubKey pubKey = myPrivKey.getPubkey(ec, extraOptions.onlyIndicatedUsage, extraOptions.signVerify);
	const Pkif pkif = pubKey.getPkif();
	const PubAddress pubAddr = pubKey.getAddress();
	
	std::cout << "PUB : " << pubAddr << std::endl;
	if(usesCashAddress())
	{
		std::cout << "PUBC: " << pubAddr.toCashAddrString() << std::endl;		
	}
	
	std::cout << "PKIF: " << pkif.toString() << std::endl;	
	std::cout << "PRIV: " << wif.toString() << std::endl;
		
	const Mnemonic mnemonicObj(privKey);
		
	saveAllFiles(pubAddr, wif.toString(), generator, generationExtra, thetime, params, mnemonicObj, newNum);
}






void GenerationMethods::generateFromWif(const std::vector<std::string>& args, const std::string& thetime)
{
	//std::cout << "Generating from wif" << std::endl;
	GenerationParameters params;	
	
	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 1);

	ExtraOptionsRandom extraOptions;
	
		
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		
		if(params.useArg(arg))
		{
			//Nothing
		}
		else if(extraOptions.useArg(arg))
		{
			//Nothing			
		}
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();
	
	const int newNum = getNextNumberIfConfigured(params);	
		
	std::string wifStr(args[1]);

	const Wif wif(wifStr);
	
	const PrivKey myPrivKey = wif.getPriv();

	std::list<ExtraInfo> generationExtra;
	
	const ExtraInfo extraInfo("Wif", "");
	generationExtra.push_back(extraInfo);

	
	BitcoinEllipticCurve ec;

	const PubKey pubKey = myPrivKey.getPubkey(ec, extraOptions.onlyIndicatedUsage, extraOptions.signVerify);
	const Pkif pkif = pubKey.getPkif();
	const PubAddress pubAddr = pubKey.getAddress();
	
	std::cout << "PUB : " << pubAddr << std::endl;
	std::cout << "PKIF: " << pkif.toString() << std::endl;	
	std::cout << "PRIV: " << wif.toString() << std::endl;
				
	const Mnemonic mnemonicObj(myPrivKey.key);		
		
	saveAllFiles(pubAddr, wif.toString(), "Wif",
		generationExtra, thetime, params, mnemonicObj, newNum);
}




std::string GenerationMethods::generateOneFileContents(const BitcoinKeyPair& keypair, const bool addPubkey, std::string& customString)
{
	std::string contents;
	
	if(!customString.empty())
	{
		for(int i = 0 ; i < customString.size() ; i++)
		{
			const char c = customString[i];
			if(c == '#')		//Pub
			{
				contents += keypair.pubaddr.toString();				
			}
			else if(c == '$')		//CashAddr Pub
			{
				contents += keypair.pubaddr.toCashAddrString();				
			}			
			else if(c == '@')	//Priv
			{
				contents += keypair.privaddr.toString();
			}
			else
			{
				contents += c;
			}
		}

		contents += "\n";

		return contents;
	}
	
	contents += keypair.pubaddr.toString();
	contents += ", ";
	if(addPubkey)
	{
		contents += keypair.pubaddr.toString();
		contents += ", ";							
	}
	contents += keypair.privaddr.toString();
	contents += "\n";
	
	return contents;
}


void GenerationMethods::generateBulk(const std::vector<std::string>& args, const std::string& thetime)
{		
	GenerationParameters params;
		
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen bulk NumAddresses [extraOptions]" << std::endl;
		return;			
	}

	const std::string numAddresses(args[1]);
	//std::cout << "NUM ADDR: " << numAddresses << std::endl;
	const int num = atoi(numAddresses.c_str());


	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 1);
		
	bool useURandom(false);
	bool longbuf(false);	
	bool oneFile(false);
	bool addPubkey(false);
	bool readCustom(false);
	
	std::string customString;
	
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		
		if(readCustom)
		{
			readCustom = false;
			customString = arg;
			std::cout << "Custom string: " << customString << std::endl;
			continue;
		}
		
		if(params.useArg(arg))
		{
			//Nothing
		}						
		else if(arg == "urandom")
		{
			if(longbuf)
			{
				throw std::string("Can not combine urandom and long");
			}
			useURandom = true;
		}
		else if(arg == "long")
		{
			if(useURandom)
			{
				throw std::string("Can not combine urandom and long");
			}
			
			std::cout << "Using 128 bytes from /dev/random" << std::endl;
			longbuf = true;
		}
		else if(arg == "onefile")
		{
			oneFile = true;
		}
		else if(arg == "onefilecustom")
		{
			oneFile = true;
			readCustom = true;
		}		
		else if(arg == "pubkey")
		{
			addPubkey = true;
		}		
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();
	
	const std::string generator = useURandom ? "/dev/urandom" : "/dev/random";


	std::cout << "Generating " << num << " random addresses" << std::endl;
	
	if(!useURandom)
	{
		std::cout << "Press random keys or move the mouse if needed" << std::endl;
	}

	std::string contents;
	std::string filename;

	for(int i = 0 ; i < num ; i++)
	{
		std::cout << "Address " << (i + 1) << " " << std::flush;

		const int newNum = getNextNumberIfConfigured(params);
		
		const BigInt<256> privKey = useURandom ? getBlockCalcRandomNumber() : getRandomNumber(longbuf);
				
		const PrivKey myPrivKey(privKey, params.getCompressed());
		const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(myPrivKey);

		std::cout << keypair.pubaddr.toString() << std::endl;
		
		if(oneFile)
		{
			filename = std::string("bulk_") + keypair.pubaddr.toString() + ".txt";
			
			contents += generateOneFileContents(keypair, addPubkey, customString);			
		}
		else
		{	
			
			const std::string hexStr = hexString(privKey.getBinaryLong());

			std::list<ExtraInfo> generationExtra;
			const ExtraInfo extraInfo("Raw hex", hexStr);
			generationExtra.push_back(extraInfo);
						
			const Mnemonic mnemonicObj(privKey);

			
			saveAllFiles(keypair.pubaddr, keypair.privaddr.toString(), generator,
				generationExtra, thetime, params, mnemonicObj, newNum);				
		}
	}

	if(oneFile)
	{
		std::cout << std::endl;
		std::cout << "Writing file: " << filename << std::endl;
		fileWrite(filename, contents);

	}
		
	std::cout << std::endl;
	std::cout << "All addresses generated. Ready" << std::endl;
}










void GenerationMethods::generateHash(const std::vector<std::string>& args,
	const std::string& thetime)
{
	GenerationParameters params;
	const int minChars(200);
	
	std::cout << "Generating address from hash" << std::endl;
		
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen hash \"The hashval\" [extraOptions]" << std::endl;
		std::cout << " or" << std::endl;
		std::cout << "       bitgen hash - [extraOptions]" << std::endl;
		
		return;			
	}


	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 1);
	//std::cout << "Num extra args: " << allExtraArgs.size() << std::endl;

		
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		if(params.useArg(arg))
		{
			//Nothing
		}										
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();

	std::string hashval(args[1]);
	
	if(hashval == "-")
	{
		std::cout << "Enter the hash string at one row" << std::endl;
		std::cout << "Press enter when everything is entered" << std::endl;
		
		hashval = readStdinLine(minChars, false, everythingOk);
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;			
		std::cout << std::endl;		
	}


	const int newNum = getNextNumberIfConfigured(params);
		
	const BigInt<256> privKey = hashStringToBigInt(hashval, minChars);
		
	std::list<ExtraInfo> generationExtra;
	const std::string privHex = hexString(privKey.getBinaryLong());

	const ExtraInfo extraInfo("Hex from hash", privHex);
	generationExtra.push_back(extraInfo);
			
	const PrivKey myPrivKey(privKey, params.getCompressed());

	const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(myPrivKey);

	const Mnemonic mnemonicObj(privKey);

	saveAllFiles(keypair.pubaddr, keypair.privaddr.toString(), "hash", 
		generationExtra, thetime, params, mnemonicObj, newNum);
}









void GenerationMethods::generateHex(const std::vector<std::string>& args, const std::string& thetime)
{
	GenerationParameters params;
		
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen-" << getCurrencyShortName() << " hex hexdigits [extraOptions]" << std::endl;
		std::cout << " or" << std::endl;
		std::cout << "       bitgen-" << getCurrencyShortName() << " hex - [extraOptions]" << std::endl;
		
		return;			
	}
		
	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 1);
	//std::cout << "Num extra args: " << allExtraArgs.size() << std::endl;
	
	bool printInfo(false);
		
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		if(params.useArg(arg))
		{
			//Nothing
		}										
		else if(arg == "info")	//Todo: Move to GenerationParameters ???
		{
			printInfo = true;
		}									
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();
		
	std::string privKeyStrMix(args[1]);

	if(privKeyStrMix == "-")
	{
		std::cout << "Enter the 64 hex values at one row" << std::endl;
		std::cout << "Press enter when all digits are entered" << std::endl;
		
		privKeyStrMix = readStdinLine(64, true, hexChar);
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;
		std::cout << std::endl;
	}
	
	
	const BigInt<256> privKey = hexStringToBigInt(privKeyStrMix);

	const int newNum = getNextNumberIfConfigured(params);

	std::cout << "Generating bitcoin address from hex private key" << std::endl;

	std::cout << "Private key (hex): " << hexString(privKey.getBinaryLong()) << std::endl;	

	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Hex privkey", hexString(privKey.getBinaryLong()));
	generationExtra.push_back(extraInfo);				
	
	BitcoinEllipticCurve ec;

	const PrivKey myPrivKey(privKey, params.getCompressed());
	const PubKey pubKey = myPrivKey.getPubkey(ec);
	const PubAddress address = pubKey.getAddress();

	if(printInfo)
	{
		std::cout << "Wif    : " << myPrivKey.toString() << std::endl;
		std::cout << "Pkif   : " << pubKey.toString() << std::endl;		
		std::cout << "Address: " << address.toString() << std::endl;
		std::cout << "CashAddress: " << address.toCashAddrString() << std::endl;		
	}

	const Mnemonic mnemonicObj(privKey);
		
	saveAllFiles(address, myPrivKey.toString(), "hex input", 
		generationExtra, thetime, params, mnemonicObj, newNum);
}







void GenerationMethods::generateFromMnemonic(const std::vector<std::string>& args, const std::string& thetime)
{
	GenerationParameters params;	
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen mnemonic Mnemonic [extraOptions]" << std::endl;
		std::cout << "       bitgen mnemonic - [extraOptions]" << std::endl;
		
		return;			
	}
					
	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 1);
	//std::cout << "Num extra args: " << allExtraArgs.size() << std::endl;

	
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		if(params.useArg(arg))
		{
			//Nothing
		}
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
		
	params.finally();
	
	std::string mnemonicStr(args[1]);
	
	if(mnemonicStr == "-")
	{
		std::cout << "Enter the mnemonic string at one row" << std::endl;
		std::cout << "Press enter when everything is entered" << std::endl;

		mnemonicStr = readStdinLine(0, false, everythingOk);		
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;
		std::cout << std::endl;
	}
			
	const Mnemonic mnemonicObj(mnemonicStr);
	const BigInt<256> privKey = mnemonicObj.toPrivKey();
	


	std::cout << "Generating bitcoin address from mnemonic private key" << std::endl;
	std::cout << "Private key (hex): " << hexString(privKey.getBinaryLong()) << std::endl;	

	const std::string accountName = params.getAccountName();
	params.setAccountName(accountName);
	
	const int newNum = getNextNumberIfConfigured(params);
		

	std::list<ExtraInfo> generationExtra;

	const PrivKey myPrivKey(privKey, params.getCompressed());

	const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(myPrivKey);

	const Mnemonic myMnemonicObj(privKey);
		
	saveAllFiles(keypair.pubaddr, keypair.privaddr.toString(), "mnemonic input", 
		generationExtra, thetime, params, myMnemonicObj, newNum);
}





//#ifndef NO_BRAINWALLET_GENERATION

void GenerationMethods::generateBrainWallet(const std::vector<std::string>& args,
	const std::string& thetime)
{	
	
#ifdef NO_BRAINWALLET_GENERATION
		std::cout << "No brainwallet support" << std::endl;
		return;
#else		
	
		
	GenerationParameters params;	
		
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen brainwallet email/salt \"The passphrase\" [extraOptions]" << std::endl;
		return;
	}

	const std::vector<std::string> allExtraArgs = getExtraArgs(args, 2);
	std::cout << "Num extra args: " << allExtraArgs.size() << std::endl;

	
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		if(params.useArg(arg))
		{
			//Nothing
		}								
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
	
	params.finally();
	
	const std::string salt(args[1]);

	std::string passphrase(args[2]);
	if(passphrase == "-")
	{
		std::cout << "Enter the brainwallet phrase" << std::endl;
		std::cout << "Press enter when all characters are entered" << std::endl;
		
		passphrase = readStdinLine(50, false, everythingOk);
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;			
		std::cout << std::endl;		
	}

	const int newNum = getNextNumberIfConfigured(params);


	std::cout << "Generating brainwallet" << std::endl;

	std::cout << "Salt: \"" << salt << "\"" << std::endl;		
	std::cout << "Passphrase: \"" << passphrase << "\"" << std::endl;


	const BigInt<256> privKey =  brainwalletToBigInt(passphrase, salt);
		
	std::list<ExtraInfo> generationExtra;
	const ExtraInfo extraInfo("Passphrase", passphrase);
	generationExtra.push_back(extraInfo);		
		
		
	std::cout << "Calculating keys..." << std::endl;	
		
	const PrivKey myPrivKey(privKey, params.getCompressed());
		
	const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(myPrivKey);

	const Mnemonic myMnemonicObj(privKey);

	saveAllFiles(keypair.pubaddr, keypair.privaddr.toString(), "brainwallet", 
		generationExtra, thetime, params, myMnemonicObj, newNum);

#endif
		
}










BigInt<256> generateRandomWithMethod(const std::string& method, const std::string& extra, const std::string& extra2)
{
	if(method == "random")
	{
		std::cout << "Generating from /dev/random" << std::endl;

		const std::string random = getFromDevRandom(32);
		std::cout << std::endl;
	
		const BigInt<256> privkey(random, 'c');
	
	
		//std::cout << "Number: " << hexString(privkey.getBinaryLong()) << std::endl;
		return privkey;
	}
	else if(method == "dice")
	{
		std::cout << "Generating from dice: " << extra << std::endl;
		
		const BigInt<256> privkey = getRandomNumFrom6SideDice(extra);		
	
		return privkey;
	}
	else if(method == "hex")
	{
		std::cout << "Generating from hex: " << extra << std::endl;
		
		const BigInt<256> privkey = hexStringToBigInt(extra);
		
		return privkey;
	}
	else if(method == "hash")
	{
		std::cout << "Generating from hash: " << extra << std::endl;
				
		const BigInt<256> privkey = hashStringToBigInt(extra);
		
		return privkey;
	}
	
	else if(method == "brain")
	{
#ifdef NO_BRAINWALLET_GENERATION
		std::cout << "No brainwallet support" << std::endl;
		throw std::string("Brainwallet not supported");
#else				
		std::cout << "Brain string: " << extra << std::endl;
		std::cout << "Salt: " << extra2 << std::endl;
		std::cout << std::endl;
		
		const BigInt<256> privkey =  brainwalletToBigInt(extra, extra2);
						
		return privkey;
#endif
	}	
	else
	{
		std::cout << "Unknown method: " << method << std::endl;
		throw std::string("Unknown method");
	}
}


