#ifndef CRYPTO_DECODER_H
#define CRYPTO_DECODER_H

/**
 * transaction.h - Bitcoin poscript generator
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


#include <string>
#include <iostream>

#include "readStream.h"
#include "bigint.h"



template<int NUM_BITS>
std::string getReversed(BigInt<NUM_BITS>& hash)
{
	std::string ret;
	const std::string bytes = hash.getBinaryLong();
	for(int i = (bytes.size() - 1) ; i >= 0 ; i--)
	{
		const unsigned char c = bytes[i];
		ret += c;
	}
	return ret;
}


class CryptoDecoder
{
public:

	//Encode	
	static std::string varIntSize(const int num);
	static unsigned char intByte(const int val);
	
	//Decode
	static int decodeVariableSizeInt(ReadStream& stream);
	static int decodeVariableSizeInteger(ReadStream& stream, int& sizeOfSize);
	static BigInt<64> reversedIntStr(const std::string& str);	
	static int decodeByteInteger(ReadStream& stream);	

};





#endif
