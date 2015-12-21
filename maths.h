#ifndef __MATHS_H
#define __MATHS_H
#include <math.h>

#define FLOAT_ROUNDING_ERROR_32 0.000001f
#define FLOAT_ROUNDING_ERROR_64 0.0000001

#ifndef PI
#define PI 3.14159265359f
#endif // !PI

namespace raymond
{
namespace maths
{

//TODO: provide generic templated functions for all these, 
//instead of only specific implementations

//functions for comparing floating point numbers with a given tolerance
inline bool equals(float a, float b, float tolerance = FLOAT_ROUNDING_ERROR_32)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}
inline bool equals(double a, double b, double tolerance = FLOAT_ROUNDING_ERROR_64)
{
    return (a + tolerance >= b) && (a - tolerance <= b);
}

inline float squareroot(float n)
{
    return sqrtf(n);
}
inline double squareroot(double n)
{
    return sqrt(n);
}

inline float tangent(float n)
{
    return tanf(n);
}
inline double tangent(double n)
{
    return tan(n);
}

template <class T>
inline T square(const T& n)
{
    return n*n;
}

template <class T>
inline T clamp(const T& n, const T& max, const T& min)
{
    if (n < min) return min;
    if (n > max) return max;
    return n;
}

} //maths
} //raymond
#endif // !__MATHS_H
