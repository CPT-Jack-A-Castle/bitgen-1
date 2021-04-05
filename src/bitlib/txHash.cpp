
#include "txHash.h"



bool operator==(const TxHash& a, const TxHash& b)
{
	return (a.str == b.str);
}


bool operator!=(const TxHash& a, const TxHash& b)
{
	return !(a == b);
}

bool operator<(const TxHash& a, const TxHash& b)
{
	return (a.str < b.str);
}


bool operator>(const TxHash& a, const TxHash& b)
{
	return (a.str > b.str);
}

