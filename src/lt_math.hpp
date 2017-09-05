#ifndef LT_MATH_HPP
#define LT_MATH_HPP

#include <stdio.h>
#include <cmath>
#include <iostream>

#include "lt_core.hpp"
#include "math.h"

#ifndef LT_PI
#define LT_PI 3.14159265358979323846
#endif

struct Point3f
{
    f32 x, y, z;

    explicit Point3f(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}
};

struct Size2f
{
    f32 width, height;

    explicit Size2f(f32 width, f32 height) : width(width), height(height) {}
};
/////////////////////////////////////////////////////////
//
// Vector2
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

    explicit Vec2(T x, T y): x(x), y(y) {}

    inline const Vec2<T>& operator-(Vec2<T> rhs) const {return Vec2<T>(x - rhs.x, y - rhs.y);}
};

template<typename T> static inline Vec2<T>
operator*(const Vec2<T>& v, f32 k)
{
    return Vec2<T>(v.x * k, v.y * k);
}
template<typename T> static inline Vec2<T>
operator*(const Vec2<T>& v, f64 k)
{
    return Vec2<T>(v.x * k, v.y * k);
}

/////////////////////////////////////////////////////////
//
// Vector3
//
// Definition of a vector structure.
//

template<typename T>
union Vec3
{
    T val[3];
    struct
    {
        T x, y, z;
    };
    struct
    {
        T r, g, b;
    };
    struct
    {
        T i, j, k;
    };

    explicit Vec3() : x(0), y(0), z(0) {}
    explicit Vec3(T val) : x(val), y(val), z(val) {}
    explicit Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

    inline Vec3<T> operator-(const Vec3<T>& rhs) const { return Vec3<T>(x-rhs.x, y-rhs.y, z-rhs.z); }
    inline Vec3<T> operator-()                   const { return Vec3<T>(-x, -y, -z); }
    inline Vec3<T> operator+(const Vec3<T>& rhs) const { return Vec3<T>(x+rhs.x, y+rhs.y, z+rhs.z); }

    inline void operator-=(const Vec3<T>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    inline void operator+=(const Vec3<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
};

template<typename T> static inline Vec3<T>
operator*(const Vec3<T>& v, f32 k)
{
    return Vec3<T>(v.x*k, v.y*k, v.z*k);
}
template<typename T> static inline Vec3<T>
operator*(f32 k, const Vec3<T>& v)
{
    return Vec3<T>(v.x*k, v.y*k, v.z*k);
}
template<typename T> static inline Vec3<T>
operator*(const Vec3<T>& v, f64 k)
{
    return Vec3<T>(v.x*k, v.y*k, v.z*k);
}
template<typename T> static inline Vec3<T>
operator*(f64 k, const Vec3<T>& v)
{
    return Vec3<T>(v.x*k, v.y*k, v.z*k);
}

/////////////////////////////////////////////////////////
//
// Vector3
//
// Definition of a vector structure.
//

template<typename T>
union Vec4
{
    T val[4];
    struct
    {
        T x, y, z, w;
    };
    struct
    {
        T r, g, b, a;
    };

    explicit Vec4(): x(0), y(0), z(0), w(0) {}
    explicit Vec4(T x, T y, T z, T w): x(x), y(y), z(z), w(w) {}
    explicit Vec4(const Vec3<T>& v, T w): x(v.x), y(v.y), z(v.z), w(w) {}
};

namespace lt
{

template<typename T> inline T
norm(const Vec4<T>& v) { return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w); }

template<typename T> inline T
norm(const Vec3<T>& v) { return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

template<typename T> inline T
norm(const Vec2<T>& v) { return std::sqrt(v.x*v.x + v.y*v.y); }

template<typename T> inline Vec2<T>
normalize(const Vec2<T>& v)
{
    return Vec2<T>(v.x/lt::norm(v), v.y/lt::norm(v), v.z/lt::norm(v));
}

template<typename T> inline Vec3<T>
normalize(const Vec3<T>& v)
{
    return Vec3<T>(v.x/lt::norm(v), v.y/lt::norm(v), v.z/lt::norm(v));
}

template<typename T> inline Vec4<T>
normalize(const Vec4<T>& v)
{
    return Vec4<T>(v.x/lt::norm(v), v.y/lt::norm(v), v.z/lt::norm(v), v.w /lt::norm(v));
}

template<typename T> inline T
radians(T angle) { return angle * (static_cast<T>(M_PI) / static_cast<T>(180)); }

template<typename T> inline T
dot(const Vec2<T>& a, const Vec2<T>& b) { return (a.x * b.x) + (a.y * b.y); }

template<typename T> inline T
dot(const Vec3<T>& lhs, const Vec3<T>& rhs) { return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z); }

template<typename T> inline Vec2<T>
projection(const Vec2<T>& p, const Vec2<T>& plane)
{
    f32 alpha = lt::dot(p, plane) / lt::dot(plane, plane);
    return alpha * plane;
}

template<typename T> inline Vec3<T>
cross(const Vec3<T>& a, const Vec3<T>& b)
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
    explicit Mat4();
    explicit Mat4(T diag);
    explicit Mat4(T m00, T m01, T m02, T m03,
                  T m10, T m11, T m12, T m13,
                  T m20, T m21, T m22, T m23,
                  T m30, T m31, T m32, T m33);

    inline T operator()(isize row, isize col) const
    {
        return m_col[col].val[row];
    }

    inline T& operator()(isize row, isize col)
    {
        return m_col[col].val[row];
    }

    inline T *data() const
    {
        return (T*)&m_col[0].val[0];
    }

private:
    Vec4<T> m_col[4];
};

template<typename T> inline
std::ostream& operator<<(std::ostream& os, const Mat4<T>& mat)
{
    for (isize row = 0; row < 4; ++row)
    {
        os << "| ";
        for (isize col = 0; col < 4; ++col) os << mat(row, col) << " ";
        os << "|";
        os << "\n";
    }
    return os;
}


namespace lt
{

template<typename T> Mat4<T>
perspective(f32 fovy, f32 aspect_ratio, f32 znear, f32 zfar);

template<typename T> Mat4<T>
look_at(const Vec3<T> eye, const Vec3<T> center, const Vec3<T> up);

template<typename T> Mat4<T>
translation(Mat4<T> in_mat, Vec3<T> amount);

template<typename T> Mat4<T>
scale(Mat4<T> in_mat, Vec3<T> scale);

}

/////////////////////////////////////////////////////////
//
// Quaternion
//
// Definition of a quaternion structure.
//
// Some properties (not necessarily complete):
//     - Not comutative (q1q2 != q2q1)
//     - Associative ((q1q2)q3 == q1(q2q3))
//     - The quaternion (1, 0, 0, 0) maps to the identity matrix.
//
template<typename T>
union Quat
{
    T val[4];
    struct
    {
        T       s;
        Vec3<T> v;
    };

    explicit Quat(T s, T i, T j, T k) : val{s, i, j, k} {}
    explicit Quat(T s, const Vec3<T>& v) : s(s), v(v) {}
    explicit Quat() : s(0), v(Vec3<T>(0, 0, 0)) {}

    static inline Quat<T>
    rotation(T angle, const Vec3<T>& axis)
    {
        Vec3<T> sin_axis = axis * std::sin(angle/static_cast<T>(2));
        return Quat<T>(std::cos(angle/static_cast<T>(2)), sin_axis);
    }

    template<typename S> Mat4<S>
    to_mat4() const
    {
        return Mat4<S>(s,   -v.i, -v.j, -v.k,
                       v.i,    s, -v.k,  v.j,
                       v.j,  v.k,    s, -v.i,
                       v.k, -v.j,  v.i,    s);
    }

    Quat<T>
    operator+(const Quat<T>& rhs) const
    {
        return Quat<T>(s+rhs.scalar, v.i+rhs.i, v.j+rhs.j, v.k+rhs.k);
    }

    Quat<T>
    operator*(f32 k) const
    {
        return Quat<T>(s*k, v*k);
    }

    Quat<T>
    operator*(f64 k) const
    {
        return Quat<T>(s*k, v*k);
    }
};

template<typename T> static inline Quat<T>
operator*(const Quat<T>& lhs, const Quat<T>& rhs)
{
    return Quat<T>((lhs.s*rhs.s) - lt::dot(lhs.v, rhs.v),
                   rhs.s*lhs.v + lhs.s*rhs.v + lt::cross(lhs.v, rhs.v));
}

namespace lt
{

template<typename T> inline T
norm(const Quat<T>& q)
{
    T v = q.val[0]*q.val[0] + q.val[1]*q.val[1] + q.val[2]*q.val[2] + q.val[3]*q.val[3];
    return std::sqrt(v);
}

template<typename T> inline Quat<T>
normalize(const Quat<T>& q)
{
    return Quat<T>(q.s/lt::norm(q), q.v.i/lt::norm(q), q.v.j/lt::norm(q), q.v.k/lt::norm(q));
}

template<typename T> inline Quat<T>
conjugate(const Quat<T>& q)
{
    return Quat<T>(q.s, -q.v);
}

template<typename T> inline Quat<T>
rotate(const Quat<T>& q, T angle, const Quat<T>& axis)
{
    const Quat<T> rotor = Quat<T>::rotation(angle, axis.v);

    // NOTE: Assert that the rotor is normalized, to avoid calculating the inverse instead of the conjugate.
    LT_Assert(lt::norm(rotor) == 1);
    // In the case that rotor is NOT normalized.
    // return rotor * point * lt::inverse(rotor);
    return rotor * q * lt::conjugate(rotor);
}

}

typedef Vec2<i32> Vec2i;
typedef Vec2<f32> Vec2f;
typedef Vec3<i32> Vec3i;
typedef Vec3<f32> Vec3f;
typedef Vec4<i32> Vec4i;
typedef Vec4<f32> Vec4f;
typedef Mat4<f32> Mat4f;
typedef Quat<f32> Quatf;
typedef Quat<f64> Quatd;

#endif // LT_MATH_HPP
