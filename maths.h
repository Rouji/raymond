#ifndef __MATHS_H
#define __MATHS_H
#include <math.h>

#include "types.h"

//maths functions and constants
//some mere proxies for math.h functions, just in case someone needs to 
//swap them out for other implementations

const f32 FLOAT_ROUNDING_ERROR_32 = 0.000001f;
const f64 FLOAT_ROUNDING_ERROR_64 = 0.0000001;

#ifndef PI
const f32 PI = 3.14159265359f;
#endif // !PI

const f32 DEG_TO_RAD = PI / 180.0f;

namespace raymond
{
namespace maths
{

//TODO: provide generic templated functions for all these, 
//instead of only specific implementations

//functions for comparing floating point numbers with a given tolerance
inline bool equals(f32 a, f32 b, f32 tolerance = FLOAT_ROUNDING_ERROR_32)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}
inline bool equals(f64 a, f64 b, f64 tolerance = FLOAT_ROUNDING_ERROR_64)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}

inline f32 squareroot(f32 n)
{
    return sqrtf(n);
}
inline f64 squareroot(f64 n)
{
    return sqrt(n);
}

inline f32 tangent(f32 n)
{
    return tanf(n);
}
inline f64 tangent(f64 n)
{
    return tan(n);
}

inline f32 cosine(f32 n)
{
    return cosf(n);
}
inline f64 cosine(f64 n)
{
    return cos(n);
}

template <class T>
inline T square(const T& n)
{
    return n*n;
}

template <class T>
inline T powf(const T& base, const T& exp)
{
    return (T)pow((f64)base, (f64)exp);
}

template <class T>
inline T min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template <class T>
inline T max(const T& a, const T& b)
{
    return a > b ? a : b;
}

template <class T>
inline T clamp(const T& n, const T& low, const T& high)
{
    return min(max(low, n), high);
}

} //maths
} //raymond
#endif // !__MATHS_H
