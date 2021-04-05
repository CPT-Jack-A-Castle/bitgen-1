/**
 * pubAddress.cpp - Bitcoin poscript generator
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

#include "pubAddress.h"
#include "base58.h"
#include "currencySpecific.h"
#include "util.h"
#include "fiveBitItems.h"
#include "cashAddress.h"


bool PubAddress::isCashAddr(const std::string& address)
{	
	try
	{
		bool isMultisig(false);
		std::string versionAndHash_out;
		std::string checksumRaw_out;
		CashAddress::fullDecodeCashAddr(address, isMultisig, versionAndHash_out, checksumRaw_out);	//Throws on error
	}
	catch(const std::string& err)
	{
		return false;
	}
	
	return true;
}





bool PubAddress::addressIsMultisig(const std::string& address)
{
	if(isCashAddr(address))
	{
		bool isMultisig(false);
		std::string versionAndHash_out;
		std::string checksumRaw_out;
		const std::string hash = CashAddress::fullDecodeCashAddr(address, isMultisig, 
								versionAndHash_out, checksumRaw_out);
		
		return isMultisig;			//Todo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}
	
	const BigInt<512> decoded = Base58Decode<512>(address);
	
	const BigInt<512> lastFour = decoded.returnMaskHighBits(32);
	
	const BigInt<512> fourBytesDropped = decoded >> 32;

	const BigInt<512> netVersion = fourBytesDropped >> 160;		//160 bit hash

	const int multiVersionInt = getMultisigVersion();
	const BigInt<512> multiVersionBig(multiVersionInt);

	if(netVersion == multiVersionBig)
	{
		return true;
	}


	return false;
}


BigInt<32> PubAddress::calculateChecksum() const
{
	const char netVersion = (isAMultisig ? getMultisigVersion() : getNetVersion());

	const std::string netByte(1, netVersion);
	
	const std::string toHash = netByte + theRipeSum;
	
	const std::string hash = doubleSha256(toHash);
		
	const std::string firstFourBytes = hash.substr(0,4);
	const BigInt<32> checkSum(firstFourBytes, 'c');
	return checkSum;	
}


bool operator<(const PubAddress& a, const PubAddress& b)
{
	return (a.theRipeSum < b.theRipeSum);
}


std::string PubAddress::getRipeSumFromAddress(const std::string& address)
{
	try
	{
		//Try if it is a cashaddr
		const std::string ripeStr = CashAddress::getRipeSumFromCashAddress(address);
		return ripeStr;
	}
	catch(const std::string& err)
	{
	}
	
	//This is a legacy address
	
	const BigInt<512> numeric = Base58Decode<512>(address);
	
	const BigInt<512> fourBytesDropped = numeric >> 32;
	const BigInt<512> ripe = fourBytesDropped & 160;
	const BigInt<160> ripeSmall(ripe);
	return ripeSmall.getBinaryLong();
}


std::string PubAddress::toCashAddrString() const
{
	return CashAddress::toCashAddrString(theRipeSum, isAMultisig);
}

std::string PubAddress::toFullCashAddrString() const
{
	return cashAddrPrefix() + ":" + toCashAddrString();
}


std::string PubAddress::toCashAddrReadableString() const
{
	const std::string cashAddr = toCashAddrString();
	
	std::string ret;
	
	for(int i = 0 ; i < cashAddr.size() ; i++)
	{
		ret += cashAddr[i];
		
		if(i == 41)
		{
			continue;
		}
		
		if(i % 7 == 6)
		{
			ret += " ";
		}
	}
	
	return ret;
}



PubAddress PubAddress::bitcoinAddresFromPubkey(const ECPoint& pubk, const bool compressed)
{	
	const std::string uncompStr = pubk.getRaw(compressed);
	return pubkeyToBitcoinAddress(uncompStr);		
}


std::string PubAddress::getHash160() const
{
	return theRipeSum;
}



bool PubAddress::isMultisig() const
{
	return isAMultisig;
}





//Throws on error
void PubAddress::validatePubAddress(const std::string& address)
{	
	if(isCashAddr(address))
	{
		return;
	}
	
	const BigInt<512> decoded = Base58Decode<512>(address);
		
	const BigInt<512> lastFour = decoded.returnMaskHighBits(32);
	
	const BigInt<512> fourBytesDropped = decoded >> 32;

	const int netVersionInt = getNetVersion();
	const BigInt<512> netVersionBig(netVersionInt);

	const int multiVersionInt = getMultisigVersion();
	const BigInt<512> multiVersionBig(multiVersionInt);


	const BigInt<512> netVersion = fourBytesDropped >> 160;		//160 bit hash
	//std::cout << "Net version: \n" << netVersion << std::endl;
	if(netVersion != netVersionBig && netVersion != multiVersionBig)
	{
		std::string errMsg("Given net version mismatch: ");
		errMsg += netVersion.strHex();
		errMsg += " != ";
		errMsg += netVersionBig.strHex();
		errMsg += " or ";		
		errMsg += multiVersionBig.strHex();
		
		throw errMsg;
	}
	


	const BigInt<32> calculatedChecksum = calculateChecksum();
	const BigInt<512> checkSum(calculatedChecksum.getBinaryLong(), 'c');

	if(lastFour != checkSum)
	{
		std::string errMsg("Incorrect checksum for public address: ");
		errMsg += address;
		throw errMsg;
	}
}




PubAddress PubAddress::pubkeyToBitcoinAddress(const std::string& addressStringRepresentation)
{
	const char netVer = getNetVersion();
	return stringToBitcoinAddress(addressStringRepresentation, netVer);
}


PubAddress PubAddress::multisigToBitcoinAddress(const BinaryScript& addressStringRepresentation)
{
	const char netVer = getMultisigVersion();
	return stringToBitcoinAddress(addressStringRepresentation.raw(), netVer);
}







PubAddress PubAddress::fromHash160(const std::string& theRipe, const char netVersion)
{		
	const char multiVersionInt = getMultisigVersion();	
	const bool isMultisig = (netVersion == multiVersionInt);

	return PubAddress(theRipe, isMultisig);
}


std::string PubAddress::ripeToAddress(const std::string& theRipe, const char netVersion)	
{
	const std::string netVersionByte(1, netVersion);
	
	const std::string ripeWithVersion = netVersionByte + theRipe;
	
	const std::string ripeShaSha = doubleSha256(ripeWithVersion);

	const std::string checkSum = ripeShaSha.substr(0, 4);
	
	const std::string ripeWithChecksum = ripeWithVersion + checkSum;
	
	BigInt<200> ripeChecksumInt(ripeWithChecksum, 'c');
	
	std::string b58 = Base58Encode(ripeChecksumInt);
	return b58;
}



PubAddress PubAddress::stringToBitcoinAddress(const std::string& addressStringRepresentation, const char netVersion)
{			
	const std::string theSha = sha256(addressStringRepresentation);
			
	const std::string theRipe = ripemd160(theSha);
	
	return fromHash160(theRipe, netVersion);	
}





std::ostream& operator<<(std::ostream& stream, const PubAddress& addr)
{
	stream << addr.toString();
	return stream;
}


bool operator==(const PubAddress& a, const PubAddress& b)
{
	return (a.theRipeSum == b.theRipeSum);
}

bool operator!=(const PubAddress& a, const PubAddress& b)
{
	return (a.theRipeSum != b.theRipeSum);
}


