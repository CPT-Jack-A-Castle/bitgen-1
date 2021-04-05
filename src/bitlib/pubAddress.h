#ifndef PUB_ADDRESS_H
#define PUB_ADDRESS_H
/**
 * pubAddress.h - Bitcoin poscript generator
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


#include "bigint.h"
#include "bitcoinEC.h"
#include "hash.h"
#include "base58.h"
#include "currencySpecific.h"
#include "BinaryScript.h"


class PubAddress
{
public:
	explicit PubAddress(const std::string& address) : theRipeSum(getRipeSumFromAddress(address)), 
		isAMultisig(addressIsMultisig(address))
	{
		validatePubAddress(address);
	}


	PubAddress(const std::string& ripe, const bool isMultisig) : 
		theRipeSum(ripe), isAMultisig(isMultisig)
	{
	}


	static bool isCashAddr(const std::string& address);

	static bool isAddress(const std::string& address)
	{
		try
		{
			PubAddress a(address);
		}
		catch(const std::string& err)
		{
			return false;
		}
		
		return true;
	}
	
	static PubAddress fromHash160(const std::string& theRipe, const char netVersion);
	
	std::string getHash160() const;


	BigInt<512> getNumeric() const
	{
		const char netVersion = getNetVersion();
	
		const std::string address = ripeToAddress(theRipeSum, netVersion);	
		return Base58Decode<512>(address);		
	}
	
	BigInt<32> calculateChecksum() const;

	std::string toString() const
	{
		const char netVersion = (isAMultisig ? getMultisigVersion() : getNetVersion());
		
		return ripeToAddress(theRipeSum, netVersion);
	}

	std::string toCurrencySpecificString() const
	{
		if(getCurrencyShortName() == "bch")
		{
			return toCashAddrString();
		}
		else
		{
			return toString();
		}
	}


	std::string toCashAddrString() const;
	std::string toFullCashAddrString() const;
	std::string toCashAddrReadableString() const;


	bool isMultisig() const;

	static PubAddress multisigToBitcoinAddress(const BinaryScript& addressStringRepresentation);


	friend bool operator!=(const PubAddress& a, const PubAddress& b);
	friend bool operator==(const PubAddress& a, const PubAddress& b);
	friend std::ostream& operator<<(std::ostream& stream, const PubAddress& addr);
	friend bool operator<(const PubAddress& a, const PubAddress& b);
	friend class PubKey;	//Todo: Remove!
	
	static PubAddress pubkeyToBitcoinAddress(const std::string& addressStringRepresentation);
	
private:

	static bool addressIsMultisig(const std::string& address);



	static std::string getRipeSumFromAddress(const std::string& address);
	
	static std::string ripeToAddress(const std::string& theRipe, const char netVersion);


	static PubAddress stringToBitcoinAddress(const std::string& addressStringRepresentation, const char netVersion);


	static PubAddress bitcoinAddresFromPubkey(const ECPoint& pubk, const bool compressed);


	void validatePubAddress(const std::string& a);

	//Todo: Remove this method? No compressed argument present!
	static PubAddress not_used_pubPointToBitcoinAddress(const ECPoint& pubkey);

private:
	const std::string theRipeSum;	//Todo: char[]
	const bool isAMultisig;
};


bool operator<(const PubAddress& a, const PubAddress& b);
std::ostream& operator<<(std::ostream& stream, const PubAddress& addr);
bool operator==(const PubAddress& a, const PubAddress& b);
bool operator!=(const PubAddress& a, const PubAddress& b);

#endif
