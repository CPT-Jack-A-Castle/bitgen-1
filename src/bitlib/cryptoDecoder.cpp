

#include "cryptoDecoder.h"


//Todo: Move to separate class
int CryptoDecoder::decodeByteInteger(ReadStream& stream)
{
	const std::string str = stream.getStr(1);	
	const unsigned char count = str[0];
	const int numIn(count);
	//std::cout << "Input count: " << numIn << std::endl;	
	return numIn;
}


BigInt<64> CryptoDecoder::reversedIntStr(const std::string& str)
{
	//std::cout << "In reversedIntStr" << std::endl;
	std::string unreversed;
	for(int i = str.size() - 1 ; i >= 0 ; i--)
	{
		const unsigned char c = str[i];
		unreversed += c;
	}

	//std::cout << "Unreversed size: " << unreversed.size() << std::endl;
	const BigInt<64> val(BigInt<64>::fromBytes(unreversed));
	return val;
}


int CryptoDecoder::decodeVariableSizeInt(ReadStream& stream)
{
	//std::cout << "Will decode variable size integer" << std::endl;
	int sizeOfSize(0);
	return decodeVariableSizeInteger(stream, sizeOfSize);
}





int CryptoDecoder::decodeVariableSizeInteger(ReadStream& stream, int& sizeOfSize)
{
	const int first = CryptoDecoder::decodeByteInteger(stream);
	if(first < 0xfd)
	{
		sizeOfSize = 1;
		return first;
	}
	else if(first == 0xfd)
	{
		const int low = CryptoDecoder::decodeByteInteger(stream);
		const int high = CryptoDecoder::decodeByteInteger(stream);
		
		const int result = high * 256 + low;
		sizeOfSize = 3;
		return result;
	}
	else if(first == 0xfe)
	{
		const int b1 = CryptoDecoder::decodeByteInteger(stream);
		const int b2 = CryptoDecoder::decodeByteInteger(stream);
		const int b3 = CryptoDecoder::decodeByteInteger(stream);
		const int b4 = CryptoDecoder::decodeByteInteger(stream);

		const int result = (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
		
		sizeOfSize = 5;		
		return result;		
	}
	else if(first == 0xff)
	{
		std::cout << "Varint FF not implemented" << std::endl;
		throw std::string("Varint FF is not implemented");
/*		
		const int test = 0xffffffff;
		if(test != 0xffffffff)
		{
			std::cout << "Error, must have 64 bit support" << std::endl;
			throw std::string("Error, must have 64 bit support");
		}
		
		const int b1 = CryptoDecoder::decodeByteInteger(stream);
		const int b2 = CryptoDecoder::decodeByteInteger(stream);
		const int b3 = CryptoDecoder::decodeByteInteger(stream);
		const int b4 = CryptoDecoder::decodeByteInteger(stream);
		const int b5 = CryptoDecoder::decodeByteInteger(stream);
		const int b6 = CryptoDecoder::decodeByteInteger(stream);
		const int b7 = CryptoDecoder::decodeByteInteger(stream);
		const int b8 = CryptoDecoder::decodeByteInteger(stream);

		const long result1 = (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
		const long result2 = (b8 << 24) + (b7 << 16) + (b6 << 8) + b5;
		
		const long result = (result2 << 32) + result1;	//Todo: Handle 32 bit integer machines
		std::cout << "FINAL RESULT: " << result << std::endl;
		
		sizeOfSize = 9;	
		return result;
*/
	}	
	else
	{
		std::cout << "First byte: " << first << std::endl;
		throw std::string("Varint error, no match for first byte");
	}
	
	return 0;	//Should never get here
}


unsigned char CryptoDecoder::intByte(const int val)
{
	if(val > 255)
	{
		std::cout << "Can not encode as byte, number out of range: " << val << std::endl;
		throw std::string("Number out of range");
	}
	
	const unsigned char num = val;
	return num;
}



std::string CryptoDecoder::varIntSize(const int num)
{
	std::string ret;
	
	if(num < 0xfd)
	{
		ret += intByte(num);
		return ret;
	}
	else if(num < 0xffff)
	{
		const int low = num % 256;
		const int high = num / 256;

		ret += intByte(0xfd);
		ret += intByte(low);
		ret += intByte(high);
		
		//const int result = high * 256 + low;
		return ret;
	}
	else if(num < 0xffffffff)
	{
		const int b1 = (num >> 0) & 0xff;
		const int b2 = (num >> 8) & 0xff;
		const int b3 = (num >> 16) & 0xff;
		const int b4 = (num >> 24) & 0xff;
		
		
		ret += intByte(0xfe);
		ret += intByte(b1);
		ret += intByte(b2);
		ret += intByte(b3);
		ret += intByte(b4);
		
		return ret;
		
		//const int result = (b4 << 24) + (b3 << 16) + (b2 << 8) + b1;
		//return result;		
	}
	else
	{
		throw std::string("Varint error");
	}
	
}

