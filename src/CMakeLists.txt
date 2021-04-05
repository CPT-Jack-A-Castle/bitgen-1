

cmake_minimum_required (VERSION 2.6)
project (bitgen)

include_directories(
	.
	..
	bitlib
	bitlib/bigintctl
	bitgen
	qrenc
	argon
)

add_definitions("-DHAVE_CONFIG_H -O2 -msse2")



add_library(bitgenl STATIC 
	CommandlineParser.cpp
	ElectrumCommandline.cpp
	EncryptedResult.cpp
	EntityInformationCommandline.cpp
	ExtendedAddressCommandline.cpp
	ExtendedKey.cpp
	GenerationMethods.cpp
	GenerationParameters.cpp
	HierarchialRandom.cpp
	MiscCommandline.cpp
	MnemonicCommandline.cpp
	RangeSearcher.cpp
	RootGenerationCommandline.cpp
	SaveFolderHandler.cpp
	SignatureImpl.cpp
	StaticXor.cpp
	TransactionCommandline.cpp
	VanityCommandline.cpp
	VanitySearcher.cpp
	aes.cpp
	bitcalccli.cpp
	bitgenConfig.cpp
	bitgencli.cpp
	bitsigConfig.cpp
	commandLine.cpp
	encrypt.cpp
	encryptionFileFormats.cpp
	hmac.cpp
	keychainFunc.cpp
	license.cpp
	miniPriv.cpp
	predicates.cpp
	sigFile.cpp
	signatureFileFormats.cpp
	unittest.cpp
	usagePrintout.cpp
	argon/argon2d-ref.cpp
	argon/blake2b-ref.cpp
	bitgen/Directory.cpp
	bitgen/electrumMnemonic.cpp
	bitgen/keyDerivationFunction.cpp
	bitgen/language.cpp
	bitgen/mnemonic.cpp
	bitgen/mnemonicBase.cpp
	bitgen/postscriptGeneration.cpp
	bitgen/printPS.cpp
	bitgen/qrenc.cpp
	bitgen/random.cpp
	bitgen/txtGeneration.cpp
	bitgen/url.cpp
	bitlib/ECPoint.cpp
	bitlib/FileUtil.cpp
	bitlib/RSVal.cpp
	bitlib/Script.cpp
	bitlib/ScriptItem.cpp
	bitlib/Timestamp.cpp
	bitlib/WinRandom.cpp
	bitlib/addressConversion.cpp
	bitlib/amount.cpp
	bitlib/base58.cpp
	bitlib/base64.cpp
	bitlib/binaryTransaction.cpp
	bitlib/bitcoinEC.cpp
	bitlib/bitcoinKeyPair.cpp
	bitlib/bitsigFileFormat.cpp
	bitlib/cashAddress.cpp
	bitlib/cryptoDecoder.cpp
	bitlib/fiveBitItems.cpp
	bitlib/hash.cpp
	bitlib/multiSig.cpp
	bitlib/nonblockFile.cpp
	bitlib/pkif.cpp
	bitlib/privKey.cpp
	bitlib/pubAddress.cpp
	bitlib/pubKey.cpp
	bitlib/randomUtils.cpp
	bitlib/ripemd160.cpp
	bitlib/scriptdecoder.cpp
	bitlib/sha2.cpp
	bitlib/signature.cpp
	bitlib/simpleFile.cpp
	bitlib/testutils.cpp
	bitlib/timelock.cpp
	bitlib/transaction.cpp
	bitlib/transactionSignatureChecker.cpp
	bitlib/transactiondecoder.cpp
	bitlib/txHash.cpp
	bitlib/util.cpp
	bitlib/wif.cpp
	bitlib/bigintctl/bigintutil.cpp
	qrenc/bitstream.c
	qrenc/mask.c
	qrenc/mmask.c
	qrenc/mqrspec.c
	qrenc/qrencode.c
	qrenc/qrinput.c
	qrenc/qrspec.c
	qrenc/rscode.c
	qrenc/split.c
)

add_executable(bitgen bitlib/currencySpecific_bitcoin_specific.cpp bitgen_bitcoin.cpp)
add_executable(bitgen-bch bitlib/currencySpecific_bitcoincash_specific.cpp bitgen_bitcoincash.cpp)
add_executable(bitgen-doge bitlib/currencySpecific_dogecoin_specific.cpp bitgen_dogecoin.cpp)
add_executable(bitgen-ftc bitlib/currencySpecific_feathercoin_specific.cpp bitgen_feathercoin.cpp)
add_executable(bitgen-ltc bitlib/currencySpecific_litecoin_specific.cpp bitgen_litecoin.cpp)
add_executable(bitgen-nmc bitlib/currencySpecific_namecoin_specific.cpp bitgen_namecoin.cpp)
add_executable(bitgen-ppc bitlib/currencySpecific_peercoin_specific.cpp bitgen_peercoin.cpp)
add_executable(bitgen-vtc bitlib/currencySpecific_vertcoin_specific.cpp bitgen_vertcoin.cpp)
add_executable(bitsig bitlib/currencySpecific_bitcoin_specific.cpp bitsig.cpp)

target_link_libraries(bitgen LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-bch LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-doge LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-ftc LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-ltc LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-nmc LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-ppc LINK_PUBLIC bitgenl)
target_link_libraries(bitgen-vtc LINK_PUBLIC bitgenl)
target_link_libraries(bitsig LINK_PUBLIC bitgenl)

