

#include "TransactionCommandline.h"
#include "binaryTransaction.h"
#include "sigPos.h"
#include "transactiondecoder.h"
#include "transaction.h"
#include "binaryTransaction.h"
#include "FileUtil.h"
#include "randomUtils.h"
#include "transactionSignatureChecker.h"
#include "timelock.h"


#include <stdlib.h>
#include <set>


void TransactionCommandline::getTransactionInputHashes(const std::vector<std::string>& args)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen transinputhashes transaction" << std::endl;	
		std::cout << "Displays the hashes for the inputs" << std::endl;
		std::cout << std::endl;
		std::cout << " Example: bitgen transinputhashes 0100000001488D8209894206F1448DA9840CE0D3129B34CEC4EC7025110972E4FF92730002000000006A47304402200CBFB3D94A83B08816B73EF78AF75AE88A72465E394860B2B84227895F648DBE022009633E98C5B6E66649A837414CA191C51128DBE71EA030CC0436F22996E37BFB012103B53D5F9D8CFA70A03667D95BD3B9D7550195792898A140CA2156D3EAAD907AF2FFFFFFFF0140420F00000000001976A91488B052248006D938AF0600C8D2FB2FA0767C787988AC00000000" << std::endl;
		std::cout << std::endl;
		
		return;
	}	
	
	std::cout << std::endl;
	
	const std::string hexStr(args[1]);
	
	
	//Determine if filename or hex string
	const BinaryTransaction binaryTransaction = getTrans(hexStr);
	const CryptoTransaction myTrans = CryptoTransaction::parse(binaryTransaction);
	const std::list<TxHash> hashes = myTrans.getInputHashes();
	
	std::cout << "Num inputs: " << hashes.size() << std::endl;
	
	for(std::list<TxHash>::const_iterator it = hashes.begin() ;
		it != hashes.end() ;
		++it)
	{
		const TxHash& hash = (*it);
		
		std::cout << "Input hash: " << hash.toPrintoutString() << std::endl;
	}
}





//Todo: Remove?????
void not_used_signMultisig(const std::vector<std::string>& args, const bool partSign)
{
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen signmultisig transaction wif" << std::endl;	
		return;
	}	
	
	const std::string transactionStr(args[1]);
	const std::string wifStr(args[2]);
	
	const BinaryTransaction transaction = TransactionCommandline::getTrans(transactionStr);	
	
	const Wif wif(wifStr);
	
	const PrivKey givenPriv = wif.getPriv();
	
	//Todo: Return signed transaction from function
	
	if(partSign)
	{
		const std::string random = getFromDevRandom(32);				
		const BigInt<256> tempKey(random, 'c');
		
		TransactionSigner::partlySignMultisigTransaction(transaction, givenPriv, tempKey);
	}
	else
	{
		TransactionSigner::signMultisigTransaction(transaction, givenPriv);
	}
	
	
	
	//Todo: Save result here
}





//Todo: Remove?
void not_used_combineNormalSignatures(const std::vector<std::string>& args)
{
	const std::string currency = getCurrencyShortName();
	if(currency != "btc" && currency != "btc" && currency != "doge" && currency != "vtc" && currency != "nmc"  && currency != "ftc")
	{
		std::cerr << "Combine signature not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen combinesig unsignedTransaction sig1 sig2 ... sigN" << std::endl;	
		return;
	}	
	
	const std::string transactionStr(args[1]);	
	const BinaryTransaction transaction = TransactionCommandline::getTrans(transactionStr);	
		
	std::list<RSVal> signatures;	//Todo: Use RSVal for the signatures??
	
	for(int i = 0 ; i < (args.size() - 2) ; i++)
	{
		const std::string sigStr(args[2 + i]);	
		const RSVal signature = TransactionCommandline::getSigFromFile(sigStr);		
		signatures.push_back(signature);
	}
	
	const BinaryTransaction signedTransaction = TransactionSigner::insertSignaturesInNormalTransaction(transaction, signatures);	
	
	if(signedTransaction.raw().empty())
	{
		std::cout << "Could not sign transaction" << std::endl;
		throw std::string("Could not sign");
	}
	
	std::cout << "Signed transaction: " << signedTransaction.asHex() << std::endl;
	Transaction::saveTranscation(signedTransaction);
}










void createTimelock(const std::vector<std::string>& args)
{
	if(!TransactionCommandline::transactionSupportedForCurrency())
	{
		const std::string currency = getCurrencyShortName();
		std::cout << "Timelock not supported for currency: " << currency << std::endl;
		throw std::string("Not supported");
	}
	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen timelock blockheight pkif" << std::endl;
		std::cout << "Creates timelocked script" << std::endl;
		return;
	}
		
	std::string blockHeightStr(args[1]);
	const int blockHeight = atoi(blockHeightStr.c_str());
	std::cout << "Blockheight: " << blockHeight << std::endl;

	const std::string pkifStr = args[2];
	
	const PubKey pubKey = TransactionCommandline::stringToPubkey(pkifStr);

	const BinaryScript script = createTimelockScript(blockHeight, pubKey);
	std::cout << "Redeem script: " << script.hex() << std::endl;

	
	const PubAddress pubAddress = PubAddress::multisigToBitcoinAddress(script);

	std::cout << std::endl;
	std::cout << "The timelock address: " << pubAddress.toString() << std::endl;			
	
	const std::string scriptFilename = "redeem_timelock_" + getCurrencyShortName() + "_" + pubAddress.toString() + ".script";
	Script::saveScriptWithFilename(script, scriptFilename);	
}








std::string createMultisigTxtFile(const int numReq, const std::list<PubKey>& mypkifSet, 
	const PubAddress& pubAddress, const std::string& script)
{
	std::string fileContent;
	fileContent += "Type    : Multisig ";
	fileContent += intToString(numReq);
	fileContent += "/";
	fileContent += intToString(mypkifSet.size());
	fileContent += "\n";

	fileContent += "Address : ";
	fileContent += pubAddress.toString();
	fileContent += "\n";

	fileContent += "\n";
	
	int num(1);
	for(std::list<PubKey>::const_iterator it = mypkifSet.begin() ;
		it != mypkifSet.end() ;
		++it)
	{
		const PubKey& pk = (*it);
		const PubAddress& pubAddress = pk.getAddress();
		fileContent += "Pubkey ";
		fileContent += intToString(num++);		
		fileContent += ": ";
		fileContent += pk.toString();
		fileContent += " ";
		fileContent += pubAddress.toString();
		fileContent += "\n";
	}
	
	fileContent += "\n";
	
	fileContent += "Redeem script: ";
	fileContent += hexString(script);
	fileContent += "\n";

	return fileContent;
}







PubKey TransactionCommandline::stringToPubkey(const std::string pkifStr)
{
	if(Pkif::isPkif(pkifStr))
	{
		const Pkif pkif(pkifStr);
		const PubKey pubKey = pkif.getPubKey();
		return pubKey;
	}
	else if(PubKey::isPubkey(pkifStr))
	{
		const PubKey pubKey = PubKey::fromHex(pkifStr);
		return pubKey;		
	}
	else
	{
		std::cout << "Not a pkif or pubkey: " << pkifStr << std::endl;
		throw std::string("PKIF error");
	}
}




std::list<PubKey> getSortedPkifs(std::list<std::string> pkifStrings)
{
	std::set<PubKey> mypkifSet;
	
	for(std::list<std::string>::const_iterator it = pkifStrings.begin() ;
		it != pkifStrings.end() ;
		++it)
	{
		const std::string pkifStr = (*it);		

		const PubKey pubKey = TransactionCommandline::stringToPubkey(pkifStr);	
		mypkifSet.insert(pubKey);		
	}
	
	std::list<PubKey> pkifList;
	
	int num(1);
	for(std::set<PubKey>::const_iterator it = mypkifSet.begin() ;
		it !=  mypkifSet.end() ;
		++it)
	{
		const PubKey& pubKey = (*it);
		std::cout << "Pubkey #" << num++ << ": " << pubKey.toString() << std::endl;;
		std::cout << "" << pubKey.toStringHex() << std::endl;

		pkifList.push_back(pubKey);
	}
	
	
	if(pkifStrings.size() != pkifList.size())	//Check if there are duplicates
	{
		throw std::string("Incorrect number public keys");
	}
	
	return pkifList;
}








void createMultisig(const std::vector<std::string>& args)
{
	if(!TransactionCommandline::transactionSupportedForCurrency())
	{
		std::cerr << "Create multisig not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen multisig numReq NumTotal pkif1 ... pkifn" << std::endl;
		return;
	}
		
	std::string numReqStr(args[1]);
	const int numReq = atoi(numReqStr.c_str());

	std::string numTotalStr(args[2]);
	const int numTotal = atoi(numTotalStr.c_str());
	
	if(numReq > numTotal)
	{
		std::cout << "Required more than total" << std::endl;
		throw std::string("Required can not be more than total");		
	}
	
	
	if(args.size() <= 2 + numTotal)
	{
		std::cout << "Pkif missing" << std::endl;
		std::cout << "Usage: bitgen multisig numReq NumTotal pkif1 ... pkifn" << std::endl;
		return;
	}
	
	std::list<std::string> pkifList;
	for(int i = 0 ; i < numTotal ; i++)
	{
		const std::string pkif = args[3 + i];
		//std::cout << "Found pkif/pubkey: " << pkif << std::endl;
		
		pkifList.push_back(pkif);
	}
	
	std::cout << std::endl;
	std::cout << "CREATING MULTISIG ADDRESS " << numReq << "/" << pkifList.size() << std::endl;
	

	
	const std::list<PubKey> mypkifSet = getSortedPkifs(pkifList);	

	
	const BinaryScript script = ScriptCreator::createMultiSigScript(numReq, mypkifSet);	



	std::cout << std::endl;
	std::cout << "Redeem script: " << script.hex() << std::endl;

	std::cout << std::endl;


	const PubAddress pubAddress = PubAddress::multisigToBitcoinAddress(script);

	std::cout << std::endl;
	std::cout << "The multisig address: " << pubAddress.toString() << std::endl;
	
	std::string fileContent = createMultisigTxtFile(numReq, mypkifSet, pubAddress, script.raw());
	
	const std::string filename = "multi_" + pubAddress.toString() + "_pub.txt";
	
	std::cout << "Writing file: " << filename << std::endl;
	fileWrite(filename, fileContent);
	
	//Save script
	const std::string scriptFilename = "multi_redeem_" +  getCurrencyShortName() + "_" + pubAddress.toString() + ".script";
	Script::saveScriptWithFilename(script, scriptFilename);
	
}








void createInScript(const std::vector<std::string>& args)
{
	if(!TransactionCommandline::transactionSupportedForCurrency())
	{
		std::cerr << "Create inscript not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	//Todo
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen inscript type [extra]" << std::endl;	
		return;
	}	
	
	const std::string typeStr(args[1]);
	if(typeStr == "addr")
	{
		const std::string pkifStr(args[2]);
	
	
		std::cout << "Creating address in script without signature information" << std::endl;
		std::cout << "Note: The script can not be used directly as in script. " << std::endl;
		std::cout << "      it is used for creating the signature" << std::endl;
	
		const PubKey pubkey(PubKey::fromPkif(pkifStr));
	

		std::cout << "Pubkey: " << pubkey.toString() << std::endl;
								
		const std::string pubAddRaw = pubkey.getRaw();
		const std::string theSha = sha256(pubAddRaw);
		const std::string scriptHashStr = ripemd160(theSha);
				
		const BinaryScript script = ScriptCreator::scriptPubkeyWithHash(scriptHashStr);
	
		const PubAddress pubAddress	= pubkey.getAddress();
	
		const std::string scriptFilename = "redeem_addr_" + getCurrencyShortName() + "_" + pubAddress.toString() + ".script";
		Script::saveScriptWithFilename(script, scriptFilename);	
	}
	else
	{
		std::cout << "Unknown input script type: " << typeStr << std::endl;
		throw std::string("Unknown type");
	}
}








void createOutScript(const std::vector<std::string>& args)
{
	if(!TransactionCommandline::transactionSupportedForCurrency())
	{
		std::cerr << "Create outscript not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}


	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen outscript addr address" << std::endl;	
		std::cout << "       bitgen outscript pubkey pubkey/pkif" << std::endl;	
		std::cout << "       bitgen outscript opreturn data rettype" << std::endl;
		std::cout << "       bitgen outscript anyone" << std::endl;
		
		return;
	}	
	
	const std::string scriptType(args[1]);
	
	if(scriptType == "addr")
	{
		if(args.size() < 3)
		{
			std::cout << "Usage: bitgen outscript addr address" << std::endl;		
			return;
		}	
		
		std::cout << "Creating address out script" << std::endl;
		
		const std::string nextAddrStr(args[2]);
	
		const PubAddress pubAddress(nextAddrStr);
	
		if(pubAddress.isMultisig())
		{				
			const BinaryScript script = ScriptCreator::createMultisigFundScript(pubAddress);
			const std::string scriptFilename = "fund_multisig_" + getCurrencyShortName() + "_" + pubAddress.toString() + ".script";
			Script::saveScriptWithFilename(script, scriptFilename);	
		}
		else
		{					
			const BinaryScript script = ScriptCreator::scriptPubAddress(pubAddress);
			const std::string scriptFilename = "fund_address_" + getCurrencyShortName() + "_" + pubAddress.toString() + ".script";
			Script::saveScriptWithFilename(script, scriptFilename);	
		}
	}
	else if(scriptType == "pubkey")
	{
		if(args.size() < 3)
		{
			std::cout << "Usage: bitgen outscript pubkey pubkey/pkif" << std::endl;	
			return;
		}	
	
		std::cout << "Creating pubkey out script" << std::endl;
	
		const std::string pkifStr(args[2]);	
		
		const PubKey pubkey(PubKey::fromPkif(pkifStr));
		const PubAddress pubAddress = pubkey.getAddress();
	
		std::cout << "pubkey: " << pubkey.toString() << std::endl;
		const BinaryScript fundScript = ScriptCreator::createOldPubkeyFundscript(pubkey);
			
		const std::string scriptFilename = "fund_pubkey_" + getCurrencyShortName() + "_" + pubAddress.toString() + ".script";
		Script::saveScriptWithFilename(fundScript, scriptFilename);	
	}
	else if(scriptType == "opreturn")
	{

		if(args.size() < 4)
		{
			std::cout << "Usage: bitgen outscript opreturn data rettype" << std::endl;	
			std::cout << "rettype: OP_RETURN op_return DOCPROOF DOCPROOFFILE EW EWA" << std::endl;	
			
			return;
		}	
		std::cout << "Creating OP_RETURN out script" << std::endl;
	
	
		const std::string dataStr(args[2]);
		const std::string typeStr(args[3]);
	
		std::cout << "Data: " << dataStr << std::endl;
		std::cout << "Type: " << typeStr << std::endl;
	
		const BinaryScript script = TransactionCommandline::createOpreturnScript(dataStr, typeStr);
		const std::string scriptHash = doubleSha256(script.raw());

		const std::string scriptFilename = "fund_opreturn_" + getCurrencyShortName() + "_" + hexString(scriptHash) + ".script";
		Script::saveScriptWithFilename(script, scriptFilename);	
	}
	else if(scriptType == "anyone")
	{

		if(args.size() < 2)
		{
			std::cout << "Usage: bitgen outscript anyone" << std::endl;	
			return;
		}	

		std::cout << "Creating anyone-can-spend out script" << std::endl;

		const BinaryScript script = ScriptCreator::createAnyoneCanSpendScript();			

		const std::string scriptFilename = "fund_anyone_" + getCurrencyShortName() + ".script";
		Script::saveScriptWithFilename(script, scriptFilename);
	}
	else
	{
		std::cerr << "Unknown script type: " << scriptType << std::endl;
	}	
}





void TransactionCommandline::saveScript(const std::vector<std::string>& args)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen savescript hexscript" << std::endl;	
		std::cout << std::endl;
		std::cout << " Example: bitgen savescript 47304402200CBFB3D94A83B08816B73EF78AF75AE88A72465E394860B2B84227895F648DBE022009633E98C5B6E66649A837414CA191C51128DBE71EA030CC0436F22996E37BFB012103B53D5F9D8CFA70A03667D95BD3B9D7550195792898A140CA2156D3EAAD907AF2" << std::endl;	
		std::cout << std::endl;
		
		return;
	}	
	
	
	const std::string argScript(args[1]);
	const BinaryScript script = getScript(argScript);	
	
	const Script parsedScript = Script::parse(script);


	std::cout << std::endl;

	Script::saveTheScript(script);
}





std::string signatureFilename(const PrivKey& givenPriv)
{
	const BitcoinEllipticCurve ec;
	const PubKey pubkey = givenPriv.getPubkey(ec);
	
	const std::string filename = "sig_" + getCurrencyShortName() + "_" + pubkey.toString() + ".sig";
	return filename;
}



void saveSignatureFile(const std::string& signature, const PrivKey& givenPriv)
{
	const std::string filename = signatureFilename(givenPriv);
		
	const std::string content = hexString(signature) + "\n";
	fileWrite(filename, content);
	std::cout << std::endl;
	std::cout << "Saved signature file: " << filename << std::endl;
	std::cout << std::endl;	
}





BigInt<256> getTempKey(const bool fixedNounce)
{
	if(fixedNounce)
	{
		std::cout << std::endl;
		std::cout << "WARNING, USING FIXED NOUNCE, USE ONLY FOR TEST" << std::endl;
		std::cout << std::endl;
		
		const BigInt<256> tempKey("6722228373827382837283738483837483728384786374837483727383738273");
		return tempKey;		
	}
	else
	{
		std::cout << std::endl;
		std::cout << "Will get random bytes from /dev/random." << std::endl;
		std::cout << "Press keys or move the mouse if needed" << std::endl;
	
		const std::string random = getFromDevRandom(32);				
		const BigInt<256> tempKey(random, 'c');
		return tempKey;
	}
}





void partSignMultisig(const std::vector<std::string>& args)
{
	if(!TransactionCommandline::transactionSupportedForCurrency())
	{
		std::cerr << "Sign multisig not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen signmultisig unsignedTransaction wif" << std::endl;	
		return;
	}	
	
	bool fixedNounce(false);
	if(args.size() > 3)
	{
		const std::string extra = args[3];
		if(extra == "fixednounce")
		{
			std::cout << "Warning, will use fixed nounce" << std::endl;
			fixedNounce = true;
		}
	}
	const std::string transactionStr(args[1]);
	const std::string wifStr(args[2]);
	
	const BinaryTransaction transaction = TransactionCommandline::getTrans(transactionStr);
	
	const Wif wif(wifStr);
	
	const PrivKey givenPriv = wif.getPriv();

	const BigInt<256> tempKey = getTempKey(fixedNounce);
		
	const RSVal rs = TransactionSigner::partlySignMultisigTransaction(transaction, givenPriv, tempKey);
	
	if(rs.r != 0)
	{
		const std::string signature = Script::encodeSignature(rs);
		saveSignatureFile(signature, givenPriv);			
	}
	
		
	//Todo: Save result here
}





BinaryScript TransactionCommandline::getScript(const std::string& arg)
{
	//Determine if filename or hex string	
	
	try
	{
		const std::string script = convertFromHex(arg);
		return BinaryScript(script);
	}
	catch(const std::string& err)
	{
		//Not a hex string, file name?
		const std::string filename = arg;
		if(!endsWith(filename, ".script"))
		{
			throw std::string("Script file must have extension .script");
		}
		
		const BinaryScript binScript = TransactionDecoder::getScriptFromFile(filename);
		return binScript;
	}
	
	//Will never get here
	return BinaryScript("");
}




RSVal TransactionCommandline::getSigFromFile(const std::string& filename)
{
	if(!endsWith(filename, ".sig"))
	{
		throw std::string("Signature file must end with .sig");
	}
		
	
	const std::string signature = TransactionDecoder::getSignatureFromFile(filename);

	//Check that the RS value is valid
	ReadStream stream(signature);
	const RSVal rs = ScriptDecoder::decodeSignatureRS(stream);
	return rs;
}




void combineMultisigSignatures(const std::vector<std::string>& args)
{
	if(!TransactionCommandline::transactionSupportedForCurrency())
	{
		const std::string currency = getCurrencyShortName();
		std::cout << "Combine multisig not supported for currency: " << currency << std::endl;
		throw std::string("Not supported");
	}
	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen combinemultisig unsignedTransaction sig1 sig2 ... sigN" << std::endl;	
		return;
	}	
	
	const std::string transactionStr(args[1]);	
	const BinaryTransaction transaction = TransactionCommandline::getTrans(transactionStr);	
	
	std::list<RSVal> signatures;
	
	for(int i = 0 ; i < (args.size() - 2) ; i++)
	{
		const std::string sigStr(args[2 + i]);	
		const RSVal signature = TransactionCommandline::getSigFromFile(sigStr);	
		
		signatures.push_back(signature);
	}
	
	const BinaryTransaction signedTransaction = TransactionSigner::insertSignaturesInMultisigTransaction(transaction, signatures);	
	
	if(!signedTransaction.raw().empty())		
	{
		std::cout << "Signed transaction: " << signedTransaction.asHex()  << std::endl;
		Transaction::saveTranscation(signedTransaction);
	}
	else
	{
		std::cout << "Could not sign transaction" << std::endl;
	}
}



void TransactionCommandline::decodeScript(const std::vector<std::string>& args)
{
	if(!transactionSupportedForCurrency())
	{
		const std::string currency = getCurrencyShortName();
		std::cout << "Decode script not supported for currency: " << currency << std::endl;
		throw std::string("Not supported");
	}
	
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen decodescript hextransaction [verbose]" << std::endl;	
		std::cout << std::endl;		
		std::cout << " Example: bitgen decodescript 47304402200CBFB3D94A83B08816B73EF78AF75AE88A72465E394860B2B84227895F648DBE022009633E98C5B6E66649A837414CA191C51128DBE71EA030CC0436F22996E37BFB012103B53D5F9D8CFA70A03667D95BD3B9D7550195792898A140CA2156D3EAAD907AF2" << std::endl;
		std::cout << std::endl;
		
		return;
	}	
	
	std::cout << std::endl;
	bool verbose(false);
	
	const std::string hexStr(args[1]);


	if(args.size() > 2)
	{
		const std::string argTwo(args[2]);
		
		if(argTwo == "verbose")
		{
			verbose = true;
		}
		else
		{
			std::cout << "Incorrect argument: " << argTwo << std::endl;
			throw std::string("Incorrect argument");
		}
	}	
	
	//Determine if filename or hex string
	
	
	const BinaryScript script = getScript(hexStr);
		
	//std::cout << "Script: " << hexString(script) << std::endl;
	
	const Script scr = Script::parse(script);
	
	std::cout << "Decoded: " << scr.toString() << std::endl;
	std::cout << std::endl;
	
	
	const std::string raw = scr.serialize().raw();
	if(raw != script.raw())
	{
		std::cout << std::endl;
		std::cout << "Serialize error" << std::endl;
		
		std::cout << "Orig     : " << script.hex() << std::endl;
		std::cout << "Serialzed: " << hexString(raw) << std::endl;
		
		throw std::string("Serialize error");
	}
	
	std::cout << "Script type: " << scr.scriptTypeString() << std::endl;
	
}




bool likelySignature(const std::string& sigStr)
{
	//std::cout << "Checking if signature: " << hexString(sigStr) << std::endl;	
	if(sigStr.size() < 2)
	{
		return false;
	}
	
	const unsigned char first = sigStr[0];
	const unsigned char last = sigStr[sigStr.size() - 1];
	
	if(first == 0x30 && last == 0x01)
	{
		return true;
	}
	
	return false;
}





void fixLowSTransaction(const std::vector<std::string>& args)
{	
	const std::string currency = getCurrencyShortName();
	if(currency != "btc" && currency != "btc" && currency != "doge" && currency != "vtc" && currency != "nmc"  && currency != "ftc")
	{
		std::cerr << "Fix low-s not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen fixlowstrans hextransaction" << std::endl;	
		return;
	}	
	
	std::cout << std::endl;
	
	const std::string hexStr(args[1]);
	
	
	//Determine if filename or hex string	
	//const std::string trans
	const BinaryTransaction trans = TransactionCommandline::getTrans(hexStr);
	//const std::string hash = trans.hash();
	
	//std::cout << "Orig trans: " << trans.asHex() << std::endl;
	
	const CryptoTransaction myTrans = CryptoTransaction::parse(trans);
	std::vector<TransactionInput> newInputs;

	//Go through all input scripts to find high-s value
	for(std::vector<TransactionInput>::const_iterator it = myTrans.inputs.begin() ;
		it != myTrans.inputs.end() ;
		++it)
	{
		const TransactionInput& ti = (*it);
		const Script parsedScript = Script::parse(ti.script);
		Script newScript;
		//Find Signature data
		for(std::list<ScriptItem>::const_iterator it = parsedScript.items.begin() ;
			it != parsedScript.items.end() ;
			++it)
		{
			const ScriptItem& si = (*it);
			if(si.object == ScriptItem::DATA)
			{
				if(likelySignature(si.data))
				{
					//std::cout << "This is a signature" << std::endl;
					
					const RSVal rs = ScriptDecoder::decodeSignatureRS(si.data);
					//std::cout << "R: " << rs.r << std::endl;
					//std::cout << "S: " << rs.s << std::endl;
					if(!rs.lowS())
					{
						std::cout << "Found signature with non-low S" << std::endl;
						const RSVal newRs = rs.getLowS();
						//std::cout << "Replaced S: " << newRs.s << std::endl;
						const std::string encodedRs = Script::encodeSignature(newRs);

						const ScriptItem newSi(ScriptItem::DATA, encodedRs);
						newScript.items.push_back(newSi);
						continue;
					}
					
				}
			}
			newScript.items.push_back(si);
		}
	
		const BinaryScript binScript(newScript.serialize());
		const TransactionInput newTi(ti.txHash, ti.index, binScript, ti.sequence);
		newInputs.push_back(newTi);

	}
	const BigInt<64> version(1);	//Todo
	const CryptoTransaction theNewTrans(version, newInputs, myTrans.outputs, myTrans.locktime);
	
	const BinaryTransaction newTrans = theNewTrans.serialize();
	
	if(newTrans == trans)
	{
		std::cout << "No non-low-s signature found" << std::endl;
		return;
	}
	
	std::cout << std::endl;
	std::cout << "Created transaction with low-s" << std::endl;
	
	std::cout << "New transaction: " << newTrans.asHex() << std::endl;
	
	Transaction::saveTranscation(newTrans);	
}








void TransactionCommandline::decodeTransaction(const std::vector<std::string>& args)
{	
	if(!transactionSupportedForCurrency())
	{
		const std::string currency = getCurrencyShortName();
		std::cout << "Decode transaction not supported for currency: " << currency << std::endl;
		throw std::string("Not supported");
	}
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen decodetrans hextransaction [verbose | savescript] " << std::endl;	
		std::cout << "Option savescript: Saves all scripts in the transaction " << std::endl;
		std::cout << "Option verbose: Prints extra information" << std::endl;

		std::cout << std::endl;
		std::cout << " Example: bitgen decodetrans 0100000001488D8209894206F1448DA9840CE0D3129B34CEC4EC7025110972E4FF92730002000000006A47304402200CBFB3D94A83B08816B73EF78AF75AE88A72465E394860B2B84227895F648DBE022009633E98C5B6E66649A837414CA191C51128DBE71EA030CC0436F22996E37BFB012103B53D5F9D8CFA70A03667D95BD3B9D7550195792898A140CA2156D3EAAD907AF2FFFFFFFF0140420F00000000001976A91488B052248006D938AF0600C8D2FB2FA0767C787988AC00000000" << std::endl;
		std::cout << std::endl;

		return;
	}	
	
	std::cout << std::endl;
	bool verbose(false);
	bool saveScript(false);
	
	const std::string hexStr(args[1]);
	
	std::string extraArg;
	if(args.size() > 2)
	{
		extraArg = args[2];
	}

	if(extraArg == "verbose")
	{
		verbose = true;
	}
	else if(extraArg == "savescript")
	{
		saveScript = true;
	}

	
	
	//Determine if filename or hex string	
	//const std::string trans
	const BinaryTransaction binaryTransaction = getTrans(hexStr);
	//BinaryTransaction binaryTransaction(trans);
	
	if(verbose)
	{
		//const std::string hash = doubleSha256(trans);		
		std::cout << "Hash of transaction: " << binaryTransaction.hashStr() /*
			hexString(Transaction::getReversedStr(hash))*/ << std::endl;
	}
	
	//std::cout << "Decoded: " << hexString(trans) << std::endl;
	
	const CryptoTransaction myTrans = CryptoTransaction::parse(binaryTransaction); //trans);


	if(verbose)
	{
		myTrans.printTransactionInfo(verbose);
	}
	else if(saveScript)
	{
		myTrans.saveScripts();
	}	
	else
	{
		std::cout << myTrans.stringSimple();
	}
	
	
	//if(saveTransaction)
	//{
	//	Transaction::saveTranscation(trans);		
	//}
}






void saveSignedScripts(const BinaryTransaction& transaction, const std::string& transHash)
{
	const CryptoTransaction trans = CryptoTransaction::parse(transaction);
	
	int i(0);
	for(std::vector<TransactionInput>::const_iterator it = trans.inputs.begin() ;
		it !=  trans.inputs.end() ;
		++it)
	{
		const TransactionInput input = (*it);
		const BinaryScript script = input.script;
		const std::string scriptFilename = "redeem_" + getCurrencyShortName() + "_" + transHash + "_" + intToString(i) + "_signed.script";
		Script::saveScriptWithFilename(script, scriptFilename);		
		i++;
	}
}



void saveUnsignedScripts(const TxData& txData, const std::string& transHash)
{
	
	int i(0);
	for(std::list<TxInput>::const_iterator it = txData.inputs.begin() ;
		it != txData.inputs.end() ;
		++it)
	{
		const TxInput& input = (*it);
		
		if(input.scriptIsSigned())
		{
			std::cout << "Script already signed: " << intToString(i) << std::endl;
			continue;
		}
		
		const BinaryScript script = input.input.script;
		
		const std::string scriptFilename = "redeem_" + getCurrencyShortName() + "_" + transHash + "_" + intToString(i) + "_unsigned.script";
		Script::saveScriptWithFilename(script, scriptFilename);
		i++;
	}
}



void parseExtra(const std::vector<std::string>& args, const int posExtra, Timestamp& locktime, bool& fixednounce, bool& saveScripts, bool& useSchnorr)
{
	for(int currPos = posExtra + 1 ; currPos < args.size() ; currPos++)
	{
		const std::string extraArgName = args[currPos];
		
		if(extraArgName == "locktime")
		{
			currPos++;
			if(currPos >=  args.size())
			{
				throw std::string("No locktime specified");
			}
			
			const std::string locktimeStr = args[currPos];
			locktime = Timestamp(atoi(locktimeStr.c_str()));
			std::cout << "Locktime: " << locktime.numVal() << std::endl;			
		}
		else if(extraArgName == "fixednounce")
		{
			fixednounce = true;
			
			std::cout << std::endl;
			std::cout << "WARNING: USING FIXED NOUNCE, USE **ONLY** FOR TEST" << std::endl;
			std::cout << std::endl;			
		}
		else if(extraArgName == "savescripts")
		{
			saveScripts = true;
			
			std::cout << "Saving transaction scripts" << std::endl;
		}		
		else if(extraArgName == "schnorr")
		{
			useSchnorr = true;
			
			std::cout << "Using Schnorr signature" << std::endl;
		}				
		else
		{
			std::cout << "Unknown extra argument: " << extraArgName << std::endl;
			throw std::string("Unknown extra argument");
		}
	}
}






bool TransactionCommandline::transactionSupportedForCurrency()
{
	const std::string currency = getCurrencyShortName();
	if(currency == "ltc" || currency == "btc" || currency == "bch" || currency == "doge" || 
		currency == "vtc" || currency == "nmc"  || currency == "ftc")
	{
		return true;
	}
	
	return false;
}

void printTransactionUsage()
{
	std::cout << "Usage: bitgen transaction txHash1 outIndex1 wif1 prevAmountSatoshi1 out nextAddr1 amountSatoshi1 [nextAddr2 amountSatoshi2]" << std::endl;
	std::cout << " Example: " << std::endl;
	
	if(getCurrencyShortName() == "btc")
	{
		std::cout << " bitgen transaction 02007392ffe47209112570ecc4ce349b12d3e00c84a98d44f106428909828d48 0 L17Csy8GPucwp3tnrRfi9G4hHMcbaTNmXKhqdQTDRTnFH3JmyeUn 1000500 out 1NznAXLVvhS5dcrA3bbntHrVmYz8LVy8Jm 1000000" << std::endl;
	}
	else if(getCurrencyShortName() == "vtc")
	{
		std::cout << " bitgen-vtc transaction 02007392ffe47209112570ecc4ce349b12d3e00c84a98d44f106428909828d48 0 Wa9nR8gyenxeZGbsA3pC757vQKMYZ5VahoGTxJHpHH3LjtZ73frx 1000500 out VuZYjNA4CsLNamg9dDnPzq5UN4ysG4FNG8 1000000" << std::endl;
	}
	else if(getCurrencyShortName() == "ltc")
	{
		std::cout << " bitgen-ltc transaction 02007392ffe47209112570ecc4ce349b12d3e00c84a98d44f106428909828d48 0 T9tXxitiY2adg7NTWiPR6e1F2p2J7wKhGjCzZa9ryvEaTV2vyM3q 1000500 out LXpESwa4K12gKf2NjY1iH6dkfeCYxDThDa 1000000" << std::endl;
	}	
	else if(getCurrencyShortName() == "doge")
	{
		std::cout << "bitgen-doge transaction 02007392ffe47209112570ecc4ce349b12d3e00c84a98d44f106428909828d48 0 QPMyCc8nmfDQ7hHT14JTyadpuFHq2jWiT1XhMwizPmWZaUoBkeFj 1000500 out DFCUCpLGEz1faATGoD35yMkSHLnd7werUR 1000000" << std::endl;
	}
	else if(getCurrencyShortName() == "bch")
	{
		std::cout << "bitgen-bch transaction 02007392ffe47209112570ecc4ce349b12d3e00c84a98d44f106428909828d48 0 KyPgYyfizUcCRfnGLzN45LVw7wExKJjDMbZsWhC2PCmp8bxnAaCS 1000500 out qzvljfg2ggnpe0yfe8wye3qdut8jvy3xl5szc26the 1000000	" << std::endl;
	}
	else if(getCurrencyShortName() == "ftc")
	{
		std::cout << "bitgen-ftc transaction 02007392ffe47209112570ecc4ce349b12d3e00c84a98d44f106428909828d48 0 N6YE8tVbDHd75SAx4fBcTj1nV9qXMUwPEX3jAVeHWdQTFMGezjje 1000500 out 6rCBubgV9fMN3eLmc1GJmyX8Sz3UKPujHg 1000000" << std::endl;
	}	
	else
	{
		std::cout << "Example command line missing" << std::endl;
	}
}




BinaryScript TransactionCommandline::createOpreturnScript(const std::string& dataStr, const std::string& typeStr)
{		
	if(typeStr == "OP_RETURN")
	{
		const BinaryScript script = ScriptCreator::createOpReturnScript(dataStr);
		return script;
	}
	else if(typeStr == "op_return")
	{
		const std::string decoded = convertFromHex(dataStr);
		std::cout << "op_return: " << hexString(decoded) << ": " << ScriptDecoder::printable(decoded) << std::endl;
		const BinaryScript script = ScriptCreator::createOpReturnScript(decoded);
		return script;
	}
	else if(typeStr == "DOCPROOF")
	{
		const std::string decodedHash = convertFromHex(dataStr);
		//std::cout << "DOCPROOF: " << hexString(decodedHash) << std::endl;
		const std::string toStore = "DOCPROOF" + decodedHash;
		const BinaryScript script = ScriptCreator::createOpReturnScript(toStore);
		return script;
	}
	else if(typeStr == "DOCPROOFFILE")
	{
		//Read file and calculate doublesha256
		const std::string file = readFile(dataStr);
		const std::string fileHash = doubleSha256(file);
		
		std::cout << "DOCPROOF: " << hexString(fileHash) << std::endl;
		const std::string toStore = "DOCPROOF" + fileHash;
		const BinaryScript script = ScriptCreator::createOpReturnScript(toStore);
		return script;
	}	
	else if(typeStr == "EW")
	{				
		const std::string toStore = convertFromHex("455720") + dataStr;	//"EW "
		const BinaryScript script = ScriptCreator::createOpReturnScript(toStore);
		return script;
	}
	else if(typeStr == "EWA")
	{
		const std::string toStore = convertFromHex("455741") + dataStr;				
		const BinaryScript script = ScriptCreator::createOpReturnScript(toStore);
		return script;
	}
	else
	{
		std::cerr << "Unknown type: " << typeStr << std::endl;
		
		throw std::string("Unknown type");
	}

	return BinaryScript(""); //Should not get here
}



std::list<TransactionOutput> createOutputParts(const std::vector<std::string>& args, const std::list<TxInput>& inputs, const int addPos)
{
	std::list<TransactionOutput> recipients;
	//std::cout << "Parsing outputs: " << addPos << std::endl;
	
	for(int i = 0 ; ; i++)
	{
		//std::cout << "Parsing output #" << i << std::endl;
		const int pos1 = addPos + 2 + inputs.size() * 4 + i * 2;
		const int pos2 = addPos + 3 + inputs.size() * 4 + i * 2;

		
		if(args.size() <= pos1)
		{
			//std::cout << "Nothing more to parse" << std::endl;
			break;
		}
		
		if(args.size() < pos2)
		{
			throw std::string("No amount for output");
		}
		
		const std::string nextAddrStr = args[pos1];
		//std::cout << "Next addr str: " << nextAddrStr << std::endl;
		
		
		//if(nextAddrStr == "fixnounce")
		//{
		//	std::cout << "Using fixed nounce" << std::endl;
		//	break;
		//}
		
		//std::cout << "NextAddr: " << nextAddrStr << std::endl;
		
		if(nextAddrStr == "extra")
		{
			std::cout << "Has extra arguments" << std::endl;
			break;
		}
				
		const std::string amountStr = args[pos2];
		
		//std::cout << "amountStr: " << amountStr << std::endl;
		

		if(nextAddrStr == "OP_RETURN" || nextAddrStr == "op_return" || nextAddrStr == "DOCPROOF" || nextAddrStr == "DOCPROOFFILE" 
			|| nextAddrStr == "EW" || nextAddrStr == "EWA")
		{
			//std::cout << "op_return" << std::endl;
			const Amount zeroAmountVal;

			const BinaryScript script = TransactionCommandline::createOpreturnScript(amountStr, nextAddrStr);
			const TransactionOutput scriptAndAmount(script, zeroAmountVal);
			recipients.push_back(scriptAndAmount);

			continue;
		}

		//std::cout << "AmountStr: " << amountStr << std::endl;
		const Amount amountVal(Amount::parseAmountString(amountStr));
		
		
		if(nextAddrStr == "anyone")
		{
			std::cout << "Anyone can spend output" << std::endl;
			const BinaryScript script = ScriptCreator::createAnyoneCanSpendScript();	
			//const BinaryScript binScript(script);		
			const TransactionOutput scriptAndAmount(script, amountVal);
			recipients.push_back(scriptAndAmount);			
			continue;
		}

		
		try
		{

			
			const PubAddress nextAddress(nextAddrStr);
			if(nextAddress.isMultisig())
			{
				//std::cout << "Multisig addr not supported: " << nextAddress.toString() << std::endl;
				//std::cout << "Use the multisig script instead" << std::endl;
				
				const BinaryScript script = ScriptCreator::createMultisigFundScript(nextAddress);
				TransactionOutput scriptAndAmount(script, amountVal);
				recipients.push_back(scriptAndAmount);				
			}
			else
			{					
				const BinaryScript script = ScriptCreator::scriptPubAddress(nextAddress);
				TransactionOutput scriptAndAmount(script, amountVal);
				recipients.push_back(scriptAndAmount);
			}
			
			continue;
		}
		catch(const std::string& err)
		{
		}
		
		try
		{
			//std::cout << "Not normal address, assuming multisig script" << std::endl;
			const std::string redeemScript = convertFromHex(nextAddrStr);			
			std::cout << "Multisig redeem script: " << hexString(redeemScript) << std::endl;
			const BinaryScript fundScript = ScriptCreator::createP2SHFundScript(redeemScript);
			std::cout << "Fund script: " << fundScript.hex() << std::endl;
			
			const TransactionOutput scriptAndAmount(fundScript, amountVal);
			recipients.push_back(scriptAndAmount);
			
			continue;
		}
		catch(const std::string& err)
		{
		}
		
		//Try pubkey
		try
		{
			const PubKey pubkey(PubKey::fromPkif(nextAddrStr));
			std::cout << "pubkey: " << pubkey.toString() << std::endl;
			const BinaryScript fundScript = ScriptCreator::createOldPubkeyFundscript(pubkey);
			const TransactionOutput scriptAndAmount(fundScript, amountVal);
			recipients.push_back(scriptAndAmount);
			
			continue;
			
		}
		catch(const std::string& err)
		{
		}

		//Try predefined script file
		//std::cout << "Will check if script" << std::endl;
		
		if(endsWith(nextAddrStr, ".script"))
		{
			std::cout << "This is a script" << std::endl;
			try
			{
				const BinaryScript fundScript = TransactionDecoder::getScriptFromFile(nextAddrStr);
				std::cout << "Got fund script: " << fundScript.hex() << std::endl;
				const TransactionOutput scriptAndAmount(fundScript, amountVal);
				recipients.push_back(scriptAndAmount);
			
				continue;
			}
			catch(const std::string& err)
			{
				std::cout << "Can not open script file: " << nextAddrStr << " : " << err << std::endl;
				throw std::string("Can not open script file");
			}				
		}			
				
		std::cout << "Output value error" << std::endl;
		throw std::string("Output value error");
	}
	
	return recipients;
}











std::list<TxInput> createInputParts(const std::vector<std::string>& args, const bool saveTransaction, const int addPos)
{	
	std::list<TxInput> inputs;
	//const int addPos = saveTransaction ? 0 : 1;
	
	//std::cout << "Will parse inputs" << std::endl;
	for(int i = 0 ; ; i++)
	{
		if(args.size() < (addPos + 4 + i * 4))
		{
			throw std::string("Input argument error");			
		}
		
		const std::string outStr = args[addPos + 1 + i * 4];
		if(outStr == "out")
		{
			break;
		}		
		
		
		const std::string txHashStr = args[addPos + 1 + i * 4];
		const std::string outputIndexStr = args[addPos + 2 + i * 4];
		const std::string wifStrOrig = args[addPos + 3 + i * 4];	
		const std::string prevAmountStr = args[addPos + 4 + i * 4];
		
		std::string wifStr;
		bool usePayToPubkey(false);
		if(wifStrOrig[0] == '_')
		{
			wifStr = wifStrOrig.substr(1);	//Remove the undescore
			usePayToPubkey = true;
		}
		else
		{
			wifStr = wifStrOrig;
		}
		
		//const std::string outStr = args[addPos + 5 + i * 4];

		if(txHashStr.size() != 64)
		{
			std::cout << std::endl;
			std::cout << "Warning, transaction hash not 64 characters: " << txHashStr << std::endl;
			std::cout << "Got " << txHashStr.size() << " characters" << std::endl;			
			
			std::cout << std::endl;		
			throw std::string("Transaction hash must be 64 characters");	
		}
		
		TxHash txHash(TxHash::fromHexReverse(txHashStr));
		//std::cout << "THE TXHASH: " << txHash.toPrintoutString() << std::endl;
		
		const int outputIndexNum = atoi(outputIndexStr.c_str());		
		const BigInt<128> prevAmountBigInt(Amount::parseAmountString(prevAmountStr));
		
		if(wifStr == "anyone")
		{
			std::cout << "Get from anyone-can-spend" << std::endl;

			const BinaryScript script = ScriptCreator::createAnyoneCanSpendFundscript();
			//const BinaryScript binScript(script);
			const BigInt<64> sequence(0);
			const TransactionInput input(txHash, outputIndexNum, script, sequence);
			
			const TxInput txInput(input, prevAmountBigInt, InputExtraInfo::PAYTO_ANYONECANSPEND);
			
			inputs.push_back(txInput);				
			
			std::cout << "Ready with anyone-can-spend" << std::endl;
			continue;
		}
		
		try
		{
			const Wif wif(wifStr);			
			const PrivKey privkey = wif.getPriv();

			const BitcoinEllipticCurve ec;
			const PubKey pubkey = privkey.getPubkey(ec);
			
			if(usePayToPubkey)
			{
				//std::cout << "Using pay-to-pubkey for input" << std::endl;
				const BinaryScript script = ScriptCreator::createOldPubkeyFundscript(pubkey);
				//const BinaryScript binScript(script);
				//const std::string script = Transaction::createPayToPubkeyRedeemUnsigned(privkey);
				const BigInt<64> sequence(0);
				const TransactionInput input(txHash, outputIndexNum, script, sequence);
				
				const TxInput txInput(input, privkey, prevAmountBigInt, InputExtraInfo::PAYTO_PUBKEY);
				inputs.push_back(txInput);				
			}
			else
			{
				//Normal pay-to-pubkey-hash address
				
				const std::string pubAddRaw = pubkey.getRaw();
				const std::string theSha = sha256(pubAddRaw);
				const std::string scriptHashStr = ripemd160(theSha);
				
				const BinaryScript script = ScriptCreator::scriptPubkeyWithHash(scriptHashStr);
				//const BinaryScript binScript(script);
				//const Script unsignedScript = Script::parse(script);
				//std::cout << "The script: " << unsignedScript.toString() << std::endl;
				const BigInt<64> sequence(0);
				const TransactionInput input(txHash, outputIndexNum, script, sequence);
				
				const TxInput txInput(input, privkey, prevAmountBigInt, InputExtraInfo::PAYTO_PUBKEYHASH);
		
				inputs.push_back(txInput);
			}
		}
		catch(const std::string& err)
		{
			const BinaryScript script = endsWith(wifStr, ".script") ? TransactionDecoder::getScriptFromFile(wifStr) : BinaryScript(convertFromHex(wifStr));
			
			
			std::cout << "Got script: " << script.hex() << std::endl;
			const BigInt<64> sequence(0);
			const TransactionInput input(txHash, outputIndexNum, script, sequence);
			
			const TxInput txInput(input, prevAmountBigInt, InputExtraInfo::PAYTO_SCRIPTHASH);
		
			inputs.push_back(txInput);
			
		}		
	}
	
	if(inputs.empty())
	{
		throw std::string("No outputs specified");
	}
	
	return inputs;
}













TxData parseTransactionArguments(const std::vector<std::string>& args, bool& saveTransaction, bool& fixednounce, bool& saveScripts, bool& useSchnorr, bool& debug)
{	
	if(args.size() < 7)
	{
		printTransactionUsage();
		throw std::string("Incorrect usage");
	}	
	
	
	if(args[1] == "nosave")
	{
		saveTransaction = false;
	}
		
	
	const int addPos = saveTransaction ? 0 : 1;

	//std::cout << "Will parse inputs" << std::endl;
	const std::list<TxInput> inputs = createInputParts(args, saveTransaction, addPos);

	//std::cout << "Will parse outputs" << std::endl;			
	const std::list<TransactionOutput> recipients = createOutputParts(args, inputs, addPos);
	
	//std::cout << "Parse outputs ready" << std::endl;			
	
	
	const int posExtra = addPos + 2 + inputs.size() * 4 + recipients.size() * 2;
	
	//std::cout << "posExtra: " << posExtra << std::endl;
	//std::cout << "args.size(): " << args.size() << std::endl;
	
	Timestamp locktime(0);
	
	parseExtra(args, posExtra, locktime, fixednounce, saveScripts, useSchnorr);
	
	const TxData txData(inputs, recipients, locktime, debug);
	return txData;
}




BinaryTransaction TransactionCommandline::getTrans(const std::string& arg)
{
	//Determine if filename or hex string	
	try
	{
		const std::string trans = convertFromHex(arg);
		return BinaryTransaction(trans);
	}
	catch(const std::string& err)
	{
		//Not a hex string, file name?
		const std::string filename = arg;
		if(!endsWith(filename, ".trans"))
		{
			throw std::string("Transaction file must end with .trans");
		}
		
		const BinaryTransaction trans = TransactionDecoder::getTransactionFromFile(filename);
		return trans;
	}
	
	//Should not get here
	return BinaryTransaction("");
}



bool runGivenTransaction(const BinaryTransaction& transaction, /*const std::string& transaction,*/ const bool verbose)
{	
	//std::cout << "RUNGIVENTRANSACTION: " << (verbose ? "VERBOSE" : "silent") << std::endl;
	//std::cout << "Transaction: " << hexString(transaction.raw()) << std::endl;


	std::list<SigPos> inputScriptPositions;
	const BinaryTransaction binaryTransaction(transaction);		
	
	const CryptoTransaction trans = CryptoTransaction::parseBinaryTransaction(binaryTransaction, inputScriptPositions);

	const TransAndInScriptPos transWithPos(transaction, inputScriptPositions);

	Amount totalIn;


	const bool transactionSuccess = (getCurrencyShortName() == "bch") ? 
										trans.runBch(totalIn, verbose) :
										trans.run(transWithPos, totalIn, verbose);

	
	if(transactionSuccess)
	{
		std::cout << "Transaction OK, all inputs OK" << std::endl;

		std::cout << std::endl;
		std::cout << "Total in amount : " << totalIn.amountString() << std::endl;
	
		const Amount totalOut = trans.getTotalOutAmount();
		std::cout << "Total out amount: " << totalOut.amountString() << std::endl;

		const Amount minerFee(totalIn - totalOut);

		std::cout << "Miner fee       : " << minerFee.amountString() << std::endl;
		
	}
	else
	{
		std::cout << "Transaction FAILED" << std::endl;
	}


	return transactionSuccess;	
}









void TransactionCommandline::runTrans(const std::vector<std::string>& args)
{	
	if(!transactionSupportedForCurrency())
	{
		std::cerr << "Run transaction not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen runstrans transaction [verbose]" << std::endl;	
		return;
	}	
	
	bool verbose(false);
	
	std::cout << std::endl;
	
	const std::string argTransaction(args[1]);

	//const std::string transaction
	const BinaryTransaction transaction = getTrans(argTransaction);
	
	if(args.size() > 2)
	{
		const std::string argVerb(args[2]);	
		if(argVerb == "verbose")
		{
			verbose = true;
		}
		else
		{
			std::cout << "Argument error: " << argVerb << std::endl;
			throw std::string("Argument error");
		}
	}	
	
	runGivenTransaction(transaction, verbose);	
}






void TransactionCommandline::saveTheTransaction(const std::vector<std::string>& args)
{	
	const std::string currency = getCurrencyShortName();
	if(currency != "bch" && currency != "btc" && currency != "btc" && currency != "doge" && currency != "vtc" && currency != "nmc"  && currency != "ftc")
	{
		std::cerr << "Save transactions not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen savetrans hextransaction [verbose]" << std::endl;
		std::cout << "verbose: Prints information about the transaction" << std::endl;

		std::cout << std::endl;
		std::cout << "Example: " << std::endl;		
		std::cout << "bitgen-btc savetrans 0100000001488D8209894206F1448DA9840CE0D3129B34CEC4EC7025110972E4FF92730002000000006A47304402200CBFB3D94A83B08816B73EF78AF75AE88A72465E394860B2B84227895F648DBE022009633E98C5B6E66649A837414CA191C51128DBE71EA030CC0436F22996E37BFB012103B53D5F9D8CFA70A03667D95BD3B9D7550195792898A140CA2156D3EAAD907AF2FFFFFFFF0140420F00000000001976A91488B052248006D938AF0600C8D2FB2FA0767C787988AC00000000" << std::endl;
		std::cout << std::endl;
		
		return;
	}	

	bool printInfo(false);
	const std::string content(args[1]);

	if(args.size() > 2)
	{
		const std::string argVerb(args[2]);	
		if(argVerb == "verbose")
		{
			printInfo = true;
		}
		else
		{
			std::cout << "Argument error: " << argVerb << std::endl;
			throw std::string("Argument error");
		}
	}	


	//const std::string trans
	const BinaryTransaction trans = getTrans(content);

	if(printInfo)
	{
		std::cout << "Will parse, len: " << trans.size() << std::endl;
	}

	
	const CryptoTransaction cryptoTrans = CryptoTransaction::parse(trans, printInfo);
	
	//OK, no parse errors
	Transaction::saveTranscation(trans);

	//Serialize to make sure the result is the same
	//const std::string
	const BinaryTransaction newTrans = cryptoTrans.serialize();
	//const BinaryTransaction binaryTransaction = cryptoTrans.serialize();
	
	if(trans != newTrans)
	{
		std::cout << std::endl;
		std::cout << "Original transaction binary  : " << trans.asHex() /*hexString(trans.raw())*/ << std::endl;
		std::cout << "Serialized transaction binary: " << newTrans.asHex() /*hexString(newTrans.raw())*/ << std::endl;
		
		std::cout << "Parsed info: " << std::endl;
		cryptoTrans.printTransactionInfo(true);
		std::cout << std::endl;
		
		throw std::string("Error serialized version does not equal original transaction");
	}
	
}




void TransactionCommandline::parseTransaction(const std::vector<std::string>& args)
{	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen parsetrans transaction" << std::endl;	
		return;
	}	
	
	const std::string hexStr = args[1];	
	
	//const std::string trans
	const BinaryTransaction trans = getTrans(hexStr);	
	//std::cout << "Decoded: " << hexString(trans) << std::endl;

	const BinaryTransaction binaryTransaction(trans);	
	const CryptoTransaction ct = CryptoTransaction::parse(binaryTransaction /*trans*/, true);
	
	std::cout << "Parse ready" << std::endl;
}





void TransactionCommandline::createTransaction(const std::vector<std::string>& args)
{	
	if(!transactionSupportedForCurrency())
	{
		std::cerr << "Create transaction not supported for " << getCurrencyName() << std::endl;
		throw std::string("Currency not supported");
	}
		
	bool saveTransaction(true);
	bool fixednounce(false);
	bool saveScripts(false);	//Saves the scripts as separate files
	bool useSchnorr(false);
	bool debug(false);
	
	const TxData txData = parseTransactionArguments(args, saveTransaction, fixednounce, saveScripts, useSchnorr, debug);

	if(useSchnorr && getCurrencyShortName() != "bch")
	{
		std::cout << "Schnorr signature only allowed for bitcoin cash" << std::endl;
		throw std::string("Schnorr not allowed");
	}

	txData.printTransactionInformation();

	const int numTempkeysNeeded = txData.getNumTempkeysNeeded();
	const std::list<BigInt<256> > tempKeys = getTempKeys(numTempkeysNeeded, fixednounce);

	const BinaryTransaction binaryTransaction = txData.createSignedTransaction(tempKeys, useSchnorr);
	
	
	const BigInt<128> transactionSize(binaryTransaction.size());	
	const BigInt<128> minerFee(txData.getMinerFee().amount);
	//std::cout << "T size: " << transactionSize.strDec() << std::endl;
	//std::cout << "T fee : " << minerFee.strDec() << std::endl;
	
	
	const Amount feePerByte = minerFee / transactionSize;
	
	//std::cout << "Tempkeys size: " << tempKeys.size() << std::endl;
	//std::cout << "Inputs size: " << txData.inputs.size() << std::endl;
	
	const bool signedAll = (tempKeys.size() == txData.numInputs());
	
	if(!signedAll)
	{
		std::cout << "Unsigned ";
	}
	
	std::cout << "Transaction: " << binaryTransaction.asHex() << std::endl;
		
	if(!signedAll)
	{
		std::cout << "Note: Multisig inputs were not signed" << std::endl;
	}
	
	std::cout << std::endl;	
	
	std::cout << "Transaction size   : " << binaryTransaction.size() << std::endl;
		std::cout << "Fee per byte       : ";
	if(minerFee.isNegative())
	{
		std::cout << "negative " << std::endl;
	}
	else
	{
		std::cout  << feePerByte.amount.strDec() << " satoshi/byte" << std::endl;	
	}
	
	std::cout << "Hash of transaction: " << binaryTransaction.hashStr()  << std::endl;
	
	if(saveTransaction)
	{
		Transaction::saveTranscation(binaryTransaction, signedAll);
	}
	
	if(saveScripts)
	{
		std::cout << "Saving transaction scripts" << std::endl;
		
		saveUnsignedScripts(txData, binaryTransaction.hashStr());
		saveSignedScripts(binaryTransaction, binaryTransaction.hashStr());
	}
}
		


