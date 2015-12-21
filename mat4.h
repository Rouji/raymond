#ifndef __MAT4_H
#define __MAT4_H

#include "maths.h"
#include "vec3.h"

#include <string.h> //for memset etc.

namespace raymond
{

template <class T>
class mat4
{
public:
    enum mat4ConstType
    {
        MAT4CONST_EMPTY = 0,
        MAT4CONST_IDENTITY
    };

    mat4(mat4ConstType type = MAT4CONST_IDENTITY);
    mat4(const mat4<T>& o);

    //set matrix to identity
    mat4<T>& makeId();

    //set this matrix to the product of 2 others
    mat4<T>& setProduct(const mat4<T>& a, const mat4<T>& b);

    //set translation of the matrix
    mat4<T>& setTranslation(const vec3<T>& t);
    //get translation set in the matrix
    vec3<T> getTranslation();

    //set scale of the matrix
    mat4<T>& setScale(const vec3<T>& s);
    //set scale of all 3 directions to single value
    mat4<T>& setScale(const T& s);
    //get scale set in the matrix
    vec3<T> getScale();


    //TODO: rotation


    //transform a vector by this matrix
    vec3<T> transform(const vec3<T>& v);

    
    bool operator==(const mat4<T>& o);
    bool operator!=(const mat4<T>& o);

    mat4<T>& operator=(const mat4<T>& o); //set equal to other matrix
    mat4<T>& operator=(T& n); //set all elements to one value

    //simple add/sub
    mat4<T> operator+(const mat4<T>& o);
    mat4<T>& operator+=(const mat4<T>& o);
    mat4<T> operator-(const mat4<T>& o);
    mat4<T>& operator-=(const mat4<T>& o);

    //product of 2 matrices
    mat4<T> operator*(const mat4<T>& o);
    mat4<T>& operator*=(const mat4<T>& o);

    //multiplication by single scalar
    mat4<T> operator*(const T& n);
    mat4<T>& operator*=(const T& o);

    //access element at row/col
    T& operator()(int row, int col);

private:
    T M[16]; //matrix data
};

template<class T>
inline mat4<T>::mat4(mat4ConstType type)
{
    if (type == MAT4CONST_IDENTITY)
    {
        makeId();
    }
    else if (type == MAT4CONST_EMPTY)
    {
        memset(M, 0, 16 * sizeof(T));
    }
}

template<class T>
inline mat4<T>::mat4(const mat4<T>& o)
{
    memcpy(M, o.M, 16 * sizeof(T));
}

template<class T>
inline mat4<T>& mat4<T>::makeId()
{
    memset(M, 0, 16 * sizeof(T));
    M[0 * 4 + 0] = 1;
    M[1 * 4 + 1] = 1;
    M[2 * 4 + 2] = 1;
    M[3 * 4 + 3] = 1;
    return *this;
}

template<class T>
inline mat4<T>& mat4<T>::setProduct(const mat4<T>& a, const mat4<T>& b)
{
    M[ 0] = a.M[ 0] * b.M[ 0] + a.M[ 4] * b.M[ 1] + a.M[ 8] * b.M[ 2] + a.M[12] * b.M[ 3];
    M[ 1] = a.M[ 1] * b.M[ 0] + a.M[ 5] * b.M[ 1] + a.M[ 9] * b.M[ 2] + a.M[13] * b.M[ 3];
    M[ 2] = a.M[ 2] * b.M[ 0] + a.M[ 6] * b.M[ 1] + a.M[10] * b.M[ 2] + a.M[14] * b.M[ 3];
    M[ 3] = a.M[ 3] * b.M[ 0] + a.M[ 7] * b.M[ 1] + a.M[11] * b.M[ 2] + a.M[15] * b.M[ 3];

    M[ 4] = a.M[ 0] * b.M[ 4] + a.M[ 4] * b.M[ 5] + a.M[ 8] * b.M[ 6] + a.M[12] * b.M[ 7];
    M[ 5] = a.M[ 1] * b.M[ 4] + a.M[ 5] * b.M[ 5] + a.M[ 9] * b.M[ 6] + a.M[13] * b.M[ 7];
    M[ 6] = a.M[ 2] * b.M[ 4] + a.M[ 6] * b.M[ 5] + a.M[10] * b.M[ 6] + a.M[14] * b.M[ 7];
    M[ 7] = a.M[ 3] * b.M[ 4] + a.M[ 7] * b.M[ 5] + a.M[11] * b.M[ 6] + a.M[15] * b.M[ 7];

    M[ 8] = a.M[ 0] * b.M[ 8] + a.M[ 4] * b.M[ 9] + a.M[ 8] * b.M[10] + a.M[12] * b.M[11];
    M[ 9] = a.M[ 1] * b.M[ 8] + a.M[ 5] * b.M[ 9] + a.M[ 9] * b.M[10] + a.M[13] * b.M[11];
    M[10] = a.M[ 2] * b.M[ 8] + a.M[ 6] * b.M[ 9] + a.M[10] * b.M[10] + a.M[14] * b.M[11];
    M[11] = a.M[ 3] * b.M[ 8] + a.M[ 7] * b.M[ 9] + a.M[11] * b.M[10] + a.M[15] * b.M[11];

    M[12] = a.M[ 0] * b.M[12] + a.M[ 4] * b.M[13] + a.M[ 8] * b.M[14] + a.M[12] * b.M[15];
    M[13] = a.M[ 1] * b.M[12] + a.M[ 5] * b.M[13] + a.M[ 9] * b.M[14] + a.M[13] * b.M[15];
    M[14] = a.M[ 2] * b.M[12] + a.M[ 6] * b.M[13] + a.M[10] * b.M[14] + a.M[14] * b.M[15];
    M[15] = a.M[ 3] * b.M[12] + a.M[ 7] * b.M[13] + a.M[11] * b.M[14] + a.M[15] * b.M[15];
    return *this;
}

template<class T>
inline mat4<T>& mat4<T>::setTranslation(const vec3<T>& t)
{
    M[3 * 4 + 0] = t.X;
    M[3 * 4 + 1] = t.Y;
    M[3 * 4 + 2] = t.Z;
    return *this;
}

template<class T>
inline vec3<T> mat4<T>::getTranslation()
{
    return vec3<T>(M[3 * 4 + 0],
                   M[3 * 4 + 1],
                   M[3 * 4 + 2]);
}

template<class T>
inline mat4<T>& mat4<T>::setScale(const vec3<T>& s)
{
    M[0 * 4 + 0] = s.X;
    M[1 * 4 + 1] = s.Y;
    M[2 * 4 + 2] = s.Z;
    return *this;
}

template<class T>
inline mat4<T>& mat4<T>::setScale(const T & s)
{
    M[0 * 4 + 0] = s;
    M[1 * 4 + 1] = s;
    M[2 * 4 + 2] = s;
    return *this;
}

template<class T>
inline vec3<T> mat4<T>::getScale()
{
    return vec3<T>(M[0 * 4 + 0],
                   M[1 * 4 + 1],
                   M[2 * 4 + 2]);
}

template<class T>
inline vec3<T> mat4<T>::transform(const vec3<T>& v)
{
    T result[3];

    result[0] = v.X*M[0] + v.Y*M[4] + v.Z*M[ 8] + M[12];
    result[1] = v.X*M[1] + v.Y*M[5] + v.Z*M[ 9] + M[13];
    result[2] = v.X*M[2] + v.Y*M[6] + v.Z*M[10] + M[14];

    return vec3<T>(result[0],result[1],result[2]);
}

template<class T>
inline bool mat4<T>::operator==(const mat4<T>& o)
{
    for (int i = 0; i < 16; i++)
    {
        if (M[i] != o.M[i])
            return false;
    }
    return true;
}

template<class T>
inline bool mat4<T>::operator!=(const mat4<T>& o)
{
    return !(*this == o);
}

template<class T>
inline mat4<T>& mat4<T>::operator=(const mat4<T>& o)
{
    memcpy(M, o.M, 16 * sizeof(T));
    return *this;
}

template<class T>
inline mat4<T>& mat4<T>::operator=(T & n)
{
    for (int i = 0; i < 16; i++)
    {
        M[i] = n;
    }
    return *this;
}

template<class T>
inline mat4<T> mat4<T>::operator+(const mat4<T>& o)
{
    mat4 tmp(MAT4CONST_EMPTY);
    for (int i = 0; i < 16; i++)
    {
        tmp.M[i] = M[i] + o.M[i];
    }
    return tmp;
}

template<class T>
inline mat4<T>& mat4<T>::operator+=(const mat4<T>& o)
{
    for (int i = 0; i < 16; i++)
    {
        M[i] += o.M[i];
    }
    return *this;
}

template<class T>
inline mat4<T> mat4<T>::operator-(const mat4<T>& o)
{
    mat4 tmp(MAT4CONST_EMPTY);
    for (int i = 0; i < 16; i++)
    {
        tmp.M[i] = M[i] - o.M[i];
    }
    return tmp;
}

template<class T>
inline mat4<T>& mat4<T>::operator-=(const mat4<T>& o)
{
    for (int i = 0; i < 16; i++)
    {
        M[i] -= o.M[i];
    }
    return *this;
}

template<class T>
inline mat4<T> mat4<T>::operator*(const mat4<T>& o)
{
    mat4<T> tmp(MAT4CONST_EMPTY);
    tmp.setProduct(*this, o);
    return tmp;
}

template<class T>
inline mat4<T>& mat4<T>::operator*=(const mat4<T>& o)
{
    mat4<T> tmp(*this);
    return setProduct(tmp, o);
}

template<class T>
inline mat4<T> mat4<T>::operator*(const T & n)
{
    mat4<T> tmp(MAT4CONST_EMPTY);
    for (int i = 0; i < 16; i++)
    {
        tmp[i] = M[i] * n;
    }
    return tmp;
}

template<class T>
inline mat4<T>& mat4<T>::operator*=(const T & o)
{
    mat4<T> tmp(MAT4CONST_EMPTY);
    for (int i = 0; i < 16; i++)
    {
        tmp[i] = M[i] * o.M[i];
    }
    return tmp;
}

template<class T>
inline T & mat4<T>::operator()(int row, int col)
{
    return M[col + 4 * row];
}


typedef mat4<float> mat4f;

}//raymond
#endif // !__MAT4_H

