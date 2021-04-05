



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
	
	const std::string compStr = hexString(pubKey.point.getRaw(tru‰PNG

   IHDR           szzô   	pHYs    Òİ~ü  	<IDATX…Å–[ŒÇA†Ÿ™ïûûïî¿'ï®í	>4q“´i›€‘RR—´D½hJP,¨,Q•«H”†›JAEÍEP7¨$PAuš@@¤¥Æ×±ìÄÇ=şıÏßa¾ùæÄ…i•Ò´„©ï\ÌÕ¼ï3£Í?f‰·³øùçŸ¯MLL<˜$ÉCŞû{ò<ŸQJÅa|O.’•ë—.]:³İ¾øwÏzñµÿw€§Ÿ~úøÑ£G?766vw²,©×ëlmm‘¦)­V‹lê½ÈÎ…<t_èµ7ç©§ºò¶üñfµZıÒ±cÇ§Óé¸Ro†}ûßÍôô4õzV«ÅÙ+«lù[BiëQ‘zI÷|;Y{ùäïıî“Ï½Ñ/ú¿„Ÿ<yrÂ9÷7ÍfóáZ­æÒ4õ7®‹LÔj‚µõ%ÚMvïc°µ:•‚Á{¼ff<xÿÈ­·Ìl~ûÂ¹s?À}÷İwª6µöP—_Ãú.£İìß»›‘ø2·9‚™>È@’‘ä&¦,<Ö‚±øà”ŒİàC£uñÒâââµ·°xã«âà¡N®w/|vl¬ájAáÖè·?yïıìÜSarJĞ‰˜›$®‡¬’g•{t0¥C¨–e/NssôÀ­~åÊ•"şaÁgÏù^aŠ_Z¹:ø™K—.©;pÁCEâşû–ĞÓ…ôšÈÕ	ùkŒÊ˜ºÉÚ«‰«»±ö^g„2Ã9oFÛ^_QŸ|S€—_yv·-Ôıfïx½›Wşa	:Ù5fÇ+Öƒµ1ÍÉUn´Nc/®°swÊhc)ë@Òr‚lÍ!ã
ó¸²À}B9ºP8g©Wå‰=·ùıï8wáÔƒn˜üIXêï1í_X®^]'ªåÎÛF5!4Ën‰êT‡Y9G£›„<4èk¼.gØœX ÛÖØ¬jC˜¼ƒÊ
¥|ğş€ôÅ=ßpö[_ù¨OÒ¯¸«ƒšn%ØDqCÖÙŞŞÓ³Õà­Ãzª5+bú-ÁâÙ&“Û³F6œÁ„VÃNÚ­’´S`†ÛølEø|,’eJeŞ#ËR¿ç» /¿úâÏ‡ìÚ)·”UuW¡š ıkQôtá3Îæ3¥©º8€÷Tjuƒ«Hn¬–®¼ƒ±[o%“szš¤“R7	ù²°Ù6Yšg	*OÉoBà¬Ù\¸ñÒa¼vJUÕö4en@ÊAV¯øÌ7Î\PJ}¶2šŠÈa4ëˆ+àbµŠäzÄÎ‘Ã´6¦på“u±é^mŠ" ò•'dé<O)TF¥h]Öc€ní‹ãôÇMfpÚà\ Q‘¿ıĞç¿ğo»öšŞ·kZõZÉ¨’c)±®DF’ZµIKLº±²p/ñÚ+“àuO”E†R9ZåE†Ê3TR¨œ¢P¨¢Ä{;Œ_<÷µÃ™Zyxb¤$„oAˆ¬"å_dªè÷½>WÛ¥ë˜äêõ:qµJ<¶“¤»L;n3Îß#¢š0ÆQ–
[h] }sÖ*¿¹s•§Ô+-å•8#ıˆuY5Ø’Ğ0 ¼vŞ[ËşÎƒ{ÎöÉ{Š2fÏB$oàNiW‹Ğn·C¥R	Y–1¸ö
ñY\9$„€öuté1zˆ.=¡ì‘äyNABaŒõ/ÅyV-‚Â1ãI/şø¿ïèƒTÿjMŠv»ôj&*9±3L"ÛóˆëÕĞYŞËËËA)ò"|Š)úı> >$Ø0@Èg­Äø .F|ô>¿Z]›q†ª0ø	‡4—pß'?øüÓ:½,’ü˜Œëû„ÀÏLNÊÑ	Ø¡â±óZT1u×¤œİ;'ÍX¸J*2»7tÖGå)º€¢4B)+ËœÇµÎ¾-IÂH'ä\pŠ²TD² º£¤~PÍ)²¯ÿû“O|leeÅ¿ãÀ“ë­NÑj÷e–e¡ÓéàOKJa0…Ã-¥2Í”èn!¦í·<z{4ûññÄ#»äØÑ)çca½l¿ ­z zôÑGoF‹ôxÃ\°4c‹œuÈi3V`>ö‰ßÿÓw|çE]‰úí÷5Ñl6E¿Û§š×(÷jLaÑFShMZ$ômŸ!}ÔˆBìŒDíğˆh¾wB6ßİdöşéKû~yWeô¶‘•è“ŸúÌ»ºçÚ÷níXeÉ§¬ËhpLai”DóŠd,»MÔôcwíŸß?·÷îFBf&¥ô†ŞV!å\AQ(ôèÑ'
ğ„àñÚc‡İ/I®'w´ş¹›aùZŒ×Ï7¦îúµùÓ’w^áµÑ•~¢&9A3PCAarŒ¯ÍÏïj ƒàÕë	^8Œ+Ù<»N³6NXğ¤&Á
K0à“@¶Q/çäK9Åv‰Íl‡Àoä‹ÅŸÄÀ™©FçÉ#ïŸøfuÈÒšî²Vñ¼ìj4KÁX¨ë˜PÖ(Ò*¹OÑ^£¼"+Vÿe™îÀ[Or9%½¡V
ÊÁ;‡Y‘ßñéì²ºô/@ <÷Üsïº|ùò¿²zc«×fE_!ŸÛDU´µèÂ€ÈRR3UFÊ„-É]ŠòŠÂàÁt-zKc3D,nKá<‰_È®ææàwKé3Ï<óØåk_Îu=.´¤´Ø\%»X™("_¡nˆ‘‚~eïüÍw^z²ËŠàB
!n ŸÎÕ×ß¬{|O+~â‰'>ríFû7{Ñ¼µc$Ö9œ×ØP‚'%cµ16Ó—èÍ\ Ğ›%¦e@
 @ ü_€üõ|Im¼Y8üNxúôé×îƒüµÕİİı¡»Ã‡ŒqS‰jÔ+5j•
Õ¸‚*ºd#[/%èòf0™€ßÌ—õçÌÀ¦?(üûNà:qâÄOµ{áÄ0>`Üï‚àæÔk1R®«ÿŒÏÔ¼²Ø°”Û%B„ó!ğ	µ¬Ïı ï·ğ?şñ±B‡Û3åÔjÑìÌd-,,,tşKë´›Q×Á
€? ğ[ù²ÊŞJøÛÖìÃ3¦Ş×£ûF6ûG~ñGñø¡µüSd9_lÉ¯ä7ÔÕ·ãõcÓ%£¾î]¿t°    IEND®B`‚                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      0\r§mûü   J   ğs    _keyhttps://gofile.io/plugins/popper/umd/popper.min.js 
https://gofile.io/    £~·Ö·ŞÀİrQË	S  –¢åğ
   ¨3  ¥7Ç…`	   €° €ğ  Ø  Ø  ğ  P €   €   €   €S,Ì`       L`       SH`    X   L`       Q@6²”   exports Q@fh£   module  Q@Ö5/‡   define  Qa–¥ŸS   amd     Q@6#Ç   Popper  K`        Dl            §  sšs™&û&ù_ù&ú.û  %ú‹3sš&û)û˜&ú&û'ù_ûú‹&ù_ù&ú. %ú«  (Rc           Âq                I`    ÿÿÿÿDa    ‘         ¼a
       `   @% $P   2   https://gofile.io/plugins/popper/umd/popper.min.js      a                D`       D`       D`        İA`    u   $
  $
 á$SÙ`    t  ıL`    }   9Rc    Œ       âq             B   QaÎï‘¼   e       Q@f ìÔ   t       Qa.Aå   o       QaÆdåv   n        ñQaş¾C   r       QaŞı¤C   p       Qa&ÛI²   s       Qaş*É   d        béQa,ÏZ   l       Qa¦Bğå   f       QavºÈ   m       Qa®Ÿw”   h       Qa¾×‡°   c        B• ¢• bìQa–v€   w       Qa^½\#   y       Qa&‰R	   E       Qa¾išù   v       Qa¾Ö°   x       QaÁ¥¥   O       QaæÀH%   L       Qa–†&   S       Qa†è¹   T       Qa.Rãm   C       Q@N¬çš   D       Qa6æò7   N       Qa"èÕ   P       QağÌ<   k       Qa&âÎ   W       Qa†v     B       Qa>:ãa   H       QaîÁÁ¥   A       QaÆ£‡–   M       QaÇM¨   F       QaÎæ*8   I       Qaş¢[–   R       QaîÌD+   U       QaY`ñ   Y       QaN0÷\   V       Qan5R   j       Qavİ?³   q       Qa}(   K       Qa‹l	   z       Qav¬ü   G       Q@æ&Ò   _       QaöEÍg   X       Qa¶3H   Q       Qa¾®œ   Z        âyQavb ·   ee      QaN2ê²   te      Qa.Œ~Û   oe      QaÆô)m   ie      Qa.›&   re      QaVî_}   pe      Qaò    se      Qa&õûƒ   de      QaŞG   ae      Qa¦µY—   le      Qaî‘¢¸   fe      Qa^k,   he      QaÎF_    ce      A    Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ?     Òÿ? I`    ÿÿÿÿDa    +      ßR  S9I`E  }  
 ?
 A-
 ¡
a    
 @    S”I`‡  ÷  
 a?–—a    
 @    S”I`  6  
 –—a    
 @    S”I`@  ,  
`–—a    
 @    S”I`6  f   ñ–—a    
 @    S”I`p  –  
À–—a    
 @    S9I`   	  
!
 A-
 ¡
a    
 @ 	   S•I`  c  
—a    
 @ 
   S•I`m    
á—a    
 @    S•I`¨     bé—a    
 @    S•I`    
A—a    
 @    S•I`  ²  
¡—a    
 @    S9I`¼  K	  

 A-
 ¡
a    
 @    S–I`U	  8
  
a‘a    
 @    S–I`B
  ¼
  
Á‘a    
 @    S–I`Æ
     B•‘a    
 @    S–I`  ì   ¢•‘a    
 @