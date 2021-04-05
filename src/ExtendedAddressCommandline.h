#ifndef EXTENDED_ADDRESS_COMMANDLINE_H
#define EXTENDED_ADDRESS_COMMANDLINE_H

#include <vector>
#include <string>

#include "privKey.h"
#include "mnemonic.h"


void calcAddressDerivation(const std::vector<std::string>& args);
void calcDerivation(const std::vector<std::string>& args);
void calcFirstHdAddress(const std::vector<std::string>& args);
PrivKey mnemonicToFirstPrivateKey(const Mnemonic& mnemonicObj, std::string& path);


#endif

