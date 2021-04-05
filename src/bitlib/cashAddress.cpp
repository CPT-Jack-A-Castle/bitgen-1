
#include "pubAddress.h"
#include "currencySpecific.h"
#include "util.h"
#include "fiveBitItems.h"


#include "cashAddress.h"




FiveBitItems CashAddress::computeCashAddrChecksum(const FiveBitItems& input)
{		
    const BigInt<64> one(1);	
    const BigInt<64> a_const(BigInt<64>::fromHex("07ffffffff"));
	const BigInt<64> b_const(BigInt<64>::fromHex("98f2bc8e61"));
	const BigInt<64> c_const(BigInt<64>::fromHex("79b76d99e2"));
	const BigInt<64> d_const(BigInt<64>::fromHex("f33e5fb3c4"));
	const BigInt<64> e_const(BigInt<64>::fromHex("ae2eabe2a8"));
	const BigInt<64> f_const(BigInt<64>::fromHex("1e4f43e470"));

    BigInt<64> c(1);
    
    for(int i = 0 ; i < input.size() ; i++)
    {
		const unsigned char dd = input.getAt(i);		
		const BigInt<64> d(dd);
		
        unsigned char c0 = (c >> 35).intVal();
                
        c = ((c & a_const) << 5) ^ d;
        
        if (c0 & 0x01)
        {
			c ^= b_const;
		}
			
        if (c0 & 0x02)
        {
			c ^= c_const;
		}
			
        if (c0 & 0x04)
        {
			c ^= d_const;
		}
			
        if (c0 & 0x08)
        {
			c ^= e_const;
		}
						
        if (c0 & 0x10)
        {
			c ^= f_const;
		}
    }
    
	const BigInt<64> result(c ^ one);
    
	const BigInt<512> resultLong(result);
	const FiveBitItems	theChecksum(resultLong, 8);
    return theChecksum;
}






std::string CashAddress::encodeBase32(const FiveBitItems& imp) 
{
	static const char base32chars[] = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";
	
	std::string ret;
		
	for(int i = 0 ; i < imp.size()  ; i++)
	{ 
		const unsigned char val = imp.getAt(i);
		//std::cout << int(val) << ", ";

		const char c = base32chars[val];
		ret += c;
	}
	
	return ret;
}






FiveBitItems CashAddress::lower5Bits(const std::string& prefix)
{
	FiveBitItems ret;
	
    for(int i = 0 ; i < prefix.size() ; i++)
    {
		unsigned char dd = prefix[i];
		unsigned char ddLower = dd & 0x1f;
		
		ret.addLast(dd);		
	}	
		
	return ret;
}




FiveBitItems CashAddress::computeTheChecksumForVersionAndRipeSum(const FiveBitItems& payloadInput)
{
	//std::cout << "Will compute checksum for payload with size: " << payload.size() << std::endl;
	
	FiveBitItems total;

	const std::string prefix = cashAddrPrefix();
	
	const FiveBitItems lower5bitsVal = lower5Bits(prefix);
	
	total.addInput(lower5bitsVal);	
	total.addLast(0);

	total.addInput(payloadInput);

	const std::string zeroChecksum(5, '\0');
	const FiveBitItems checksumInput(zeroChecksum);
	total.addInput(checksumInput);
				
		
	const FiveBitItems	theChecksum = CashAddress::computeCashAddrChecksum(total);
	return theChecksum;
}




FiveBitItems getVersionAndRipeSum(const std::string& theRipeSum, const bool isAMultisig = false)
{
	if(theRipeSum.size() != 20)
	{
		throw std::string("Internal error, the hash must be 20 bytes");
	}
	
	//The payload is composed of 3 elements:
    //A version byte indicating the type of address.
    //A hash.
    //A 40 bits checksum.
	//const std::string zero(1, 0);    
    
	FiveBitItems ripeSumFive(theRipeSum);
	
	const unsigned char extra = ripeSumFive.shiftLeftTwo();
	
	FiveBitItems versionFive;
	versionFive.addLast(isAMultisig ? 1 : 0);
	versionFive.addLast(extra);	
	
	FiveBitItems payloadInput;
	payloadInput.addInput(versionFive);
	payloadInput.addInput(ripeSumFive);	

	return payloadInput;
}



//Todo!!!!!!!!!!!!!!!!
//unsigned char versionByte(isAMultisig ? 8 : 0);	
//versionByte |= 0; // 160 bit hash 3;	//256 bit hash
void CashAddress::verifyCashAddrChecksum(const std::string& hash, const bool isMultiSig,
	const FiveBitItems& givenChecksumFiveBit)
{	
	const FiveBitItems versionAndHash = getVersionAndRipeSum(hash, isMultiSig);
	
	const FiveBitItems computedChecksum = computeTheChecksumForVersionAndRipeSum(versionAndHash);
		
	if(givenChecksumFiveBit != computedChecksum)	
	{
		std::cout << "Checksum mismatch, given: " << hexString(givenChecksumFiveBit.getBytes()) << 
			" != computed: " << hexString(computedChecksum.getBytes()) << std::endl;
		throw std::string("Cashaddr checksum error");
	}
}



bool CashAddress::isCashAddrChar(const char c)
{	
	//Permitted chars:  a cdefgh jklmn pqrstuvwxyz 0 23456789
	if(c == 'a')
	{
		return true;
	}
	else if(c >= 'c' && c <= 'h')
	{
		return true;
	}
	else if(c >= 'j' && c <= 'n')
	{
		return true;
	}
	else if(c >= 'p' && c <= 'z')
	{
		return true;
	}
	else if(c == '0')
	{
		return true;
	}
	else if(c >= '2' && c <= '9')
	{
		return true;
	}

	return false;
}	
	





void CashAddress::verifyOnlyCashAddrCharacters(const std::string& str)
{
	for(int i = 0 ; i < str.size() ; i++)
	{
		const char c = str[i];
		if(!CashAddress::isCashAddrChar(c))
		{
			throw std::string("Illegal character found in cashaddr");
		}
	}
}




//+0 	q 	p 	z 	r 	y 	9 	x 	8
//+8 	g 	f 	2 	t 	v 	d 	w 	0
//+16 	s 	3 	j 	n 	5 	4 	k 	h
//+24 	c 	e 	6 	m 	u 	a 	7 	l
//void
FiveBitItems CashAddress::decodeCashAddr(const std::string& str)
{
	
	static const int mapping[256] =
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,15,-1,10,17,21,20,26,30,7,5,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		29,-1,24,13,25,9,8,23,-1,18,22,31,27,19,-1,1,0,3,16,11,28,12,14,6,4,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
	
		
	FiveBitItems res;
	for(int i = 0 ; i < str.size() ; i++)
	{
		const unsigned char c = str[i];
		//std::cout << "Checking: " << i << " " << int(c) << std::endl;
		
		const int mapVal = mapping[c];
		
		//std::cout << "Mapval: " << mapVal << std::endl;
		
		if(mapVal == -1)
		{
			throw std::string("Internal error when converting cash addr");
		}
		
		res.addLast(mapVal);
	}
	
	return res;
	
	/*
	//static const char base32chars[] = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";
	FiveBitItems res;
	 
	for(int i = 0 ; i < str.size() ; i++)
	{
		const unsigned char c = str[i];
		
		for(int j = 0 ; j < 32 ; j++)
		{
			if(base32chars[j] == c)
			{
				res.add(j);
				break;
			}
		}				
	}

	return res;

	*/
}


	/*
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl << "{ ";
	for(int j = 0 ; j < 256 ; j++)
	{
		bool found(false);
		
		for(int i = 0 ; i < 32 ; i++)
		{
			if(base32chars[i] == j)
			{
				std::cout << i << ",";;	
				found = true;
				break;
			}
		}

		if(!found)
		{
			std::cout << -1 << ",";
		}
		
	}				
	std::cout << "}" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	*/
	
	//int map[256] = {-1, -1, -1, 5, };
	//map['q'] = 0;
	//map['p'] = 1;
	//map['p'] = z;
	//std::map<char, int> mapping;
	//mapping.insert('q', 0);
	//mapping.insert('p', 1);




std::string CashAddress::fullDecodeCashAddr(const std::string& origStr, bool& isMultisig, 
	std::string& versionAndHash_out, std::string& checksumRaw_out)
{
	const std::string prefixWithColon = getUrlPrefix();
	
	std::string str(origStr);

	//Is there a prefix "bitcoincash:" ?	
	if(startsWith(str, prefixWithColon))		//Todo: Use prefix for the current currency
	{
		//std::cout << "Has prefix" << std::endl;		
		const std::string withoutPrefix = str.substr(prefixWithColon.size());
		//std::cout << "Without prefix: " << withoutPrefix << std::endl;
		str = withoutPrefix;
	}
	
	if(str.size() != 42)
	{
		throw std::string("Cash address error, must be 42 characters");
	}
	
	//First make a fast check if the characters are permitted
	verifyOnlyCashAddrCharacters(str);
	
	const FiveBitItems res = decodeCashAddr(str);

	const std::string verAndHash = res.getVersionAndHashBytes();
	versionAndHash_out = verAndHash;
	
	if(verAndHash.size() != 21)
	{
		throw std::string("Internal error, cash address payload must have len 21");
	}

	
	const unsigned char versionByte = verAndHash[0];
	//std::cout << "Version byte: " << int(versionByte) << std::endl;
	
	isMultisig = versionByte & 0x08;
	//std::cout << "Is " << (isMultisig ? "MULTISIG" : "not multisig") << std::endl;
		
	const std::string hash = verAndHash.substr(1);
	
	const FiveBitItems checksumFiveBit = res.getRange(34, 42);
	checksumRaw_out = checksumFiveBit.getBytes();
	

	verifyCashAddrChecksum(hash, isMultisig, checksumFiveBit);
	
	return hash;
}








//The version byte's most signficant bit is reserved and must be 0. 
//The 4 next bits indicate the type of address 
//the 3 least significant bits indicate the size of the hash.
//Size bits 	Hash size in bits
//0 	160
//1 	192
//2 	224
//3 	256
//4 	320
//5 	384
//6 	448
//7 	512
std::string CashAddress::toCashAddrString(const std::string& theRipeSum, const bool isAMultisig)
{
	
	if(theRipeSum.size() != 20)
	{
		throw std::string("Internal error, the hash must be 20 bytes");
	}
	
	//The payload is composed of 3 elements:
    //A version byte indicating the type of address.
    //A hash.
    //A 40 bits checksum.

	const FiveBitItems payloadInput = getVersionAndRipeSum(theRipeSum, isAMultisig);

	const FiveBitItems	theChecksum = CashAddress::computeTheChecksumForVersionAndRipeSum(payloadInput);
	//std::cout << "Adding checksum to the cash addr: " << theChecksum.not_used_toString() << std::endl;
	
	FiveBitItems finalString(payloadInput);
	finalString.addInput(theChecksum);	
		
	const std::string encoded = CashAddress::encodeBase32(finalString);
		
	return encoded;
}




std::string CashAddress::getRipeSumFromCashAddress(const std::string& address)
{	
	bool isMultisig(false);
	std::string versionAndHash_out;
	std::string checksumRaw_out;	
	const std::string hash = CashAddress::fullDecodeCashAddr(address, isMultisig, 
															versionAndHash_out, checksumRaw_out);
		
	return hash;
}




