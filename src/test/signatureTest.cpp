/**
 * unittest.cpp - Bitcoin poscript generator
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



#include "unittest.h"
#include "signature.h"
#include "binaryTransaction.h"
#include "transaction.h"

#include <iostream>


void testSchnorrSign1()
{	
	std::cout << "Testing schnorr signature........." << std::flush;
	
	const BigInt<256> privKey(BigInt<256>::fromHex("a664ecbaed04f26e36c3cf68f0b110a4e3b20c65480226ae26b9edbaa96a2729"));	
	const BigInt<256> hashNum(BigInt<256>::fromHex("93067d093b27803afe5d08d7b946f9ff7ad85881ea4a07bc358d1cb0df846651"));
	const BigInt<256> tempKey(BigInt<1024>::fromDec("34098929056647590465493972493627697409106209010079429966959107997133444047839"));
		
	const RSVal rs = SignatureImplementation::signSchnorr(privKey, tempKey, hashNum);

	const BigInt<1024> r(BigInt<1024>::fromHex("00fd11b3445c5ace14ce0a1796e15a1a4aae125a6520a986096a2ffc9f2187b6"));
	const BigInt<1024> s(BigInt<1024>::fromHex("f44887beea02006aa0417f34fe44cf5df9172f2707f5a9381d3dafc6316e8177"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 1 OK" << std::endl;
}




void testSchnorrSign2()
{	
	std::cout << "Testing schnorr signature........." << std::flush;
	
	const BigInt<256> privKey(BigInt<256>::fromHex("bd8a5376872e339cb73bf676611e33f6bcbe0e13802bc0bf213aa75c4521cb66"));	
	const BigInt<256> hashNum(BigInt<256>::fromHex("0505721bb0dc40179fe7c48c4c4c88c72cb474c0ad7f45e1ce611e46ca202258"));
	const BigInt<256> tempKey(BigInt<1024>::fromDec("93979158398773342739859979543981927347650561301338592170547773114562803527923"));
		
	const RSVal rs = SignatureImplementation::signSchnorr(privKey, tempKey, hashNum);

	const BigInt<1024> r(BigInt<1024>::fromHex("abfb77a1034f66a15d5589cdaf9b9ca350ba6a7bcdec0e62b888198a70e4a405"));
	const BigInt<1024> s(BigInt<1024>::fromHex("28df3969f2907eaf4302680306c2f5ef7d5d59683747bae847d72f5390e32382"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 2 OK" << std::endl;
}




void testSchnorrSign3()
{	
	std::cout << "Testing schnorr signature........." << std::flush;
	
	const BigInt<256> privKey(BigInt<256>::fromHex("d488afe591a56a37379317636fe67865bbcbcb305b76386768b5ad228ee4c4de"));	
	const BigInt<256> hashNum(BigInt<256>::fromHex("ae4ea03b07ae298bcde2fe42d946a05b34d8fbff69671c1040bdb1d7e070db05"));
	const BigInt<256> tempKey(BigInt<1024>::fromDec("86102767120192375686964379544096419447546400819143598802241691219678682013879"));
		
	const RSVal rs = SignatureImplementation::signSchnorr(privKey, tempKey, hashNum);

	const BigInt<1024> r(BigInt<1024>::fromHex("b305ecc14616aed35180ae3908b630b9abd866a4b906fcd3fdc78b511bb6e136"));
	const BigInt<1024> s(BigInt<1024>::fromHex("7f478dc5d057b580ee921c58bae73e0d66f6a592dbf8f2d971de140ae42a4062"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 3 OK" << std::endl;
}




void testSchnorrSign4()
{	
	std::cout << "Testing schnorr signature........." << std::flush;
	
	const BigInt<256> privKey(BigInt<256>::fromHex("d9b90ea97d96e59442be0a67be76171fbd8c384cedf3310074f62b6e4d5b2c28"));	
	const BigInt<256> hashNum(BigInt<256>::fromHex("b7ddf66a416989bccca5f0cabaaa74302efa3ddd64a192a6f4d680130bc03392"));
	const BigInt<256> tempKey(BigInt<1024>::fromDec("68819215988952220322472888571768923842004796881505119443195041572478355534172"));
		
	const RSVal rs = SignatureImplementation::signSchnorr(privKey, tempKey, hashNum);

	const BigInt<1024> r(BigInt<1024>::fromHex("00373b82b8ae79db65fc2debb4ba1fba7d77f9542f10573ff3179533653cd4e9"));
	const BigInt<1024> s(BigInt<1024>::fromHex("b4db6873ff9ec98ef227898ce0c0bfa3e6d61240e35550f581108f8a56f75449"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 4 OK" << std::endl;
}


void testSchnorrSign5()
{	
	std::cout << "Testing schnorr transaction signature........." << std::flush;
	
	const BigInt<256> tempKey(BigInt<1024>::fromDec("68819215988952220322472888571768923842004796881505119443195041572478355534172"));
		
	
	const BinaryTransaction raw("weoiruweioruweioru");

	const BigInt<256> mypriv(666234);
	PrivKey privKey(mypriv, true);	


	const RSVal rs = Transaction::getSignature(privKey, tempKey, raw, true);

	const BigInt<1024> r(BigInt<1024>::fromHex("00373b82b8ae79db65fc2debb4ba1fba7d77f9542f10573ff3179533653cd4e9"));
	const BigInt<1024> s(BigInt<1024>::fromHex("39566D3C3623467E6740FF93049D02E12FB444B95414F355F177D1DEDD0DF105"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 4 OK" << std::endl;
}



void testSchnorrSign6()
{	
	std::cout << "Testing schnorr transaction signature........." << std::flush;
	
	const BigInt<256> tempKey(BigInt<1024>::fromDec("63498573489573487538947589347589374589734895738455119443195041572478355534172"));
		
	
	const BinaryTransaction raw("wekjsdfhksdhfjkshfjshdfjkhsdjkfhsjkfhjsdhfoiruwe345345345345345sdfgdfgioruweioru");

	const Wif wif("L5HqRRaEVrofZjdCQj3B6bPkTwk732dy9iy1dgyexz8knW14irFF");			
	const PrivKey privKey = wif.getPriv();



	const RSVal rs = Transaction::getSignature(privKey, tempKey, raw, true);

	const BigInt<1024> r(BigInt<1024>::fromHex("9777CE3F734FEDFE07B20C7B515A7E9A6C7B307FAE1AB79535A393E8756B696C"));
	const BigInt<1024> s(BigInt<1024>::fromHex("85C61ACABA0233EF92951EA3BE7B1479D9F238A0DCDE7D58452423CDF401D38B"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 4 OK" << std::endl;
}



void testSchnorrSign7()
{	
	std::cout << "Testing schnorr transaction signature........." << std::flush;
	
	const BigInt<256> tempKey(BigInt<1024>::fromDec("63498573489573487534534534534534534589734895738455119443195041572478355534172"));
		
	
	const BinaryTransaction raw("345345345345345345345dfdfdgdjkfhsjkfhjsdhfoiruwe345345345345345sdfgdfgioruweioru");

	const Wif wif("L5HqRRaEVrofZjdCQj3B6bPkTwk732dy9iy1dgyexz8knW14irFF");			
	const PrivKey privKey = wif.getPriv();



	const RSVal rs = Transaction::getSignature(privKey, tempKey, raw, true);

	const BigInt<1024> r(BigInt<1024>::fromHex("ED0DAEF44E9E8D0F8148B539FF86F3A5657C1A0EC9F3168B63260A9BDA4867EF"));
	const BigInt<1024> s(BigInt<1024>::fromHex("B75BAA3EEDF15658309EE5082145E6E414F4A4CA8816F5C91767DC0F6E91FC3"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 4 OK" << std::endl;
}


void testSchnorrSign8()
{	
	std::cout << "Testing schnorr transaction signature........." << std::flush;
	
	const BigInt<256> tempKey(BigInt<1024>::fromDec("63453453453453453453453453453453453453453453453453453453455041572478355534172"));

	const BinaryTransaction raw("weoiruwe3dfgdfgdfg45345345345345sdfgdfgioruweioru");

	const BigInt<256> mypriv(848475234);
	PrivKey privKey(mypriv, true);	


	const RSVal rs = Transaction::getSignature(privKey, tempKey, raw, true);

	const BigInt<1024> r(BigInt<1024>::fromHex("4BD88C5BC63A65F6E61C82D16905925920C8924C6FD0D1AB70DC937607810056"));
	const BigInt<1024> s(BigInt<1024>::fromHex("C489A426BB94125DB028174F00417F6505F4A12D0F9642239DEE6A717AEFB159"));

	if(rs.r != r)
	{
		std::cout << "Should r val: " << r << std::endl;
		std::cout << "Has r val   : " << rs.r << std::endl;
		
		throw std::string("Schnorr sig error for r");
	}

	if(rs.s != s)
	{
		std::cout << "Should s val: " << s << std::endl;
		std::cout << "Has s val   : " << rs.s << std::endl;
		
		throw std::string("Schnorr sig error for s");
	}
			
	std::cout << "Schnorr Test 4 OK" << std::endl;
}



void testJacobi1(const BigInt<1024>& argA, const BigInt<1024>& argN, const int shouldBe)
{
	std::cout << "Testing Jacobi............ " << std::flush;
	
	const int res = SignatureImplementation::jacobi(argA, argN);
			
	if(res != shouldBe)
	{
		std::cout << "Should be: " << shouldBe << std::endl;
		std::cout << "Has      : " << res << std::endl;
		
		throw std::string("Jacobi error");		
	}
	
	std::cout << "Test OK" << std::endl;
	
	
}




void testSignSchnorr()
{	
	const Wif wif("KzN68chcyLrPX2sX91mt3c6AF6RKcDDGwwLNLr5hA28PAWtthjKF");			
	const PrivKey pk = wif.getPriv();
		
	const std::string theHash = doubleSha256("mess");
	const BigInt<256> hashNum(theHash, 'c');

	const BitcoinEllipticCurve ec;	

	const PubKey pubk = pk.getPubkey(ec);		
	const ECPoint pubkey = pubk.point;
	
	for(int i = 1 ; i < 50 ; i++)
	{
		std::cout << "Testing signing " << i << " ....." << std::flush;
		const BigInt<256> tempKey(i);

		const RSVal rs = SignatureImplementation::signSchnorr(pk.key, tempKey, hashNum);
				
		if(!SignatureImplementation::verifySignSchnorr(rs, pubkey, hashNum))
		{
			std::cout << "Error in message signature!!!!!" << std::endl;
			std::cout << "r: " << rs.r << std::endl;
			std::cout << "s: " << rs.s << std::endl;
			std::cout << "pubkey: " << pubkey << std::endl;
			std::cout << "hashnum: " << hashNum << std::endl;
		
			throw std::string("Error in message signature!!!!!");
		}

		std::cout << "OK" << std::endl;
	}		
}



void unitTestsBitcoinCash2()
{
	std::cout << "Unit tests for bitcoin cash part 2" << std::endl;
	
	testSchnorrSign1();
	testSchnorrSign2();
	testSchnorrSign3();
	testSchnorrSign4();
	testSchnorrSign5();
	testSchnorrSign6();
	testSchnorrSign7();
	testSchnorrSign8();
	testSignSchnorr();

	const BigInt<1024> argA(BigInt<1024>::asPositive(BigInt<1024>::fromDec("68394344506689415654209670109703033153466065634392348462219117637129189786953")));
	const BigInt<1024> argN(BigInt<1024>::asPositive(BigInt<1024>::fromDec("115792089237316195423570985008687907853269984665640564039457584007908834671663")));
	const int shouldBe(1);
	testJacobi1(argA, argN, shouldBe);

	const BigInt<1024> argA2(BigInt<1024>::asPositive(BigInt<1024>::fromDec("69238472389472893472389742897489237423874892374892374982374892374129189786953")));
	const BigInt<1024> argN2(BigInt<1024>::asPositive(BigInt<1024>::fromDec("115827346782364782364782364723647862378468737234786237846239847238473878888887")));
	const int shouldBe2(1);
	testJacobi1(argA2, argN2, shouldBe2);


	const BigInt<1024> argA3(BigInt<1024>::asPositive(BigInt<1024>::fromHex("6923ABABABABBBBAB47238974289748923742387489237489237498237489237")));
	const BigInt<1024> argN3(BigInt<1024>::asPositive(BigInt<1024>::fromHex("11582734678236478ABABBABABAB236478623784687372347862378462398471")));
	const int shouldBe3(0);
	testJacobi1(argA3, argN3, shouldBe3);

	const BigInt<1024> argA4(BigInt<1024>::asPositive(BigInt<1024>::fromHex("692389878973284723478837428974892374238FF89237489237498237489237")));
	const BigInt<1024> argN4(BigInt<1024>::asPositive(BigInt<1024>::fromHex("11582734678236478ABABBAB34234234234237846FF372347862378462398471")));
	const int shouldBe4(1);
	testJacobi1(argA4, argN4, shouldBe4);


	std::cout << "End unit tests for bitcoin cash part 2" << std::endl;	
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;	
}

