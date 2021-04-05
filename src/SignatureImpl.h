#ifndef BITGEN_SIGNATURE_EXTRA_H
#define BITGEN_SIGNATURE_EXTRA_H


#include "bitcoinEC.h"
#include "pubAddress.h"
#include "RSVal.h"

#include <list>

class SignatureImplementationExtra
{
public:
	static void verifyPubaddrSpecifiedByUser(const std::string & pubadd, const PubAddress& bitaddress, std::string& alias);

	static std::string verifySignatureForFile(const std::string& signedFile,const std::string& pubadd, std::string& alias, 
									std::string& verifiedAddress, const bool rawContent);

};





#endif

