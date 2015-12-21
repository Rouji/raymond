#ifndef __VEC2_H
#define __VEC2_H

#include "types.h"
#include "maths.h"

namespace raymond
{

    template <class T>
    class vec2
    {
    public:
        T X; T Y; //x,y components

                       //constructors
        vec2() : X(0), Y(0) {} //default to all 0
        vec2(T x, T y) : X(x), Y(y) {}
        vec2(T n) : X(n), Y(n) {} //set all components to same value

        //copy constr.
        vec2(const vec2<T>& o) : X(o.X), Y(o.Y) {}

        //check 2 vectors for equality within a certain tolerance
        bool equals(const vec2<T> o, const T tolerance = (T)FLOAT_ROUNDING_ERROR_32) const
        {
            return equals(o.X, X, tolerance) &&
                equals(o.Y, Y, tolerance);
        }

        //set both of this vec2
        vec2<T>& set(T x, T y)
        {
            X = x;
            Y = y;
            return *this;
        }

        //set vec2 to be the same as another (essentially the same as the operator=)
        vec2<T>& set(const vec2<T>& o)
        {
            X = o.X;
            Y = o.Y;
            return *this;
        }

        //set both components to same value
        vec2<T>& set(T n)
        {
            X = n;
            Y = n;
            return *this;
        }

        T length()
        {
            return maths::squareroot(X*X + Y*Y);
        }

        T lengthSquared()
        {
            return X*X + Y*Y;
        }

        vec2<T>& normalise()
        {
            T len = length();

            //prevent div. by 0
            if (len == 0)
                return *this;

            X = (T)(X / len);
            Y = (T)(Y / len);
            return *this;
        }

        vec2<T>& invert()
        {
            X = -X;
            Y = -Y;
            return *this;
        }

        //set vector to given length, keeping its direction
        vec2<T>& setLength(T l)
        {
            normalise();
            *this *= l;
            return *this;
        }

        //distance to another vector
        T distance(const vec2<T>& o)
        {
            return (*this - o).length();
        }

        //squared distance to another vector
        T distanceSquared(const vec2<T>& o)
        {
            return (*this - o).lengthSquared();
        }

        //returns new vector linearly interpolated between this and the other one
        //d between 0.0 and 1.0
        //0.0 = entirely at this vector
        //1.0 = entirely at the other one
        vec2<T> interpolate(const vec2<T>& o, f64 d)
        {
            return *this + ((o - *this) * d);
        }

        //operators
        bool operator==(const vec2<T>& o)
        {
            return this->equals(o);
        }
        bool operator!=(const vec2<T>& o)
        {
            return !this->equals(o);
        }

        vec2<T>& operator=(const vec2<T>& o)
        {
            X = o.X;
            Y = o.Y;
            return *this;
        }

        vec2<T> operator+(const vec2<T>& o) const
        {
            return vec2<T>(X + o.X, Y + o.Y);
        }
        vec2<T>& operator+=(const vec2<T>& o)
        {
            X += o.X;
            Y += o.Y;
            return *this;
        }

        vec2<T> operator-() const
        {
            return vec2<T>(-X, -Y);
        }
        vec2<T> operator-(const vec2<T>& o) const
        {
            return vec2<T>(X - o.X, Y - o.Y);
        }
        vec2<T>& operator-=(const vec2<T>& o)
        {
            X -= o.X;
            Y -= o.Y;
            return *this;
        }

        //multiplies each component with the corresponding one of the other vector
        vec2<T> operator*(const vec2<T>& o) const
        {
            return vec2<T>(X * o.X, Y * o.Y);
        }
        vec2<T>& operator*=(const vec2<T>& o)
        {
            X *= o.X;
            Y *= o.Y;
            return *this;
        }
        //multiplies all 3 components by one scalar
        vec2<T> operator*(T n) const
        {
            return vec2(X * n, Y * n);
        }
        vec2<T>& operator*=(T n)
        {
            X *= n;
            Y *= n;
            return *this;
        }

        //divides each component by the corresponding one of the other vector
        vec2<T> operator/(const vec2<T>& o) const
        {
            return vec2<T>(X / o.X, Y / o.Y);
        }
        vec2<T>& operator/=(const vec2<T>& o)
        {
            X /= o.X;
            Y /= o.Y;
            return *this;
        }
        //divides all 3 components by one value
        vec2<T> operator/(T n) const
        {
            return vec2(X / n, Y / n);
        }
        vec2<T>& operator/=(T n)
        {
            X /= n;
            Y /= n;
            return *this;
        }
    };

    //convenient typedefs
    typedef vec2<f32> vec2f;
    typedef vec2<u32> vec2i;
    typedef vec2<u32> dim2i;

} //raymond
#endif // !__VEC2_H
