/**
 * printPS.cpp - Bitcoin poscript generator
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

#include "printPS.h"

#include <iostream>
#include <string>
#include <list>

#include "util.h"
#include "qrenc.h"
#include "currencySpecific.h"
#include "url.h"
#include "ExtendedKey.h"
#include "StaticXor.h"

//Todo: Move to file "postscriptGeneration.cpp"



std::string PostscriptGenerator::textAt(const int x, const int y, const std::string& str)
{
	std::string ret;
	
	ret += minSize(intToString(x), 4);
	ret += " ";		
	ret += minSize(intToString(y), 4);
	ret += " moveto ";	
	ret += "(";
	ret += str;
	ret += ") show\n";
	
	return ret;
}




//Todo: Member in PostscriptGenerator
std::string lineBetweenPoints(const std::list<Coordinate>& coordinates)
{
	std::string ret;
	
	bool first(true);
	
	for(std::list<Coordinate>::const_iterator it = coordinates.begin() ;
		it != coordinates.end() ;
		++it)
	{
		const Coordinate& coord = (*it);
		
		ret += intToString(coord.x);
		ret += " ";
		ret += intToString(coord.y);
		if(first)
		{
			first = false;			
			ret += " moveto ";
		}
		else
		{
			ret += " lineto ";
		}			
		
	}
	
	ret += "closepath stroke\n";
	
	return ret;
}



std::string PostscriptGenerator::generateQR(const QRInfo& qrinfo)
{
	std::string ret;
	
	const int w = qrinfo.width;
	const int h = qrinfo.height();

	ret += "0.01 setlinewidth\n";

	//ret += "0 setgray\n";
	int myval(0);
	int numMyval(0);
	int numHexDigits(0);
	for(int x = 0 ; x < qrinfo.width ; x++)
	{
		myval = 0;
		numMyval = 0;		
		for(int y = 0 ; y < qrinfo.height() ; y++)		
		{
			const bool val = qrinfo.get(x, y);
			if(val)
			{
				//ret += "newpath ";
				ret += intToString(x * 10);
				ret += " ";
				ret += intToString(qrinfo.height() * 10 - y * 10);
				
				ret += " box ";
			}
		}		
		ret += "\n";		
	}


	return ret;
}



std::string PostscriptGenerator::intro()
{
	std::string ret;
ret += "\
%!PS-Adobe-1.0\n\
%%Title: ";
ret += getCurrencyName();
ret += " address\n\
%%Creator: bitgen\n\
%%Pages: (atend)\n\
%%BoundingBox: 5 5 605 787\n\
%%EndComments\n\
%\n\
\n\
/Big_font { /Helvetica findfont 40 scalefont } def\n\
/Titel_font { /Helvetica findfont 16 scalefont } def\n\
/Text_font { /Helvetica findfont 14 scalefont } def\n\
/Small_font { /Helvetica findfont 10 scalefont } def\n\
/Tiny_font { /Helvetica findfont 7 scalefont } def\n\
/box\n\
{ moveto 10 0 rlineto\n\
 0 10 rlineto\n\
-10 0 rlineto\n\
closepath gsave fill grestore stroke\n\
} def\n\
\n\
Text_font setfont\n\
1 setlinewidth\n\
\n\
%\n\
%%EndProlog\n\
%%Page: \"1\" 1\n\
%%BeginPageSetup\n\
%%EndPageSetup\n";

return ret;
}







std::string PostscriptGenerator::beginPage()
{
	std::string ret;

	ret += "%%Page: \"";
	ret += "1";
	ret += "\" ";
	ret += "1";
	ret += "\n";

	return ret;
}




std::string PostscriptGenerator::endPage()
{
	std::string ret;
	
	ret += "stroke\n";
	ret += "showpage\n";
	ret += "%%EndPage: \"";
	ret += "1";
	ret += "\" ";
	ret += "1";
	ret += "\n";

	return ret;
}








std::string PostscriptGenerator::privateRoot(const std::string& privIndex, const std::string& signature) const
{
	std::string ret;

	ret += "Big_font setfont\n";

	ret += textAt(margin, 360, "PRIVATE ROOT");

	ret += "Text_font setfont\n";


	ret += textAt(margin, 320, "Use this private root key to find the private root for a particular bitcoin address.");
	ret += textAt(margin, 300, "You must first generate the public part explained above.");
	ret += textAt(margin, 280, "Command:");
	
	std::string command;
	
	const std::string currencyShortName = getCurrencyShortName();
	
	command += "bitgen";
	if(currencyShortName != "btc")
	{
		command += "-";
		command += currencyShortName;
	}
	
	command += " genPriv root_";
	command += currencyShortName;
	command += "_";
	command += signature;
	command += "_priv.privroot privindexfile.privindex";
	
	ret += textAt(margin, 260, command);

	ret += textAt(margin, 320, "Use this private root key to find the private root for a particular bitcoin address.");
	ret += textAt(margin, 300, "You must first generate the public part explained above.");
	ret += textAt(margin, 280, "Command:");


	ret += textAt(margin, 220, "Private index:");

		
	const std::string privStart = privIndex.substr(0, 32);
	const std::string privEnd = privIndex.substr(32);
		
	ret += textAt(margin, 200, privStart);
	ret += textAt(margin, 180, privEnd);

	return ret;
}


//Todo: Member in PostscriptGenerator
std::string lineBetween(const int x1, const int y1, const int x2, const int y2)
{
	std::string ret;
	
	ret += intToString(x1);	
	ret += " ";	
	ret += intToString(y1);	
	ret += " moveto ";	
	ret += intToString(x2);	
	ret += " ";	
	ret += intToString(y2);	
	
	ret += " lineto\n";

	return ret;
}



std::pair<std::string, std::string> splitInTwoParts(const std::string& str)
{
	const int middlePos = str.size() / 2;
	const std::string start = str.substr(0, middlePos);
	const std::string end = str.substr(middlePos);
	
	const std::pair<std::string, std::string> ret(start, end);
	return ret;
}




std::string PostscriptGenerator::publicRoot(const HierarcialInfo& hierarcialInfo,
	const PublicPostscriptInfo& pubInfo, const std::string& label) const
{
	std::string ret;

	ret += "Big_font setfont\n";

	ret += textAt(margin, 720, (lang == LANG_EN) ? "PUBLIC ROOT" : "TEILEN");
	
	ret += "Text_font setfont\n";



	if(!label.empty())
	{
		ret += textAt(margin,       700, "Label:");
		ret += textAt(margin + 150, 700, label);
	}


	ret += textAt(margin,       680, (lang == LANG_EN) ? "Generate date:" : "Datum:");
	ret += textAt(margin + 150, 680, pubInfo.thetime);

	ret += textAt(margin,       660, "Signature:");
	ret += textAt(margin + 150, 660, hierarcialInfo.signature);


	std::string myText;
	myText += "Use this public root key to generate ";
	const std::string currencyName = getCurrencyName();
	myText += currencyName;
	myText += " addresses.";		

	ret += textAt(margin,       620, myText);

	std::string myCommand;
	myCommand += "Command: bitgen";
	
	const std::string currencyShortName = getCurrencyShortName();
	
	if(currencyShortName != "btc")
	{
		myCommand += "-";
		myCommand += currencyShortName;
	}
	
	myCommand +=" genPub root";
	myCommand += currencyShortName;
	myCommand += "_";
	myCommand += hierarcialInfo.signature;
	myCommand += "_pub.pubroot";



	ret += textAt(margin,       600, myCommand);

	ret += textAt(margin,       570, "Public point X");

	const std::string pubXStart = hierarcialInfo.pubX.substr(0, 32);
	const std::string pubXEnd = hierarcialInfo.pubX.substr(32);

	ret += textAt(margin,       550, pubXStart);
	ret += textAt(margin,       530, pubXEnd);
	
	ret += textAt(margin,       510, "Public point Y");



	const std::pair<std::string, std::string> pubYParts = splitInTwoParts(hierarcialInfo.pubY);
	const std::string pubYStart = pubYParts.first;		//hierarcialInfo.pubY.substr(0, 32);
	const std::string pubYEnd = pubYParts.second; 		//hierarcialInfo.pubY.substr(32);


	ret += textAt(margin,       490, pubYStart);
	ret += textAt(margin,       470, pubYEnd);

	ret += "Text_font setfont\n";

	ret += lineBetween(margin, 418, 540, 418);
	
	return ret;	
}










std::string PostscriptGenerator::generatePaymentRequest(
						const PublicPostscriptInfo& pubInfo,
						const std::string& amount, const std::string& message) const
{
	std::string ret;

	ret += "Big_font setfont\n";


	ret += textAt(margin,       720, "INVOICE");

	ret += "Text_font setfont\n";

	if(!amount.empty())
	{
		ret += textAt(margin,       700, "Requested amount:");
		
		const std::string currencyShortName = getCurrencyShortName();

		ret += textAt(margin + 150,       700, amount + " " + currencyShortName);
	}



	if(!pubInfo.accountName.empty())
	{
		ret += textAt(margin,       680, "Label:");
		ret += textAt(margin + 150, 680, pubInfo.accountName);
	}

	if(!message.empty())
	{
		ret += textAt(margin,       660, "Message:");
		ret += textAt(margin + 150, 660, message);		
	}



	if(!pubInfo.thetime.empty())
	{
		ret += textAt(margin,       640, "Last payment date:");
		ret += textAt(margin + 150, 640, pubInfo.thetime);
	}

	const std::string currencyName = getCurrencyName();
	
	std::string payString;	
	payString += "Pay to ";
	payString += currencyName;
	payString += " address ";


	ret += textAt(margin,       590, payString);


	ret += textAt(margin,       570, pubInfo.pubkey.toString());
	
	if(getCurrencyShortName() == "bch" || getCurrencyShortName() == "bch_slp")
	{
		ret += textAt(margin,       550, pubInfo.pubkey.toCashAddrString());		
	}



	const std::string myEncStr = createEncString(pubInfo, amount, message);

	const QRInfo qrinfo = QRInfo::qrencode((const unsigned char*)myEncStr.c_str(), myEncStr.size());
	//ret += qrCode(qrinfo, margin, 370, 15.0);
	ret += generateQRPostscriptWithText(qrinfo, "pub legacy", pubInfo.pubkey.toString(), margin, 370, 15.0);			

	const QRInfo qrinfoCashAddr = qrEncodeAddress(pubInfo.pubkey.toCashAddrString(), pubInfo.accountName, true);						
	ret += generateQRPostscriptWithText(qrinfoCashAddr, "pub cashaddr", pubInfo.pubkey.toCashAddrString(), 
		margin + 200, 370, 15.0);			
	

	ret += "Text_font setfont\n";

	return ret;
}








std::string PostscriptGenerator::publicKeyPart(const PublicPostscriptInfo& pubInfo) const
{
	std::string ret;

	ret += "Titel_font setfont\n";
	
	ret += textAt(margin,       780, pubInfo.pubkey.toString());

	ret += "Text_font setfont\n";

	std::string myText;
	myText += "Generated by ";
	myText += applicationName;
	myText += " ";
	myText += versionNumber;
	
	ret += textAt(margin,       760, myText);

	if(!pubInfo.thetime.empty())
	{
		std::string dateStr;
		dateStr += (lang == LANG_EN) ? "Generate date" : "Generieren Datum";
		dateStr += ": ";
		dateStr += pubInfo.thetime;
		
		ret += textAt(margin,       740, dateStr);		
	}

	if(!pubInfo.accountName.empty())
	{
		ret += textAt(margin,       720, "Keypair name: " + pubInfo.accountName);		
	}

	ret += textAt(margin,       680, (lang == LANG_EN) ? "Bitcoin pubkey " : "Bitcoin-Adresse");

	ret += textAt(margin,       660, pubInfo.pubkey.toString());

	const std::string myEncStr = createEncString(pubInfo, "amount", "message");

	const QRInfo qrinfo = QRInfo::qrencode((const unsigned char*)myEncStr.c_str(), myEncStr.size());

	ret += qrCode(qrinfo, margin, 480, 15.0);

	ret += "Big_font setfont\n";


	ret += textAt(270,       610, "SHARE");
	
	ret += textAt(270,       560, "Encrypt &");
	ret += textAt(270,       510, "verify signature");


	ret += lineBetween(margin, 418, 540, 418);
	
	ret += "Text_font setfont\n";

	return ret;
}






QRInfo PostscriptGenerator::qrEncodeAddress(const std::string& pubkeyVal, const std::string& accountName, 
	const bool useAlphaNumeric)
{
	const std::string urlPrefix = getUrlPrefix();
	std::string encStr(urlPrefix + pubkeyVal);

/*
	if(useAlphaNumeric && accountName.empty())
	{
		std::cout << "Will encode alpha numeric: " << encStr << std::endl;
		const std::string upperStr = toUpper(encStr);
		std::cout << "Will encode alpha numeric upper: " << upperStr << std::endl;
		
		const QRInfo qrinfo = QRInfo::qrencodeAlfaNumeric(upperStr.c_str());
		return qrinfo;		
	}
*/
	
	if(!accountName.empty())
	{
		encStr += "?label=";		
		encStr += urlEncode(accountName);
	}

	const QRInfo qrinfo = QRInfo::qrencode((const unsigned char*)encStr.c_str(), encStr.size());
	return qrinfo;
}



QRInfo PostscriptGenerator::qrEncodeExtendedAddress(const std::string& pub)
{
	const QRInfo qrinfo = QRInfo::qrencode((const unsigned char*)pub.c_str(), pub.size());
	return qrinfo;
}









std::string PostscriptGenerator::publicMnemonic(const PublicExtendedPostscriptInfo& pubInfo, const bool useSmallDescription, 
												const int numWords,
												const std::string& derivedXpub) const
{
	//const bool specifyCurrency(false);
	
	const std::string currencyName = getCurrencyName();
	
	const QRInfo qrinfo = isExtended() ? qrEncodeExtendedAddress(pubInfo.pubkey) :
										qrEncodeAddress(pubInfo.pubkey, pubInfo.accountName);

		
	std::string ret;

	ret += "Titel_font setfont\n";

	ret += textAt(margin,       760, "Mnemonic");
	
	ret += "Text_font setfont\n";


	int yPos(720);
	ret += textAt(margin,       yPos, "Generated by:");
	ret += textAt(margin + 100, yPos, applicationName + " " + versionNumber);
	yPos -= 20;

	if(currencySpecific || !derivedXpub.empty())
	{
		ret += textAt(350,       720, "Currency:");
		ret += textAt(350 + 100, 720, currencyName);		
	}

	ret += textAt(margin,       yPos, "Num words:");
	ret += textAt(margin + 100, yPos, intToString(numWords));		
	yPos -= 20;


	if(!pubInfo.thetime.empty())
	{
		ret += textAt(margin,       yPos, "Generate date:");
		ret += textAt(margin + 100, yPos, pubInfo.thetime);		
		yPos -= 20;
	}

	if(!pubInfo.accountName.empty())
	{
		ret += textAt(margin,       yPos, "Account name:");
		ret += textAt(margin + 100, yPos, pubInfo.accountName);
		yPos -= 20;		
	}


	if(!pubInfo.pubkey.empty())
	{
		//ret += textAt(margin,       670, "xpub:");
		
		const std::pair<std::string, std::string> pubYParts = splitInTwoParts(pubInfo.pubkey);
		
		ret += textAt(margin, 640 /*650*/, pubYParts.first);
		ret += textAt(margin, 625 /*630*/, pubYParts.second);


		ret += generateQRPostscript(pubInfo.pubkey, "xpub", margin, 440, 17.0);
	
	/*
		const QRInfo qrinfo = qrEncodeExtendedAddress(pubInfo.pubkey);

		ret += qrCode(qrinfo, margin, 430, 17.0);
	*/
	}

	if(!derivedXpub.empty())
	{
		//std::cout << "Derived xpub: " << derivedXpub << std::endl;
		const std::string derivationStr = DerivationPath::getCurrencyDerivationPath();
		const std::string infoStr = "derived xpub " + derivationStr;
		ret += generateQRPostscript(derivedXpub, infoStr /*"derived xpub m/44H/zH/0H"*/, margin + 200, 440, 17.0);		
	}


	if(useSmallDescription)
	{
		ret += "Titel_font setfont\n";
	}
	else
	{
		ret += "Big_font setfont\n";
	}
	

	ret += textAt(370 + (useSmallDescription ? 100 : 0), 550, (lang == LANG_EN) ? "SHARE" : "TEILEN");

	ret += "Text_font setfont\n";

	ret += lineBetween(margin, 418, 540, 418);

	return ret;
}






std::string PostscriptGenerator::qrCode(const QRInfo& qrinfo, const int x, const int y, const double scale) //const
{
	std::string ret;
	
	const double scalefactor = scale / double(qrinfo.height());

	
	ret += "gsave ";	
	ret += intToString(x);
	ret += " ";	
	ret += intToString(y);
	ret += " translate ";	
	ret += doubleToString(scalefactor);	
	ret += " ";	
	ret += doubleToString(scalefactor);			
	ret += " scale\n";	
	ret += generateQR(qrinfo);
	ret += "grestore\n";
	
	return ret;
}





std::string PostscriptGenerator::publicPart(const PublicPostscriptInfo& pubInfo, const bool useSmallText) const
{
	//std::cout << "Generating public postscript" << std::endl;
	
	const std::string currencyName = getCurrencyName();

	std::string ret;

	ret += "Titel_font setfont\n";
	
	int yPos(780);

/*	
	if(isExtended())	//Todo: REMOVE
	{
		std::string extAdr;
		if(addrType == ADDRTYPE_EXTENDED)
		{
			extAdr += "Extended address";
		}
		else
		{
			extAdr += "Extended electrum address";			
		}
		
		if(!pubInfo.accountName.empty())
		{
			extAdr += ": ";
			extAdr += pubInfo.accountName;
		}

		
		ret += textAt(margin,       yPos, extAdr);
		yPos -= 20;		
	}
	else
	{
	*/
		//pubkey.empty()
		const std::string pubAddressStr = usesCashAddress() ? pubInfo.pubkey.toCashAddrString() : pubInfo.pubkey.toString();
		const std::string displayAdr; //Empty!!!  // = pubInfo.displayHashOfTime ? "" : pubAddressStr;
				
		ret += textAt(margin,       yPos, (lang == LANG_EN) ? currencyName + " address " + displayAdr : 
													currencyName + "-Adresse " + displayAdr);		
		yPos -= 20;
	//}
	

	ret += "Text_font setfont\n";

	if(!isExtended() || currencySpecific || isElectrum())
	{
		ret += textAt(350,      yPos, "Currency:");
		ret += textAt(350 + 100,yPos, currencyName);
	}


	ret += textAt(margin,       yPos, "Generated by:");
	ret += textAt(margin + 100, yPos, applicationName + " " + versionNumber);
	yPos -= 20;
	



	if(!pubInfo.thetime.empty())
	{
		ret += textAt(margin,        yPos, (lang == LANG_EN) ? "Generate date:" : "Generieren Datum:");
		ret += textAt(margin + 100 , yPos, pubInfo.thetime);
		yPos -= 20;
	}

	if(!pubInfo.accountName.empty())
	{
		ret += textAt(margin,       yPos, "Account name:");
		ret += textAt(margin + 100, yPos, pubInfo.accountName);		
		yPos -= 20;		
	}

/*
	if(isExtended())
	{
		ret += textAt(margin,       yPos, "Derivation path:");
		ret += textAt(margin + 100, yPos, "m");
		yPos -= 20;
		
		const std::pair<std::string, std::string> pubParts = splitInTwoParts(pubInfo.pubkey.toString());
		
		const std::string pubLeft = pubParts.first;
		const std::string pubRight = pubParts.second;

		ret += textAt(margin,       yPos, pubLeft);
		yPos -= 20;
		
		ret += textAt(margin,       yPos, pubRight);	
		yPos -= 20;
	}
	else
	{
	*/
		if(pubInfo.displayHashOfTime)
		{
			ret += textAt(margin,       yPos, "Time hash:");
			//yPos -= 20;				
			
			ret += textAt(margin + 100, yPos, hexString(ripemd160(pubInfo.thetime)).substr(0, 8));
			yPos -= 20;			
		}
		else
		{
			ret += textAt(margin,       yPos, (lang == LANG_EN) ? currencyName + " address " : currencyName + " adresse ");
			yPos -= 20;				

			if(getCurrencyShortName() != "bch_slp")
			{
				ret += textAt(margin, yPos, pubInfo.pubkey.toString());
			}
			yPos -= 20;
			
			if(getCurrencyShortName() == "bch" || getCurrencyShortName() == "bch_slp")
			{
				//ret += textAt(margin,       yPos, currencyName + " cashaddress ");
				//yPos -= 20;				
		
				ret += textAt(margin, yPos, pubInfo.pubkey.toCashAddrString());
				yPos -= 20;			
			}
			
		}

		ret += textAt(margin, 460, (lang == LANG_EN) ? "Amount added:____________" : "Menge zugesetzt:____________");
		ret += textAt(margin + 200, 460, (lang == LANG_EN) ? "Date:__________" : "Datum:______");		
		ret += textAt(margin + 330, 460, (lang == LANG_EN) ? "Spent" : "Verbraucht");


		std::list<Coordinate> coordinates;
		const Coordinate coordinate1(450, 460);
		const Coordinate coordinate2(450, 480);
		const Coordinate coordinate3(470, 480);
		const Coordinate coordinate4(470, 460);
		const Coordinate coordinate5(450, 460);
		
		coordinates.push_back(coordinate1);
		coordinates.push_back(coordinate2);
		coordinates.push_back(coordinate3);
		coordinates.push_back(coordinate4);
		coordinates.push_back(coordinate5);
		
		ret += lineBetweenPoints(coordinates);	
	//}


	if(!pubInfo.displayHashOfTime)	//Address specified
	{
		const QRInfo qrinfo = isExtended() ? qrEncodeExtendedAddress(pubInfo.pubkey.toString()) :
										qrEncodeAddress(pubInfo.pubkey.toString(), pubInfo.accountName);
		const std::string pubLegacyStr = (getCurrencyShortName() == "bch") ? "pub legacy" : "pub";

		if(getCurrencyShortName() != "bch_slp")
		{
			ret += generateQRPostscript(qrinfo, (isExtended() ? "xpub" : pubLegacyStr), margin, isExtended() ? 470 : 500, 15.0);
		}
		
		if(!isExtended() && (getCurrencyShortName() == "bch" || getCurrencyShortName() == "bch_slp"))
		{
			const QRInfo qrinfoCashAddr = qrEncodeAddress(pubInfo.pubkey.toCashAddrString(), pubInfo.accountName, true);			
			
			//Todo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			const std::string displayString = (getCurrencyShortName() == "bch") ? "pub cashaddr" : "pub SLP";
			ret += generateQRPostscript(qrinfoCashAddr, displayString, margin + 200, 500, 15.0);			
		}
		
	}

	//ret += qrCode(qrinfo, margin, extended ? 470 : 500, 15.0);

	if(useSmallText)
	{
		ret += "Titel_font setfont\n";
	}
	else
	{
		ret += "Big_font setfont\n";
	}
	

	ret += textAt(270 + (useSmallText ? 200 : 0), 610, (lang == LANG_EN) ? "SHARE" : "TEILEN");

	ret += textAt(270 + (useSmallText ? 200 : 0), 560, (lang == LANG_EN) ? "Load & verify" : "Laden & prüfen");


	ret += lineBetween(margin, 418, 540, 418);
		
	ret += "Text_font setfont\n";

	return ret;
}




std::string PostscriptGenerator::publicPartExtended(const PublicExtendedPostscriptInfo& pubInfo, const bool useSmallText) const
{
	const std::string currencyName = getCurrencyName();

	std::string ret;

	ret += "Titel_font setfont\n";
	
	int yPos(780);
	
	if(isExtended())
	{
		std::string extAdr;
		if(addrType == ADDRTYPE_EXTENDED)
		{
			extAdr += "Extended address";
		}
		else
		{
			extAdr += "Extended electrum address";			
		}
		
		if(!pubInfo.accountName.empty())
		{
			extAdr += ": ";
			extAdr += pubInfo.accountName;
		}

		
		ret += textAt(margin,       yPos, extAdr);
		yPos -= 20;		
	}
	else
	{
		//pubkey.empty()
		const std::string displayAdr = pubInfo.displayHashOfTime ? "" : pubInfo.pubkey;
				
		ret += textAt(margin,       yPos, (lang == LANG_EN) ? currencyName + " address " + displayAdr : 
													currencyName + "-Adresse " + displayAdr);		
		yPos -= 20;
	}
	

	ret += "Text_font setfont\n";

	if(!isExtended() || currencySpecific || isElectrum())
	{
		ret += textAt(350,      yPos, "Currency:");
		ret += textAt(350 + 100,yPos, currencyName);
	}


	ret += textAt(margin,       yPos, "Generated by:");
	ret += textAt(margin + 100, yPos, applicationName + " " + versionNumber);
	yPos -= 20;
	



	if(!pubInfo.thetime.empty())
	{
		ret += textAt(margin,        yPos, (lang == LANG_EN) ? "Generate date:" : "Generieren Datum:");
		ret += textAt(margin + 100 , yPos, pubInfo.thetime);
		yPos -= 20;
	}

	if(!pubInfo.accountName.empty())
	{
		ret += textAt(margin,       yPos, "Account name:");
		ret += textAt(margin + 100, yPos, pubInfo.accountName);		
		yPos -= 20;		
	}


	if(isExtended())
	{
		ret += textAt(margin,       yPos, "Derivation path:");
		ret += textAt(margin + 100, yPos, "m");
		yPos -= 20;
		
		const std::pair<std::string, std::string> pubParts = splitInTwoParts(pubInfo.pubkey);
		
		const std::string pubLeft = pubParts.first;
		const std::string pubRight = pubParts.second;

		ret += textAt(margin,       yPos, pubLeft);
		yPos -= 20;
		
		ret += textAt(margin,       yPos, pubRight);	
		yPos -= 20;
	}
	else
	{
		if(pubInfo.displayHashOfTime)
		{
			ret += textAt(margin,       yPos, "Time hash:");
			//yPos -= 20;				
			
			ret += textAt(margin + 100, yPos, hexString(ripemd160(pubInfo.thetime)).substr(0, 8));
			yPos -= 20;			
		}
		else
		{
			ret += textAt(margin,       yPos, (lang == LANG_EN) ? currencyName + " address " : currencyName + " adresse ");
			yPos -= 20;				
		
			ret += textAt(margin, yPos, pubInfo.pubkey);
			yPos -= 20;
		}

		ret += textAt(margin, 460, (lang == LANG_EN) ? "Amount added:____________" : "Menge zugesetzt:____________");
		ret += textAt(margin + 200, 460, (lang == LANG_EN) ? "Date:__________" : "Datum:______");		
		ret += textAt(margin + 330, 460, (lang == LANG_EN) ? "Spent" : "Verbraucht");


		std::list<Coordinate> coordinates;
		const Coordinate coordinate1(450, 460);
		const Coordinate coordinate2(450, 480);
		const Coordinate coordinate3(470, 480);
		const Coordinate coordinate4(470, 460);
		const Coordinate coordinate5(450, 460);
		
		coordinates.push_back(coordinate1);
		coordinates.push_back(coordinate2);
		coordinates.push_back(coordinate3);
		coordinates.push_back(coordinate4);
		coordinates.push_back(coordinate5);
		
		ret += lineBetweenPoints(coordinates);	
	}


	if(!pubInfo.displayHashOfTime)	//Address specified
	{
		const QRInfo qrinfo = isExtended() ? qrEncodeExtendedAddress(pubInfo.pubkey) :
										qrEncodeAddress(pubInfo.pubkey, pubInfo.accountName);

		ret += generateQRPostscript(qrinfo, (isExtended() ? "xpub" : "pub"), margin, isExtended() ? 470 : 500, 15.0);
		
		if(!isExtended() && (getCurrencyShortName() == "bch" || getCurrencyShortName() == "bch_slp"))
		{
			const QRInfo qrinfoCashAddr = qrEncodeAddress(pubInfo.pubkey, pubInfo.accountName);			
			
			//Todo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			ret += generateQRPostscript(qrinfo, "pub cashaddr", margin + 200, 500, 15.0);			
		}
		
	}

	//ret += qrCode(qrinfo, margin, extended ? 470 : 500, 15.0);

	if(useSmallText)
	{
		ret += "Titel_font setfont\n";
	}
	else
	{
		ret += "Big_font setfont\n";
	}
	

	ret += textAt(270 + (useSmallText ? 200 : 0), 610, (lang == LANG_EN) ? "SHARE" : "TEILEN");

	ret += textAt(270 + (useSmallText ? 200 : 0), 560, (lang == LANG_EN) ? "Load & verify" : "Laden & prüfen");


	ret += lineBetween(margin, 418, 540, 418);
		
	ret += "Text_font setfont\n";

	return ret;
}








std::string PostscriptGenerator::hierPriv(const std::string& privIndex, 
	const HierarcialInfo& hierarcialInfo,
	const std::string& pubAddr) const
{
	std::string ret;
	Language lang = LANG_EN;

	ret += textAt(margin,       380, (lang == LANG_EN) ? "Raw private index" : "Privater Schlüssel");

	const std::string privIndexStart = privIndex.substr(0, 32);
	const std::string privIndexEnd = privIndex.substr(32);


	ret += textAt(margin, 360, privIndexStart);
	ret += textAt(margin, 340, privIndexEnd);
		
	ret += textAt(margin, 260, "Should be combined with the private key corresponding to signature");
	
	ret += textAt(margin, 240, hierarcialInfo.signature);

	ret += textAt(margin, 220, "Command:");


	std::string theCommand;
	theCommand += "bitgen";

	const std::string currencyShortName = getCurrencyShortName();
	
	if(currencyShortName != "btc")
	{
		theCommand += "-";
		theCommand += currencyShortName;
	}
	
	
	theCommand += " genPriv root";
	theCommand += currencyShortName;
	theCommand += "_";
	theCommand += hierarcialInfo.signature;
	theCommand += "_priv.privroot ";


	ret += textAt(margin, 200, theCommand);

	ret += textAt(margin + 20, 180, pubAddr + ".privindex");

	ret += textAt(margin, 140, (lang == LANG_EN) ? "PubX" : "Privater Schlüssel");

	const std::string pubXstart = hierarcialInfo.pubX.substr(0, 32);
	const std::string pubXend = hierarcialInfo.pubX.substr(32);


	ret += textAt(margin, 120, pubXstart);

	ret += textAt(margin, 100, pubXend);

	ret += textAt(margin, 80, "PubY");

	const std::string pubYstart = hierarcialInfo.pubY.substr(0, 32);
	const std::string pubYend = hierarcialInfo.pubY.substr(32);


	ret += textAt(margin, 60, pubYstart);
	ret += textAt(margin, 40, pubYend);
	
	ret += "Big_font setfont\n";

	ret += textAt(270, 300, (lang == LANG_EN) ? "CONFIDENTIAL" : "GEHEIMNIS");
	
	ret += "Text_font setfont\n";

	return ret;	 
}





std::string PostscriptGenerator::addExtraTextLine(const int yPos, const std::string& thisPart, const int extraXindent) const
{
	std::string ret;
	
	ret += textAt(margin + extraXindent, yPos, thisPart);

	return ret;
}


/*
std::list<std::string> PostscriptGenerator::splitLongLineOnWordBoundry(const std::string& str)
{
	//std::cout << "Splitting line: " << str << std::endl;
	
	std::list<std::string> ret;
	std::string thisPart;
	for(int i = 0 ; i < str.size() ; i++)
	{
		const char c = str[i];
		thisPart += c;
		
		if(c == ' ' && thisPart.size() > 50)
		{
			ret.push_back(thisPart);
			thisPart = "";
		}
	}
	
	if(!thisPart.empty())
	{
		ret.push_back(thisPart);		
	}
	
	return ret;
}
*/


std::list<std::string> PostscriptGenerator::splitLongLine(const std::string& str, const bool splitWordBoundry)
{
	//std::cout << "Splitting line: " << str << std::endl;
	
	std::list<std::string> ret;
	std::string thisPart;
	for(int i = 0 ; i < str.size() ; i++)
	{
		const char c = str[i];
		thisPart += c;
		
		if(splitWordBoundry)
		{
			if(c == ' ' && thisPart.size() > 50)
			{
				ret.push_back(thisPart);
				thisPart = "";
			}			
		}
		else
		{
			if(thisPart.size() > 40)
			{
				ret.push_back(thisPart);
				thisPart = "";
			}
		}
	}
	
	if(!thisPart.empty())
	{
		ret.push_back(thisPart);		
	}
	
	return ret;
}




std::string PostscriptGenerator::privateKeyPart(const PrivatePostscriptInfo& privInfo) const
{
	std::string ret;

	std::string privText;
	privText +=  ((lang == LANG_EN) ? "Private key" : "Privater Schlüssel");
	privText += " (WIF, Wallet Import Format)";
	
	ret += textAt(270,       350, privText);

	ret += textAt(margin,       390, privInfo.privkey);

	
	std::string genText;
	genText += (lang == LANG_EN) ? "Generation method" : "Erzeugungsverfahren";
	genText += ": ";
	genText += privInfo.generationMethod;
	
	ret += textAt(270,       220, genText);
	
	ret += textAt(270,       200, (privInfo.compressed) ? "Compressed format" : "Uncompressed format");

	int yPos(90);
	for(std::list<ExtraInfo>::const_iterator it = privInfo.generationExtra.begin() ;
		it != privInfo.generationExtra.end() ;
		++it)
	{
		const ExtraInfo& thisExtra = (*it);
		const std::string& thisPart = thisExtra.value;
		std::list<std::string> smallParts = splitLongLine(thisPart);
		
		for(std::list<std::string>::const_iterator jt = smallParts.begin() ;
			jt != smallParts.end() ;
			++jt)
		{
			const std::string& smallPart = (*jt);
			ret += addExtraTextLine(yPos, smallPart);
			yPos -= 20;
		}
	}




	ret += "Big_font setfont\n";


	ret += textAt(270,       300, (lang == LANG_EN) ? "SECRET" : "GEHEIMNIS");

	ret += textAt(270,       250, "Decrypt & sign");
	
	ret += "Text_font setfont\n";


	const std::string myEncStr = createPrivateEncString(privInfo);
	const QRInfo privinfo = QRInfo::qrencode((const unsigned char*)myEncStr.c_str(), myEncStr.size());
	ret += qrCode(privinfo, margin, 210, 20.0);

	return ret;
}


std::list<std::string> PostscriptGenerator::splitMnemonic(const std::string& mnemonic, const int spacesPerPart)
{
	std::list<std::string> ret;

	int numSpace(0);
	int i(0);
	int lastPos(0);
	for( ; i < mnemonic.size() ; i++)
	{
		if(mnemonic[i] == ' ')
		{
			numSpace++;
			if(numSpace % spacesPerPart == 0)
			{
				const std::string part = mnemonic.substr(lastPos, i - lastPos);
				ret.push_back(part);
				lastPos = i + 1;				
			}
			//else if(numSpace == 16)
			//{
			//	break;
			//}

		}
	}
	
	const std::string lastPart = mnemonic.substr(lastPos, i - lastPos);
	ret.push_back(lastPart);

	return ret;
}


std::string PostscriptGenerator::generateQRPostscriptWithText(const QRInfo& qrinfo, 
											const std::string& lowerStr, const std::string& upperStr,
											const int x, const int y, const double scale) 
{		
	std::string ret;
	
	ret += qrCode(qrinfo, x, y, scale);
	ret += "Small_font setfont\n";
	ret += textAt(x, y - 10, lowerStr);
	ret += "Tiny_font setfont\n";	
	ret += textAt(x, y + 160, upperStr);
	
	return ret;
}



std::string PostscriptGenerator::generateQRPostscript(const QRInfo& qrinfo, const std::string& txtStr, 
											const int x, const int y, const double scale) 
{		
	std::string ret;
	
	ret += qrCode(qrinfo, x, y, scale);
	ret += "Small_font setfont\n";
	ret += textAt(x, y - 10, txtStr);
	
	return ret;
}


std::string PostscriptGenerator::generateQRPostscript(const std::string& qrStr, const std::string& txtStr, 
											const int x, const int y, const double scale) 
{		
	const QRInfo qrinfo = QRInfo::qrEncodeWif(qrStr);		
	
	return generateQRPostscript(qrinfo, txtStr, x, y, scale) ;
}





std::string PostscriptGenerator::privateMnemonic(const std::string mnemonic, const std::string& generationMethod,
	const std::list<ExtraInfo>& generationExtra, const std::string& xpriv) const
{
	
	std::string ret;

	const std::pair<std::string, std::string> privParts = splitInTwoParts(xpriv);

	ret += textAt(margin, 390, privParts.first);
	ret += textAt(margin, 370, privParts.second);

	int ypos(160);

/*
	ret += textAt(margin,       160, "Text words:");
	ret += textAt(margin + 100, 160, intToString(numWords));
*/	
	ret += textAt(margin,       ypos, "Gen method:");	
	ret += textAt(margin + 100, ypos, generationMethod);	
	ypos -= 20;

	//int ypos(120);


	const std::string mnemonicText = ( (addrType == ADDRTYPE_ELECTRUM) ? "EMnemonic:" : "Mnemonic:");
	ret += textAt(margin, ypos, mnemonicText);	

	ypos -= 25;

	//Todo: Use
	//std::cout << "Will split mnemonic" << std::endl;
	std::list<std::string> mnemonicParts = splitMnemonic(mnemonic, 8);

	//std::cout << "Ready splitting mnemonic" << std::endl;

	int wordNum(1);
	const int tabSize(0);

	for(const std::string& part : mnemonicParts)
	{
		const std::list<std::string> words = splitMnemonic(part, 1);	//Split into words

		int i(0);
		for(const std::string& word : words)
		{	
			ret += textAt(margin + tabSize + (i * 63), ypos, word);	
			
			ret += "Tiny_font setfont\n";
			ret += textAt(margin + tabSize + (i * 63), ypos + 12, intToString(wordNum));				
			ret += "Text_font setfont\n";			
			i++;
			wordNum++;
		}
		
		ypos -= 25;
	}


	for(std::list<ExtraInfo>::const_iterator it = generationExtra.begin() ;
		it != generationExtra.end() ;
		++it)
	{
		const ExtraInfo& extraInfo = (*it);
		const std::string totTitle(extraInfo.title + ":");
		ret += addExtraTextLine(ypos, totTitle);
		//yPos -= 20;
		
		const std::string& value = extraInfo.value;
		std::list<std::string> smallParts = splitLongLine(value);
		
		for(std::list<std::string>::const_iterator jt = smallParts.begin() ;
			jt != smallParts.end() ;
			++jt)
		{
			const std::string& smallPart = (*jt);
			ret += addExtraTextLine(ypos, smallPart, 100);
			ypos -= 20;
		}
	}


	const bool hasXPriv = !xpriv.empty();

	if(hasXPriv)
	{
		ret += generateQRPostscript(xpriv, "xpriv", margin, 190, 17.0);		
	}


	ret += textAt(370 + (hasXPriv ? 100 : 0), 350, (lang == LANG_EN) ? "Private mnemonic" : "Privater mnemonic");

	if(hasXPriv)
	{
		ret += "Titel_font setfont\n";
	}
	else
	{
		ret += "Big_font setfont\n";		
	}

	ret += textAt(370 + (hasXPriv ? 100 : 0), 300, (lang == LANG_EN) ? "SECRET" : "GEHEIMNIS");
	ret += textAt(370 + (hasXPriv ? 100 : 0), 250, (lang == LANG_EN) ? "Spend" : "Verbringen");

	ret += "Text_font setfont\n";

	ret += generateQRPostscript(mnemonic, "mnemonic", margin + 200, 190, 17.0);
	
	return ret;
}










std::string PostscriptGenerator::privatePart(const PrivatePostscriptInfo& privInfo) const
{
	
	std::string ret;

/*
	std::string text = (lang == LANG_EN) ? "Private key" : "Privater Schlüssel";
	
	if(!extended)
	{
		text += " (WIF, Wallet Import Format)";
	}


	ret += textAt(270, 350, text);
*/

		

	if(isExtended())
	{
		const std::pair<std::string, std::string> privkeyParts = splitInTwoParts(privInfo.privkey);

		const std::string privLeft = privkeyParts.first;
		const std::string privRight = privkeyParts.second;
	
		ret += textAt(margin, 390, privLeft);
		ret += textAt(margin, 370, privRight);		
	}
	else
	{
		if(privInfo.isPad)	
		{
			const std::string padTxt = "PAD " + intToString(privInfo.padNum) + "/" + 
				intToString(privInfo.totalPads); // + ":";
			ret += textAt(margin + 400, 390, padTxt);		
			
			const std::pair<std::string, std::string> parts = splitInTwoParts(privInfo.privkey);
			ret += textAt(margin, 390, parts.first);
			ret += textAt(margin, 370, parts.second);	

			ret += "Small_font setfont\n";
			ret += textAt(margin, 200, privInfo.privkey);
			ret += "Text_font setfont\n";								
		}
		else
		{
			ret += textAt(margin, 390, privInfo.privkey);
		}
	}


	int yPosition(180);
	
	if(!isExtended())
	{
		ret += textAt(margin + 100 + 200, yPosition, (privInfo.compressed) ? "Compressed format" : "Uncompressed format");		
	}


	std::string printText;
	printText += ((lang == LANG_EN) ? "Gen method" : "Erzeugungsverfahren");
	printText += ":";


	const BigInt<256> zero;

	const std::string hashBin = staticXorHash(privInfo.staticXor);
	const std::string hashStr = hexString(hashBin);

	const std::string staticExtra = ((privInfo.staticXor != zero) ? " with static XOR (" + hashStr + ")": "");
	

	ret += textAt(margin,       yPosition, printText);
	ret += textAt(margin + 100, yPosition, privInfo.generationMethod + staticExtra);
	yPosition -= 20;


	if(!isExtended())
	{
		const std::string mnemonicText = ( (addrType == ADDRTYPE_ELECTRUM) ? "EMnemonic:" : "Mnemonic:");		
		ret += textAt(margin, yPosition, mnemonicText);		
		yPosition -= 20;
	
		const std::list<std::string> mnemonicParts = splitMnemonic(privInfo.mnemonic, 8);

		int wordNum(1);

		for(const std::string& part : mnemonicParts)
		{
			int i(0);
			const std::list<std::string> words = splitMnemonic(part, 1);
			
			for(const std::string& word : words)
			{
				ret += textAt(margin + (i * 63), yPosition, word);
			
				ret += "Tiny_font setfont\n";
				ret += textAt(margin + (i * 63), yPosition + 12, intToString(wordNum));				
				ret += "Text_font setfont\n";			
			
				i++;
				wordNum++;
			}		
			yPosition -= 25;
		}
	}


	for(std::list<ExtraInfo>::const_iterator it = privInfo.generationExtra.begin() ;
		it != privInfo.generationExtra.end() ;
		++it)
	{
		const ExtraInfo& extraInfo = (*it);
		const std::string totTitle(extraInfo.title + ":");
		ret += addExtraTextLine(yPosition, totTitle);
		
		const std::string& value = extraInfo.value;
		std::list<std::string> smallParts = splitLongLine(value, extraInfo.splitWords);
		
		for(std::list<std::string>::const_iterator jt = smallParts.begin() ;
			jt != smallParts.end() ;
			++jt)
		{
			const std::string& smallPart = (*jt);
			ret += addExtraTextLine(yPosition, smallPart, 100);
			yPosition -= 20;
		}
	}


	const bool hasMnemonic = !privInfo.mnemonic.empty();

	if(hasMnemonic)
	{
		ret += "Titel_font setfont\n";
	}
	else
	{
		ret += "Big_font setfont\n";
	}


	ret += textAt(270 + (hasMnemonic ? 200 : 0), 300, (lang == LANG_EN) ? "SECRET" : "GEHEIMNIS");
		
	ret += textAt(270 + (hasMnemonic ? 200 : 0), 250, (lang == LANG_EN) ? "Spend" : "Verbringen");
	

	ret += "Text_font setfont\n";

	//const std::string privEncStr(privInfo.privkey);
	//const QRInfo privkeyQR = QRInfo::qrEncodeWif(privEncStr);



	if(isExtended())
	{
		if(hasMnemonic)
		{
			const std::string mnemonicText = ( (addrType == ADDRTYPE_ELECTRUM) ? "Electrum mnemonic" : "mnemonic");
			
			ret += generateQRPostscript(privInfo.mnemonic, mnemonicText, margin + 200, 190, 15.0);
		}
		//else
		//{
		//	std::cout << "DOES NOT HAVE MNEMONIC" << std::endl;
		//}
		
		ret += generateQRPostscript(privInfo.privkey, "xpriv", margin, 190, 15.0);
		
		//ret += qrCode(privkeyQR, margin, 190, 15.0);		
	}
	else
	{
		if(privInfo.hasBip39Mnemonic())
		{
			ret += generateQRPostscript(privInfo.mnemonic, "BIP 39 mnemonic", margin + 210, 210, 15.0);
		}
		
		if(privInfo.isPad)
		{
			//const std::string qrText = std::string("pad:") + privInfo.privkey;
			//ret += generateQRPostscript(qrText, qrText, margin, 210, 15.0);
		}
		else
		{
			ret += generateQRPostscript(privInfo.privkey, "wif", margin, 210, 15.0);
		}
		
		//ret += qrCode(privkeyQR, margin, 210, 15.0);				
	}

	return ret;
}




std::string PostscriptGenerator::staticXorInfo(const std::string& thetime, const BigInt<256>& staticXor) const
{
	std::string ret;

	const std::string hash = staticXorHash(staticXor);

	ret += "Text_font setfont\n";
	const int columnWidth(100);

	const std::string header = "Static XOR " + hexString(hash);
	
	ret += textAt(margin, 720, header);
	//ret += textAt(margin + columnWidth, 680, hexString(hash));

	const std::string bitgenVersion = applicationName + " " + versionNumber;

	ret += textAt(margin, 700, "Generated by:");
	ret += textAt(margin + columnWidth, 700, bitgenVersion);

	ret += textAt(margin, 680, "Generate date:");
	ret += textAt(margin + columnWidth, 680, thetime);


	ret += textAt(margin, 660, "Hash: ");
	ret += textAt(margin + columnWidth, 660, hexString(hash));

	ret += "Big_font setfont\n";

	ret += textAt(margin, 440, "SECRET");

	ret += textAt(margin, 400, "STATIC XOR");

	ret += "Text_font setfont\n";


	ret += textAt(margin, 360, "This static xor key is used to generate split wallets.");
	ret += textAt(margin, 340, "To be able to recreate a private key the split xor key MUST BE PRESENT.");
	ret += textAt(margin, 320, "It is very important that this private xor key is securely stored");
	
	
	const std::string xorStrFull = hexString(staticXor.getBinaryLong());
	const std::pair<std::string, std::string> xorParts = splitInTwoParts(xorStrFull);

	
	ret += textAt(margin, 260, xorParts.first);
	ret += textAt(margin, 240, xorParts.second);


	return ret;
}




std::string PostscriptGenerator::generateStaticXor(
	const std::string& thetime, const BigInt<256>& staticXor) const
{
	const int margin(70);
	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	
	ret += staticXorInfo(thetime, staticXor);
	
	ret += endPage();
	
	ret += "%%EOF\n";
	return ret;
}




std::string PostscriptGenerator::generatePrivateRoot(
	const HierarcialInfo& hierarcialInfo,
	const std::string& thetime, const std::string& label,
	const std::string& privIndex) const
{
	const int margin(70);
	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	const PubAddress pubDummy("dummyPubVal", true);
	const PublicPostscriptInfo pubInfo(pubDummy /*"dummyPubVal"*/, thetime, "accountName");
	
	ret += publicRoot(hierarcialInfo, pubInfo, label);
	
	ret += privateRoot(privIndex, hierarcialInfo.signature);
	
	ret += endPage();
	
	ret += "%%EOF\n";
	return ret;
}




std::string PostscriptGenerator::generatePublicRoot(const HierarcialInfo& hierarcialInfo,
	const PublicPostscriptInfo& pubInfo, const std::string& label) const
{
	const int margin(70);
	
	std::string ret;

	ret += intro();
	
	ret += beginPage();

	ret += publicRoot(hierarcialInfo, pubInfo, label);
	
	ret += endPage();
	
	ret += "%%EOF\n";
	return ret;
}




std::string PostscriptGenerator::postscriptRequestPaymentPage(
							const PublicPostscriptInfo& pubInfo,
							const std::string& amount,
							const std::string& message) const
{		
	std::string ret;

	ret += intro();
	
	ret += beginPage();
		
	ret += generatePaymentRequest(pubInfo, amount, message);
	
	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}






std::string PostscriptGenerator::generateInvoice(const PublicPostscriptInfo& pubInfo,
								const std::string amount, const std::string& message) const
{		
	std::string ret;

	ret += intro();
	
	ret += beginPage();
		
	ret += generatePaymentRequest(pubInfo, amount, message);
	
	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}



std::string PostscriptGenerator::privateHierarcialPrivate(
							const std::string& privIndex,
							const PublicPostscriptInfo& pubInfo,
							const HierarcialInfo& hierarcialInfo
							) const
{		
	std::string ret;

	ret += intro();
	
	ret += beginPage();
		
	ret += publicPart(pubInfo, true);
	
	ret += hierPriv(privIndex, hierarcialInfo, pubInfo.pubkey.toString());
	
	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}



std::string PostscriptGenerator::postscriptPagePublic(const PublicPostscriptInfo& pubInfo) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
		
	ret += publicPart(pubInfo, true);
	
	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}



std::string PostscriptGenerator::postscriptPagePublicExtended(const PublicExtendedPostscriptInfo& pubInfo) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
		
	ret += publicPartExtended(pubInfo, true);
	
	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}



std::string PostscriptGenerator::postscriptPagePublicKey(const PublicPostscriptInfo& pubInfo) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	ret += publicKeyPart(pubInfo);
	
	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}





std::string PostscriptGenerator::pubPrivPairPostscriptPage(
							const bool isPrivate, 
							const PrivatePostscriptInfo& privInfo,
							const PublicPostscriptInfo& pubInfo
							) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	ret += publicKeyPart(pubInfo);
	
	//std::cout << "Will start with private part" << std::endl;
	if(isPrivate)
	{
		ret += privateKeyPart(privInfo);
	}

	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}




std::string PostscriptGenerator::generatePublicMnemonic(const std::string mnemonic, const int numWords, 
	const std::string& accountName,	
	const std::string& generationMethod,
	const std::string& theTime, const std::list<ExtraInfo>& generationExtra,
	const std::string& xpriv,
	const ExtendedPublicKey /*std::string*/& xpub,
	const std::string& derivedXpub) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	const PublicExtendedPostscriptInfo pubInfo(xpub.toString(), theTime, accountName);
	
	const bool useSmallDescription = !xpriv.empty();
	ret += publicMnemonic(pubInfo, useSmallDescription, numWords, derivedXpub);
	
	//ret += privateMnemonic(mnemonic, numWords, generationMethod, generationExtra, xpriv);

	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}



std::string PostscriptGenerator::generatePrivateMnemonic(const std::string mnemonic, const int numWords, 
	const std::string& accountName,	
	const std::string& generationMethod,
	const std::string& theTime, const std::list<ExtraInfo>& generationExtra,
	const std::string& xpriv,
	const ExtendedPublicKey /*std::string*/& xpub,
	const std::string& derivedXpub) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	const PublicExtendedPostscriptInfo pubInfo(xpub.toString(), theTime, accountName);
	
	const bool useSmallDescription = !xpriv.empty();
	ret += publicMnemonic(pubInfo, useSmallDescription, numWords, derivedXpub);
	
	ret += privateMnemonic(mnemonic, generationMethod, generationExtra, xpriv);

	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}






std::string PostscriptGenerator::generatePrivate(
							const bool isPrivate, 
							const PrivatePostscriptInfo& privInfo,
							const PublicPostscriptInfo& pubInfo
							) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	const bool useSmallText = !privInfo.mnemonic.empty();
	ret += publicPart(pubInfo, useSmallText);
	
	if(isPrivate)
	{
		ret += privatePart(privInfo);
	}

	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}




std::string PostscriptGenerator::generatePrivateExtended(
							const bool isPrivate, 
							const PrivatePostscriptInfo& privInfo,
							const PublicExtendedPostscriptInfo& pubInfo
							) const
{	
	std::string ret;

	ret += intro();
	
	ret += beginPage();
	
	const bool useSmallText = !privInfo.mnemonic.empty();
	ret += publicPartExtended(pubInfo, useSmallText);
	
	if(isPrivate)
	{
		ret += privatePart(privInfo);
	}

	ret += endPage();
	
	ret += "%%EOF\n";

	return ret;
}








