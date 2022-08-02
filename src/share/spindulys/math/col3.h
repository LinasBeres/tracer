#ifndef SPINDULYS_COL3_H
#define SPINDULYS_COL3_H

#include <cstddef>
#include <assert.h>
#include <iostream>

#include "../../spindulys.h"
#include "../platform.h"

#include "constants.h"

SPINDULYS_NAMESPACE_OPEN_SCOPE

////////////////////////////////////////////////////////////////////////////////
/// RGB Color Class
////////////////////////////////////////////////////////////////////////////////

template<typename T> struct Col3
{
	T r, g, b;

	////////////////////////////////////////////////////////////////////////////////
	/// Construction
	////////////////////////////////////////////////////////////////////////////////

	__forceinline Col3           ( )                   { }
	__forceinline Col3           ( const Col3& other ) { r = other.r; g = other.g; b = other.b; }
	__forceinline Col3& operator=( const Col3& other ) { r = other.r; g = other.g; b = other.b; return *this; }

	__forceinline explicit Col3 (const T& v)                         : r(v), g(v), b(v) {}
	__forceinline          Col3 (const T& r, const T& g, const T& b) : r(r), g(g), b(b) {}

	////////////////////////////////////////////////////////////////////////////////
	/// Constants
	////////////////////////////////////////////////////////////////////////////////

	__forceinline Col3 (ZeroTy)   : r(zero)   , g(zero)   , b(zero)    {}
	__forceinline Col3 (OneTy)    : r(one)    , g(one)    , b(one)     {}
	__forceinline Col3 (PosInfTy) : r(pos_inf), g(pos_inf), b(pos_inf) {}
	__forceinline Col3 (NegInfTy) : r(neg_inf), g(neg_inf), b(neg_inf) {}
};

/*! output operator */
template<typename T> inline std::ostream& operator<<(std::ostream& cout, const Col3<T>& a) {
	return cout << "(" << a.r << ", " << a.g << ", " << a.b << ")";
}

/*! default template instantiations */
typedef Col3<unsigned char> Col3uc;
typedef Col3<float        > Col3f;

SPINDULYS_NAMESPACE_CLOSE_SCOPE

#endif //SPINDULYS_COL3_H
