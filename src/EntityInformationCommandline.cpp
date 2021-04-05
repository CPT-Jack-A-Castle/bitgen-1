

#include "EntityInformationCommandline.h"



#include "wif.h"
#include "privKey.h"
#include "commandLine.h"
#include "predicates.h"
#include "util.h"
#include "readStream.h"
#include "RSVal.h"
#include "scriptdecoder.h"
#include "cashAddress.h"


void signatureInfo(const std::vector<std::string>& args)
{	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen signatureinfo hexsignature" << std::endl;
		std::cout << "Prints the R and S values for a signature" << std::endl;
		std::cout << "The signature should be given in blockchain hex format, starting with 30..." << std::endl;
		return;
	}	

	//Todo: Accept .sig file as argument

	const std::string hexStr(args[1]);
	const std::string signature = convertFromHex(hexStr);
	//std::cout << "Sig: " << hexString(signature) << std::endl;

	ReadStream sigStream(signature);
	
	const RSVal rs = ScriptDecoder::decodeSignatureRS(sigStream);
		
	std::cout << "R: " << rs.r << std::endl;
	std::cout << "S: " << rs.s << std::endl;


	if(!rs.lowS())
	{
		std::cout << "The signature does not use low-s value" << std::endl;		
		const RSVal rsLowS = rs.getLowS();
		std::cout << "Corresponding LowS:" << std::endl;				
		std::cout << "R: " << rsLowS.r << std::endl;
		std::cout << "S: " << rsLowS.s << std::endl;
		
	}
		
}




//Todo: Remove this function, the command "info" should be used instead
void EntityInformationCommandline::verifyWif(int argc, char* argv[], const std::string& thetime)
{
	if(argc < 3)
	{
		std::cout << "Usage: bitgen verifyWIF wif" << std::endl;
		return;			
	}
	
	//const
	std::string wif(argv[2]);
	if(wif == "-")
	{
		std::cout << "Enter the wif value at one row" << std::endl;
		std::cout << "Press enter when all chars are entered" << std::endl;
		
		wif = readStdinLine(10, false, isBase58Char);
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;			
		std::cout << std::endl;		
	}


	const Wif myWif(wif);
		
		
	//const BigInt<256> priv = myWif.toPrivKey();
	const PrivKey pk = myWif.getPriv();
	
	std::cout << "Priv: " << pk.key /*priv*/ << std::endl;
		
	std::cout << "Wif OK" << std::endl;
}




void giveInfoAboutWif(const std::string& wif)
{
	const Wif myWif(wif);
	
	const PrivKey myPrivKey = myWif.getPriv();

	std::cout << "Format is     : " << (myPrivKey.compressed ? "compressed" : "non-compressed") << std::endl;
	std::cout << "WIF           : " << myWif << std::endl;
	
	std::cout << "Private key   : " << hexString(myPrivKey.key.getBinaryLong()) << std::endl;

	BitcoinEllipticCurve ec;

	const PubKey pubKey = myPrivKey.getPubkey(ec);
	const ECPoint publicPoint = pubKey.point;
	std::cout << "Public point  :(" << publicPoint.x << std::endl;
	std::cout << "              : " << publicPoint.y << ")" << std::endl;
	std::cout << "Public key    : " << hexString(publicPoint.getRaw(myPrivKey.compressed)) << std::endl;
	std::cout << "PKIF          : " << pubKey.toString() << std::endl;

	
	PubAddress address = pubKey.getAddress();
	std::cout << "Public address: " << address << std::endl;

	if(usesCashAddress())
	{
		std::cout << "Cash address  : " << address.toCashAddrString() << std::endl;
	}


	std::cout << std::endl;
	std::cout << "Validate OK" << std::endl;
}







void giveInfoAboutPubKey(const PubKey& pubkey)
{
	std::cout << "Pkif          : " << pubkey.toString() << std::endl;	
	std::cout << "Format is     : " << (pubkey.compressed ? "compressed" : "non-compressed") << std::endl;

	std::cout << "Use           : ";
	if(!pubkey.onlyIndicatedUsage)
	{
		std::cout << "Any" << std::endl;
	}
	else
	{
		std::cout << (pubkey.signVerify ? "Signature verification" : "Encrypt") << std::endl;		
	}
	
	
	
	std::cout << "Public point  :(" << pubkey.point.x << std::endl;
	std::cout << "              : " << pubkey.point.y << ")" << std::endl;
	std::cout << "Public key    : " << hexString(pubkey.point.getRaw(pubkey.compressed)) << std::endl;
	std::cout << "Public address: " << pubkey.getAddress() << std::endl;
}


void giveInfoAboutPkif(const std::string& pkifStr)
{
	const PubKey pubkey = PubKey::fromPkif(pkifStr);
	 giveInfoAboutPubKey(pubkey);
}


void giveInfoAboutPublicKey(const std::string& entity)
{
	const PubKey pubkey = PubKey::fromHex(entity);
	giveInfoAboutPubKey(pubkey);
}



void giveInfoAboutAddress(const std::string& entity)
{
	std::cout << "Entity type: Address" << std::endl;
	
	const PubAddress address(entity);	
	
	std::cout << "Address    : " << address.toString() << std::endl;	
	if(getCurrencyShortName() == "bch")
	{
		std::cout << "Cash addr  : " << address.toCashAddrString() << std::endl;
		std::cout << "Cash read  : " << address.toCashAddrReadableString() << std::endl;
	}
	
	std::cout << "Is multisig: " << (address.isMultisig() ? "Yes (P2SH)" : "No (P2KH)") << std::endl;
	
		
	
	//std::cout << "Validate OK" << std::endl;
	
	if(!PubAddress::isCashAddr(entity))
	{
		const BigInt<200> decoded(address.getNumeric());
		std::cout << "Digits     : 1         2         3         4         5         6" << std::endl;

		std::cout << "Numeric    : " << hexStrFull(decoded.getBinaryLong()) << std::endl;
	
		const BigInt<168> fourBytesDropped(decoded >> 32);
		std::cout << "NoChecksum : " << hexStrFull(fourBytesDropped.getBinaryLong()) << std::endl;

		const BigInt<168> hashVal(fourBytesDropped & 160);
		const BigInt<160> hashVal160(hashVal);
		
		std::cout << "Hash160    :   " << hexStrFull(hashVal160.getBinaryLong()) << std::endl;


		const BigInt<168> netVersion = fourBytesDropped >> 160;		//160 bit hash
		std::cout << "NetVersion : " << netVersion << std::endl;
	}
	else
	{
		std::cout << "Hash160    : " << hexStrFull(address.getHash160()) << std::endl;
		
		bool isMultisig(false);
		std::string versionAndHash;
		std::string checksumRaw;
		const std::string zz = CashAddress::fullDecodeCashAddr(entity, isMultisig, 
																versionAndHash, checksumRaw);

		std::cout << "VersionHash: " << hexStrFull(versionAndHash) << std::endl;	
		std::cout << "Checksum   : " << hexStrFull(checksumRaw) << std::endl;		
		
		const std::string fullRaw = versionAndHash + checksumRaw;
		std::cout << "Raw data   : " << hexStrFull(fullRaw) << std::endl;		
		
	}
}


void giveInfoAboutCashAddress(const std::string& entity)
{
	const PubAddress address(entity);	
	
	std::cout << "Cash addr  : " << address.toCashAddrString() << std::endl;	
	const std::string legacyAddr = address.toString();	
	std::cout << "Legacy addr: " << legacyAddr << std::endl;
	
	std::cout << " -------------------------------- " << std::endl;
	std::cout << "Digits     : 1         2         3         4         5         6" << std::endl;

	std::cout << "Hash       : " << hexStrFull(address.getHash160()) << std::endl;	
}
























void EntityInformationCommandline::informationAboutEntity(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen info wif/pkif/address" << std::endl;
		return;
	}
		
	std::string entity(args[1]);
	
	bool unsafeInput(false);
	if(entity == "-")
	{
		std::cout << "Enter the entity value at one row" << std::endl;
		std::cout << "Press enter when all chars are entered" << std::endl;
		
		entity = readStdinLine(10, false, isBase58Char);
	}
	else
	{
		unsafeInput = true;
	}
		
	

	//Check which kind of entity
	if(BitgenPredicate::isWif(entity))
	{
		//It is a wif
		if(unsafeInput)
		{
			std::cout << "WARNING: The information entered at the command line" << std::endl;
			std::cout << "WARNING: might be stored in a shell history file." << std::endl;
			std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;	
			std::cout << std::endl;		
		}
		
		std::cout << "Entity type: WIF" << std::endl;
		giveInfoAboutWif(entity);
	}
	else if(BitgenPredicate::isPkif(entity))
	{		
		std::cout << "Entity type   : PKIF" << std::endl;
		giveInfoAboutPkif(entity);
	}
	else if(BitgenPredicate::isPublicKey(entity))
	{		
		std::cout << "Entity type   : Public key" << std::endl;
		giveInfoAboutPublicKey(entity);
	}	
	else if(BitgenPredicate::isAddress(entity))
	{		
		giveInfoAboutAddress(entity);
	}
	else if(PubAddress::isCashAddr(entity))		//Todo: Remove
	{		
		std::cout << "Entity type   : Cash Address" << std::endl;
		giveInfoAboutCashAddress(entity);
	}	
	else
	{
		//std::cout << "Unknown entity: " << entity << std::endl;
		std::string errMsg("Unknown entity: ");
		errMsg += entity;
		throw errMsg;
	}



	
}



void validatePrivateWif(int argc, char* argv[], const std::string& thetime)
{
	if(argc < 3)
	{
		std::cout << "Usage: bitgen infoPrivate wif" << std::endl;
		return;
	}
		
	//const
	std::string wif(argv[2]);
	if(wif == "-")
	{
		std::cout << "Enter the wif value at one row" << std::endl;
		std::cout << "Press enter when all chars are entered" << std::endl;
		
		wif = readStdinLine(10, false, isBase58Char);
	}
	else
	{
		std::cout << "WARNING: The information entered at the command line" << std::endl;
		std::cout << "WARNING: might be stored in a shell history file." << std::endl;
		std::cout << "WARNING: Consider using the \"-\" option for entering information." << std::endl;	
		std::cout << std::endl;		
	}
		
	

		
	const Wif myWif(wif);
		

	const PrivKey thePrivKey = myWif.getPriv();	
	const BigInt<257> privKeyLong(thePrivKey.key);

	BitcoinEllipticCurve ec;

	const PubKey pubKey = thePrivKey.getPubkey(ec);
	const Pkif pkif = pubKey.getPkif();

	std::cout << "Format is     : " << (thePrivKey.compressed ? "compressed" : "non-compressed") << std::endl;
	std::cout << "WIF           : " << myWif << std::endl;
	
	std::cout << "Private key   : " << hexString(privKeyLong.getBinaryLong())  << std::endl;

	const ECPoint publicKey = pubKey.point;
	std::cout << "Public point  :(" << publicKey.x << std::endl;
	std::cout << "              : " << publicKey.y << ")" << std::endl;
	std::cout << "Public key    : " << pubKey.toStringHex() << std::endl;
	std::cout << "PKIF          : " << pkif.toString() << std::endl;

	const PubAddress address = pubKey.getAddress();
	std::cout << "Public address: " << address << std::endl;


	std::cout << std::endl;
	std::cout << "Validate OK" << std::endl;
}




void verifyAddress(int argc, char* argv[], const std::string& thetime)
{
	if(argc < 3)
	{
		std::cout << "Usage: bitgen infoAddress bitcoinAddress" << std::endl;
		return;			
	}
	
	const std::string adr(argv[2]);
	const PubAddress myPub(adr);
	//myPub.validate();
	std::cout << "Validate OK" << std::endl;
}






