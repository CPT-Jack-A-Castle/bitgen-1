#ifndef BINARY_TRANSACTION_H
#define BINARY_TRANSACTION_H

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
#include "bigintutil.h"
#include "hash.h"
#include "txHash.h"

class BinaryTransaction
{
public:
	explicit BinaryTransaction(const std::string& inTransaction) : transaction(inTransaction) {}

	static BinaryTransaction fromHex(const std::string& hexStr);

	std::string asHex() const
	{
		return hexString(transaction);
	}

	TxHash hash() const
	{
		const std::string hash = doubleSha256(transaction);			
		const TxHash hashFirst(hash);	
		return hashFirst;
	}

	
	std::string hashStr() const;
	std::string raw() const { return transaction; }
	
	int size() const { return transaction.size(); }
	
private:
	const std::string transaction;
	
	friend bool operator==(const BinaryTransaction& a, const BinaryTransaction& b);
	friend bool operator!=(const BinaryTransaction& a, const BinaryTransaction& b);	
};


bool operator==(const BinaryTransaction& a, const BinaryTransaction& b);
bool operator!=(const BinaryTransaction& a, const BinaryTransaction& b);


#endif
