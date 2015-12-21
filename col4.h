#ifndef __COLOUR_H
#define __COLOUR_H

#include "maths.h"
#include "types.h"
#include "vec3.h"

namespace raymond
{


//4 component (RGB+A) colour class
//pretty much just implements all basic operators
//to make colour maths easier
template <class T>
class col4
{
public:
    T R; T G; T B; T A;

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

    col4(const vec3<T>& o)
    {
        R = o.X;
        G = o.Y;
        B = o.Z;
        A = 0;
    }

    col4<T>& clamp(const T& min, const T& max)
    {
        R = maths::clamp(R, min, max);
        G = maths::clamp(G, min, max);
        B = maths::clamp(B, min, max);
        A = maths::clamp(A, min, max);
        return *this;
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
        G += o.G;
        B += o.B;
        A += o.A;
        return *this;
    }

    col4<T> operator-(const col4<T>& o) const
    {
        return col4<T>(R - o.R, G - o.G, B - o.B, A - o.A);
    }

    col4<T>& operator-=(const col4<T>& o)
    {
        R -= o.R;
        G -= o.G;
        B -= o.B;
        A -= o.A;
        return *this;
    }

    col4<T> operator*(const col4<T>& o) const
    {
        return col4<T>(R * o.R, G * o.G, B * o.B, A * o.A);
    }

    col4<T>& operator*=(const col4<T>& o)
    {
        R *= o.R;
        G *= o.G;
        B *= o.B;
        A *= o.A;
        return *this;
    }

    col4<T> operator*(const T& n) const
    {
        return col4<T>(R * n, G * n, B * n, A * n);
    }

    col4<T>& operator*=(const T& n)
    {
        R *= n;
        G *= n;
        B *= n;
        A *= n;
        return *this;
    }

    col4<T> operator/(const col4<T>& o) const
    {
        return col4<T>(R / o.R, G / o.G, B / o.B, A / o.A);
    }

    col4<T>& operator/=(const col4<T>& o)
    {
        if (!equals(R, 0)) R /= o.R;
        if (!equals(G, 0)) G /= o.G;
        if (!equals(B, 0)) B /= o.B;
        if (!equals(A, 0)) A /= o.A;
        return *this;
    }

    col4<T> operator/(const T& n) const
    {
        if (maths::equals(n, n)) return *this;
        return col4<T>(R / n, G / n, B / n, A / n);
    }

    col4<T>& operator/=(const T& n)
    {
        if (!equals(R, 0)) R /= n;
        if (!equals(G, 0)) G /= n;
        if (!equals(B, 0)) B /= n;
        if (!equals(A, 0)) A /= n;
        return *this;
    }
};

typedef col4<f32> col4f;

}

#endif // !__COLOUR_H
