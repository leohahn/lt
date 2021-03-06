#ifndef LT_MATH_HPP
#define LT_MATH_HPP

#include <stdio.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <type_traits>
#include <limits>

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

template<typename T> typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, T epsilon = std::numeric_limits<T>::epsilon())
{
	// http://realtimecollisiondetection.net/blog/?p=89
	bool almost = std::abs(x - y) <= epsilon * std::max(std::max(static_cast<T>(1), std::abs(x)), std::abs(y));
	return almost;
}

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

    Vec2(): x(0), y(0) {}
    explicit Vec2(T k): x(k), y(k) {}
    explicit Vec2(T x, T y): x(x), y(y) {}

    inline Vec2<T> operator-(Vec2<T> rhs) const {return Vec2<T>(x - rhs.x, y - rhs.y);}
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

template<typename T> static inline Vec2<T>
operator+(const Vec2<T> &a, const Vec2<T> &b)
{
    return Vec2<T>(a.x + b.x, a.y + b.y);
}

template<typename T> static inline std::ostream &
operator<<(std::ostream& os, const Vec2<T> &v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

/////////////////////////////////////////////////////////
//
// Vector3
//
// Definition of a vector structure.
//

template<typename T> union Vec4;

template<typename T>
struct Vec3
{
    union
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
        struct
        {
            Vec2<T> xy;
            f32     _ignored_z;
        };
        struct
        {
            f32     _ignored_x;
            Vec2<T> yz;
        };
    };

    Vec3() noexcept : x(0), y(0), z(0) {}
    explicit Vec3(T val) noexcept : x(val), y(val), z(val) {}
    explicit Vec3(T x, T y, T z) noexcept : x(x), y(y), z(z) {}
    explicit Vec3(Vec4<T> v) noexcept : x(v.x), y(v.y), z(v.z) {}
    explicit Vec3(Vec2<T> v, T z) noexcept : x(v.x), y(v.y), z(z) {}

    inline Vec3<T> operator-(const Vec3<T>& rhs) const { return Vec3<T>(x-rhs.x, y-rhs.y, z-rhs.z); }
    inline Vec3<T> operator-()                   const { return Vec3<T>(-x, -y, -z); }
    inline Vec3<T> operator+(const Vec3<T>& rhs) const { return Vec3<T>(x+rhs.x, y+rhs.y, z+rhs.z); }
    inline Vec2<T> xz() const { return Vec2<T>(x, z); }

    inline void operator-=(const Vec3<T>& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; }
    inline void operator+=(const Vec3<T>& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; }
};

template<typename T> inline bool
operator==(const Vec3<T> &a, const Vec3<T> &b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<> inline bool
operator==<f32>(const Vec3<f32> &a, const Vec3<f32> &b)
{
    return almost_equal(a.x, b.x) && almost_equal(a.y, b.y) && almost_equal(a.z, b.z);
}

template<> inline bool
operator==<f64>(const Vec3<f64> &a, const Vec3<f64> &b)
{
	return almost_equal(a.x, b.x) && almost_equal(a.y, b.y) && almost_equal(a.z, b.z);
}

template<typename T> inline bool
operator!=(const Vec3<T> &a, const Vec3<T> &b)
{
	return a.x != b.x && a.y != b.y && a.z != b.z;
}

template<> inline bool
operator!=<f32>(const Vec3<f32> &a, const Vec3<f32> &b)
{
	return !almost_equal(a.x, b.x) || !almost_equal(a.y, b.y) || !almost_equal(a.z, b.z);
}

template<> inline bool
operator!=<f64>(const Vec3<f64> &a, const Vec3<f64> &b)
{
	return !almost_equal(a.x, b.x) || !almost_equal(a.y, b.y) || !almost_equal(a.z, b.z);
}

template<typename T> static inline std::ostream &
operator<<(std::ostream& os, const Vec3<T> &v)
{
	os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}

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
// Vector4
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

    Vec4(): x(0), y(0), z(0), w(0) {}
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
	const f32 EPSILON = 0.0001f;
	f32 length = lt::norm(v);
	if (length <= EPSILON) return v;

    return Vec3<T>(v.x/length, v.y/length, v.z/length);
}

template<typename T> inline Vec4<T>
normalize(const Vec4<T>& v)
{
    return Vec4<T>(v.x/lt::norm(v), v.y/lt::norm(v), v.z/lt::norm(v), v.w /lt::norm(v));
}

template<typename T> inline T
radians(T angle) { return angle * (static_cast<T>(M_PI) / static_cast<T>(180)); }

template<typename T> inline T
degrees(T angle) { return angle * (static_cast<T>(180) / static_cast<T>(M_PI)); }

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
union Mat4f
{
    Mat4f();
    explicit Mat4f(f32 diag);
    explicit Mat4f(f32 m00, f32 m01, f32 m02, f32 m03,
				   f32 m10, f32 m11, f32 m12, f32 m13,
				   f32 m20, f32 m21, f32 m22, f32 m23,
				   f32 m30, f32 m31, f32 m32, f32 m33);

    inline f32 operator()(isize row, isize col) const
    {
        return m_col[col].val[row];
    }

    inline f32& operator()(isize row, isize col)
    {
        return m_col[col].val[row];
    }

	inline Vec4<f32> col(isize col)
	{
		return m_col[col];
	}

    inline f32 *data() const
    {
        return (f32*)&m_col[0].val[0];
    }

    Mat4f operator*(const Mat4f& rhs);

private:
    Vec4<f32> m_col[4];
};

inline std::ostream &operator<<(std::ostream& os, const Mat4f &mat)
{
    for (i32 row = 0; row < 4; row++)
    {
        os << "|  ";
        for (i32 col = 0; col < 4; col++)
        {
            os << std::setw(9) << std::setprecision(3) << mat(row, col) << "  ";
        }
        os << "|\n";
    }
    return os;
}

inline Mat4f
operator*(const Mat4f &lhs, const Mat4f &rhs)
{
    Mat4f ret(1.0);
    // First row
    ret(0,0) = lhs(0,0)*rhs(0,0) + lhs(0,1)*rhs(1,0) + lhs(0,2)*rhs(2,0) + lhs(0,3)*rhs(3,0);
    ret(0,1) = lhs(0,0)*rhs(0,1) + lhs(0,1)*rhs(1,1) + lhs(0,2)*rhs(2,1) + lhs(0,3)*rhs(3,1);
    ret(0,2) = lhs(0,0)*rhs(0,2) + lhs(0,1)*rhs(1,2) + lhs(0,2)*rhs(2,2) + lhs(0,3)*rhs(3,2);
    ret(0,3) = lhs(0,0)*rhs(0,3) + lhs(0,1)*rhs(1,3) + lhs(0,2)*rhs(2,3) + lhs(0,3)*rhs(3,3);
    // Second row
    ret(1,0) = lhs(1,0)*rhs(0,0) + lhs(1,1)*rhs(1,0) + lhs(1,2)*rhs(2,0) + lhs(1,3)*rhs(3,0);
    ret(1,1) = lhs(1,0)*rhs(0,1) + lhs(1,1)*rhs(1,1) + lhs(1,2)*rhs(2,1) + lhs(1,3)*rhs(3,1);
    ret(1,2) = lhs(1,0)*rhs(0,2) + lhs(1,1)*rhs(1,2) + lhs(1,2)*rhs(2,2) + lhs(1,3)*rhs(3,2);
    ret(1,3) = lhs(1,0)*rhs(0,3) + lhs(1,1)*rhs(1,3) + lhs(1,2)*rhs(2,3) + lhs(1,3)*rhs(3,3);
    // Third row
    ret(2,0) = lhs(2,0)*rhs(0,0) + lhs(2,1)*rhs(1,0) + lhs(2,2)*rhs(2,0) + lhs(2,3)*rhs(3,0);
    ret(2,1) = lhs(2,0)*rhs(0,1) + lhs(2,1)*rhs(1,1) + lhs(2,2)*rhs(2,1) + lhs(2,3)*rhs(3,1);
    ret(2,2) = lhs(2,0)*rhs(0,2) + lhs(2,1)*rhs(1,2) + lhs(2,2)*rhs(2,2) + lhs(2,3)*rhs(3,2);
    ret(2,3) = lhs(2,0)*rhs(0,3) + lhs(2,1)*rhs(1,3) + lhs(2,2)*rhs(2,3) + lhs(2,3)*rhs(3,3);
    // Fourth row
    ret(3,0) = lhs(3,0)*rhs(0,0) + lhs(3,1)*rhs(1,0) + lhs(3,2)*rhs(2,0) + lhs(3,3)*rhs(3,0);
    ret(3,1) = lhs(3,0)*rhs(0,1) + lhs(3,1)*rhs(1,1) + lhs(3,2)*rhs(2,1) + lhs(3,3)*rhs(3,1);
    ret(3,2) = lhs(3,0)*rhs(0,2) + lhs(3,1)*rhs(1,2) + lhs(3,2)*rhs(2,2) + lhs(3,3)*rhs(3,2);
    ret(3,3) = lhs(3,0)*rhs(0,3) + lhs(3,1)*rhs(1,3) + lhs(3,2)*rhs(2,3) + lhs(3,3)*rhs(3,3);
    return ret;
}

namespace lt
{

Mat4f perspective(f32 fovy, f32 aspect_ratio, f32 znear, f32 zfar);

Mat4f orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

Mat4f orthographic(f32 left, f32 right, f32 bottom, f32 top);

Mat4f look_at(const Vec3<f32> eye, const Vec3<f32> center, const Vec3<f32> up);

Mat4f translation(const Mat4f &in_mat, Vec3<f32> amount);

Mat4f scale(const Mat4f &in_mat, Vec3<f32> scale);

inline Mat4f
rotation_x(const Mat4f &in_mat, f32 degrees)
{
	f32 rad = lt::radians(degrees);
	return in_mat * Mat4f(1,        0,         0,    0,
						  0, cos(rad), -sin(rad),    0,
						  0, sin(rad),  cos(rad),    0,
						  0,        0,         0,    1);
}

inline Mat4f
rotation_y(const Mat4f &in_mat, f32 degrees)
{
	f32 rad = lt::radians(degrees);
	return in_mat * Mat4f(cos(rad), 0, sin(rad), 0,
						  0, 1, 0, 0,
						  -sin(rad), 0, cos(rad), 0,
						  0, 0, 0, 1);
}

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
    Quat() : s(0), v(Vec3<T>(0, 0, 0)) {}

    static inline Quat<T> identity() { return Quat<T>(1, 0, 0, 0); }

    static inline Quat<T>
    rotation(T angle, const Vec3<T>& axis)
    {
        Vec3<T> sin_axis = axis * std::sin(angle/static_cast<T>(2));
        return Quat<T>(std::cos(angle/static_cast<T>(2)), sin_axis);
    }

    Mat4f
    to_mat4() const
    {
        return Mat4f(s,   -v.i, -v.j, -v.k,
					 v.i,    s, -v.k,  v.j,
					 v.j,  v.k,    s, -v.i,
					 v.k, -v.j,  v.i,    s);
    }

    inline Quat<T>
    operator+(const Quat<T>& rhs) const
    {
        return Quat<T>(s+rhs.s, v.i+rhs.v.i, v.j+rhs.v.j, v.k+rhs.v.k);
    }

    inline Quat<T>
    operator/(T k) const
    {
        return Quat<T>(val[0]/k, val[1]/k, val[2]/k, val[3]/k);
    }
};

template<typename T> inline Quat<T>
operator*(const Quat<T> &q, T k)
{
    return Quat<T>(q.s*k, q.v*k);
}

template<typename T> inline Quat<T>
operator*(T k, const Quat<T> &q)
{
    return Quat<T>(q.s*k, q.v*k);
}

template<typename T> static inline Quat<T>
operator*(const Quat<T>& lhs, const Quat<T>& rhs)
{
    return Quat<T>((lhs.s*rhs.s) - lt::dot(lhs.v, rhs.v),
                   rhs.s*lhs.v + lhs.s*rhs.v + lt::cross(lhs.v, rhs.v));
}

template<typename T> inline std::ostream &
operator<<(std::ostream &os, const Quat<T> &q)
{
    os << "(" << std::setprecision(3) << q.val[0] << ", ";
    os << q.val[1] << ", " << q.val[2] << ", " << q.val[3] << ")";
    return os;
}

template<typename T> inline bool
operator==(const Quat<T> &a, const Quat<T> &b)
{
    return (a.val[0] == b.val[0]) &&
        (a.val[1] == b.val[1]) &&
        (a.val[2] == b.val[2]) &&
        (a.val[3] == b.val[3]);
}

template<> inline bool
operator==<f32>(const Quat<f32> &a, const Quat<f32> &b)
{
    return almost_equal(a.val[0], b.val[0]) &&
        almost_equal(a.val[1], b.val[1]) &&
        almost_equal(a.val[2], b.val[2]) &&
        almost_equal(a.val[3], b.val[3]);
}

template<> inline bool
operator==<f64>(const Quat<f64> &a, const Quat<f64> &b)
{
    return almost_equal(a.val[0], b.val[0]) &&
        almost_equal(a.val[1], b.val[1]) &&
        almost_equal(a.val[2], b.val[2]) &&
        almost_equal(a.val[3], b.val[3]);
}

namespace lt
{

template<typename T> inline T
norm(const Quat<T> &q)
{
    T v = q.val[0]*q.val[0] + q.val[1]*q.val[1] + q.val[2]*q.val[2] + q.val[3]*q.val[3];
    return std::sqrt(v);
}

template<typename T> inline T
sqr_norm(const Quat<T> &q)
{
    T v = q.val[0]*q.val[0] + q.val[1]*q.val[1] + q.val[2]*q.val[2] + q.val[3]*q.val[3];
    return v;
}

template<typename T> inline Quat<T>
normalize(const Quat<T> &q)
{
    return Quat<T>(q.s/lt::norm(q), q.v.i/lt::norm(q), q.v.j/lt::norm(q), q.v.k/lt::norm(q));
}

template<typename T> inline Quat<T>
conjugate(const Quat<T> &q)
{
    return Quat<T>(q.s, -q.v);
}

template<typename T> inline Quat<T>
inverse(const Quat<T> &q)
{
    Quat<T> inv = lt::conjugate(q) / lt::sqr_norm(q);
    LT_Assert(q*inv == Quat<T>::identity());
    return inv;
}

template<typename T> inline Quat<T>
rotate(const Quat<T> &q, T angle, const Quat<T> &axis)
{
    const Quat<T> rotor = Quat<T>::rotation(angle, axis.v);
    return rotor * q * lt::inverse(rotor);
}

template<typename T> T
dot(const Quat<T> &a, const Quat<T> &b)
{
	return a.val[0]*b.val[0] + a.val[1]*b.val[1] + a.val[2]*b.val[2] + a.val[3]*b.val[3];
}

template<typename T> Quat<T>
slerp(const Quat<T> &start_q, const Quat<T> &end_q, T t)
{
    LT_Assert(t >= 0);
    LT_Assert(t <= 1);

    const T EPSILON = static_cast<T>(0.0001); // FIXME: Find a more specific epsilon value here.
    T start_dot_end = lt::dot(start_q, end_q);

    if (start_dot_end < 1-EPSILON)
    {
        T angle = std::acos(start_dot_end);
        LT_Assert(angle != static_cast<T>(0));
        return (std::sin((static_cast<T>(1) - t) * angle) * start_q + std::sin(t * angle) * end_q) /
            std::sin(angle);
    }
    else
    {
        return start_q;
    }
}

}

typedef Vec2<i32> Vec2i;
typedef Vec2<f32> Vec2f;
typedef Vec3<i32> Vec3i;
typedef Vec3<f32> Vec3f;
typedef Vec4<i32> Vec4i;
typedef Vec4<f32> Vec4f;
typedef Quat<f32> Quatf;
typedef Quat<f64> Quatd;

#endif // LT_MATH_HPP
