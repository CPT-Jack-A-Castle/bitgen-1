

#include "transactiondecoder.h"
#include "util.h"
#include "FileUtil.h"
#include "transaction.h"


std::string TransactionOutput::serialize() const
{
	std::string str;
	
	const std::string amountStr = Transaction::encodeAmount(amount.amount);		
	str += amountStr;

	const std::string scriptStr = script.raw();
	str += Transaction::intByte(scriptStr.size());
	str += scriptStr;
	
	return str;
}



BigInt<64> TransactionDecoder::reversedIntStr(const std::string& str)
{
	return CryptoDecoder::reversedIntStr(str);	
}





BigInt<64> TransactionDecoder::decodeVersion(ReadStream& stream)
{
	const std::string str = stream.getStr(4);

	const BigInt<64> version = reversedIntStr(str);
	
	return version;
}



int TransactionDecoder::decodeOutputIndex(ReadStream& stream)
{
	const std::string str = stream.getStr(4);
	const BigInt<64> index = reversedIntStr(str);
	return index.intVal();
}



BigInt<64> TransactionDecoder::decodeFourByteInteger(ReadStream& stream)
{
	const std::string str = stream.getStr(4);
	const BigInt<64> num = reversedIntStr(str);
	return num;
}



BigInt<64> TransactionDecoder::decodeEightByteInteger(ReadStream& stream)
{
	const std::string str = stream.getStr(8);
	const BigInt<64> num = reversedIntStr(str);
	return num;
}


BigInt<64> TransactionDecoder::decodeSequence(ReadStream& stream)
{
	const std::string str = stream.getStr(4);
	const BigInt<64> sequence = reversedIntStr(str);
	return sequence;
}



//Todo: Move to util
std::string TransactionDecoder::reverseBytes(const std::string& str)
{
	
	std::string reversed;
	for(int i = str.size() - 1 ; i >= 0 ; i--)
	{
		const unsigned char c = str[i];
		reversed += c;
	}
	
	return reversed;
}


TxHash TransactionDecoder::decodeTxHashPlain(ReadStream& stream)
{
	const std::string str = stream.getStr(32);	
	const TxHash txHash(str);	
	return txHash;
}






int TransactionDecoder::decodeVariableSizeInteger(ReadStream& stream, int& sizeOfSize)
{
	return CryptoDecoder::decodeVariableSizeInteger(stream, sizeOfSize);	
}



BinaryScript TransactionDecoder::doDecodeRawInputScript(ReadStream& stream)
{
	int sigStartPos(0);
	int sigLen(0);

	return decodeRawInputScript(stream, sigStartPos, sigLen);	
}


BinaryScript TransactionDecoder::decodeRawInputScript(ReadStream& stream, int& sigStartPos, int& sigLen)
{	
	sigStartPos = stream.currentPos();

	int sizeOfSize(0);
	const int size = decodeVariableSizeInteger(stream, sizeOfSize);
		
	sigLen = size + (sizeOfSize - 1);	//Todo: WHY MINUS ONE???????????

	const std::string script = stream.getStr(size);
	if(script.size() != size)
	{
		std::cout << "Need size: " << size << ", got: " << script.size() << std::endl;
		
		throw std::string("Input script error");
	}
	
	return BinaryScript(script);
}



BinaryScript TransactionDecoder::decodeScript(ReadStream& stream, const int size)
{
	const std::string script = stream.getStr(size);	
	return BinaryScript(script);
}



BinaryScript TransactionDecoder::decodeScriptTotal(ReadStream& stream)
{
	const int size = CryptoDecoder::decodeByteInteger(stream);
	const BinaryScript script = decodeScript(stream, size);
	return script;	
}



BinaryTransaction CryptoTransaction::serialize() const
{
	std::string str;
	
	const std::string versionStr = Transaction::getVersion(version);
	
	const std::string inputCountStr = Transaction::inputCount(inputs.size());

	
	str += versionStr;
	str += inputCountStr;

	for(std::vector<TransactionInput>::const_iterator it = inputs.begin() ;
		it != inputs.end() ;
		++it)
	{
		const TransactionInput& ti = (*it);
		
		//Todo: Make method TransactionInput::serialize()
		
		const std::string prevTxHashStr = Transaction::prevTxHash(ti.txHash);
		const std::string outputIndexStr = Transaction::outputIndex(ti.index);
		
		str += prevTxHashStr;
		str += outputIndexStr;
		
		const std::string scriptWithSize = Transaction::sizeIndicationAndScript(ti.script, true);			
		str += scriptWithSize;
		
		const BigInt<32> mySeq(ti.sequence);
		const std::string sequenceStr = Transaction::fourByteInt(mySeq);
		str += sequenceStr;
	}
	
	
	const std::string numberOutputsStr = Transaction::numberOutputs(outputs.size());		
	str += numberOutputsStr;
	
	
	for(std::vector<TransactionOutput>::const_iterator it = outputs.begin() ;
		it != outputs.end() ;
		++it)
	{
		const TransactionOutput& to = (*it);
		
		str += to.serialize();
	}

	const std::string locktimeStr = Transaction::locktime(locktime.intVal());
	str += locktimeStr;
	
	return BinaryTransaction(str);
}





CryptoTransaction CryptoTransaction::parse(const BinaryTransaction& trans,
	const bool printInfo)
{
	std::list<SigPos> signaturePositions;
	const CryptoTransaction cryptoTrans = CryptoTransaction::parseBinaryTransaction(trans, signaturePositions, printInfo);
	return cryptoTrans;
}






//Todo: Rename "signaturePositions" to inputScriptPositions
CryptoTransaction CryptoTransaction::parseBinaryTransaction(
		const BinaryTransaction& transaction,
		std::list<SigPos>& signaturePositions, const bool printInfo)
{
	
	ReadStream stream(transaction.raw());

	return parseBinaryTransactionStream(stream, signaturePositions, printInfo);
}

CryptoTransaction CryptoTransaction::parseBinaryTransaction(const BinaryTransaction& transaction, const bool printInfo)
{
	ReadStream stream(transaction.raw());
	std::list<SigPos> signaturePositions;
	return parseBinaryTransactionStream(stream, signaturePositions, printInfo);
}



CryptoTransaction CryptoTransaction::parseTransaction(ReadStream& rs, const bool printInfo)
{
	std::list<SigPos> signaturePositions;	//Not used
	return CryptoTransaction::parseBinaryTransactionStream(rs, signaturePositions, printInfo);
}




TransactionOutput CryptoTransaction::parseMyTransactionOutput(ReadStream& stream)
{
	const BigInt<128> amount(TransactionDecoder::decodeEightByteInteger(stream));
	const BinaryScript script = TransactionDecoder::decodeScriptTotal(stream);
				
	const TransactionOutput transactionOutput(script, amount);
		
	return transactionOutput;
}




CryptoTransaction CryptoTransaction::parseBinaryTransactionStream(
		ReadStream& stream,
		std::list<SigPos>& signaturePositions, const bool printInfo)
{	
	const BigInt<64> version = TransactionDecoder::decodeVersion(stream);
	
	if(printInfo)
	{
		std::cout << "Version: " << version << std::endl;
	}
	
	const int numInputs = CryptoDecoder::decodeVariableSizeInt(stream);

	if(printInfo)
	{
		std::cout << "Num inputs: " << numInputs << std::endl;
	}


	std::vector<TransactionInput> inputs;
	inputs.reserve(numInputs);
	
	for(int i = 0 ; i < numInputs ; i++)
	{
		const TxHash txHash = TransactionDecoder::decodeTxHashPlain(stream);	
		if(printInfo)
		{
			std::cout << "TxHash: " << txHash.toPrintoutString() << std::endl;
		}
			
		const int index = TransactionDecoder::decodeOutputIndex(stream);
		if(printInfo)
		{
			std::cout << "index: " << index << std::endl;
		}

		
		int sigStartPos(0);
		int sigLen(0);
		const BinaryScript inputScript = TransactionDecoder::decodeRawInputScript(stream, sigStartPos, sigLen);	
		
		const SigPos sigPos(sigStartPos, sigLen, inputScript);
		signaturePositions.push_back(sigPos);
		
		if(printInfo)
		{
			std::cout << "inputScript with size " << inputScript.raw().size() << ": " << hexString(inputScript.raw()) << std::endl;
		}
		
		const BigInt<64> sequence = TransactionDecoder::decodeSequence(stream);
		
		if(printInfo)
		{
			std::cout << "sequence: " << sequence << std::endl;
		}

				
		const TransactionInput transactionInput(txHash, index, inputScript, sequence);
		inputs.push_back(transactionInput);		
	}

	const int numOutputs = CryptoDecoder::decodeVariableSizeInt(stream);

	if(printInfo)
	{
		std::cout << "Num outputs: " << numOutputs << std::endl;
	}
	
	std::vector<TransactionOutput> outputs;		
	outputs.reserve(numOutputs);
	
	for(int i = 0 ; i < numOutputs ; i++)
	{
		const TransactionOutput transactionOutput = parseMyTransactionOutput(stream);
		
		outputs.push_back(transactionOutput);
	}
	
	const BigInt<64> locktime = TransactionDecoder::decodeFourByteInteger(stream);

	if(printInfo)
	{
		std::cout << "Locktime: " << locktime << std::endl;
		std::cout << "End parse transaction" << std::endl;
	}

	const CryptoTransaction cryptoTransaction(version, inputs, outputs, locktime);
	return cryptoTransaction;
}






std::string CryptoTransaction::stringSimple() const
{
	std::string ret;

	ret += "Inputs: ";
	ret += intToString(inputs.size());
	ret += " Outputs: ";
	ret += intToString(outputs.size());
	
	ret += "\n\n";
	
	if(isCoinbase())
	{
		ret += "Coinbase transaction\n";
	}
	
	for(std::vector<TransactionInput>::const_iterator it = inputs.begin() ;
		it != inputs.end() ;
		++it)
	{
		
		const TransactionInput& input = (*it);
		
		const bool txIsZero = input.txHash.zero();
		
		if(txIsZero)
		{
			ret += "Zero hash, coinbase transaction\n";
		}
		else
		{
			ret += minSize(input.script.scriptToAddress(), 34);
			ret += " ";
			ret += input.txHash.toPrintoutString();
			ret += " at ";
			ret += intToString(input.index);
			ret += "\n";			
		}
	}

	ret += "\n";

	int outputNum(0);
	for(std::vector<TransactionOutput>::const_iterator it = outputs.begin() ;
		it != outputs.end() ;
		++it)
	{
		const TransactionOutput& output = (*it);
		
		const std::string theAddress = output.script.scriptToAddress();
		ret += minSize(theAddress, 34);
		
		const Amount outAmount(output.amount);
		ret += " ";
		ret += minSize(output.amount.amount.strDec(), 15, true);
		ret += " satoshi = ";
		ret += minSize(outAmount.amountString(), 15);
		ret += " ";
		ret += getCurrencyShortName();
		ret += "\n";
		
	}

	
	ret += "\n";
	
	return ret;
}




TxHash CryptoTransaction::calculateHash() const
{
	const BinaryTransaction serialized = serialize();
	return serialized.hash();
}




void CryptoTransaction::saveScript(const BinaryScript& script, const TxHash& transHash, const int index, const std::string& extra) const
{
	const std::string indexStr = intToString(index);
	const std::string filename = getCurrencyShortName() + "_script_" + extra + "_" + 
		transHash.toPrintoutString() + "_" + indexStr + ".script";
	
	Script::saveScriptWithFilename(BinaryScript(script), filename);	
}


void CryptoTransaction::saveScripts() const
{
	const TxHash transHash = calcTxHashPlain();
	
	std::cout << "Inputs" << std::endl;
	int index(0);
	for(std::vector<TransactionInput>::const_iterator it = inputs.begin() ;
		it != inputs.end() ;
		++it)
	{
		const TransactionInput& input = (*it);
		saveScript(input.script, transHash, index, "input");
		index++;
	}

	std::cout << std::endl;
	std::cout << "Outputs" << std::endl;

	int outIndex(0);
	for(std::vector<TransactionOutput>::const_iterator it = outputs.begin() ;
		it != outputs.end() ;
		++it)
	{
		const TransactionOutput& output = (*it);
		saveScript(output.script, transHash, outIndex, "output");		
		//Script::saveTheScript(output.script);
		outIndex++;
	}

}





std::string CryptoTransaction::locktimeInfoStr() const
{	
	if(locktime.intVal() < 500000000)
	{
		return "(block height)";
	}
	else
	{
		return "(Unix epoch time)";
	}	
}



std::string CryptoTransaction::toString(const bool verbose) const
{
	std::string ret;
	if(verbose)
	{	
		ret += "Transaction data----------------------\n";
		ret += "Version   : ";
		ret += version.strDec();
		ret += "\n";
		
		//Todo: If locktime is unix epoc time, print the time string
		ret += "Locktime  : ";
		ret += locktime.strDec();
		ret += " ";
		ret += locktimeInfoStr();
		ret += "\n";
	}


	ret += "Inputs: ";
	ret += intToString(inputs.size());
	ret += " Outputs: ";
	ret += intToString(outputs.size());
	ret += "\n\n";
	
	if(isCoinbase())
	{
		ret += "Coinbase transaction\n";
	}
	
	int inputNum(0);
	for(std::vector<TransactionInput>::const_iterator it = inputs.begin() ;
		it != inputs.end() ;
		++it)
	{
		if(verbose)
		{	
			ret += "--Input index ";
			ret += intToString(inputNum);
			ret += "\n";				
		}
		
		const TransactionInput& input = (*it);
		ret += "IHash  : ";
		ret += input.txHash.toPrintoutString();
		ret += " at ";
		ret += intToString(input.index);
		ret += "\n";
		
		const bool txIsZero = input.txHash.zero();
		
		if(txIsZero)
		{
			ret += "Zero hash, coinbase transaction\n";
		}
		else
		{
			ret += "Address: ";
			ret += input.script.scriptToAddress();
			ret += "\n";
			if(verbose)
			{	
				ret += "Type   : ";
				ret += input.script.scriptTypeString();
				ret += "\n";				
				ret += "Seq    : ";
				ret += input.sequence.strHex();
				ret += "\n";
			}
		}
		
		if(verbose)
		{		
			ret += "IScript: ";
			ret += hexString(input.script.raw());
			ret += "\n";
			
			if(!txIsZero)
			{
				const Script parsedScript = Script::parse(input.script);
				ret += "Decoded script: ";
				ret += parsedScript.toString();
				ret += "\n";
			}
			
		}
		inputNum++;		
	}

	ret += "\n";

	int outputNum(0);
	for(std::vector<TransactionOutput>::const_iterator it = outputs.begin() ;
		it != outputs.end() ;
		++it)
	{
		const TransactionOutput& output = (*it);
		if(verbose)
		{
			ret += "--Output index ";
			ret += intToString(outputNum++);
			ret += "\n";			
			ret += "OScript: ";
			ret += hexString(output.script.raw());
			ret += "\n";
			const Script parsedScript = Script::parse(output.script);
			ret += "Decoded script: ";
			ret += parsedScript.toString();
			ret += "\n";
			ret += "Script type: ";
			ret += output.script.scriptTypeString();
			ret += "\n";			
		}
		

		const std::string theAddress = output.script.scriptToAddress();
		ret += " ";
		ret += minSize(theAddress, 34);
		

		const Amount outAmount(output.amount);
		ret += " ";
		ret += minSize(output.amount.amount.strDec(), 15, true);
		ret += " satoshi = ";
		ret += minSize(outAmount.amountString(), 15);
		ret += " ";
		ret += getCurrencyShortName();
		ret += "\n";
		

	}

	ret += "\n";
	return ret;
}




//Todo: Remove, use toString() instead
void CryptoTransaction::printTransactionInfo(const bool verbose) const
{
	std::cout << toString(verbose) << std::endl;
}






std::string TransactionDecoder::getSignatureFromFile(const std::string& filename)
{
	const std::string content = readFile(filename);
	const std::string hexOnly = getHexString(content);
	const std::string script = convertFromHex(hexOnly);	
	return script;
}



BinaryScript TransactionDecoder::getScriptFromFile(const std::string& filename)
{
	const std::string content = readFile(filename);
	const std::string hexOnly = getHexString(content);
	const std::string script = convertFromHex(hexOnly);	
	return BinaryScript(script);
}

BinaryTransaction TransactionDecoder::getTransactionFromFile(const std::string& filename)
{
	const std::string content = readFile(filename);
	const std::string hexOnly = getHexString(content);
	const std::string script = convertFromHex(hexOnly);	
	return BinaryTransaction(script);
}




BinaryTransaction TransactionDecoder::tryGetTransactionFromFile(const std::string& filename)
{
	try
	{
		return BinaryTransaction(getTransactionFromFile(filename));
	}
	catch(const std::string& err)
	{
		return BinaryTransaction("");
	}
}



std::list<TxHash> CryptoTransaction::getInputHashes() const
{
	std::list<TxHash> ret;
	
	for(std::vector<TransactionInput>::const_iterator it = inputs.begin() ;
		it != inputs.end() ;
		++it)
	{
		const TransactionInput& ti = (*it);
		const TxHash& hash = ti.txHash;
		ret.push_back(hash);
	}

	return ret;
}




TxData convertCryptoTransactionToTxData(const CryptoTransaction& ct)	
{
	std::list<TxInput> inputs;

	for(const TransactionInput& ti : ct.inputs)
	{
		const TxInput myTi(ti);			
		inputs.push_back(myTi);
	}
		
	std::list<TransactionOutput> recipients;
		
	for(const TransactionOutput& to : ct.outputs)
	{
		recipients.push_back(to);
	}
		
	const Timestamp locktime(ct.locktime.intVal());
		
	const TxData txData(inputs, recipients, locktime, false);
	return txData;
}






bool CryptoTransaction::run(const TransAndInScriptPos& transWithPos,  
	Amount& totalIn, const bool verbose) const
{	
	bool transactionSuccess(true);
	
	int numToCheck = 0;
	//Run input script
	for(std::vector<TransactionInput>::const_iterator it = inputs.begin() ;
		it != inputs.end() ;
		++it)
	{
		const TransactionInput& ti = (*it);
		const TxHash& hash = ti.txHash;
		const int index = ti.index;
		std::cout << "InputHash: " << hash.toPrintoutString() << " Index: " << index << std::endl;
		
		const bool txIsZero = hash.zero();
		
		if(txIsZero)
		{
			std::cout << "Coinbase input, skipping" << std::endl;
			continue;
		}
		
		const BinaryScript unlockScript = ti.script;
		
		
		Script unlockScr = Script::parse(unlockScript);
		
		if(verbose)
		{
			std::cout << "The Unlock script: " << unlockScr.toString() << std::endl;
		}
		
		//If first item is OP_0, this is a multisig, and the last item should be duplicated
		if(unlockScr.isMultiSigUnlockScript())
		{
			//Is multisig unlock script, duplication last item
			unlockScr.items.push_back(unlockScr.items.back());
		}
		//std::cout << "Ready parsing unlock script" << std::endl;



		
		const std::string lockingFilename = Transaction::transactionFilename(hash);
		
		
		//Todo: Get transaction from TransactionSet instead of from file
		const BinaryTransaction lockingTransRaw = TransactionDecoder::tryGetTransactionFromFile(lockingFilename);
		if(lockingTransRaw.raw().empty())
		{
			std::cout << "Could not find locking transaction file: " << lockingFilename << std::endl;
			std::cout << "Skipping verification for this input" << std::endl;
			std::cout << std::endl;
			
			transactionSuccess = false;
			continue;
		}
		
		std::cout << "Got script from file" << std::endl;
		//std::cout << "TODO: GET AMOUNT FROM LOCKING SCRIPT" << std::endl;
		
		std::list<SigPos> lockSignaturePositions;
		const CryptoTransaction lockingTrans = CryptoTransaction::parseBinaryTransaction(lockingTransRaw, lockSignaturePositions);
		
	
				
		const TransactionOutput& to = lockingTrans.getOutputRef(index);
		const BinaryScript lockingScript = to.script;
		const Script lockScr = Script::parse(lockingScript);
		
		if(verbose)
		{
			std::cout << "Locking script: " << lockScr.toString() << std::endl;
		}
		
		const Amount amount(to.amount);
		std::cout << "InAmount: " << amount.amountString() << std::endl;
		totalIn += amount;

		std::string unsignedScript;
		
		if(unlockScr.isMultiSigUnlockScript())
		{
			//Todo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			const ScriptItem lastUnlockItem = unlockScr.items.back();
			if(lastUnlockItem.object != ScriptItem::DATA)
			{
				std::cout << "Unlock Script: " << unlockScr.toString() << std::endl;
				throw std::string("Multisig err");
			}
		
		
			const BinaryScript redeemScript = BinaryScript(lastUnlockItem.data);
		
			const Script parsedRedeemScript = Script::parse(redeemScript);
			if(verbose)
			{	
				std::cout << "============================Redeem script: " << parsedRedeemScript.toString() << std::endl;
			}
		
		
			if(!parsedRedeemScript.isMultiSigRedeem())
			{
				std::cout << "Multisig error" << std::endl;
				throw std::string("Multisig redeem error");
			}
			
			unsignedScript = redeemScript.raw();
		}
		else
		{
			unsignedScript = lockingScript.raw();
		}
				
		const BinaryTransaction unsignedTransaction = transWithPos.getUnsignedTransactionForIndex(numToCheck, BinaryScript(unsignedScript));
		
		if(verbose)
		{	
			std::cout << "Raw unsigned transaction for index: " << numToCheck << ": " << hexString(unsignedTransaction.raw()) << std::endl;
		}
		

		const Script totScript(unlockScr, lockScr);
		
		if(verbose)
		{
			std::cout << "Lock script: " << lockScr.toString() << std::endl;
			std::cout << "Unlock script: " << unlockScr.toString() << std::endl;	
			std::cout << std::endl;
			std::cout << "Total script: " << totScript.toString() << std::endl;
		}
		
		const TxData mytx = convertCryptoTransactionToTxData(*this);		
		const Script stack = totScript.run(mytx, unsignedTransaction, verbose);
		
		const bool success = Script::getSuccessStatus(stack);
		if(success)
		{
			std::cout << "Unlock succeeded for script" << std::endl;
		}
		else
		{
			std::cout << "Unlock FAILED" << std::endl;
			std::cout << "The stack after operation: " << stack.toString() << std::endl;
			transactionSuccess = false;
		}
		
		std::cout << std::endl;
		
		numToCheck++;
	}
	
	return transactionSuccess;
}





bool CryptoTransaction::runBch(Amount& totalIn, const bool verbose) const
{	
	bool transactionSuccess(true);
	
	int numToCheck = 0;
	//Run input script
	for(const TransactionInput& transInput : inputs)
	{
		const TxHash& hash = transInput.txHash;
		const int index = transInput.index;
		std::cout << "InputHash: " << hash.toPrintoutString() << " Index: " << index << std::endl;
		
		const bool txIsZero = hash.zero();
		
		if(txIsZero)
		{
			std::cout << "Coinbase input, skipping" << std::endl;
			continue;
		}
		
		const BinaryScript unlockScript = transInput.script;
		
		
		Script unlockScr = Script::parse(unlockScript);
		
		if(verbose)
		{
			std::cout << "The Unlock script: " << unlockScr.toString() << std::endl;
		}
				
		const std::string lockingFilename = Transaction::transactionFilename(hash);
		
		//Todo: Get transaction from TransactionSet instead of from file
		const BinaryTransaction lockingTransRaw = TransactionDecoder::tryGetTransactionFromFile(lockingFilename);
		if(lockingTransRaw.raw().empty())
		{
			std::cout << "Could not find locking transaction file: " << lockingFilename << std::endl;
			std::cout << "Skipping verification for this input" << std::endl;
			std::cout << std::endl;
			
			transactionSuccess = false;
			continue;
		}
		
		std::cout << "Got script from file" << std::endl;
		
		const CryptoTransaction lockingTrans = CryptoTransaction::parseBinaryTransaction(lockingTransRaw);
		
		const TransactionOutput& lockingOutput = lockingTrans.getOutputRef(index);

		//const BinaryScript lockingScript = lockingOutput.script;
		const Script lockScr = Script::parse(lockingOutput.script);
		
		const Amount amount(lockingOutput.amount);
		std::cout << "InAmount: " << amount.amountString() << std::endl;
		totalIn += amount;
	

		const TransactionInput ourTi(transInput.txHash, transInput.index, lockingOutput.script, 55555); //ti.sequence);
		
		const TxInput myTi(ourTi, lockingOutput.amount);
					
		const TxData mytx = convertCryptoTransactionToTxData(*this);

		const BinaryTransaction thingToVeirfySign = mytx.bch_createTransactionInternal(myTi);
		
		if(verbose)
		{	
			std::cout << "Raw buffer to verify signature for, with index " << numToCheck << ": " << hexString(thingToVeirfySign.raw()) << std::endl;
		}
		

		const Script totScript(unlockScr, lockScr);
		
		if(verbose)
		{
			
			std::cout << "Lock script: " << lockScr.toString() << std::endl;
			std::cout << "Unlock script: " << unlockScr.toString() << std::endl;	
			std::cout << std::endl;
			std::cout << "Total script: " << totScript.toString() << std::endl;
		}
		const Script stack = totScript.run(mytx, thingToVeirfySign, verbose);
		
		const bool success = Script::getSuccessStatus(stack);
		if(success)
		{
			std::cout << "Unlock succeeded for script" << std::endl;
		}
		else
		{
			std::cout << "Unlock FAILED" << std::endl;
			std::cout << "The stack after operation: " << stack.toString() << std::endl;
			transactionSuccess = false;
		}
		
		std::cout << std::endl;
		
		numToCheck++;
	}
	
	return transactionSuccess;
}










