/**
 * bitgenConfig.cpp - Bitcoin generator
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

#include "bitgenConfig.h"
#include "util.h"
#include "FileUtil.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef __linux
#include <pwd.h>
#else
#include <shlobj.h>
#endif

#include "bigint.h"

#include "currencySpecific.h"
#include <sstream>



std::string getConfigPath()
{
#ifdef __linux	
	struct passwd *pw = getpwuid(getuid());
	const char* homedir = pw->pw_dir;
	const std::string homeDir(homedir);
#else
	char path[MAX_PATH];
	HRESULT res = SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, path);
	if(res != S_OK)
	{
		std::cerr << "Can not get home folder" << std::endl;
		throw std::string("Error, can not get home folder");
	}
	
	const std::string homeDir(path);	
#endif
	
	const std::string configDir = homeDir + "/.bitgen";
	
	return configDir;
}


bool configDirExist()
{
	const std::string configPath = getConfigPath();	
	
	return directoryExist(configPath);
}



std::string getOrCreateTheConfigDir()
{
	std::string confPath = getConfigPath();
	if(directoryExist(confPath))
	{
		return confPath;
	}
	
	
	//Create the dir
	std::cout << "Creating folder: " << confPath << std::endl;
#ifdef __linux	
	const int ret = mkdir(confPath.c_str(), S_IRWXU | S_IRWXG);
#else
	const int ret = mkdir(confPath.c_str());
#endif
	if(ret != 0)
	{
		std::cout << "Could not create: " << confPath << std::endl;
		throw std::string("Could not create work folder");
	}
	
	return confPath;	
}


void configureLang(const std::string& lang)
{
	const std::string confDir = getOrCreateTheConfigDir();
	const std::string confFile = confDir + "/language.conf";
	
	fileWrite(confFile, lang);
	std::cout << "Writing " << confFile << std::endl;
}


std::string getConfiguredLang()
{
	const std::string confPath = getConfigPath();
	const std::string confFile = confPath + "/language.conf";

	//std::cout << "Checking if file exist: " << confFile << std::endl;
	if(!fileExist(confFile))
	{
		//std::cout << "No lang configured" << std::endl;
		return "";
	}
	
	const std::string confLang = readFile(confFile);
	
	//std::cout << "Using lang: " << confLang << std::endl;
	return confLang;
}


void createNumFile(const std::string& filename, const int val)
{
	std::stringstream ss;
	ss << val;
	
	const std::string content = ss.str();
	if(!fileWrite(filename, content))
	{
		std::cout << "Could not write file: " << filename << std::endl;
		throw std::string("Error, could not save num file");
	}
	
}


void setConfiguredNum(const int val)
{
	const std::string confPath = getConfigPath();
	const std::string confFile = confPath + "/nextNum_" + getCurrencyShortName() + ".conf";
	
	std::cout << "Writing file: " << confFile << std::endl;
	
	createNumFile(confFile, val);
}



int getConfiguredNum(const bool increase)
{
	const std::string confPath = getConfigPath();

	if(!directoryExist(confPath))
	{
		//create config folder if needed		
		createDirectory(confPath);
	}

	const std::string confFile = confPath + "/nextNum_" + getCurrencyShortName() + ".conf";
	
	//std::cout << "Checking if file exist: " << confFile << std::endl;
	if(!fileExist(confFile))
	{
		std::cout << "No next num configured, setting to one (1)" << std::endl;
				
		createNumFile(confFile, 1);		
	}
	
	const std::string confNum = readFile(confFile);
	const int num = atoi(confNum.c_str());

	if(increase)
	{
		const int nextNum = num + 1;
		createNumFile(confFile, nextNum);
	}
	
	//std::cout << "Using num: " << num << std::endl;
	return num;
}



void saveStaticXor(const BigInt<256>& privkey)
{
	const std::string configFolder = getOrCreateTheConfigDir();
	
	std::cout << "Saving static XOR mask: " << hexString(privkey.getBinaryLong()) << std::endl;
	
	
	const std::string filename = configFolder + "/staticxor.conf"; 
	
	const std::string content = hexString(privkey.getBinaryLong());
	if(!fileWrite(filename, content))
	{
		std::cout << "Could not write file: " << filename << std::endl;
		throw std::string("Error, could not save xor file");
	}
	
	std::cout << "Saving in file: " << filename << std::endl;

}








//Returns static xor if defined. 
//If no static xor is defined, zero is returned. 
BigInt<256> getStaticXor(const bool useStaticXorIfPresent)
{
	if(!useStaticXorIfPresent)
	{
		const BigInt<256> zero;		//Not using static xor
		return zero;		
	}
	
	const std::string configFolder = getOrCreateTheConfigDir();
	
	//std::cout << "Getting static xor mask" << std::endl;
	const std::string filename = configFolder + "/staticxor.conf"; 

	if(!fileExist(filename))
	{
		const BigInt<256> zero;
		return zero;
	}


	
	const std::string content = readFile(filename);
		
	const BigInt<256> priv = parseHex256Bit(content);	
	
	//std::cout << "Static xor defined: " << hexString(priv.getBinaryLong()) << std::endl;
	
	return priv;
}



void deleteStaticXor()
{
	const std::string configFolder = getOrCreateTheConfigDir();
	
	const std::string filename = configFolder + "/staticxor.conf"; 
	std::cout << "Deleting file: " << filename << std::endl;
	deleteFile(filename);
}




std::list<std::string> getPublicAndOtpFolders(std::string& publicFolder)
{
	//std::cout << "Getting OTP folders" << std::endl;

	const std::string configFolder = getOrCreateTheConfigDir();
	const std::string folderConfigFile = configFolder + "/otpfolders.config";
	
	const std::string confContent = readFile(folderConfigFile);
	
	std::list<std::string> folders;
	std::string folder;
	bool first(true);
	for(int i = 0 ; i < confContent.size() ; i++)
	{
		const unsigned char c = confContent[i];
		if(c == '\n')
		{
			if(first)
			{
				publicFolder = folder;
				first = false;
			}
			else
			{
				folders.push_back(folder);
			}
			folder = "";
		}
		else
		{
			folder += c;
		}
	}


	return folders;
}


void checkFoldersExist(const std::list<std::string>& folders)
{
	for(std::list<std::string>::const_iterator it = folders.begin() ;
		it != folders.end() ;
		++it)
	{
		const std::string& folder = (*it);
		if(!directoryExist(folder))
		{
			std::cout << "Directory does not exist: " << folder << std::endl;
			throw std::string("Folder does not exist");
		}
		
		//std::cout << "Folder: " << folder << std::endl;
	}	
}


void removeFolderConfig()
{
	const std::string configFolder = getOrCreateTheConfigDir();
	const std::string folderConfigFile = configFolder + "/otpfolders.config";

	std::cout << "Removing: " << folderConfigFile << std::endl;
	deleteFile(folderConfigFile);
}





void addFoldersToConfig(const std::list<std::string>& folders)
{
	checkFoldersExist(folders);
	
	
	std::string configStr;
	
	for(std::list<std::string>::const_iterator it = folders.begin() ;
		it != folders.end() ;
		++it)
	{
		const std::string& folder = (*it);
		configStr += folder;
		configStr += "\n";
	}
	
	//std::cout << std::endl << "ConfigStr:\n" << configStr << std::endl;
	
	const std::string configFolder = getOrCreateTheConfigDir();
	const std::string folderConfigFile = configFolder + "/otpfolders.config";
	
	if(!fileWrite(folderConfigFile, configStr))
	{
		std::cout << "Could not save file: " << folderConfigFile << std::endl;
		throw std::string("Could not save file");
	}

	std::cout << "Saved configuration: " << folderConfigFile << std::endl;	
}

