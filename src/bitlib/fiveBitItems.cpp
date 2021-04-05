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
#include "util.h"
#include "bigintutil.h"
#include <vector>


FiveBitItems::FiveBitItems(const BigInt<512>& inVal, const int inNum) : num(inNum) 
{	
	BigInt<512> myVal(inVal);
	
	for(int i = 0 ; i < inNum ; i++)
	{
		const BigInt<512> lastVal = myVal & 5;
		myVal >>= 5;
		
		const unsigned char val = lastVal.intVal();
		const int index = inNum - i - 1;		
		thevalues[index] = val;
	}
}



unsigned char FiveBitItems::shiftLeftTwo()
{
	unsigned char extra(0);
	for(int i = num - 1 ; i >= 0 ; i--)
	{
		
		thevalues[i] <<= 2;
		thevalues[i] |= extra;		

		extra = thevalues[i];
		extra >>= 5;	

		thevalues[i] &= 0x1f;
	}

	return extra;
}


//The input string is a byte-wise representation of a binary number
FiveBitItems::FiveBitItems(const std::string& str) : num(0)
{	
	//Should be divisible with both 5 and 8
	const int numBytes = str.size();
	const int numBits = numBytes * 8;	
	
	if(numBits % 8 != 0)
	{
		throw std::string("Num bits must be divisible with 8");		
	}
	
	if(numBits % 5 != 0)
	{
		throw std::string("Num bits must be divisible with 5");
	}
	
	
	
	const int numFiveParts = numBits / 5 / 8;


	int myPos(0);
	
	for(int part = 0 ; part < numFiveParts ; part++)
	{
		std::vector<unsigned char> valueVec;
		
		unsigned long long current(0);

		for(int i = 0 ; i < 5 ; i++)
		{
			const unsigned char eightBits = str[myPos++];
			current <<= 8;
			current |= eightBits;			
		}

		for(int i = 0 ; i < 8 ; i++)
		{
			const unsigned char fiveBits = current & 0x1f;
			current >>= 5;
			valueVec.push_back(fiveBits);
			
		}
		
		for(std::vector<unsigned char>::const_reverse_iterator it = valueVec.rbegin();
			it != valueVec.rend();
			++it)
		{
			const unsigned char c = (*it);
			addLast(c);			
		}				
	}
}



/*
//The string parameter is a binary representation of a number
FiveBitItems::FiveBitItems(const std::string& str) : num(0)
{	
	BigInt<512> payloadInt(BigInt<512>::fromBytes(str));
		
	const int numBits = str.size() * 8;
	const int numExtraBits = numBits % 5;
	const int padBits = ((numExtraBits == 0) ? 0 : (5 - numExtraBits));
	//std::cout << "padBits: " << padBits << std::endl;
	
	if(numBits % 8 != 0)
	{
		throw std::string("Num bits must be divisible with 8");		
	}
	
	if(numBits % 5 != 0)
	{
		throw std::string("Num bits must be divisible with 5");
	}

	
	if(padBits != 0)
	{
		throw std::string("Error, pad bits not zero");
	}
	
	payloadInt <<= padBits;

	const int finalNumBits = numBits + padBits;
	const int num5bitItems = finalNumBits / 5;
			
	std::vector<unsigned char> valueVec;
	
	for(int i = 0 ; i < num5bitItems ; i++)
	{
		BigInt<512> myVal = payloadInt & 5;
		payloadInt >>= 5;
		const unsigned char v = myVal.intVal();

		thevalues[num5bitItems - 1 - i] = v;		
	}
	num = num5bitItems;
}
*/


bool operator==(const FiveBitItems& a, const FiveBitItems& b)
{	
	if(a.num != b.num)
	{
		return false;
	}
	
	for(int i = 0 ; i < a.num ; i++)
	{
		if(a.thevalues[i] != b.thevalues[i])
		{
			return false;
		}
	}
	
	return true;
}


bool operator!=(const FiveBitItems& a, const FiveBitItems& b)
{
	return !(a == b);	
}





void FiveBitItems::addInput(const FiveBitItems& other)
{
	if((size() + other.size() + 1) >= MAX_SIZE)
	{
		throw std::string("The max capacity of FiveBitItems reached");
	}
	
	
	for(int i = 0 ; i < other.num ; i++)
	{
		thevalues[i + num] = other.thevalues[i];
	}
	
	num += other.num;
}


void FiveBitItems::addLast(unsigned char myChar)
{
	if((size() + 1) >= MAX_SIZE)
	{
		throw std::string("Max capacity of FiveBitItems reached");
	}
	
	const unsigned char ddLower = myChar & 0x1f;
	
	thevalues[num] = ddLower;
	num++;
}


unsigned char FiveBitItems::getAt(const int i) const
{	
	if(i >= num)
	{
		//std::cout << "Getting outside of range: " << i << std::endl;
		return 0;
	}
	
	const unsigned char ret = thevalues[i];
	
	return ret;
}



FiveBitItems FiveBitItems::getRange(const int start, const int end) const
{	
	FiveBitItems ret;

	for(int i = start ; i < end ; i++)
	{
		const unsigned char c = getAt(i);
		ret.addLast(c);
	}
		
	return ret;
}



std::string FiveBitItems::getAsMyBytes() const
{	
	//std::cout << "Getting as bytes for size: " << size() << std::endl;
	//Should be divisible with both 5 and 8
	int numBits = num * 5;	
	int numExtraFiveBits(0);
	
	while(numBits % 8 != 0)
	{
		numExtraFiveBits++;
		
		numBits = (num + numExtraFiveBits) * 5;		
	}
	

	const int numEightParts = numBits / 5 / 8;

	std::string totRet;

	int myPos(0);

	for(int part = 0 ; part < numEightParts ; part++)
	{
		unsigned long long current(0);

		for(int i = 0 ; i < 8 ; i++)
		{
			const unsigned char fiveBits = getAt(myPos++);
			current <<= 5;
			current |= fiveBits;
		}

		std::string ret;

		for(int i = 0 ; i < 5 ; i++)
		{
			const unsigned char eightBits = current & 0xff;	
			const std::string e(1, eightBits);
			ret = e + ret;
			current >>= 8;
		}
		
		totRet += ret;
	}

	return totRet;
}



std::string FiveBitItems::getBytes() const
{	
	const std::string would = getAsMyBytes();
	return would;	
}





std::string FiveBitItems::getVersionAndHashBytes() const
{
	if(size() != 42)
	{
		std::cout << "Size: " << size() << std::endl;
		throw std::string("Internal error, size must be 42 for getting version and hash bytes");
	}
		
	const int numBitsTotal = num * 5;
	const int numExtraBits = numBitsTotal % 8;
	const int numBits = numBitsTotal - numExtraBits;
		
	const int numBytes = numBits / 8;

	const std::string myBytes = getAsMyBytes();

	const std::string otherVersionAndHashStr = myBytes.substr(0, 21);
	return otherVersionAndHashStr;
}



std::string FiveBitItems::not_used_toString() const
{	
	std::string ret;
	ret += intToString(num);
	ret += " : ";
		
	for(int i = 0 ; i < num ; i++)
	{
		const unsigned char c = getAt(i);
		ret += intToString(int(c));
		ret += ",";
	}
		
	return ret;
}


