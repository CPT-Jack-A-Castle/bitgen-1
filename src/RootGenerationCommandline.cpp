


#include "GenerationMethods.h"
#include "randomUtils.h"
#include "HierarchialRandom.h"
#include "random.h"
#include "FileUtil.h"
#include "language.h"
#include "printPS.h"
#include "bitgenVersion.h"


#include <iostream>


#include "RootGenerationCommandline.h"


void HierarcialRandomCommandline::generateRootKey(const std::string& theTime, int argc, char* argv[])
{
	std::string label;
	
	if(argc < 3)
	{
		std::cout << "Generation method not given. For example random, hash, etc" << std::endl;
		throw std::string("Generation method must be given");
	}
	
	const std::string genMethod = argv[2];
	std::cout << "Generation method: " << genMethod << std::endl;
	

	
	if(genMethod == "random")
	{
		const bool compressed(true);	//C!
	if(argc >= 4)
	{
		label = argv[3];
		std::cout << "Label: " << label << std::endl;
	}
	
	GenerationMethods::printRandomSourceWarning();
		
	std::cout << std::endl;
	std::cout << "Press random keys or move the mouse if needed" << std::endl;
		

	//Todo: Use other random sources as well
	const std::string random = getFromDevRandom(32);
		
	const BigInt<256> privKeyR(random, 'c');
	generateHierarchialRootKey(privKeyR, theTime, label, compressed);
	}
	else if(genMethod == "dice")
	{
		const bool compressed(true);	//C!
		if(argc < 4)
		{
			std::cout << "Usage: bitgen genRoot dice digits(1-6)" << std::endl;
			return;			
		}
		
		const std::string dice(argv[3]);
		if(dice.size() != 100)
		{
			std::string errMsg("Need exactly 100 dice throws, got: ");
			errMsg += intToString(dice.size());
			errMsg += " throws";
			
			throw errMsg;
			
			//std::cerr << "Need exactly 100 dice throws, got: " << dice.size() << " throws" << std::endl;
			//return;
		}

		//std::string label;
		if(argc > 4)
		{
			label = argv[4];
		}

		std::cout << "Generating bitcoin address from dice, got " << dice.size() << " throws" << std::endl;
		std::cout << "Dice result (1-6): " << dice << std::endl;
		
		const BigInt<256> privKeyR = getRandomNumFrom6SideDice(dice);		
		generateHierarchialRootKey(privKeyR, theTime, label, compressed);
	}
	else
	{
		std::cout << "Unknown generation method: " << genMethod << std::endl;
	}	
}






void HierarcialRandomCommandline::generatePublicFromRoot(int argc, char* argv[], const std::string& thetime)
{		
	const bool compressed(true);	//C!
	
	bool printAll(false);

	if(argc < 3)
	{
		throw std::string("pubroot filename must be given");
	}
		
	std::string pubRootFile = argv[2];

	if(!endsWith(pubRootFile, ".pubroot"))
	{
		throw std::string("Error, file name must end with .pubroot");
	}


	std::string accountName;
	if(argc > 3)
	{
		accountName = argv[3];
		std::cout << "Account name: " << accountName << std::endl;
	}



	std::cout << "Getting random number" << std::endl;
	const std::string random = getFromDevRandom(32);
		
	const BigInt<256> keyInd(random, 'c');
	const BigInt<257> keyIndex(BigInt<257>::asPositive(keyInd));
		
	//PrivKey priv(privKeyR);

	//std::cout << "Index: " << keyIndex << std::endl;

	//std::string privFileContent(hexString(privKeyR.getBinaryVal()) + "\n" + keypair.privaddr.address);

		
	//std::cout << "Reading: " << pubRootFile << std::endl;
	const std::string pubStr = readFile(pubRootFile);
		 
	 //Parse the content
	const int newlinepos = pubStr.find("\n");
	if(newlinepos == std::string::npos)
	{
		throw std::string("Could not parse file, no newline found");
	}
	const std::string pubkeyX = pubStr.substr(0, newlinepos);
		
		
	//std::cout << "The pub key X string: " << pubkeyXHex << std::endl;
		
		
	const BigInt<1024> pubKeyXRoot = BigInt<1024>::fromHex(pubkeyX);
	//std::cout << "PubX val: " << pubKeyXRoot << std::endl;


	const int newlinepos2 = pubStr.find("\n", newlinepos + 1);
	if(newlinepos2 == std::string::npos)
	{
		throw std::string("Could not parse file, newline #2 not found");
	}
	const int yStart = newlinepos + 1;
	
	
	//Todo: Use compressed format, store only X
	
	const std::string pubkeyY = pubStr.substr(yStart, newlinepos2 - yStart);
	//std::cout << "Ykoord: " << pubkeyY << std::endl;		
	//std::cout << "The pub key Y string: " << pubkeyYHex << std::endl;
		
		
	const BigInt<1024> pubKeyYRoot = BigInt<1024>::fromHex(pubkeyY);
	//std::cout << "PubY val: " << pubKeyYRoot << std::endl;


	BitcoinEllipticCurve myec;

	ECPoint PublicKeyRoot = myec.fromCoordinates(pubKeyXRoot, pubKeyYRoot);

	//ECPoint PublicKeyRoot(pubKeyXRoot, pubKeyYRoot);

	//std::cout << "The root public key: " << std::endl << PublicKeyRoot << std::endl;


	//const PubAddress rootPub = pubPointTob58(PublicKeyRoot);
	const PubKey mypub(PublicKeyRoot, compressed);
	const PubAddress rootPub = mypub.getAddress();
	
	//const PubAddress rootPub = PubAddress::bitcoinAddresFromPubkey(PublicKeyRoot, compressed);
		
	const std::string digest = sha256(rootPub.toString()).substr(0,4);
		
	const std::string currencyShortName = getCurrencyShortName();
		
	const std::string filePrefix = std::string("root") + currencyShortName + "_" + hexString(digest);
	//std::cout << "filePrefix: " << filePrefix << std::endl;


	const BigInt<256> privAdd(keyIndex);
	const PrivKey myPrivKey(privAdd, compressed);
	const ECPoint PrivKeyAdd = myPrivKey.point(myec);
			
	const ECPoint myPublic = myec.add(PublicKeyRoot, PrivKeyAdd);
		
	const PubKey thepub(myPublic, compressed);
	const PubAddress pub = thepub.getAddress();
		
	//const PubAddress pub = PubAddress::bitcoinAddresFromPubkey(myPublic, compressed);
		

	std::cout << "PUB: " << pub << std::endl;

	const std::string fileName(pub.toString() + ".privindex");
	std::cout << "Will save file: " << fileName << std::endl;
	fileWrite(fileName, keyIndex.strHex());


	//const std::list<std::string> not_used_printExtra;

	const Language lang = getLanguage();
	const PostscriptGenerator postscriptGenerator(versionNumber, applicationName, lang);
		
	const PublicPostscriptInfo pubInfo(pub/*.toString()*/, thetime, accountName);
		

	const HierarcialInfo hierarcialInfo(hexString(digest), pubkeyX, pubkeyY);	

	//postscriptGenerator.savePrivateHierarcialFile(hexString(digest), 
	//	hexString(privAdd.getBinaryLong()), pub.toString(), pubInfo, hierarcialInfo);
			
	const std::string psPublic = postscriptGenerator.privateHierarcialPrivate(
				/*hexString(digest),*/ hexString(privAdd.getBinaryLong()), pubInfo, hierarcialInfo);
	
	const std::string pubFilename =  pubInfo.pubkey.toString() + "_priv.ps";
	std::cout << "Saving privfile: " << pubFilename << std::endl;
	fileWrite(pubFilename, psPublic);
			
}







void HierarcialRandomCommandline::generatePrivateFromRoot(int argc, char* argv[], const std::string& thetime)
{		
	const bool compressed(true);	//C!
		bool printAll(false);

		if(argc < 3)
		{
			std::cout << "Usage: bitgen hipriv privrootfile privindexfile" << std::endl;
			throw std::string("Priv root filename must be given");
		}
		
		std::string privateRootFile = argv[2];

		if(!endsWith(privateRootFile, ".privroot"))
		{
			throw std::string("Error, file name must end with .privroot");
		}


		if(argc < 4)
		{
			std::cout << "Usage: bitgen hipriv privrootfile privindexfile" << std::endl;			
			throw std::string("privindex filename must be given");
		}


		const std::string privIndexFile = argv[3];
		if(!endsWith(privIndexFile, ".privindex"))
		{
			throw std::string("Error, index file must have extension .privindex");
		}

		//const int keyIndex = atoi(argv[3]);
		//std::cout << "Using index: " << keyIndex << std::endl;
		//const int keyIndex(0);

		//std::string privFileContent(hexString(privKeyR.getBinaryVal()) + "\n" + keypair.privaddr.address);

		
		std::cout << "Reading: " << privateRootFile << std::endl;
		const std::string privStr = readFile(privateRootFile);
		 
		 //Parse the content
		const int newlinepos = privStr.find("\n");
		if(newlinepos == std::string::npos)
		{
			throw std::string("Could not parse file, no newline found");
		}
		const std::string privkey = privStr.substr(0, newlinepos);
		
		//std::cout << "The priv key string: " << privkeyHex << std::endl;
		
		
		const BigInt<256> privKeyRoot = BigInt<256>::fromHex(privkey);
		//const BigInt<256> privKeyR(privkeyHex);
		std::cout << "Rootpriv: " << hexString(privKeyRoot.getBinaryLong()) << std::endl;


		//Read the index file
		const std::string indexStr = readFile(privIndexFile);
		std::cout << "Index file content: " << indexStr << std::endl;
		//std::cout << "Will convert: " << indexHex << std::endl;
		
		const BigInt<257> keyIndex = BigInt<257>::fromHex(indexStr);



		BigInt<257> N(BitcoinEllipticCurve::Nval());


		//todo
		const BigInt<257> privKeyRootLarger(BigInt<257>::asPositive(privKeyRoot));
		const BigInt<257> privKeyTotal = privKeyRootLarger + keyIndex;
		const BigInt<257> privKeyMod = privKeyTotal % N; 	//Modulus
		const BigInt<256> privKey(privKeyMod);
		
		const PrivKey myPrivKey(privKey, compressed);
		
		
		//const BigInt<256> privKey = privKeyRoot + keyIndex; //Todo: Modulus!!!!!!!
		const BitcoinKeyPair keypair = BitcoinKeyPair::calcKeys(myPrivKey); //privKey, compressed);

		std::cout << "PRIV: " << keypair.privaddr << std::endl;			
		std::cout << "PUB: " << keypair.pubaddr << std::endl;

		std::list<ExtraInfo> generationExtra;

		std::string generationMethod("hierarchial random ");
		//generationMethod += privateRootFile;

		//const std::string mnemonic = generateMnemonic(privKey);
		const Mnemonic myMnemonicObj(privKey); // = Mnemonic::generate(privKey);
		//const std::string mnemonic = myMnemonicObj.toString();


		GenerationParameters params(compressed, true, true);

		GenerationMethods::saveAllFiles(keypair.pubaddr, keypair.privaddr.toString(), generationMethod, 
						generationExtra, "", params, myMnemonicObj);
}


























