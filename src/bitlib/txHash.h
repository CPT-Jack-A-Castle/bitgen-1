#ifndef TXHASH_H
#define TXHASH_H

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


#include "bigintutil.h"
#include "util.h"

#include <string>



class TxHash
{
public:
	TxHash() : str(std::string(32, '\0')) {}

	static TxHash fromHex(const std::string hexStr)
	{
		return TxHash(hexStrToBytes(hexStr));
	}

	static TxHash fromHexReverse(const std::string hexStr)
	{
		return TxHash(reverseStr(hexStrToBytes(hexStr)));
	}


/*
private:

	explicit TxHash(const std::string& inStr, const bool dummy1, const bool dummy2, const bool dummy3) : str(hexStrToBytes(inStr))
	{
		if(str.size() != 32)
		{
			throw std::string("Internal txHash error");
		}
	}
public:
*/
	explicit TxHash(const std::string& inStr) : str(inStr)
	{
		if(str.size() != 32)
		{
			std::cout << "Expected size: 32, got: " << str.size() << std::endl;
			throw std::string("Internal txHash error");
		}		
	}

private:
	std::string internal_getReverseTxHash() const
	{
		std::string ret;
		
		for(int i = (str.size() - 1) ; i >= 0 ; i--)
		{
			const unsigned char c = str[i];
			ret += c;
		}
		return ret;
	}
public:

	std::string raw() const
	{
		return str;
	}

	bool zero() const
	{
		std::string zeroNum(32, '\0');
		return (str == zeroNum);
	}


	std::string toPrintoutString() const	//Todo: Rename to toString()
	{
		return hexString(internal_getReverseTxHash());
	}
	

	std::string str;	//Todo: Make private
};


bool operator==(const TxHash& a, const TxHash& b);
bool operator!=(const TxHash& a, const TxHash& b);

bool operator<(const TxHash& a, const TxHash& b);
bool operator>(const TxHash& a, const TxHash& b);




#endif

