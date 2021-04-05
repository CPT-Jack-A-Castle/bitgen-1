#Generated makefile for Linux

ifeq ("$(MAKECMDGOALS)","withoutbw")
	COMPILE=g++ --std=c++11 -I. -Isrc -Isrc/bitlib/bigintctl -Isrc/bitlib -Isrc/qrenc -Isrc/argon -Isrc/bitgen -c
else
	COMPILE=g++ --std=c++11 -O2 -msse2 -I. -Isrc -Isrc/bitlib/bigintctl -Isrc/bitlib -Isrc/qrenc -Isrc/argon -Isrc/bitgen -c
endif

all: bitsig bitcry bitcalc bitcoindefault bitvanity bitcoin bitcoincash bitcoincash_slp dogecoin feathercoin litecoin namecoin peercoin vertcoin 

withoutbw: bitsig bitcry bitcalc btc bitcoin_nobw bitcoincash_nobw bitcoincash_slp_nobw dogecoin_nobw feathercoin_nobw litecoin_nobw namecoin_nobw peercoin_nobw vertcoin_nobw 

test:
	./bitgen test

bitcoin: obj/bitgen_bitcoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 
	g++ --std=c++11 -o bitgen-btc obj/bitgen_bitcoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 

bitcoincash: obj/bitgen_bitcoincash.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoincash_specific.o 
	g++ --std=c++11 -o bitgen-bch obj/bitgen_bitcoincash.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoincash_specific.o 

bitcoindefault: obj/bitgen_bitcoincash.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoincash_specific.o 
	g++ --std=c++11 -o bitgen obj/bitgen_bitcoincash.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoincash_specific.o 

bitcoincash_slp: obj/bitgen_bitcoincash_slp.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoincash_slp_specific.o 
	g++ --std=c++11 -o bitgen-slp obj/bitgen_bitcoincash_slp.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoincash_slp_specific.o 

dogecoin: obj/bitgen_dogecoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_dogecoin_specific.o 
	g++ --std=c++11 -o bitgen-doge obj/bitgen_dogecoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_dogecoin_specific.o 

feathercoin: obj/bitgen_feathercoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_feathercoin_specific.o 
	g++ --std=c++11 -o bitgen-ftc obj/bitgen_feathercoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_feathercoin_specific.o 

litecoin: obj/bitgen_litecoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_litecoin_specific.o 
	g++ --std=c++11 -o bitgen-ltc obj/bitgen_litecoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_litecoin_specific.o 

namecoin: obj/bitgen_namecoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_namecoin_specific.o 
	g++ --std=c++11 -o bitgen-nmc obj/bitgen_namecoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_namecoin_specific.o 

peercoin: obj/bitgen_peercoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_peercoin_specific.o 
	g++ --std=c++11 -o bitgen-ppc obj/bitgen_peercoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_peercoin_specific.o 

vertcoin: obj/bitgen_vertcoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_vertcoin_specific.o 
	g++ --std=c++11 -o bitgen-vtc obj/bitgen_vertcoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_vertcoin_specific.o 

bitsig: obj/bitsig.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 
	g++ --std=c++11 -o bitsig obj/bitsig.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 

bitcry: obj/bitcry.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 
	g++ --std=c++11 -o bitcry obj/bitcry.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 

bitcalc: obj/bitcalc.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 
	g++ --std=c++11 -o bitcalc obj/bitcalc.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 

bitvanity: obj/bitvanity_bitcoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 
	g++ --std=c++11 -o bitvanity obj/bitvanity_bitcoin.o obj/CommandlineParser.o obj/ElectrumCommandline.o obj/EncryptedResult.o obj/EntityInformationCommandline.o obj/ExtendedAddressCommandline.o obj/ExtendedKey.o obj/ExtraOptionsRandom.o obj/GenerationMethods.o obj/GenerationMethodsElectrum.o obj/GenerationMethodsExtended.o obj/GenerationParameters.o obj/HierarchialRandom.o obj/MiscCommandline.o obj/MnemonicCommandline.o obj/RangeSearcher.o obj/RootGenerationCommandline.o obj/SaveFolderHandler.o obj/SignatureImpl.o obj/StaticXor.o obj/TransactionCommandline.o obj/aes.o obj/bitcalccli.o obj/bitgenConfig.o obj/bitgencli.o obj/bitsigConfig.o obj/commandLine.o obj/encrypt.o obj/encryptionFileFormats.o obj/hmac.o obj/keychainFunc.o obj/license.o obj/miniPriv.o obj/predicates.o obj/sigFile.o obj/signatureFileFormats.o obj/usagePrintout.o obj/argon2d-ref.o obj/blake2b-ref.o obj/Directory.o obj/electrumMnemonic.o obj/keyDerivationFunction.o obj/language.o obj/mnemonic.o obj/mnemonicBase.o obj/postscriptGeneration.o obj/printPS.o obj/qrenc.o obj/random.o obj/txtGeneration.o obj/url.o obj/ECPoint.o obj/FileUtil.o obj/RSVal.o obj/Script.o obj/ScriptItem.o obj/Timestamp.o obj/WinRandom.o obj/addressConversion.o obj/amount.o obj/base58.o obj/base64.o obj/binaryTransaction.o obj/bitcoinEC.o obj/bitcoinKeyPair.o obj/bitsigFileFormat.o obj/cashAddress.o obj/cryptoDecoder.o obj/fiveBitItems.o obj/hash.o obj/multiSig.o obj/nonblockFile.o obj/pkif.o obj/privKey.o obj/pubAddress.o obj/pubKey.o obj/randomUtils.o obj/ripemd160.o obj/scriptdecoder.o obj/sha2.o obj/signature.o obj/simpleFile.o obj/testutils.o obj/timelock.o obj/transaction.o obj/transactionSignatureChecker.o obj/transactiondecoder.o obj/txHash.o obj/util.o obj/wif.o obj/bigintutil.o obj/signatureTest.o obj/unittest.o obj/unittestBTC.o obj/VanityCommandline.o obj/VanitySearcher.o obj/bitgenvanity.o obj/bitstream.o obj/mask.o obj/mmask.o obj/mqrspec.o obj/qrencode.o obj/qrinput.o obj/qrspec.o obj/rscode.o obj/split.o obj/currencySpecific_bitcoin_specific.o 

obj/CommandlineParser.o: src/CommandlineParser.cpp
	$(COMPILE) -o obj/CommandlineParser.o src/CommandlineParser.cpp

obj/ElectrumCommandline.o: src/ElectrumCommandline.cpp
	$(COMPILE) -o obj/ElectrumCommandline.o src/ElectrumCommandline.cpp

obj/EncryptedResult.o: src/EncryptedResult.cpp
	$(COMPILE) -o obj/EncryptedResult.o src/EncryptedResult.cpp

obj/EntityInformationCommandline.o: src/EntityInformationCommandline.cpp
	$(COMPILE) -o obj/EntityInformationCommandline.o src/EntityInformationCommandline.cpp

obj/ExtendedAddressCommandline.o: src/ExtendedAddressCommandline.cpp
	$(COMPILE) -o obj/ExtendedAddressCommandline.o src/ExtendedAddressCommandline.cpp

obj/ExtendedKey.o: src/ExtendedKey.cpp
	$(COMPILE) -o obj/ExtendedKey.o src/ExtendedKey.cpp

obj/ExtraOptionsRandom.o: src/ExtraOptionsRandom.cpp
	$(COMPILE) -o obj/ExtraOptionsRandom.o src/ExtraOptionsRandom.cpp

obj/GenerationMethods.o: src/GenerationMethods.cpp
	$(COMPILE) -o obj/GenerationMethods.o src/GenerationMethods.cpp

obj/GenerationMethodsElectrum.o: src/GenerationMethodsElectrum.cpp
	$(COMPILE) -o obj/GenerationMethodsElectrum.o src/GenerationMethodsElectrum.cpp

obj/GenerationMethodsExtended.o: src/GenerationMethodsExtended.cpp
	$(COMPILE) -o obj/GenerationMethodsExtended.o src/GenerationMethodsExtended.cpp

obj/GenerationParameters.o: src/GenerationParameters.cpp
	$(COMPILE) -o obj/GenerationParameters.o src/GenerationParameters.cpp

obj/HierarchialRandom.o: src/HierarchialRandom.cpp
	$(COMPILE) -o obj/HierarchialRandom.o src/HierarchialRandom.cpp

obj/MiscCommandline.o: src/MiscCommandline.cpp
	$(COMPILE) -o obj/MiscCommandline.o src/MiscCommandline.cpp

obj/MnemonicCommandline.o: src/MnemonicCommandline.cpp
	$(COMPILE) -o obj/MnemonicCommandline.o src/MnemonicCommandline.cpp

obj/RangeSearcher.o: src/RangeSearcher.cpp
	$(COMPILE) -o obj/RangeSearcher.o src/RangeSearcher.cpp

obj/RootGenerationCommandline.o: src/RootGenerationCommandline.cpp
	$(COMPILE) -o obj/RootGenerationCommandline.o src/RootGenerationCommandline.cpp

obj/SaveFolderHandler.o: src/SaveFolderHandler.cpp
	$(COMPILE) -o obj/SaveFolderHandler.o src/SaveFolderHandler.cpp

obj/SignatureImpl.o: src/SignatureImpl.cpp
	$(COMPILE) -o obj/SignatureImpl.o src/SignatureImpl.cpp

obj/StaticXor.o: src/StaticXor.cpp
	$(COMPILE) -o obj/StaticXor.o src/StaticXor.cpp

obj/TransactionCommandline.o: src/TransactionCommandline.cpp
	$(COMPILE) -o obj/TransactionCommandline.o src/TransactionCommandline.cpp

obj/aes.o: src/aes.cpp
	$(COMPILE) -o obj/aes.o src/aes.cpp

obj/bitcalc.o: src/bitcalc.cpp
	$(COMPILE) -o obj/bitcalc.o src/bitcalc.cpp

obj/bitcalccli.o: src/bitcalccli.cpp
	$(COMPILE) -o obj/bitcalccli.o src/bitcalccli.cpp

obj/bitcry.o: src/bitcry.cpp
	$(COMPILE) -o obj/bitcry.o src/bitcry.cpp

obj/bitgenConfig.o: src/bitgenConfig.cpp
	$(COMPILE) -o obj/bitgenConfig.o src/bitgenConfig.cpp

obj/bitgen_bitcoin.o: src/bitgen_bitcoin.cpp
	$(COMPILE) -o obj/bitgen_bitcoin.o src/bitgen_bitcoin.cpp

obj/bitgen_bitcoincash.o: src/bitgen_bitcoincash.cpp
	$(COMPILE) -o obj/bitgen_bitcoincash.o src/bitgen_bitcoincash.cpp

obj/bitgen_bitcoincash_slp.o: src/bitgen_bitcoincash_slp.cpp
	$(COMPILE) -o obj/bitgen_bitcoincash_slp.o src/bitgen_bitcoincash_slp.cpp

obj/bitgen_dogecoin.o: src/bitgen_dogecoin.cpp
	$(COMPILE) -o obj/bitgen_dogecoin.o src/bitgen_dogecoin.cpp

obj/bitgen_feathercoin.o: src/bitgen_feathercoin.cpp
	$(COMPILE) -o obj/bitgen_feathercoin.o src/bitgen_feathercoin.cpp

obj/bitgen_litecoin.o: src/bitgen_litecoin.cpp
	$(COMPILE) -o obj/bitgen_litecoin.o src/bitgen_litecoin.cpp

obj/bitgen_namecoin.o: src/bitgen_namecoin.cpp
	$(COMPILE) -o obj/bitgen_namecoin.o src/bitgen_namecoin.cpp

obj/bitgen_peercoin.o: src/bitgen_peercoin.cpp
	$(COMPILE) -o obj/bitgen_peercoin.o src/bitgen_peercoin.cpp

obj/bitgen_vertcoin.o: src/bitgen_vertcoin.cpp
	$(COMPILE) -o obj/bitgen_vertcoin.o src/bitgen_vertcoin.cpp

obj/bitgencli.o: src/bitgencli.cpp
	$(COMPILE) -o obj/bitgencli.o src/bitgencli.cpp

obj/bitsig.o: src/bitsig.cpp
	$(COMPILE) -o obj/bitsig.o src/bitsig.cpp

obj/bitsigConfig.o: src/bitsigConfig.cpp
	$(COMPILE) -o obj/bitsigConfig.o src/bitsigConfig.cpp

obj/bitvanity_bitcoin.o: src/bitvanity_bitcoin.cpp
	$(COMPILE) -o obj/bitvanity_bitcoin.o src/bitvanity_bitcoin.cpp

obj/commandLine.o: src/commandLine.cpp
	$(COMPILE) -o obj/commandLine.o src/commandLine.cpp

obj/encrypt.o: src/encrypt.cpp
	$(COMPILE) -o obj/encrypt.o src/encrypt.cpp

obj/encryptionFileFormats.o: src/encryptionFileFormats.cpp
	$(COMPILE) -o obj/encryptionFileFormats.o src/encryptionFileFormats.cpp

obj/hmac.o: src/hmac.cpp
	$(COMPILE) -o obj/hmac.o src/hmac.cpp

obj/keychainFunc.o: src/keychainFunc.cpp
	$(COMPILE) -o obj/keychainFunc.o src/keychainFunc.cpp

obj/license.o: src/license.cpp
	$(COMPILE) -o obj/license.o src/license.cpp

obj/miniPriv.o: src/miniPriv.cpp
	$(COMPILE) -o obj/miniPriv.o src/miniPriv.cpp

obj/predicates.o: src/predicates.cpp
	$(COMPILE) -o obj/predicates.o src/predicates.cpp

obj/sigFile.o: src/sigFile.cpp
	$(COMPILE) -o obj/sigFile.o src/sigFile.cpp

obj/signatureFileFormats.o: src/signatureFileFormats.cpp
	$(COMPILE) -o obj/signatureFileFormats.o src/signatureFileFormats.cpp

obj/usagePrintout.o: src/usagePrintout.cpp
	$(COMPILE) -o obj/usagePrintout.o src/usagePrintout.cpp

obj/argon2d-ref.o: src/argon/argon2d-ref.cpp
	$(COMPILE) -o obj/argon2d-ref.o src/argon/argon2d-ref.cpp

obj/blake2b-ref.o: src/argon/blake2b-ref.cpp
	$(COMPILE) -o obj/blake2b-ref.o src/argon/blake2b-ref.cpp

obj/Directory.o: src/bitgen/Directory.cpp
	$(COMPILE) -o obj/Directory.o src/bitgen/Directory.cpp

obj/electrumMnemonic.o: src/bitgen/electrumMnemonic.cpp
	$(COMPILE) -o obj/electrumMnemonic.o src/bitgen/electrumMnemonic.cpp

obj/keyDerivationFunction.o: src/bitgen/keyDerivationFunction.cpp
	$(COMPILE) -o obj/keyDerivationFunction.o src/bitgen/keyDerivationFunction.cpp

obj/language.o: src/bitgen/language.cpp
	$(COMPILE) -o obj/language.o src/bitgen/language.cpp

obj/mnemonic.o: src/bitgen/mnemonic.cpp
	$(COMPILE) -o obj/mnemonic.o src/bitgen/mnemonic.cpp

obj/mnemonicBase.o: src/bitgen/mnemonicBase.cpp
	$(COMPILE) -o obj/mnemonicBase.o src/bitgen/mnemonicBase.cpp

obj/postscriptGeneration.o: src/bitgen/postscriptGeneration.cpp
	$(COMPILE) -o obj/postscriptGeneration.o src/bitgen/postscriptGeneration.cpp

obj/printPS.o: src/bitgen/printPS.cpp
	$(COMPILE) -o obj/printPS.o src/bitgen/printPS.cpp

obj/qrenc.o: src/bitgen/qrenc.cpp
	$(COMPILE) -o obj/qrenc.o src/bitgen/qrenc.cpp

obj/random.o: src/bitgen/random.cpp
	$(COMPILE) -o obj/random.o src/bitgen/random.cpp

obj/txtGeneration.o: src/bitgen/txtGeneration.cpp
	$(COMPILE) -o obj/txtGeneration.o src/bitgen/txtGeneration.cpp

obj/url.o: src/bitgen/url.cpp
	$(COMPILE) -o obj/url.o src/bitgen/url.cpp

obj/ECPoint.o: src/bitlib/ECPoint.cpp
	$(COMPILE) -o obj/ECPoint.o src/bitlib/ECPoint.cpp

obj/FileUtil.o: src/bitlib/FileUtil.cpp
	$(COMPILE) -o obj/FileUtil.o src/bitlib/FileUtil.cpp

obj/RSVal.o: src/bitlib/RSVal.cpp
	$(COMPILE) -o obj/RSVal.o src/bitlib/RSVal.cpp

obj/Script.o: src/bitlib/Script.cpp
	$(COMPILE) -o obj/Script.o src/bitlib/Script.cpp

obj/ScriptItem.o: src/bitlib/ScriptItem.cpp
	$(COMPILE) -o obj/ScriptItem.o src/bitlib/ScriptItem.cpp

obj/Timestamp.o: src/bitlib/Timestamp.cpp
	$(COMPILE) -o obj/Timestamp.o src/bitlib/Timestamp.cpp

obj/WinRandom.o: src/bitlib/WinRandom.cpp
	$(COMPILE) -o obj/WinRandom.o src/bitlib/WinRandom.cpp

obj/addressConversion.o: src/bitlib/addressConversion.cpp
	$(COMPILE) -o obj/addressConversion.o src/bitlib/addressConversion.cpp

obj/amount.o: src/bitlib/amount.cpp
	$(COMPILE) -o obj/amount.o src/bitlib/amount.cpp

obj/base58.o: src/bitlib/base58.cpp
	$(COMPILE) -o obj/base58.o src/bitlib/base58.cpp

obj/base64.o: src/bitlib/base64.cpp
	$(COMPILE) -o obj/base64.o src/bitlib/base64.cpp

obj/binaryTransaction.o: src/bitlib/binaryTransaction.cpp
	$(COMPILE) -o obj/binaryTransaction.o src/bitlib/binaryTransaction.cpp

obj/bitcoinEC.o: src/bitlib/bitcoinEC.cpp
	$(COMPILE) -o obj/bitcoinEC.o src/bitlib/bitcoinEC.cpp

obj/bitcoinKeyPair.o: src/bitlib/bitcoinKeyPair.cpp
	$(COMPILE) -o obj/bitcoinKeyPair.o src/bitlib/bitcoinKeyPair.cpp

obj/bitsigFileFormat.o: src/bitlib/bitsigFileFormat.cpp
	$(COMPILE) -o obj/bitsigFileFormat.o src/bitlib/bitsigFileFormat.cpp

obj/cashAddress.o: src/bitlib/cashAddress.cpp
	$(COMPILE) -o obj/cashAddress.o src/bitlib/cashAddress.cpp

obj/cryptoDecoder.o: src/bitlib/cryptoDecoder.cpp
	$(COMPILE) -o obj/cryptoDecoder.o src/bitlib/cryptoDecoder.cpp

obj/currencySpecific_bitcoin_specific.o: src/bitlib/currencySpecific_bitcoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_bitcoin_specific.o src/bitlib/currencySpecific_bitcoin_specific.cpp

obj/currencySpecific_bitcoincash_slp_specific.o: src/bitlib/currencySpecific_bitcoincash_slp_specific.cpp
	$(COMPILE) -o obj/currencySpecific_bitcoincash_slp_specific.o src/bitlib/currencySpecific_bitcoincash_slp_specific.cpp

obj/currencySpecific_bitcoincash_specific.o: src/bitlib/currencySpecific_bitcoincash_specific.cpp
	$(COMPILE) -o obj/currencySpecific_bitcoincash_specific.o src/bitlib/currencySpecific_bitcoincash_specific.cpp

obj/currencySpecific_dogecoin_specific.o: src/bitlib/currencySpecific_dogecoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_dogecoin_specific.o src/bitlib/currencySpecific_dogecoin_specific.cpp

obj/currencySpecific_feathercoin_specific.o: src/bitlib/currencySpecific_feathercoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_feathercoin_specific.o src/bitlib/currencySpecific_feathercoin_specific.cpp

obj/currencySpecific_litecoin_specific.o: src/bitlib/currencySpecific_litecoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_litecoin_specific.o src/bitlib/currencySpecific_litecoin_specific.cpp

obj/currencySpecific_namecoin_specific.o: src/bitlib/currencySpecific_namecoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_namecoin_specific.o src/bitlib/currencySpecific_namecoin_specific.cpp

obj/currencySpecific_peercoin_specific.o: src/bitlib/currencySpecific_peercoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_peercoin_specific.o src/bitlib/currencySpecific_peercoin_specific.cpp

obj/currencySpecific_vertcoin_specific.o: src/bitlib/currencySpecific_vertcoin_specific.cpp
	$(COMPILE) -o obj/currencySpecific_vertcoin_specific.o src/bitlib/currencySpecific_vertcoin_specific.cpp

obj/fiveBitItems.o: src/bitlib/fiveBitItems.cpp
	$(COMPILE) -o obj/fiveBitItems.o src/bitlib/fiveBitItems.cpp

obj/hash.o: src/bitlib/hash.cpp
	$(COMPILE) -o obj/hash.o src/bitlib/hash.cpp

obj/multiSig.o: src/bitlib/multiSig.cpp
	$(COMPILE) -o obj/multiSig.o src/bitlib/multiSig.cpp

obj/nonblockFile.o: src/bitlib/nonblockFile.cpp
	$(COMPILE) -o obj/nonblockFile.o src/bitlib/nonblockFile.cpp

obj/pkif.o: src/bitlib/pkif.cpp
	$(COMPILE) -o obj/pkif.o src/bitlib/pkif.cpp

obj/privKey.o: src/bitlib/privKey.cpp
	$(COMPILE) -o obj/privKey.o src/bitlib/privKey.cpp

obj/pubAddress.o: src/bitlib/pubAddress.cpp
	$(COMPILE) -o obj/pubAddress.o src/bitlib/pubAddress.cpp

obj/pubKey.o: src/bitlib/pubKey.cpp
	$(COMPILE) -o obj/pubKey.o src/bitlib/pubKey.cpp

obj/randomUtils.o: src/bitlib/randomUtils.cpp
	$(COMPILE) -o obj/randomUtils.o src/bitlib/randomUtils.cpp

obj/ripemd160.o: src/bitlib/ripemd160.cpp
	$(COMPILE) -o obj/ripemd160.o src/bitlib/ripemd160.cpp

obj/scriptdecoder.o: src/bitlib/scriptdecoder.cpp
	$(COMPILE) -o obj/scriptdecoder.o src/bitlib/scriptdecoder.cpp

obj/sha2.o: src/bitlib/sha2.cpp
	$(COMPILE) -o obj/sha2.o src/bitlib/sha2.cpp

obj/signature.o: src/bitlib/signature.cpp
	$(COMPILE) -o obj/signature.o src/bitlib/signature.cpp

obj/simpleFile.o: src/bitlib/simpleFile.cpp
	$(COMPILE) -o obj/simpleFile.o src/bitlib/simpleFile.cpp

obj/testutils.o: src/bitlib/testutils.cpp
	$(COMPILE) -o obj/testutils.o src/bitlib/testutils.cpp

obj/timelock.o: src/bitlib/timelock.cpp
	$(COMPILE) -o obj/timelock.o src/bitlib/timelock.cpp

obj/transaction.o: src/bitlib/transaction.cpp
	$(COMPILE) -o obj/transaction.o src/bitlib/transaction.cpp

obj/transactionSignatureChecker.o: src/bitlib/transactionSignatureChecker.cpp
	$(COMPILE) -o obj/transactionSignatureChecker.o src/bitlib/transactionSignatureChecker.cpp

obj/transactiondecoder.o: src/bitlib/transactiondecoder.cpp
	$(COMPILE) -o obj/transactiondecoder.o src/bitlib/transactiondecoder.cpp

obj/txHash.o: src/bitlib/txHash.cpp
	$(COMPILE) -o obj/txHash.o src/bitlib/txHash.cpp

obj/util.o: src/bitlib/util.cpp
	$(COMPILE) -o obj/util.o src/bitlib/util.cpp

obj/wif.o: src/bitlib/wif.cpp
	$(COMPILE) -o obj/wif.o src/bitlib/wif.cpp

obj/bigintutil.o: src/bitlib/bigintctl/bigintutil.cpp
	$(COMPILE) -o obj/bigintutil.o src/bitlib/bigintctl/bigintutil.cpp

obj/signatureTest.o: src/test/signatureTest.cpp
	$(COMPILE) -o obj/signatureTest.o src/test/signatureTest.cpp

obj/unittest.o: src/test/unittest.cpp
	$(COMPILE) -o obj/unittest.o src/test/unittest.cpp

obj/unittestBTC.o: src/test/unittestBTC.cpp
	$(COMPILE) -o obj/unittestBTC.o src/test/unittestBTC.cpp

obj/VanityCommandline.o: src/vanity/VanityCommandline.cpp
	$(COMPILE) -o obj/VanityCommandline.o src/vanity/VanityCommandline.cpp

obj/VanitySearcher.o: src/vanity/VanitySearcher.cpp
	$(COMPILE) -o obj/VanitySearcher.o src/vanity/VanitySearcher.cpp

obj/bitgenvanity.o: src/vanity/bitgenvanity.cpp
	$(COMPILE) -o obj/bitgenvanity.o src/vanity/bitgenvanity.cpp

obj/bitstream.o: src/qrenc/bitstream.c
	gcc -DHAVE_CONFIG_H -o obj/bitstream.o -c src/qrenc/bitstream.c

obj/mask.o: src/qrenc/mask.c
	gcc -DHAVE_CONFIG_H -o obj/mask.o -c src/qrenc/mask.c

obj/mmask.o: src/qrenc/mmask.c
	gcc -DHAVE_CONFIG_H -o obj/mmask.o -c src/qrenc/mmask.c

obj/mqrspec.o: src/qrenc/mqrspec.c
	gcc -DHAVE_CONFIG_H -o obj/mqrspec.o -c src/qrenc/mqrspec.c

obj/qrencode.o: src/qrenc/qrencode.c
	gcc -DHAVE_CONFIG_H -o obj/qrencode.o -c src/qrenc/qrencode.c

obj/qrinput.o: src/qrenc/qrinput.c
	gcc -DHAVE_CONFIG_H -o obj/qrinput.o -c src/qrenc/qrinput.c

obj/qrspec.o: src/qrenc/qrspec.c
	gcc -DHAVE_CONFIG_H -o obj/qrspec.o -c src/qrenc/qrspec.c

obj/rscode.o: src/qrenc/rscode.c
	gcc -DHAVE_CONFIG_H -o obj/rscode.o -c src/qrenc/rscode.c

obj/split.o: src/qrenc/split.c
	gcc -DHAVE_CONFIG_H -o obj/split.o -c src/qrenc/split.c



clean:
	rm -f *.o *.exe obj/*.o objwin/*.o bitgen bitsig bitcry bitcalc bitgen-btc bitgen-ltc bitgen-doge bitgen-testnet bitgen-nmc bitgen-ppc bitgen-vtc bitgen-rdd bitgen-ftc bitgen-bch bitgen-slp bitvanity bitvanity-btc

