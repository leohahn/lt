#ifndef LT_MATH_HPP
#define LT_MATH_HPP

#include <stdio.h>

#include "lt_core.hpp"
#include "math.h"

#ifndef LT_PI
#define LT_PI 3.14159265358979323846
#endif

struct Point3f
{
    f32 x, y, z;

    Point3f(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
};

struct Size2f
{
    f32 width, height;

    Size2f(f32 width, f32 height) : width(width), height(height) {}
};
/////////////////////////////////////////////////////////
//
// Vector
//
// Definition of a vector structure.
//

template<typename T>
union Vec2
{
    T val[2];
    struct {
        T x, y;
    };

    Vec2(T x, T y): x(x), y(y) {}

    inline Vec2<T> norm() const
    {
        f32 size = length();
        LT_Assert(size >= 0);
        return Vec2<T>(x / size, y / size);
    }

    inline f32 length() {return sqrt(x*x + y*y);}
    inline Vec2<T> operator-(Vec2<T> rhs) const {return Vec2<T>(x - rhs.x, y - rhs.y);}

    template<typename K>
    inline Vec2<T> operator*(K k) const {return Vec2<T>(x * k, y * k);}
};

typedef Vec2<i32> Vec2i;
typedef Vec2<f32> Vec2f;

template<typename T>
union Vec3
{
    T val[3];
    struct {
        T x, y, z;
    };
    struct {
        T r, g, b;
    };

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    inline Vec3<T> norm()
    {
        f32 size = length();
        LT_Assert(size >= 0);
        return Vec3<T>(x / size, y / size, z / size);
    }

    inline f32 length() {return sqrt(x*x + y*y + z*z);}

    template<typename K>
    inline Vec3<T> operator*(K k) {return Vec3<T>(x*k, y*k, z*k);}

    inline Vec3<T> operator-(Vec3<T> rhs) const {return Vec3<T>(x-rhs.x, y-rhs.y, z-rhs.z);}
    inline Vec3<T> operator-() const {return Vec3<T>(-x, -y, -z);}
    inline Vec3<T> operator+(Vec3<T> rhs) const {return Vec3<T>(x+rhs.x, y+rhs.y, z+rhs.z);}

    inline void operator-=(Vec3<T> rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    inline void operator+=(Vec3<T> rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
};

typedef Vec3<i32> Vec3i;
typedef Vec3<f32> Vec3f;

template<typename T>
union Vec4
{
    T val[4];
    struct {
        T x, y, z, w;
    };
    struct {
        T r, g, b, a;
    };

    Vec4(): x(0), y(0), z(0), w(0) {}
    Vec4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
    Vec4(Vec3<T> v, T w): x(v.x), y(v.y), z(v.z), w(w) {}

    inline Vec4<T> norm() const
    {
        f32 size = length();
        LT_Assert(size >= 0);
        return Vec4<T>(x / size, y / size, z / size, w / size);
    }

    inline f32 length() const {return sqrt(x*x + y*y + z*z + w*w);}
};

typedef Vec4<i32> Vec4i;
typedef Vec4<f32> Vec4f;

namespace lt
{

inline f32
radians(f32 angle) { return angle * (M_PI / 180.0f); }

template<typename T> inline T
dot(const Vec2<T> a, const Vec2<T> b) { return (a.x * b.x) + (a.y * b.y); }

template<typename T> inline T
dot(const Vec3<T> lhs, const Vec3<T> rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z); }

template<typename T> inline Vec2<T>
projection(const Vec2<T> p, const Vec2<T> plane)
{
    f32 alpha = lt::dot(p, plane) / lt::dot(plane, plane);
    return alpha * plane;
}

template<typename T> inline Vec3<T>
cross(const Vec3<T> a, const Vec3<T> b)
{
    return Vec3<T>((a.y * b.z) - (a.z * b.y),
                 (a.z * b.x) - (a.x * b.z),
                 (a.x * b.y) - (a.y * b.x));
}

}

/////////////////////////////////////////////////////////
//
// Matrix
//
// Column major
//
template<typename T>
union Mat4
{
    Mat4();
    Mat4(T diag);
    Mat4(T m00, T m01, T m02, T m03,
         T m10, T m11, T m12, T m13,
         T m20, T m21, T m22, T m23,
         T m30, T m31, T m32, T m33);

    inline Vec4<T> operator()(isize row, isize col) const
    {
        return m_col[row][col];
    }

    inline T *data() const
    {
        return (T*)&m_col[0].val[0];
    }

private:
    Vec4<T> m_col[4];
};

typedef Mat4<f32> Mat4f;

namespace lt
{

template<typename T> Mat4<T>
perspective(f32 fovy, f32 aspect_ratio, f32 znear, f32 zfar);

template<typename T> Mat4<T>
look_at(const Vec3<T> eye, const Vec3<T> center, const Vec3<T> up);

}

#endif // LT_MATH_HPP
