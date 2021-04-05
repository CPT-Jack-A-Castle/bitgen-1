

#include "SignatureImpl.h"
#include "signature.h"
#include "bigint.h"
#include "pubAddress.h"
#include "addressConversion.h"
#include "sigFile.h"

#include "bitsigConfig.h"		//Todo: Remove dependency



void SignatureImplementationExtra::verifyPubaddrSpecifiedByUser(const std::string & pubadd, const PubAddress& bitaddress, std::string& alias)
{	
	if(!pubadd.empty()) 	//Address given on command line
	{			
		const PubAddress givenPub(pubadd);
		std::cout << "Using public address : " << givenPub << std::endl;
		//givenPub.validate();

		if(givenPub != bitaddress)
		{
			std::cout << "Error, the address does not match" << std::endl;
			
			throw std::string("Address does not match");
		}
	}
	else
	{
		std::cout << "No public address given, looking in keychain" << std::endl;
				
		if(!BitsigConfig::findStoredPubAddr(bitaddress, alias))
		{
			std::cout << std::endl;
			std::cout << "Can not find any pub addr match" << std::endl;
			
			throw std::string("Public addr not found in keychain");
		}
		
		std::cout << "Found the address in the keychain" << std::endl;		
	}
}



std::string SignatureImplementationExtra::verifySignatureForFile(const std::string& signedFile,const std::string& pubadd, std::string& alias, 
	std::string& verifiedAddress, const bool rawContent)
{
	std::string signFile;	
	const SigFileContent sigParam = parseSignedWithIncludedFile(signedFile, signFile, rawContent);
	
	//std::cout << "Content: \"" << signFile << "\"" << std::endl;
	
	//Calculate the hash of the file		
	
	const int fileSize = signFile.size();
	//std::cout << "File size: " << fileSize << std::endl;
	const std::string hashStart = SignatureImplementation::hashStringStart(fileSize);	
	const std::string totalFile = hashStart + signFile;
	
	const std::string firstHash = sha256(totalFile);		//Todo: use doubleSha256()		
	const std::string theHash = sha256(firstHash); 		
	const BigInt<256> hashNum(theHash, 'c');

	//std::cout << "Hash: " << hashNum << std::endl;

	const ECPoint pubkey = SignatureImplementation::recoverThePublicKey(sigParam.firstX, sigParam.oddY, sigParam.rs, hashNum);

	const PubKey p(pubkey, sigParam.compressed);
	const PubAddress bitaddress = p.getAddress();
	//Does this pubkey give the bitcoin address?			
	//const PubAddress bitaddress = PubAddress::bitcoinAddresFromPubkey(pubkey, sigParam.compressed);			
	verifiedAddress = bitaddress.toString(); //.address;
	
	//std::cout << "Calculated address   : " << bitaddress << std::endl;
	SignatureImplementationExtra::verifyPubaddrSpecifiedByUser(pubadd, bitaddress, alias);
	
					
	std::cout << "Verifying signature...." << std::endl;
		
	//Require lowS value
	if(SignatureImplementation::checkSigLowS(hashNum, pubkey, sigParam.rs, true))
	{		
		//std::cout << "Verify OK for address: " << bitaddress << std::endl;
		if(!alias.empty())
		{
			//std::cout << "Address alias: " << alias << std::endl;
		}
		
		return signFile;
		
		//Save embedded file 
		//const std::string saveFilename = std::string("out_") + removeEnding(signedFile, ".bitfsig");
		
		//std::cout << "Saving to: " << saveFilename << std::endl;
		//fileWrite(saveFilename, signFile);
	}


	throw std::string("Signture fail");
	return "error";
}



