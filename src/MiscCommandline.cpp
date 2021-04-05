



#include "MiscCommandline.h"
#include "base58.h"
#include "commandLine.h"
#include "miniPriv.h"
#include "extraInfo.h"
#include "privKey.h"
#include "mnemonic.h"
#include "GenerationParameters.h"
#include "GenerationMethods.h"
#include "language.h"
#include "printPS.h"
#include "bitgenVersion.h"
#include "FileUtil.h"
#include "bitgenConfig.h"
#include "keyDerivationFunction.h"
#include "binaryTransaction.h"
#include "TransactionCommandline.h"


#include <iostream>
#include <list>
#include <stdlib.h>
#include <stdio.h>



int parseNumTextWords(const std::string& numWordsStr, std::string& wallet)
{
	if(numWordsStr == "jaxx")
	{
		wallet = "Jaxx";
		return 12;
	}
	else if(numWordsStr == "coinomi")
	{
		wallet = "Coinomi";		
		return 18;
	}
	else if(numWordsStr == "exodus")
	{
		wallet = "Exodus";		
		return 12;
	}
	else if(numWordsStr == "mycelium")
	{
		wallet = "Mycelium";
		return 12;
	}
	else if(numWordsStr == "multibit")
	{
		wallet = "Multibit HD";
		return 12;
	}
	
	
	const int numWords = atoi(numWordsStr.c_str());
	return numWords;
}






void listMnemonicSize(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 1)
	{
		std::cout << "Usage: bitgen listMnemonic" << std::endl;
		return;
	}	

	std::cout << "WALLET      Default Minsize  MaxSize      (TextWords)" << std::endl;
	std::cout << "=====================================================" << std::endl;	
	std::cout << "Coinomi:    18      12       24" << std::endl;
	std::cout << "Mycelium:   12                 " << std::endl;
	std::cout << "Exodus      12                 " << std::endl;
	std::cout << "Jaxx        12                 " << std::endl;
	std::cout << "MultibitHD  12      12       24" << std::endl;
	
	
	std::cout << std::endl;
}






void getMnemonicInformation(const std::vector<std::string>& args, const std::string& thetime)
{
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen mnemonicinfo MNEMONIC ..." << std::endl;
		return;
	}	

	std::string mnemonicStr(args[1]);
	std::cout << "Mnemonic: " << mnemonicStr << std::endl;
	
	const Mnemonic mnemonic(mnemonicStr/*, false*/); 
	
	const std::string privKey = mnemonic.getAsNumber();
	
	std::cout << "Private data (without checksum):     " << hexString(privKey) << std::endl;
	
	const ExtendedPrivateKey extPk = calculateMasterKey(privKey);
	
	/*
	std::cout << "##############################" << std::endl;
	const std::string seed(convertFromHex("000102030405060708090a0b0c0d0e0f"));
	calculateMasterKey(seed);
	
	std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
	
	const std::string seed2(convertFromHex("fffcf9f6f3f0edeae7e4e1dedbd8d5d2cfccc9c6c3c0bdbab7b4b1aeaba8a5a29f9c999693908d8a8784817e7b7875726f6c696663605d5a5754514e4b484542"));
	calculateMasterKey(seed2);
	*/
}









void getCppString(const std::vector<std::string>& args)
{	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen cppstr hextransaction" << std::endl;	
		return;
	}	
	
	std::cout << std::endl;
	
	const std::string hexStr(args[1]);
	
	
	//Determine if filename or hex string	
	//const std::string trans
	const BinaryTransaction trans = TransactionCommandline::getTrans(hexStr);
	
	const std::string hex = trans.asHex();
		
	std::cout << "Orig trans: " << std::endl;
	
	for(int i = 0 ; i < hex.size() ; i++)
	{
		if(i % 79 == 0)
		{
			std::cout << "\\\n";			
		}
				
		const unsigned char c = hex[i];		
		std::cout << c;
	}
	std::cout << "\n";				
}






void showAscii(const std::vector<std::string>& args)
{	
	if(args.size() < 2)
	{
		std::cout << "Usage: bitgen showascii hextransaction" << std::endl;	
		return;
	}	

	const std::string hexStr(args[1]);

	const std::string trans = convertFromHex(hexStr);

	for(int i = 0 ; i < trans.size() ; i++)
	{
		const unsigned char c = trans[i];
		
		if(c >= 32 &&  c <= 128)
		{
			std::cout << c;
		}
		else
		{
			std::cout << "_";
		}
	}
	
	std::cout << std::endl;
}








#ifndef NO_BRAINWALLET_GENERATION

void testArgon(const std::string& passphrase, const std::string& salt,
	const std::string& hashNumStr)
{

	std::cout << "Testing argon... " << std::flush;
	const std::string kdfStr = bitgenArgon2Kdf(passphrase, salt);
	const BigInt<512> hashNumComputed(kdfStr, 'c');
	
	const BigInt<512> hashNum(BigInt<512>::fromHex(hashNumStr)); //     hashNumStr.c_str());
	if(hashNum != hashNumComputed)
	{
		std::cout << std::endl;
		std::cout << "Error, computed kdfStr: " << hexString(kdfStr) << std::endl;
		
		throw std::string("Argon error");
	}

	std::cout << "OK" << std::endl;
	
}


void brainwalletTests()
{	
	const std::string passphrase("1234567890abcdefghijklmnopq");
	const std::string salt("someone@email.com");
	const std::string hashNumStr("9A5D21E6D7F1D3D1C5A7FBE2547F16ABF2DAE34379FA6309F9672491E2D83276");
	testArgon(passphrase, salt, hashNumStr);
	
	
	const std::string passphrase2("abc");
	const std::string salt2("this@abc.org");
	const std::string hashNumStr2("BD8BBBA3F95A59CA5E3100B4EFC488A9395A253F1366DFBCD84632A2F204C23D");	
	testArgon(passphrase2, salt2, hashNumStr2);
	
	
	const std::string passphrase3("");
	const std::string salt3("");
	const std::string hashNumStr3("93687FFD2E4E6A6A4E09188D6E1CCD3D981981597FE95237231A17DB6991E4F7");
	testArgon(passphrase3, salt3, hashNumStr3);
	
}
#endif





Language getLanguage()
{
	const std::string constPath = getConfigPath();
	
	const std::string confLang = getConfiguredLang();
	
	//std::cout << "Using lang: " << confLang << std::endl;
	
	if(confLang == "en")
	{
		return LANG_EN;		
	}
	else if(confLang == "de")
	{
		return LANG_DE;
	}
	
	
	return LANG_EN;
}




void setLanguage(int argc, char* argv[], const std::string& thetime)
{
	if(argc < 3)
	{
		std::cout << "Usage: bitgen setlang LANGUAGE" << std::endl;
		std::cout << "LANGUAGE: en de" << std::endl;
		return;			
	}

	const std::string lang(argv[2]);

	if(lang == "en")
	{ 
		std::cout << "Setting language to english" << std::endl;
	} 
	else if(lang == "de")
	{ 
		std::cout << "Setting language to deutch" << std::endl;
	}
	else
	{
		std::cout << "Unknown lang: " << lang << std::endl;
		return;
	}
		 
	configureLang(lang);
}




void printIntSize()
{
	std::cout << "sizeof(int)        : " << sizeof(int) << " gives " << sizeof(int)*8 << " bits" << std::endl;
	std::cout << "sizeof(long)       : " << sizeof(long) << " gives " << sizeof(long)*8 << " bits" << std::endl;
	std::cout << "sizeof(long long)  : " << sizeof(long long) << " gives " << sizeof(long long)*8 << " bits" << std::endl;
#if __x86_64__ || __ppc64__	
	std::cout << "sizeof(__uint128_t): " << sizeof(__uint128_t) << " gives " << sizeof(__uint128_t)*8 << " bits" << std::endl;	
#endif
}








void uncompressPublicKey(int argc, char* argv[], const std::string& thetime)
{
	if(argc < 3)
	{
		std::cout << "Usage: bitgen uncompress COMPRESSEDPUBKEY" << std::endl;
		return;			
	}

	const std::string pubkeyStr(argv[2]);
	//std::cout << "Will convert: " << pubkeyStr << std::endl;
	
	if(pubkeyStr.size() != 66)
	{
		std::cout << "Got key with size: " << pubkeyStr.size() << ", but need 66 chars" << std::endl;
		throw std::string("Error, compressed key size must be 66 charcters");
	}
	

	const PubKey pubKey = PubKey::fromHex(pubkeyStr);
	//const ECPoint pubKey = PubKey::fromHexString(pubkeyStr);
	
	const std::string uncompStr = hexString(pubKey.point.getRaw(false));
	
	std::cout << "Uncompressed: " << uncompStr << std::endl;
}




void compressPublicKey(int argc, char* argv[], const std::string& thetime)
{
	if(argc < 3)
	{
		std::cout << "Usage: bitgen compress VERBOSEPUBKEY" << std::endl;
		return;			
	}

	const std::string pubkeyStr(argv[2]);
	std::cout << "Will convert: " << pubkeyStr << std::endl;
	
	if(pubkeyStr.size() != 130)
	{
		std::cout << "Got key with size: " << pubkeyStr.size() << ", but need 130 chars" << std::endl;
		throw std::string("Error, verbose key size must be 130 charcters");
	}
	

	const PubKey pubKey = PubKey::fromHex(pubkeyStr);

	//const ECPoint pubKey = PubKey::fromHexString(pubkeyStr);
	
	/*
	if(!BitcoinEllipticCurve::verifyECPoint(pubKey))
	{
		throw std::string("Error, point not on curve");
	}
	
	std::cout << "OK, point on curve" << std::endl;
*/
	
	const std::string compStr = hexString(pubKey.point.getRaw(tru�PNG

   IHDR           szz�   	pHYs    ��~�  	<IDATX�Ŗ[���A��������'��	>4q��i���RR��D�hJP,�,Q��H���JAE�EP7�$PAu�@@���ױ���=����a���ąi�Ҵ���\�ռ�3��?f�����矯MLL<�$�C��{�<�QJ�a|O.���.]:�ݾ�wϞz��w���~��ѣG?766vw��,���lmm��)�V�l��΅<t_�7穧�����f�Z�ұc����Ro�}�����4�z�V���+�l�[Bi�Q�zI�|;Y{�����Ͻ�/����<yr�9�7�f��Z���4�7��L�j���%ڝMv�c��:���{�ff<x�ȭ��l~�¹s?�}��w�6��P�_��.����߻���2�9��>�@���&�,<ւ�������C�u����⵷�x���N�w/|vl��jA���?y����SarJ����$������g�{t0�C��e/Nss���~�ʕ"�a�g��^a�_Z�:��K�.��;�p�CE�����������	�k�ʘ���ګ�����^g�2�9oF��^_Q��|S��_yv�-��f�x��W�a	:�5f�+���1��Un�Nc/��sw�hc)�@�r�l�!�
��}B9�P8g�W�=����8w�ԃn��IX��1�_X�^]'����F5!�4�n��T�Y9G���<4�k�.g؜X ��جjC����
�|�����=�p�[_��Oү����n%�DqC����ӳ���z�5�+b�-���&��۳F6���V�Nڭ��S`���lE�|�,�eJe�#�R�� /���χ��)��UuW�� �kQ�t�3��3���8��Tju��Hn������[o%�sz���R7	����6Y��g	*O�oB��\���a��vJU��4en@�AV���7�\PJ}�2��ȏa4�+�b����z�Αô6�p��u��^m�"���'d�<O)TF��h]�c�n����Mfp��\�Q������o���޷kZ�Z�ɨ�c)��DF�Z�I�KL���p/��+��uO�E�R9Z�E��3T�R���P���{;�_<��ÙZyxb�$�oA��"�_d����>Wۥ����:q�J<����L;n3��#��0�Q�
[h]�}s�*��s���+-�8#��uY5ؒ�0 �v�[��΃{���{�2f�B$o�NiW��n�C�R	Y�1��
��Y\9$���ut�1z�.=���yNABa��/�yV-��1�I/�������T�jM�v��j&*9�3L"�����Y����A)�"|�)��> >$�0@�g��� .F�|�>�Z]��q��0�	�4�p�'?����:�,���������LN�э	����ZT1uפ��;'�X�J*2��7t�G�)���4B)+˜ǵξ-I�H'�\p��TD� ���~P�)�����O|leeſ�����N�j�e�e����OKJa0��-�2͔�n!��퐷<z{4����#����)�ca��l���z z��G�oF��x�\�4c��u�i3V`>�����w|�E]�����5�l6E�ۧ��(�jLa�FShMZ$�m�!}ԈB�D���h�wB6��d���K�~yWe����蓟�̻����n�Xeɧ��hpLai�D�d,�M��cw��?���FBf&���V!�\AQ(���'
�����c��/I�'w����a�Z���7�������w^���~�&9A3�PCAar�����j�����	^8�+�<�N�6NX�&�
K0��@�Q�/��K9�v��l��o�ş����F���#��fu�Қ�V��j4K�X��P�(�*�O�^��"+V�e���[Or9%���V
ʞ�;��Y����첺��/@ <��s�|���zc��fE_!��DU����RR3UF��-�]�����t-zKc3D,nK�<�_Ȯ���wK�3�<���k_�u=.�����\%��X�("_�n���~e���w^z�ˊ�B
!n ����߬{|O+~�'>r�F�7{Ѽ�c$�9���P�'�%c�16ӗ��\ Л%�e@
 @� �_���|Im�Y8��Nx����������������qS�j�+5j�
ո�*�d#[/%��f0���̗�����?(��N��:q��O�{��0�>`������k1R�����Լ�ذ��%B��!�	���� ��?��B��3��j���d-,,,t�K봛Q��
�? �[����J�����3�����F6�G~�G�����Sd9_lɯ�7�շ��c�%���]�t�    IEND�B`�                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      0\r�m��   J   �s    _keyhttps://gofile.io/plugins/popper/umd/popper.min.js 
https://gofile.io/    �~�ַ���rQ�	S  ����
   �3  �7ǅ`	   �� ��  �  �  �  P �   �   �   �S,�`       L`       SH�`    X   L`       Q@6��   exports Q@fh�   module  Q@�5/�   define  Qa���S   amd     Q@6#Ǐ   Popper  K`        Dl            �  s�s�&�&�_�&�.�  %��3s�&�)��&�&�'�_���&�_�&�. %��  (Rc           �q                I`    ����Da    �         �a
       `   @% $P   2   https://gofile.io/plugins/popper/umd/popper.min.js      a                D`       D`       D`        �A`    u   $
  $
 �$S��`    t  �L`    }   9Rc    �       �q             B   Qa�   e       Q@f ��   t       Qa.A�   o       Qa�d�v   n        �Qa��C   r       Qa���C   p       Qa&�I�   s       Qa�*�   d        b�Qa�,�Z   l       Qa�B��   f       Qav��   m       Qa��w�   h       Qa�ׇ�   c        B� �� b�Qa�v�   w       Qa^�\#   y       Qa&�R	   E       Qa�i��   v       Qa���   x       Qa����   O       Qa��H%   L       Qa��&   S       Qa���   T       Qa.R�m   C       Q@N��   D       Qa6��7   N       Qa"��   P       Qa���<   k       Qa&��   W       Qa�v     B       Qa>:�a   H       Qa����   A       Qaƣ��   M       Qa�M�   F       Qa��*8   I       Qa��[�   R       Qa��D+   U       QaY`�   Y       QaN0�\   V       Qan5R   j       Qav�?�   q       Qa}(   K       Qa�l	   z       Qav��   G       Q@�&�   _       Qa�E�g   X       Qa�3H   Q       Qa���   Z        �yQavb �   ee      QaN2�   te      Qa.�~�   oe      Qa��)m   ie      Qa.�&   re      QaV�_}   pe      Qa��    se      Qa&���   de      Qa�G   ae      Qa��Y�   le      Qa�   fe      Qa^k,   he      Qa�F_    ce      A    ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��?     ��? I`    ����Da    +      �R  S9I`E  }  
 ?
 A-
 �
a    
 @    S�I`�  �  
 a?��a    
 @    S�I`  6  
 ��a    
 @    S�I`@  ,  
`��a    
 @    S�I`6  f   ���a    
 @    S�I`p  �  
���a    
 @    S9I`�  	  
!
 A-
 �
a    
 @ 	   S�I`  c  
���a    
 @ 
   S�I`m  �  
���a    
 @    S�I`�     b���a    
 @    S�I`    
A��a    
 @    S�I`  �  
���a    
 @    S9I`�  K	  

 A-
 �
a    
 @    S�I`U	  8
  
a��a    
 @    S�I`B
  �
  
���a    
 @    S�I`�
     B���a    
 @    S�I`  �   ����a    
 @