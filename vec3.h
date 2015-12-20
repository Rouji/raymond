#ifndef __VEC3_H
#define __VEC3_H

#include "maths.h"
namespace raymond
{
template <class T> 
class vec3
{
public:
	T X; T Y; T Z; //x,y,z components

	//constructors
	vec3() : X(0), Y(0), Z(0) {} //default to all 0
	vec3(T x, T y, T z) : X(x), Y(y), Z(z) {}
	vec3(T n) : X(n), Y(n), Z(n) {} //set all components to same value

	//copy constr.
	vec3(const vec3<T>& o) : X(o.X), Y(o.Y), Z(o.Z) {}

	//check 2 vectors for equality within a certain tolerance
	bool equals(const vec3<T> o, const T tolerance = (T)FLOAT_ROUNDING_ERROR_32) const
	{
		return equals(o.X, X, tolerance) && 
			equals(o.Y, Y, tolerance) && 
			equals(o.Z, Z, tolerance);
	}

	//set all 3 components of this vec3
	vec3<T>& set(T x, T y, T z)
	{
		X = x;
		Y = y;
		Z = z;
		return *this;
	}

	//set vec3 to be the same as another (essentially the same as the operator=)
	vec3<T>& set(const vec3<T>& o)
	{
		X = o.X;
		Y = o.Y;
		Z = o.Z;
		return *this;
	}

    //set all 3 components to same value
    vec3<T>& set(T n)
    {
        X = n;
        Y = n;
        Z = n;
        return *this;
    }

	T length()
	{
		return maths::squareroot(X*X + Y*Y + Z*Z);
	}

	T lengthSquared()
	{
		return X*X + Y*Y + Z*Z;
	}

    vec3<T>& normalise()
    {
        T len = length();

        //prevent div. by 0
        if (len == 0) 
            return *this;

        X = (T)(X / len);
        Y = (T)(Y / len);
        Z = (T)(Z / len);
        return *this;
    }

    vec3<T>& invert()
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        return *this;
    }

    //set vector to given length, keeping its direction
    vec3<T>& setLength(T l)
    {
        normalise();
        *this *= l;
        return *this;
    }

    //distance to another vector
    T distance(const vec3<T>& o)
    {
        return (*this - o).length();
    }

    //squared distance to another vector
    T distanceSquared(const vec3<T>& o)
    {
        return (*this - o).lengthSquared();
    }

	//dot product
	T dot(const vec3<T>& o)
	{
		return X*o.X + Y*o.Y + Z*o.Z;
	}

	//cross product
	vec3<T> cross(const vec3<T>& o)
	{
        return vec3<T>(Y*o.Z - Z*o.Y,
			           Z*o.X - X*o.Z,
                       X*o.Y - Y*o.X);
	}

	//operators
	bool operator==(const vec3<T>& o)
	{
		return this->equals(o);
	}
	bool operator!=(const vec3<T>& o)
	{
		return !this->equals(o);
	}

	vec3<T>& operator=(const vec3<T>& o)
	{
		X = o.X;
		Y = o.Y;
		Z = o.Z;
		return *this;
	}

	vec3<T> operator+(const vec3<T>& o) const
	{
		return vec3<T>(X + o.X, Y + o.Y, Z + o.Z);
	}
	vec3<T>& operator+=(const vec3<T>& o)
	{
		X += o.X;
		Y += o.Y;
		Z += o.Z;
		return *this;
	}

    vec3<T> operator-() const
    {
        return vec3<T>(-X, -Y, -Z);
    }
	vec3<T> operator-(const vec3<T>& o) const
	{
		return vec3<T>(X - o.X, Y - o.Y, Z - o.Z);
	}
	vec3<T>& operator-=(const vec3<T>& o)
	{
		X -= o.X;
		Y -= o.Y;
		Z -= o.Z;
		return *this;
	}

	//multiplies each component with the corresponding one of the other vector
	vec3<T> operator*(const vec3<T>& o) const
	{
		return vec3<T>(X * o.X, Y * o.Y, Z * o.Z);
	}
	vec3<T>& operator*=(const vec3<T>& o)
	{
		X *= o.X;
		Y *= o.Y;
		Z *= o.Z;
		return *this;
	}
	//multiplies all 3 components by one scalar
	vec3<T> operator*(T n) const
	{
		return vec3(X * n, Y * n, Z * n);
	}
	vec3<T>& operator*=(T n)
	{
		X *= n;
		Y *= n;
		Z *= n;
		return *this;
	}

	//divides each component by the corresponding one of the other vector
	vec3<T> operator/(const vec3<T>& o) const
	{
		return vec3<T>(X / o.X, Y / o.Y, Z / o.Z);
	}
	vec3<T>& operator/=(const vec3<T>& o)
	{
		X /= o.X;
		Y /= o.Y;
		Z /= o.Z;
		return *this;
	}
	//divides all 3 components by one value
	vec3<T> operator/(T n) const
	{
		return vec3(X / n, Y / n, Z / n);
	}
	vec3<T>& operator/=(T n)
	{
		X /= n;
		Y /= n;
		Y /= n;
		return *this;
	}
};

//convenient typedef
typedef vec3<float> vec3f;

} //raymond
#endif // !__VEC3_H
