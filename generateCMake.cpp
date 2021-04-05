
#include <iostream>
#include <set>


#include <sys/types.h>
#include <dirent.h>

#include "util.h"
#include "FileUtil.h"


class Directory
{
public:
	Directory(const std::string& path) : dir(0)
	{
		dir = opendir(path.c_str());
		if(dir == 0)
		{
			std::string errMsg("Could not open dir: ");
			errMsg += path;
			throw errMsg;
		}		
	}

	~Directory()
	{
		closedir(dir);
	}


	bool readEntry(std::string& fname) const
	{		
		for(;;)
		{
			const struct dirent* dirEntry = readdir(dir);
			if(dirEntry == 0)
			{
				return false;
			}
		
			const std::string filename(dirEntry->d_name);
			if(filename == "." || filename == "..")
			{
				continue;
			}

			fname = filename;
			return true;
		}
	}

private:
	DIR* dir; 
};









class CppFile
{
public:
	CppFile(const std::string& inPath, const std::string& inFilename) : 
		path(inPath), filename(inFilename) {}
	
	
	
	const std::string path;
	const std::string filename;
};

bool operator<(const CppFile& a, const CppFile& b)
{
	if(a.path < b.path)
	{
		return true;
	}
	else if(b.path < a.path)
	{
		return false;
	}
	else
	{
		return (a.filename < b.filename);
	}
}





std::string cppFileDependency(const CppFile& thefile)
{
	std::string ret;

	ret += "\t";	
	
	if(!thefile.path.empty())
	{
		ret += thefile.path;
		ret += "/";
	}
	
	ret += thefile.filename;
	
	return ret;
}



std::string cFileDependency(const std::string& filename)
{
	std::string ret;
		
	ret += "\tqrenc/";
	ret += filename;
	
	return ret;
}



std::string exeName(const std::string& coin)
{
	if(coin == "bitcoin")
	{
		return "bitgen";
	}
	else if(coin == "btc")
	{
		return "bitgen-btc";
	}
	else if(coin == "bitcoincash")
	{
		return "bitgen-bch";
	}		
	else if(coin == "litecoin")
	{
		return "bitgen-ltc";
	}
	else if(coin == "namecoin")
	{
		return "bitgen-nmc";
	}
	else if(coin == "peercoin")
	{
		return "bitgen-ppc";
	}
	else if(coin == "dogecoin")
	{
		return "bitgen-doge";
	}
	else if(coin == "vertcoin")
	{
		return "bitgen-vtc";
	}
	else if(coin == "feathercoin")
	{
		return "bitgen-ftc";
	}			
	else
	{
		std::cerr << "Unknown coin: " << coin << std::endl;
		throw std::string("Unknown coin");
	}
	
}









int doTheWork(const std::string& param)
{	
	std::cout << std::endl;	
	std::cout << std::endl;

	std::cout << "cmake_minimum_required (VERSION 2.6)" << std::endl;
	std::cout << "project (bitgen)" << std::endl;
	std::cout << std::endl;

	std::cout << "include_directories(" << std::endl;
	std::cout << "\t." << std::endl;
	std::cout << "\t.." << std::endl;
	std::cout << "\tbitlib" << std::endl;
	std::cout << "\tbitlib/bigintctl" << std::endl;
	std::cout << "\tbitgen" << std::endl;
	std::cout << "\tqrenc" << std::endl;
	std::cout << "\targon" << std::endl;
	std::cout << ")" << std::endl;
	std::cout << std::endl;

	std::cout << "add_definitions(\"-DHAVE_CONFIG_H -O2 -msse2\")" << std::endl;
	std::cout << std::endl;


	std::cout << std::endl;
	std::cout << std::endl;
		





	
	
	Directory thisDir("src");

	std::set<CppFile> filenames;
	std::set<std::string> c_filenames;

	for(;;)
	{
		std::string filename;
		if(!thisDir.readEntry(filename))
		{
			break;
		}
	
		if(endsWith(filename, "_specific.cpp"))
		{
			continue;
		}

		if(filename == "currencySpecific.cpp")
		{
			continue;
		}



		if(startsWith(filename, "bitgen_"))
		{
			continue;
		}

		if(filename == "bitsig.cpp" || filename == "bitcry.cpp" | filename == "bitcalc.cpp")
		{
			continue;
		}
	
		if(endsWith(filename, ".cpp"))
		{
			CppFile theFile("", filename);
			filenames.insert(theFile);
		}
		else if(endsWith(filename, ".c"))
		{
			c_filenames.insert(filename);
		}
	}
	
	
	Directory argonDir("src/argon");
	for(;;)
	{
		std::string filename;
		if(!argonDir.readEntry(filename))
		{
			break;
		}
	
		if(endsWith(filename, ".cpp"))
		{
			CppFile myFile("argon", filename);
			filenames.insert(myFile);
		}
	
	}

	Directory bitgenDir("src/bitgen");
	for(;;)
	{
		std::string filename;
		if(!bitgenDir.readEntry(filename))
		{
			break;
		}
	
		if(endsWith(filename, ".cpp"))
		{
			CppFile myFile("bitgen", filename);
			filenames.insert(myFile);
		}
	
	}

	
	Directory bigintDir("src/bitlib/bigintctl");
	for(;;)
	{
		std::string filename;
		if(!bigintDir.readEntry(filename))
		{
			break;
		}
	
		if(endsWith(filename, ".cpp"))
		{
			CppFile myFile("bitlib/bigintctl", filename);
			filenames.insert(myFile);
		}
	
	}
	

	Directory bitlibDir("src/bitlib");
	for(;;)
	{
		std::string filename;
		if(!bitlibDir.readEntry(filename))
		{
			break;
		}
	
		if(endsWith(filename, "_specific.cpp"))
		{
			continue;
		}

		if(filename == "currencySpecific.cpp")
		{
			continue;
		}
	
	
		if(endsWith(filename, ".cpp"))
		{
			CppFile myFile("bitlib", filename);
			filenames.insert(myFile);
		}
	
	}

	
	
	Directory qrencDir("src/qrenc");
	for(;;)
	{
		std::string filename;
		if(!qrencDir.readEntry(filename))
		{
			break;
		}
		
		if(endsWith(filename, ".c"))
		{
			c_filenames.insert(filename);
		}
		
	}
	
	

	std::set<CppFile> compileFilename = filenames;
	

	std::cout << "add_library(bitgenl STATIC " << std::endl;
	
	for(std::set<CppFile>::const_iterator it = compileFilename.begin();
		it != compileFilename.end() ;
		++it)
	{
		CppFile myfile = (*it);
		
		std::cout << cppFileDependency(myfile) << std::endl;		
	}
 


	for(std::set<std::string>::const_iterator it = c_filenames.begin();
		it != c_filenames.end() ;
		++it)
	{
		const std::string& filename = (*it);
		std::cout << cFileDependency(filename) << std::endl;		
	}

	std::cout << ")\n";




	std::cout << std::endl;

	std::set<std::string> coins;
	coins.insert("bitcoin");
	coins.insert("bitcoincash");	
	coins.insert("litecoin");
	coins.insert("dogecoin");
	coins.insert("namecoin");
	coins.insert("peercoin");
	coins.insert("vertcoin");
	coins.insert("feathercoin");


	for(std::set<std::string>::const_iterator it = coins.begin() ;
		it != coins.end() ;
		++it)
	{
		const std::string& coin = (*it);

		std::string myfilename ="currencySpecific_" + coin + "_specific.cpp";

		std::cout << "add_executable(" << exeName(coin) << " bitlib/" << myfilename 
			<< " bitgen_" << coin << ".cpp)" << std::endl;				
	}

	std::cout << "add_executable(bitsig bitlib/currencySpecific_bitcoin_specific.cpp bitsig.cpp)" << std::endl;				

	std::cout << std::endl;

	for(std::set<std::string>::const_iterator it = coins.begin() ;
		it != coins.end() ;
		++it)
	{
		const std::string& coin = (*it);

		std::string myfilename ="currencySpecific_" + coin + "_specific.cpp";

		std::cout << "target_link_libraries(" << exeName(coin) << " LINK_PUBLIC bitgenl)" << std::endl;
	}

	std::cout << "target_link_libraries(bitsig LINK_PUBLIC bitgenl)" << std::endl;
	std::cout << std::endl;

}



int main(int argc, const char** argv)
{
	std::string param;
	if(argc > 1)
	{
		param = argv[1];
		//std::cout << "Arg: " << param << std::endl;
	}
	
	try
	{
		doTheWork(param);
	}
	catch(const std::string& err)
	{
		std::cerr << "Error: " << err << std::endl;
	}
}
