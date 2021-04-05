#ifndef MISC_COMMANDLINE_H
#define MISC_COMMANDLINE_H


#include <string>
#include <vector>


void printIntSize();
void generateWifFromMiniPrivKey(int argc, char* argv[], const std::string& thetime);
void generatePublicPart(const std::vector<std::string>& args, int argc, char* argv[], const std::string& thetime);
void generatePaymentRequest(int argc, char* argv[], const std::string& thetime);
void uncompressPublicKey(int argc, char* argv[], const std::string& thetime);
void compressPublicKey(int argc, char* argv[], const std::string& thetime);
void setLanguage(int argc, char* argv[], const std::string& thetime);




#endif
