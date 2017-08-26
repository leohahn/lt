#include "lt_math.hpp"
#include <math.h>
#include <stdio.h>

/////////////////////////////////////////////////////////
//
// Vector implementation
//

template<typename T>
Mat4<T>::Mat4(T m00, T m01, T m02, T m03,
              T m10, T m11, T m12, T m13,
              T m20, T m21, T m22, T m23,
              T m30, T m31, T m32, T m33)
    : m_col{
        Vec4<T>(m00, m10, m20, m30),
        Vec4<T>(m01, m11, m21, m31),
        Vec4<T>(m02, m12, m22, m32),
        Vec4<T>(m03, m13, m23, m33)}
{
}

template<typename T>
Mat4<T>::Mat4(T diag)
{
    m_col[0] = Vec4<T>(diag, 0, 0, 0);
    m_col[1] = Vec4<T>(0, diag, 0, 0);
    m_col[2] = Vec4<T>(0, 0, diag, 0);
    m_col[3] = Vec4<T>(0, 0, 0, diag);
}

template<typename T> Mat4<T>
lt::perspective(f32 fovy, f32 aspect_ratio, f32 znear, f32 zfar)
{
    f32 fovy_rad = fovy / 180 * LT_PI;
    f32 f = 1.0/tanf(fovy_rad/2.0);
    f32 zz = (zfar+znear)/(znear-zfar);
    f32 zw = (2*zfar*znear)/(znear-zfar);

    return Mat4<T>(
        (f/aspect_ratio),   0,             0,                     0,
        0,                  f,             0,                     0,
        0,                  0,            zz,                    zw,
        0,                  0,            -1,                      0);
}

template<typename T> Mat4<T>
lt::look_at(const Vec3<T> eye, const Vec3<T> center, const Vec3<T> up)
{
    Vec3<T> f = (center - eye).norm();
    Vec3<T> s = lt::cross(f, up).norm();
    Vec3<T> u = lt::cross(s, f);

    /* Mat4 view = mat4( */
    /*          s.x,              u.x,               -f.x,       0, */
    /*          s.y,              u.y,               -f.y,       0, */
    /*          s.z,              u.z,               -f.z,       0, */
    /*     -vec_dot(s, eye), -vec_dot(u, eye),  vec_dot(f, eye), 1); */
    return Mat4<T>( s.x,   s.y,   s.z,   -lt::dot(s, eye),
                    u.x,   u.y,   u.z,   -lt::dot(u, eye),
                   -f.x,  -f.y,  -f.z,    lt::dot(f, eye),
                      0,     0,     0,                 1);
}

template Mat4<f32>::Mat4(f32 m00, f32 m01, f32 m02, f32 m03,
                         f32 m10, f32 m11, f32 m12, f32 m13,
                         f32 m20, f32 m21, f32 m22, f32 m23,
                         f32 m30, f32 m31, f32 m32, f32 m33);
template Mat4<f32>::Mat4(f32 diag);

template Mat4<f32> lt::perspective(f32 fovy, f32 aspect_ratio, f32 znear, f32 zfar);
template Mat4<f32> lt::look_at<f32>(const Vec3<f32> eye, const Vec3<f32> center, const Vec3<f32> up);
