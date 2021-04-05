/**
 * bitcoin.cpp - Bitcoin address generator
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
 
/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
*/
 


#include "SaveFolderHandler.h"

#include "currencySpecific.h"
#include "FileUtil.h"
#include "Directory.h"
#include "util.h"
#include <stdlib.h>

#include "bitgenConfig.h"


std::string SaveFolderHandler::getPublicRootFolder(const bool useFolderConf)
{	
	const std::string rootFolder("cold");
	const std::string pubFold("pub");

	std::string pubFolder;

	if(useFolderConf)
	{	
		std::string confPublicFolder;
		const std::list<std::string> confFoldersDummy = getPublicAndOtpFolders(confPublicFolder);

		pubFolder = (confPublicFolder + "/" + rootFolder + "/" + pubFold);		
	}
	else
	{		
		pubFolder = (rootFolder + "/" + pubFold);
	}


	const std::string currencyShortName = getCurrencyShortName();	
	const std::string pubCoinFolder = pubFolder + "/" + currencyShortName;

	return pubCoinFolder;
}









int SaveFolderHandler::getNextNumber()
{
	//Open file with next number	
	const int configuredNum = getConfiguredNum(true);
	//std::cout << "configuredNum: " << configuredNum << std::endl;
		
	return configuredNum;
}




std::string removeDirLevels(const std::string& folder, const int level)
{
	//std::cout << "Removing " << level << " levels from folder: " << folder << std::endl;
	
	if(level == 0)
	{
		return folder;
	}
	
	
	int foundLevel(0);
	for(int i = folder.size() - 1 ; i >= 0 ; i--)
	{
		const unsigned char c = folder[i];
		if(c == '/')
		{
			foundLevel++;
			//std::cout << "Found slash: " << foundLevel << std::endl;
			
		}
		
		if(foundLevel == level)
		{
			const std::string foundFolder = folder.substr(0, i);
			//std::cout << "Result: " << foundFolder << std::endl;
			return foundFolder;
		}
	}
	
	throw std::string("Could not remove folder levels");
	return "";
}



void createDirectoryFolders(const std::string& newFolder, const int levels)
{
	//std::cout << "Will create all " << levels << " folders in: " << newFolder << std::endl;
	for(int i = (levels - 1) ; i >= 0 ; i--)
	{
		const std::string folder = removeDirLevels(newFolder, i);
		//std::cout << "CREATING FOLDER: " << folder << std::endl;
		if(!directoryExist(folder))
		{
			if(i == 0)
			{
				std::cout << "Creating folder: " << withoutLeadingDot(newFolder) << std::endl;
			}
			createDirectory(folder, false);
		}
	}
}



	
	

std::pair<std::string, std::vector<std::string> > SaveFolderHandler::createNewFolders(const int newNum, 
	const std::list<std::string>& baseFolders, const bool doCreate, const bool useConfiguredFolderPaths)
{	
	const std::string rootFolderPublic = getPublicRootFolder(useConfiguredFolderPaths);
	//std::cout << "WILL USE PUBLIC ROOT: " << rootFolderPublic << std::endl;
	
	const std::string currencyShortName = getCurrencyShortName();

	const std::string pubFolderPrefix("pub_" + currencyShortName + "_");
	const std::string pubFolderMiddle = "/" + pubFolderPrefix;
	
	const std::string newPubFolder = rootFolderPublic + "/" + pubFolderPrefix + intToString(newNum);

	createDirectoryFolders(newPubFolder, 4);

	if(!directoryExist(newPubFolder))
	{
		throw std::string("Error when creating public older");
	}



	std::vector<std::string> newPrivFolders;
	int pos(0);
	for(std::list<std::string>::const_iterator it = baseFolders.begin() ;
		it != baseFolders.end() ;
		++it)
	{
		pos++;
		const std::string baseFolder = (*it);
				
		const std::string fullBase = (baseFolder.empty() ? "cold" : (baseFolder + "/cold"));

		const std::string privFold(useConfiguredFolderPaths ? ("privpad" + intToString(pos)) : "priv");
		
		const std::string privFolder(fullBase + "/" + privFold);
	
		const std::string privCoinFolder = privFolder + "/" + currencyShortName;
		const std::string privFolderPrefix("priv_" + currencyShortName + "_");
	
	
		const std::string privFolderMiddle = "/" + privFolderPrefix;
	
		const std::string newPrivfolder = privCoinFolder + privFolderMiddle + intToString(newNum);
	
		//std::cout << "Creating the folder: " << newPubFolder << std::endl;
		if(doCreate)
		{
			createDirectoryFolders(newPrivfolder, 4);
			
			if(!directoryExist(newPrivfolder))
			{
				throw std::string("Error when creating private older");
			}			
		}
		
		newPrivFolders.push_back(newPrivfolder);
	}
	
	std::pair<std::string, std::vector<std::string> >	folders(newPubFolder, newPrivFolders);
	return folders;
}


