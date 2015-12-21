#ifndef __COLOUR_H
#define __COLOUR_H

#include "maths.h"
#include "types.h"

namespace raymond
{


//4 component (RGB+A) colour class
template <class T>
class col4
{
public:
    col4(T r = 0, T g = 0, T b = 0, T a = 0) :
        R(r), G(g), B(b), A(a)
    {}

    col4(const col4<T>& o)
    {
        R = o.R;
        G = o.G;
        B = o.B;
        A = o.A;
    }

    col4<T> clamp(const T& min, const T& max)
    {
        return col4<T>(maths::clamp(R, min, max),
                       maths::clamp(G, min, max),
                       maths::clamp(B, min, max),
                       maths::clamp(A, min, max));
    }

    bool operator==(const col4<T>& o)
    {
        return R == o.R &&
            G == o.G &&
            B == o.B &&
            A == o.A;
    }

    bool operator!=(const col4<T>& o)
    {
        return !(*this == o);
    }

    col4<T>& operator=(const col4<T>& o)
    {
        R = o.R;
        G = o.G;
        B = o.B;
        A = o.A;
        return *this;
    }

    col4<T> operator+(const col4<T>& o)
    {
        return col4<T>(R + o.R, G + o.G, B + o.B, A + o.A);
    }

    col4<T>& operator+=(const col4<T>& o)
    {
        R += o.R;
        G += o.g;
        B += o.B;
        A += o.A;
        return *this;
    }

    col4<T> operator-(const col4<T>& o)
    {
        return col4<T>(R - o.R, G - o.G, B - o.B, A - o.A);
    }

    col4<T>& operator-=(const col4<T>& o)
    {
        R -= o.R;
        G -= o.g;
        B -= o.B;
        A -= o.A;
        return *this;
    }

    col4<T> operator*(const col4<T>& o)
    {
        return col4<T>(R * o.R, G * o.G, B * o.B, A * o.A);
    }

    col4<T>& operator*=(const col4<T>& o)
    {
        R *= o.R;
        G *= o.g;
        B *= o.B;
        A *= o.A;
        return *this;
    }

    col4<T> operator/(const col4<T>& o)
    {
        return col4<T>(R / o.R, G / o.G, B / o.B, A / o.A);
    }

    col4<T>& operator/=(const col4<T>& o)
    {
        if (!equals(R, 0)) R /= o.R;
        if (!equals(G, 0)) G /= o.g;
        if (!equals(B, 0)) B /= o.B;
        if (!equals(A, 0)) A /= o.A;
        return *this;
    }

    T R;
    T G;
    T B;
    T A;
};

typedef col4<f32> col4f;

}

#endif // !__COLOUR_H
