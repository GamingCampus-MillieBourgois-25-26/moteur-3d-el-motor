#pragma once

#include "Quat.hpp"

template<typename T>
Math::Quat<T>::Quat() : x(0), y(0), z(0), w(1) {}

template<typename T>
Math::Quat<T>::Quat(T m_x, T m_y, T m_z, T m_w) : m_x(m_x), m_y(m_y), m_z(m_z), m_w(m_w) {}


////// STATIC PROPRETIE //////
template<typename T>
Math::Quat<T> Math::Quat<T>::Identity() {
    return Quat<T>(0, 0, 0, 1);
}



////// PROPRETIE //////
template<typename T>
Math::Quat<T> Math::Quat<T>::Normalized() const {
    T len = Length();
    if (len < kEpsilon) return Quat<T>::Identity();
    return Quat<T>(m_x / len, m_y / len, m_z / len, m_w / len);
}

template <typename T>
T Math::Quat<T>::This(int i) {
    if (i == 0) return m_x;
    else if (i == 1) return m_y;
    else if (i == 2) return m_z;
    else if (i == 3) return m_w;
}

template <typename T>
T Math::Quat<T>::x() const { return m_x; }

template <typename T>
T Math::Quat<T>::y() const { return m_y; }

template <typename T>
T Math::Quat<T>::z() const { return m_z; }

template <typename T>
T Math::Quat<T>::w() const { return m_w; }

template<typename T>
T Math::Quat<T>::Length() { 
    return static_cast<T>(std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
}



////// PUBLIC METHODS //////
template<typename T>
void Math::Quat<T>::ToAxisAngle(Vec3<T>& outAxis, T& outAngle) {
    Quat<T> q = Normalized();
    outAngle = static_cast<T>(2) * std::acos(q.m_w);
    T s = std::sqrt(1 - q.m_w * q.m_w);
    if (s < kEpsilon)
        outAxis = Vec3<T>(1, 0, 0);
    else
        outAxis = Vec3<T>(q.m_x / s, q.m_y / s, q.m_z / s);
}

template<typename T>
Math::Quat<T> Math::Quat<T>::Conjugate() {
    return Quat<T>(-x, -y, -z, w);
}



////// STATIC METHODS //////
template<typename T>
inline Math::Quat<T> Math::Quat<T>::Slerp(const Quat<T>& a, const Quat<T>& b, T t) {
    t = clampValue(t, static_cast<T>(0), static_cast<T>(1));
    T dot = Dot(a, b);
    dot = clampValue(dot, static_cast<T>(-1), static_cast<T>(1));

    const T DOT_THRESHOLD = static_cast<T>(0.9995);
    if (absValue(dot) > DOT_THRESHOLD)
        return Lerp(a, b, t);

    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;

    T s0 = std::cos(theta) - dot * std::sin(theta) / std::sin(theta_0);
    T s1 = std::sin(theta) / std::sin(theta_0);

    Quat<T> result(
        a.m_x * s0 + b.m_x * s1,
        a.m_y * s0 + b.m_y * s1,
        a.m_z * s0 + b.m_z * s1,
        a.m_w * s0 + b.m_w * s1
    );
    return result.Normalized();
}

template<typename T>
inline Math::Quat<T> Math::Quat<T>::AngleAxis(T angle, const Vec3<T>& axis) {
    return FromAxisAngle(axis, angle);
}

template<typename T>
inline Math::Quat<T> Math::Quat<T>::Lerp(const Quat<T>& a, const Quat<T>& b, T t) {
    t = clampValue(t, static_cast<T>(0), static_cast<T>(1));
    Quat<T> q(
        a.m_x + (b.m_x - a.m_x) * t,
        a.m_y + (b.m_y - a.m_y) * t,
        a.m_z + (b.m_z - a.m_z) * t,
        a.m_w + (b.m_w - a.m_w) * t
    );
    return q.Normalized();
}

template<typename T>
inline Math::Quat<T> Math::Quat<T>::FromAxisAngle(Vec3<T>& axis, T angle) { 
    Vec3<T> vec = axis.Normalized();
    T half = angle / static_cast<T>(2);
    T s = std::sin(half);
    return Quat<T>(vec.m_x * s, vec.m_y * s, vec.m_z * s, std::cos(half));
}

template<typename T>
inline Math::Quat<T> Math::Quat<T>::Inverse() {
    Quat<T> q = this->Normalized();
    return q.Conjugate();
}


template<typename T>
inline T Math::Quat<T>::Min(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
inline T Math::Quat<T>::Abs(T v) {
    return (v < static_cast<T>(0)) ? -v : v;
}

template<typename T>
inline T Math::Quat<T>::Clamp(T v, T minVal, T maxVal) { 
    return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
}

template<typename T>
inline T Math::Quat<T>::Angle(const Quat<T>& a, const Quat<T>& b) { 
    T d = Abs(Dot(a.Normalized(), b.Normalized()));
    d = Min(d, static_cast<T>(1));
    return static_cast<T>(2) * std::acos(d);
}

template<typename T>
inline T Math::Quat<T>::Dot(const Quat<T>& a, const Quat<T>& b) { 
    return a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z + a.m_w * b.m_w;
}


template<typename T>
void Math::Quat<T>::Normalize() { 
    T len = Length();
    if (len < kEpsilon) { *this = Identity(); return; }
    m_x /= len; m_y /= len; m_z /= len; m_w /= len;
}



////// OPERATORS //////
template<typename T>
Math::Quat<T> Math::Quat<T>::operator*(const Quat<T>& rhs) const {
    return Quat<T>(
        m_w * rhs.m_x + m_x * rhs.m_w + m_y * rhs.m_z - m_z * rhs.m_y,
        m_w * rhs.m_y - m_x * rhs.m_z + m_y * rhs.m_w + m_z * rhs.m_x,
        m_w * rhs.m_z + m_x * rhs.m_y - m_y * rhs.m_x + m_z * rhs.m_w,
        m_w * rhs.m_w - m_x * rhs.m_x - m_y * rhs.m_y - m_z * rhs.m_z
    );
}

template<typename T>
Math::Vec3<T> Math::Quat<T>::operator*(const Vec3<T>& Vec) const {
    Vec3<T> qVec(m_x, m_y, m_z);
    Vec3<T> t = qv.cross(Vec) * static_cast<T>(2);
    return Vec + t * m_w + qVec.cross(t);
}

template<typename T>
bool Math::Quat<T>::operator==(const Quat<T>& q) const {
    return m_x == q.m_x && m_y == q.m_y && m_z == q.m_z && m_w == q.m_w;
}