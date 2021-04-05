#ifndef TRANSACTION_COMMANDLINE_H
#define TRANSACTION_COMMANDLINE_H


#include "binaryTransaction.h"
#include "BinaryScript.h"
#include "RSVal.h"
#include "pubKey.h"

#include <vector>
#include <string>


class TransactionCommandline
{
public:
	static void getTransactionInputHashes(const std::vector<std::string>& args);
	static void saveScript(const std::vector<std::string>& args);
	static void decodeScript(const std::vector<std::string>& args);
	static void decodeTransaction(const std::vector<std::string>& args);

	static void saveTheTransaction(const std::vector<std::string>& args);
	static void parseTransaction(const std::vector<std::string>& args);
	static void runTrans(const std::vector<std::string>& args);
	static void createTransaction(const std::vector<std::string>& args);

	static BinaryTransaction getTrans(const std::string& arg);
	static RSVal getSigFromFile(const std::string& filename);
	static bool transactionSupportedForCurrency();

	static PubKey stringToPubkey(const std::string pkifStr);
	static BinaryScript createOpreturnScript(const std::string& dataStr, const std::string& typeStr);

private:

	static BinaryScript getScript(const std::string& arg);
	
};


	



#endif

