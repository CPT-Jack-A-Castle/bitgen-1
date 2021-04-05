/**
 * random.cpp - Bitcoin poscript generator
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

#include "random.h"
#include "util.h"
#include "randomUtils.h"
#include "keyDerivationFunction.h"


BigInt<256> getRandomNumFrom6SideDice(const std::string& dice6, const int numThrows, const bool needExactNumber)
{	
	if(needExactNumber)
	{
		if(dice6.size() != numThrows)
		{
			std::cout << "Error, must have exactly " << numThrows << " dice throws, have: " << dice6.size() << std::endl;
			throw std::string("Wrong number of throws");
		}		
	}
	else
	{
		if(dice6.size() < numThrows)
		{
			std::cout << "Error, must have at least " << numThrows << " dice throws, have: " << dice6.size() << std::endl;
			throw std::string("Need more throws");
		}
	}
	
	
	BigInt<256> dice;
	
	for(int i = 0 ; i < dice6.size() ; i++)
	{
		const char c = dice6[i];
		if(!(c >= '1' && c <= '6'))
		{
			std::cout << "Error, illegal char: " << c << std::endl;
			throw std::string("Illegal char");			
			//exit(1);
		}
		const int val = c - '1';
		dice *= 6;		
		dice += val;
	}
	
	//std::cout << "Result (hex): " << dice << std::endl;
	//std::cout << "Result digits: " << dice.numberBitsNeeded() << std::endl;

	return dice;
}







BigInt<256> hexStringToBigInt(const std::string& privKeyStrMix)
{	
	if(privKeyStrMix.size() != 64)
	{
		std::string errMsg("Privkey must be 64 hex characters, got: ");
		errMsg += intToString(privKeyStrMix.size());
			
		throw errMsg;		
	}
		
	//std::cout << "The privkey: " << privKeyStr << std::endl;
	const std::string privKeyStrUpper = toUpper(privKeyStrMix);
		
	const BigInt<256> privKey = BigInt<256>::fromHex(privKeyStrUpper);
	
	return privKey;
}




BigInt<256> hashStringToBigInt(const std::string& hashval, const int minChars)
{
	checkHashEntropy(hashval, minChars);
										
	const std::string sha = sha256(hashval);
	const BigInt<256> privKey(sha, 'c');
	return privKey;
}



BigInt<256> brainwalletToBigInt(const std::string& passphrase, const std::string& salt)
{
	checkPassphraseEntropy(passphrase);
	
	if(salt.empty())
	{
		std::cout << std::endl;
		std::cout << "Salt must be at least one character" << std::endl;
		throw std::string("Salt not specified");
	}
	
	std::cout << "Calculating, this may take a while..." << std::endl;	
	const std::string kdfStr = bitgenArgon2Kdf(passphrase, salt);
	
	if(kdfStr.size() != 32)
	{
		throw std::string("KDF error");
	}
	
	const std::string sha = sha256(kdfStr);
	const BigInt<256> privKey(sha, 'c');
	
	return privKey;
}


