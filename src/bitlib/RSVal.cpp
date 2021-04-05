
#include "RSVal.h"
#include "bitcoinEC.h"


bool RSVal::lowS() const
{
	BitcoinEllipticCurve ec;

	const BigInt<1024> nHalf = (ec.n >> 1);
	return !(s > nHalf);		
}


RSVal RSVal::getLowS() const
{
	BitcoinEllipticCurve ec;

	const BigInt<1024> nHalf = (ec.n >> 1);
	
	if(s > nHalf)
	{
		//std::cout << "CALCULATING THE LOW S VALUE" << std::endl;
		const BigInt<1024> s2 = ec.n - s;
		const RSVal rs2(r, s2);
		return rs2;
	}
	else
	{
		return (*this);
	}
}

