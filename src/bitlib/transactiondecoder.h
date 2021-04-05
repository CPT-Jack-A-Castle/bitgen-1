#ifndef TRANSACTION_DECODER_H
#define TRANSACTION_DECODER_H

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
#include <vector>
#include <map>

#include "bigint.h"
#include "scriptdecoder.h"
#include "readStream.h"
#include "cryptoDecoder.h"
#include "sigPos.h"
#include "txHash.h"
#include "amount.h"
#include "binaryTransaction.h"



std::string convertFromHex(const std::string hexString);



class TransAndInScriptPos
{
public:
	TransAndInScriptPos(const BinaryTransaction& inTransaction, const std::list<SigPos> inInputScriptPositions) :
		transaction(inTransaction.raw()), inputScriptPositions(inInputScriptPositions) {}
	
	//Creates transaction TO SIGN (other input scripts empty)
	BinaryTransaction getUnsignedTransactionForIndex(const int numToCheck, const BinaryScript& redeemScript) const;
	
	//Creates SIGNED transaction (other input scripts unchanged)
	BinaryTransaction replaceScriptInTransaction(const int numToCheck, const BinaryScript& script) const;
	
	RSVal partlySignMultisig(const PrivKey& givenPriv, const BigInt<256>& tempKey) const;
	
	
	const std::string transaction;
	const std::list<SigPos> inputScriptPositions;
};





class HashWithIndex
{
public:
	HashWithIndex(const TxHash& inHash, const int inIndex) : 
		hash(inHash), index(inIndex) {}


	const TxHash hash;
	const int index;
};







class TransactionInput
{
public:	
	TransactionInput(const TxHash& inTxHash, const int inIndex, const BinaryScript& inScript, const BigInt<64> inSequence) : 
		txHash(inTxHash), index(inIndex), script(inScript), sequence(inSequence) {}

	//TransactionInput(const TxHash& inTxHash, const int inIndex, const std::string& inScript, const BigInt<64> inSequence) : 
	//	txHash(inTxHash), index(inIndex), script(inScript), sequence(inSequence) {}

	HashWithIndex getHashIndex() const
	{
		const HashWithIndex hi(txHash, index);
		return hi;
	}	
	
	Script getParsedScript() const
	{
		//const BinaryScript unlockScript = ti.script;		
		const Script parsedScript = Script::parse(script);
		return parsedScript;
	}
	
	
	//const 
	TxHash txHash;
	//const 
	int index;
	//const 
	BinaryScript script;
	//const 
	BigInt<64> sequence;
};



class TransactionOutput
{	
public:
	TransactionOutput(const BinaryScript& inScript, const Amount& inAmount) :
		script(inScript), amount(inAmount) {}


	Script getParsedScript() const
	{
		//const BinaryScript lockingScript = to.script;
		const Script parsedScript = Script::parse(script);
		return parsedScript;
	}		

	std::string toString() const
	{
		std::string ret;
		ret += script.scriptToAddress();
		ret += ":";
		ret += amount.toString();
		
		return ret;
	}
		
	std::string serialize() const;

		
	//const 
	BinaryScript script;
	//const 
	Amount amount;	
};




class TransactionSet
{
	std::map<std::string, std::string> hashToTransaction;
};


//Todo: Relation to TxData???
class CryptoTransaction
{
public:	
	CryptoTransaction(const BigInt<64>& inVersion, const std::vector<TransactionInput>& inInputs,
		const std::vector<TransactionOutput>& inOutputs, const BigInt<64>& inLocktime) : 
		version(inVersion), inputs(inInputs), outputs(inOutputs), locktime(inLocktime), myOwnHash(calculateHash()) {}

	//Todo: Rename to "parseWithPositions()"
	static CryptoTransaction parseBinaryTransaction(const BinaryTransaction& transaction,
		std::list<SigPos>& signaturePositions, const bool printInfo = false);

	static CryptoTransaction parseBinaryTransaction(const BinaryTransaction& transaction, const bool printInfo = false);



	static CryptoTransaction parseTransaction(ReadStream& stream, const bool printInfo = false);


	static TransactionOutput parseMyTransactionOutput(ReadStream& stream);

	static CryptoTransaction parseBinaryTransactionStream(
		ReadStream& stream,
		std::list<SigPos>& signaturePositions, const bool printInfo);



	static CryptoTransaction parse(const BinaryTransaction& binaryTransaction,
				const bool printInfo = false);

	std::string toString(const bool verbose = false) const;
	void printTransactionInfo(const bool verbose) const;
	std::string stringSimple() const;
	void saveScripts() const;
	std::list<TxHash> getInputHashes() const;

	BinaryTransaction serialize() const;

	std::string locktimeInfoStr() const;
private:
	TxHash calculateHash() const;	//Todo: Use getTxHash instead, use the reversed hash
public:
	TxHash calcTxHashPlain() const
	{
		return myOwnHash;	//Precalculated
		//return calcHash();
	}

/*
	TxHash calcTxHashReverse() const
	{
		//Todo: Improve implementation
		const std::string hashStr = calcHash();		
		const TxHash hashFirst(hashStr, true);		
		const TxHash hash(hashFirst.getReverseTxHash(), true);		//Todo!!!!!!!!!!!!!!!
		return hash;
	}
*/

	void saveScript(const BinaryScript& script, const TxHash /*std::string*/& transHash, const int index, const std::string& extra) const;

	bool runBch(Amount& totalIn, const bool verbose) const;
	bool run(const TransAndInScriptPos& transWithPos, Amount& totalIn, const bool verbose) const;
	//bool run2(const TransactionSet& transSet, const TransAndInScriptPos& transWithPos, Amount& totalIn, const bool verbose) const;


	bool isCoinbase() const
	{
		if(inputs.size() == 1)
		{
			const TransactionInput& input = *inputs.begin();
			return input.txHash.zero();
		}
		
		return false;
	}


	//Todo: Remove, use getOutputRef instead
	TransactionOutput getOutputObject(const int index) const
	{
		if(index >= outputs.size())
		{
			throw std::string("Index out of bounds");
		}
		
		return outputs[index];		
	}

	const TransactionOutput& getOutputRef(const int index) const
	{
		if(index >= outputs.size())
		{
			throw std::string("Index out of bounds");
		}
		
		return outputs[index];		
	}


	const TransactionInput& getInput(const int index) const
	{
		if(index >= inputs.size())
		{
			throw std::string("Index out of bounds for transaction inputs");
		}
		
		return inputs[index];		
	}

	Amount getTotalOutAmount() const
	{
		Amount total;
		
		for(std::vector<TransactionOutput>::const_iterator it = outputs.begin() ;
			it !=  outputs.end() ;
			++it)
		{
			const TransactionOutput& to = (*it);
			total += to.amount;
		}
	
		return total;
	}

/*
	Amount getReward() const
	{
		Amount total;
		
		for(std::list<TransactionOutput>::const_iterator it = outputs.begin() ;
			it !=  outputs.end() ;
			++it)
		{
			const TransactionOutput& to = (*it);
			total += to.amount;
		}

		for(std::list<TransactionInput>::const_iterator it = inputs.begin() ;
			it !=  inputs.end() ;
			++it)
		{
			const TransactionInput& ti = (*it);
			total -= ti.amount; qqq
		}
		
		return total;
	}
*/


	const BigInt<32> version;	//Todo: BigInt32 ????
	std::vector<TransactionInput> inputs;			//Todo: const
	std::vector<TransactionOutput> outputs;
	const BigInt<64> locktime;
	
	const TxHash myOwnHash;		//Must be initialized last
};





class TransactionDecoder
{
public:

	static BigInt<64> reversedIntStr(const std::string& str);	
	static int decodeVariableSizeInteger(ReadStream& stream, int& sizeOfSize);

	
	static BigInt<64> decodeVersion(ReadStream& stream);
	static int decodeOutputIndex(ReadStream& stream);
	static BigInt<64> decodeFourByteInteger(ReadStream& stream);
	static BigInt<64> decodeEightByteInteger(ReadStream& stream);
	static BigInt<64> decodeSequence(ReadStream& stream);
	static std::string reverseBytes(const std::string& str);
	static TxHash decodeTxHashPlain(ReadStream& stream);
	static BinaryScript decodeScript(ReadStream& stream, const int size);
	static BinaryScript decodeScriptTotal(ReadStream& stream);

	static BinaryScript decodeRawInputScript(ReadStream& stream, int& sigStartPos, int& sigLen);
	static BinaryScript doDecodeRawInputScript(ReadStream& stream);
	
	
	static BinaryTransaction tryGetTransactionFromFile(const std::string& filename);

	static BinaryTransaction getTransactionFromFile(const std::string& filename);
	static BinaryScript getScriptFromFile(const std::string& filename);
	static std::string getSignatureFromFile(const std::string& filename);
	
	


};




#endif
