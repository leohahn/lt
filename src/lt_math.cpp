#include "lt_math.hpp"
#include <math.h>
#include <stdio.h>

Mat4f::Mat4f(f32 m00, f32 m01, f32 m02, f32 m03,
			 f32 m10, f32 m11, f32 m12, f32 m13,
			 f32 m20, f32 m21, f32 m22, f32 m23,
			 f32 m30, f32 m31, f32 m32, f32 m33)
    : m_col{
        Vec4<f32>(m00, m10, m20, m30),
        Vec4<f32>(m01, m11, m21, m31),
        Vec4<f32>(m02, m12, m22, m32),
        Vec4<f32>(m03, m13, m23, m33)}
{
}

Mat4f::Mat4f(f32 diag)
{
    m_col[0] = Vec4<f32>(diag, 0, 0, 0);
    m_col[1] = Vec4<f32>(0, diag, 0, 0);
    m_col[2] = Vec4<f32>(0, 0, diag, 0);
    m_col[3] = Vec4<f32>(0, 0, 0, diag);
}

Mat4f::Mat4f()
{
    m_col[0] = Vec4<f32>(1, 0, 0, 0);
    m_col[1] = Vec4<f32>(0, 1, 0, 0);
    m_col[2] = Vec4<f32>(0, 0, 1, 0);
    m_col[3] = Vec4<f32>(0, 0, 0, 1);
}

Mat4f
lt::perspective(f32 fovy, f32 aspect_ratio, f32 znear, f32 zfar)
{
    f32 fovy_rad = fovy / 180 * LT_PI;
    f32 f = 1.0/tanf(fovy_rad/2.0);
    f32 zz = (zfar+znear)/(znear-zfar);
    f32 zw = (2*zfar*znear)/(znear-zfar);

    return Mat4f(
        (f/aspect_ratio),   0,             0,                     0,
        0,                  f,             0,                     0,
        0,                  0,            zz,                    zw,
        0,                  0,            -1,                      0);
}

Mat4f
lt::orthographic(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f)
{
	return Mat4f(2/(r-l), 0,       0,        -(r+l)/(r-l),
				 0,       2/(t-b), 0,        -(t+b)/(t-b),
				 0,       0,       -2/(f-n), -(f+n)/(f-n),
				 0,       0,       0,         1);
}

Mat4f
lt::look_at(const Vec3<f32> eye, const Vec3<f32> center, const Vec3<f32> up)
{
    Vec3<f32> f = lt::normalize(center - eye);
    Vec3<f32> s = lt::normalize(lt::cross(f, up));
    Vec3<f32> u = lt::cross(s, f);

    return Mat4f( s.x,   s.y,   s.z,   -lt::dot(s, eye),
				  u.x,   u.y,   u.z,   -lt::dot(u, eye),
				  -f.x,  -f.y,  -f.z,    lt::dot(f, eye),
				  0,     0,     0,                 1);
}

Mat4f
lt::translation(const Mat4f& in_mat, Vec3<f32> amount)
{
    return in_mat * Mat4f(1, 0, 0, amount.x,
                          0, 1, 0, amount.y,
                          0, 0, 1, amount.z,
                          0, 0, 0,         1);
}

Mat4f
lt::scale(const Mat4f &in_mat, Vec3<f32> scale)
{
    return in_mat * Mat4f(scale.x,       0,       0,        0,
						  0,       scale.y,       0,        0,
						  0,             0, scale.z,        0,
						  0,             0,       0,        1);
}
