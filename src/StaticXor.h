#ifndef STATIC_XOR_H
#define STATIC_XOR_H

#include <vector>
#include <string>

#include "bigint.h"



void removeStaticXor(const std::vector<std::string>& args, const std::string& thetime);
void saveStaticXorFiles(const BigInt<256> privkey, const std::string& thetime);
void addStaticXor(const std::vector<std::string>& args, const std::string& thetime);
void readStaticXor(const std::vector<std::string>& args, const std::string& thetime);

std::string staticXorHash(const BigInt<256>& staticXor);



#endif
