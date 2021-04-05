#ifndef CASH_ADDRESS_H
#define CASH_ADDRESS_H
/**
 * fiveBitItems.h - Bitcoin poscript generator
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

#include "fiveBitItems.h"


class CashAddress
{
public:
	static std::string toCashAddrString(const std::string& theRipeSum, const bool isAMultisig);
	
	static std::string fullDecodeCashAddr(const std::string& origStr, bool& isMultisig, 
											std::string& versionAndHash_out, std::string& checksumRaw_out);

	static std::string getRipeSumFromCashAddress(const std::string& address);

private:
	static void verifyCashAddrChecksum(const std::string& hash, const bool isMultiSig,
		const FiveBitItems& givenChecksumFiveBit);


	static FiveBitItems computeTheChecksumForVersionAndRipeSum(const FiveBitItems& payloadInput);

	static std::string encodeBase32(const FiveBitItems& imp);

	static void verifyOnlyCashAddrCharacters(const std::string& str);

	static FiveBitItems computeCashAddrChecksum(const FiveBitItems& input);

	static bool isCashAddrChar(const char c);

	static FiveBitItems lower5Bits(const std::string& prefix);

	static FiveBitItems decodeCashAddr(const std::string& str);

};


#endif
