#ifndef BITGEN_CCONFIG_H
#define BITGEN_CCONFIG_H

/**
 * bitgenConfig.h - Bitcoin poscript generator
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

#include <iostream>
#include <stdlib.h>
#include <list>


#include "bigint.h"
#include "bigintutil.h"


int getConfiguredNum(const bool increase = true);
void setConfiguredNum(const int val);

std::string getConfigPath();
bool configDirExist();
std::string getOrCreateTheConfigDir();
void configureLang(const std::string& lang);
std::string getConfiguredLang();

void saveStaticXor(const BigInt<256>& privkey);
BigInt<256> getStaticXor(const bool useStaticXorIfPresent = true);
void deleteStaticXor();

void addFoldersToConfig(const std::list<std::string>& folders);
std::list<std::string> getPublicAndOtpFolders(std::string& publicFolder);
void checkFoldersExist(const std::list<std::string>& folders);
void removeFolderConfig();


#endif


