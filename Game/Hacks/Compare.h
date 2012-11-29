#ifndef _COMPARE_H_
#define _COMPARE_H_

#include <sstream>

template<class T>
inline int Compare( const T a, const T b )
{
	if ( a > b ) return 1;
	else if ( a < b ) return -1;
	else return 0;
}

#endif