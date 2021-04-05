

#include "StaticXor.h"

#include "bitgenConfig.h"
#include "util.h"
#include "bitgenVersion.h"
#include "txtGeneration.h"
#include "printPS.h"
#include "FileUtil.h"
#include "hash.h"

#include <iostream>


std::string staticXorHash(const BigInt<256>& staticXor)
{
	const std::string hash = doubleSha256(staticXor.getBinaryLong());
	const std::string hashPart = hash.substr(0, 4);
	
	return hashPart;
}

void readStaticXor(const std::vector<std::string>& args, const std::string& thetime)
{
	std::cout << "Reading static xor" << std::endl;

	const BigInt<256> priv = getStaticXor();
		
	std::cout << std::endl;

	const BigInt<256> zero;
	
	if(priv == zero)
	{
		std::cout << "No static xor defined" << std::endl;
		return;
	}
	
	std::cout << "Static xor: " << hexString(priv.getBinaryLong()) << std::endl;
}



void removeStaticXor(const std::vector<std::string>& args, const std::string& thetime)
{
	const BigInt<256> priv = getStaticXor();
	
	const BigInt<256> zero;
	if(priv == zero)
	{
		std::cout << "No static xor configured" << std::endl;
		
		throw std::string("No static xor configured");
		//return;
	}
	
	const std::string hash = staticXorHash(priv);
	if(args.size() < 2)
	{
		std::cout << "Use the following hash to remove the static xor: " << hexString(hash) << std::endl;
		return;
	}
	
	
	deleteStaticXor();
	
	std::cout << "Static xor removed" << std::endl;
	
}






void saveStaticXorFiles(const BigInt<256> privkey, const std::string& thetime)
{
	std::cout << "Saving static xor txt and ps files" << std::endl;
	
	const std::string txtContent = generateStaticXorFile(thetime, 
		versionNumber, applicationName, 
		"",	//Todo: accountName
		//"mnemonic",
		privkey);
		
	
	PostscriptGenerator postscriptGenerator(versionNumber, applicationName);
	
	const std::string psContent = postscriptGenerator.generateStaticXor(thetime, privkey);
	
	const std::string hash = staticXorHash(privkey);

	const std::string txtFilename("staticxor_" + hexString(hash) + ".txt");
	const std::string psFilename("staticxor_" + hexString(hash) + ".ps");
	
	//std::cout << "Will write PS" << std::endl;
	fileWrite(psFilename, psContent);		
	std::cout << "Wrote file: " << psFilename << std::endl;

	//std::cout << "Will write TXT" << std::endl;
	fileWrite(txtFilename, txtContent);		
	
	std::cout << "Wrote file: " << txtFilename << std::endl;
	
}






void addStaticXor(const std::vector<std::string>& args, const std::string& thetime)
{

	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen addxor XOR256 [CODE]" << std::endl;
		throw std::string("Not enough arguments");
	}

	const BigInt<256> previousStatic = getStaticXor();
	const BigInt<256> zero;
	if(previousStatic != zero)
	{
		std::cout << "A STATIC XOR ALREADY EXIST" << std::endl;
		std::cout << "If the static xor should be replaced, the old value must be removed first" << std::endl;
		std::cout << "Use the \"removexor\" command to remove the old value" << std::endl;
		
		//Replacing exising static xor with value: " <<  hexString(previousStatic.getBinaryLong()) << std::endl;
		std::cout << std::endl;
		throw std::string("Static xor already exist");
	}
	

	const std::string hexStr = args[1];
	
	const BigInt<256> privkey = parseHex256Bit(hexStr);
	const std::string hash = staticXorHash(privkey);

	if(args.size() == 2)
	{
		std::cout << "Use the following hash to verify that you want to use this xor seed" << std::endl;
		std::cout << "Hash: " << hexString(hash) << std::endl;;
		return;
	}
	
	if(args.size() < 3)
	{
		std::cout << "Usage: bitgen addxor XOR256 CODE" << std::endl;
		throw std::string("Not enough arguments");
	}

	const std::string hashStr = args[2];
	const std::string givenHash = convertFromHex(hashStr);

	if(givenHash != hash)
	{
		std::cout << "Incorrect hash given, should be: " << hexString(hash) << std::endl;
		throw std::string("Incorrect hash");
	}
	

	std::cout << "Adding static xor mask" << std::endl;
	std::cout << std::endl;	
	std::cout << "Note: The xor mask MUST BE SECURELY STORED" << std::endl;
	std::cout << "Without the xor mask otp-generated private keys will not be possible to recover!" << std::endl;
	std::cout << std::endl;

	
	saveStaticXorFiles(privkey, thetime);
	saveStaticXor(privkey);
}




