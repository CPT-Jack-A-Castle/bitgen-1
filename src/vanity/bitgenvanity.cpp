/**
 * bitgencli.cpp - Bitcoin address generator
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
 



#include "test/unittest.h"
#include "bitgenVersion.h"
#include "bitlibVersion.h"
#include "RangeSearcher.h"
#include "currencySpecific.h"
#include "VanitySearcher.h"
#include "VanityCommandline.h"
#include "util.h"


#include <iostream>
#include <time.h>


void printvanityVersion()
{
	std::cout << "bitvanity version " << versionNumber << std::endl;
	std::cout << std::endl;
	//std::cout << "using bigint " << BigInt<0>::version() << std::endl;
	//std::cout << "using bitlib version " << bitlibVersionNumber << std::endl;
	//std::cout << std::endl;

	std::cout << "Currency: " << getCurrencyName() << " (" << getCurrencyShortName() << ")" << std::endl;
	std::cout << std::endl;
		
	std::cout << "http://bitgen.org/" << std::endl;		
}


void doVanityWork(int argc, char* argv[])
{		
	time_t t = time(0);
	const std::string thetime = removeNewline(asctime(localtime(&t)));

	if(argc < 2)
	{
		//std::cout << "For help, use \"bitvanity-" << getCurrencyShortName() << " help\"" << std::endl;
		std::cout << "Usage: bitvanity version" << std::endl;		
		std::cout << "       bitvanity vanity" << std::endl;
		std::cout << "       bitvanity vanityPool" << std::endl;
		std::cout << "       bitvanity vanityPoolResult" << std::endl;
		
		throw std::string("Missing argument");
		return;
	}

	const std::string firstArg(argv[1]);

	if(firstArg == "version" || firstArg == "-v")
	{
		printvanityVersion();
	}			
	else if(firstArg == "vanity")
	{
		VanityCommandline::generateVanity(argc, argv, thetime, false);
	}
	else if(firstArg == "vanityPool")
	{
		VanityCommandline::generateVanity(argc, argv, thetime, true);
	}
	else if(firstArg == "vanityPoolResult")
	{
		VanityCommandline::generateVanityPoolResult(argc, argv, thetime, true);
	}	
	else
	{
		std::cerr << "Unknown command: " << argv[1] << std::endl;
	}
	
}

