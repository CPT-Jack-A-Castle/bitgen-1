#ifndef GENERATION_METHODS_H
#define GENERATION_METHODS_H

/**
 * GenerationMethods.h - Bitcoin poscript generator
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
 
 
#include <vector>
#include <string>
#include <list>

#include "GenerationParameters.h"
#include "bitcoinKeyPair.h"
#include "extraInfo.h"

#include "mnemonic.h"

#include "ExtraOptionsRandom.h"



class GenerationMethods
{
public:	

	static void generateBrainWallet(const std::vector<std::string>& args, const std::string& thetime);
	static void generateHash(const std::vector<std::string>& args, const std::string& thetime);
	static void generateHex(const std::vector<std::string>& args, const std::string& thetime);
	static void generateBulk(const std::vector<std::string>& args, const std::string& thetime);
	static void generateWithDice(const std::vector<std::string>& args, const std::string& thetime);
	static void generateFromMnemonic(const std::vector<std::string>& args, const std::string& thetime);
	static void generateRandom(const std::vector<std::string>& args, const std::string& thetime);
	static void generateOtpParts(const std::vector<std::string>& args, const std::string& thetime);
	static void generateOtpTotal(const std::vector<std::string>& args, const std::string& thetime);
	
	
	static void generateFromWif(const std::vector<std::string>& args, const std::string& thetime);
	
	static void printRandomSourceWarning(const std::string generator = "/dev/random");
	
	static std::string generateOneFileContents(const BitcoinKeyPair& keypair, const bool addPubkey, std::string& customString);
	
	
	static void saveAllFiles(const PubAddress& pubaddr, const std::string& privaddr, const std::string& genMethod,
		const std::list<ExtraInfo>& generationExtra, const std::string& thetime, const GenerationParameters& params,
		const Mnemonic& mnemonic, 
		const int newNum = 0, const bool isPad = false, const BigInt<256> staticXor = BigInt<256>()
	);
	
	static void saveTheFilesInFolders(const PubAddress& pubaddr, const std::string& privaddr, const std::string& genMethod,
		const std::list<ExtraInfo>& generationExtra, const std::string& thetime, const GenerationParameters& params,
		const Mnemonic& mnemonic, const int newNum, const bool isPad, const BigInt<256> staticXor,
		const std::string& privPath, const std::string& pubPath)	;
	
	static void saveTheOTPPublicFilesInFolders(const PubAddress& pubaddr, 
		const std::string& thetime, const GenerationParameters& params,
		const int newNum, 
		const std::string& pubPath);
	

	static void generateBinaryRandomNumber(const std::vector<std::string>& args, const std::string& thetime);
	
	
private:
	static int getNextNumberIfConfigured(GenerationParameters& params);

	static void savePublicPadPart(const PubAddress& pubAddr, const std::string& thetime,
		const GenerationParameters& params, const int newNum, const std::string& pubPath);

	static void savePrivatePadPart(const std::list<BigInt<256> >& pads, const std::string method,
		const std::list<std::string>& hashParts, std::vector<std::string>& privatePaths, const PubAddress& pubAddr,
		const std::string generator, const std::string& thetime, const int totalPads, const GenerationParameters& params,
		const BigInt<256>& staticXor, const int newNum);


	static void splitPassphrase(const std::string& passphrase, std::list<std::string>& generationExtra);
};



BigInt<256> generateRandomWithMethod(const std::string& method, const std::string& extra, const std::string& extra2);



#endif
