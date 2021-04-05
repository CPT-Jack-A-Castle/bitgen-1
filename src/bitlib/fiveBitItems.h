#ifndef FIVE_BIT_ITEMS_H
#define FIVE_BIT_ITEMS_H
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


#include <string>
#include "bigint.h"



class FiveBitItems
{
public:

	FiveBitItems() : num(0) {}

	//From byte representation
	explicit FiveBitItems(const std::string& str);	//The input string is a byte-wise representation of a binary number
	FiveBitItems(const BigInt<512>& inVal, const int inNum);

	//To byte representation
	std::string getBytes() const;
	std::string getVersionAndHashBytes() const;	

	void addInput(const FiveBitItems& other);
	void addLast(unsigned char myChar);	
	unsigned char getAt(const int i) const;
	FiveBitItems getRange(const int start, const int end) const;
	
	int size() const { return num; }

	friend bool operator==(const FiveBitItems& a, const FiveBitItems& b);

	unsigned char shiftLeftTwo();

	std::string not_used_toString() const;
private:
	std::string getAsMyBytes() const;
	const static int MAX_SIZE = 100;
	
private:
	unsigned char thevalues[MAX_SIZE];
	int num;

};


bool operator==(const FiveBitItems& a, const FiveBitItems& b);
bool operator!=(const FiveBitItems& a, const FiveBitItems& b);




#endif
