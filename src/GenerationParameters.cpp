/**
 * GenerationParameters.cpp - Bitcoin address generator
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
 

#include "util.h"
#include "currencySpecific.h"
#include "SaveFolderHandler.h"
#include "GenerationParameters.h"

#include <iostream>
#include <stdlib.h>



//Should be called once after the parse is ready
void GenerationParameters::finally() const
{
	if(getName)
	{
		throw std::string("Error, no name provided");
	}
}




bool GenerationParameters::useCurrencySpecific(const std::string& arg)
{
	if(arg == "currencyspecific")
	{
		currencyspecific = true;
		return true;
	}
	
	return false;


}





void GenerationParameters::verifyNumWords(const int numWords)
{
	if(numWords == 0)
	{
		std::cout << "Incorrect number" << std::endl;			
		throw std::string("Incorrect number argument");
	}
	else if(numWords > 24)
	{
		std::cout << "Max 24 seed words allowed: " << numWords << std::endl;
		throw std::string("Incorrect number argument, too large");
	}		
	else if(numWords < 12)
	{
		std::cout << "Mnemonic too short, mnemomic with " << numWords << " words is NOT SECURE" << std::endl;
		std::cout << std::endl;
		throw std::string("Mnemonic too short");
	}
	
	
	
	if(numWords != 12 && numWords != 15 && numWords != 18
		 && numWords != 21 && numWords != 24)
	{
		std::cout << "Incorrect number of words: " << numWords << std::endl;
		std::cout << "Allowed values: " << "12, 15, 18, 21 or 24" << std::endl;
		throw std::string("Incorrect number text words");
	}
	
}





//Returns true is argument used, false otherwise
bool GenerationParameters::useArg(const std::string& arg)
{
	if(getName)
	{
		getName = false;
		accountName = arg;
		//std::cout << "Using name: " << accountName << std::endl;
		return true;
	}
	else if(getNumWords)
	{
		getNumWords = false;
		numWords = atoi(arg.c_str());
		verifyNumWords(numWords);
		
		//std::cout << "Using num words: " << numWords << std::endl;
		return true;
	}
	else if(getPasswordParam)
	{
		getPasswordParam = false;
		password = arg;
		std::cout << "Using password: " << password << std::endl;
		return true;
	}
	/*	
	else if(arg == "extaddr")
	{
		generateExtended = true;
		return true;
	}
	*/
	else if(arg == "nocounter")
	{
		counter = false;
		return true;
	}				
	else if(arg == "noextaddr")
	{
		generateExtended = false;
		return true;
	}			
	else if(arg == "nops")
	{
		generatePS = false;
		return true;
	}
	else if(arg == "notxt")
	{
		generateTXT = false;
		return true;		
	}
	else if(arg == "name")
	{
		getName = true;
		return true;		
	}
	else if(arg == "words")
	{
		getNumWords = true;
		return true;		
	}	
	else if(arg == "password")
	{
		getPasswordParam = true;
		return true;		
	}	
	else if(arg == "folder")
	{
		useFolder = true;
		return true;		
	}				
	else if(arg == "compressed")
	{
		compressed = true;
		return true;		
	}
	else if(arg == "uncompressed")
	{
		compressed = false;
		return true;
	}
	else if(arg == "printextendedlegacy")
	{
		printExtendedLegacy = true;
		return true;
	}
	
	return false;
}




void GenerationParameters::setAccountNameforFolder(const bool useFolder, const int newNum)
{
	//const int myNum = SaveFolderHandler::getNextNumber(useFolder); //AndCreateBaseFolders(useFolder);
	
	std::string accountName = getAccountName();
	if(useFolder && accountName.empty())
	{
		const std::string currency = getCurrencyShortName();
		accountName = currency + " address " + intToString(newNum);
	}
	
	setAccountName(accountName);
	
	//return myNum;
}




void GenerationParameters::parseArgs(const std::vector<std::string>& allExtraArgs)
{
	for(std::vector<std::string>::const_iterator it = allExtraArgs.begin() ;
		it != allExtraArgs.end() ;
		++it)
	{
		const std::string& arg = (*it);
		
		if(useArg(arg))
		{
			//Nothing
		}		
		else
		{
			std::cout << "Incorrect argument: " << arg << std::endl;
			throw std::string("Argument error");			
		}
	}
}

