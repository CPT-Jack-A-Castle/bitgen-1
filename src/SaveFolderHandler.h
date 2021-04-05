#ifndef SAVE_FOLDER_HANDLER_H
#define SAVE_FOLDER_HANDLER_H

/**
 * wif .h - Bitcoin poscript generator
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
 
 
 
#include <string>
#include <vector>
#include <list> 



class SaveFolderHandler
{
public:
	static int getNextNumber();

	static std::string getPublicRootFolder(const bool useFolderConf);

	static std::pair<std::string, std::vector<std::string> > createNewFolders(const int newNum, 
		const std::list<std::string>& baseFolders, const bool doCreate = true, const bool useFolderConf = false);	
};


 
 
 
 #endif
 
