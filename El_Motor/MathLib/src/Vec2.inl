#pragma once

#include "Vec2.hpp"

template <typename T>
Math::Vec2<T>::Vec2(T m_x, T m_y) : m_x(m_x), m_y(m_y) {}

/////// STATIC PORPRETIES ///////
template<typename T>
inline Math::Vec2<T> Math::Vec2<T>::Down() { return Math::Vec2<T>(0.0f, -1.0f); }

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Up() { return Math::Vec2<T>(0.0f, 1.0f); }

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Left() { return Math::Vec2<T>(-1.0f, 0.0f); }

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Right() { return Math::Vec2<T>(1.0f, 0.0f); }


template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::One() { return Math::Vec2<T>(1.0f, 1.0f); }

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Zero() { return Math::Vec2<T>(0.0f, 0.0f); }

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::PositiveInfinity() { return Math::Vec2<T>(std::numeric_limits<T>::infinity(),std::numeric_limits<T>::infinity()); };

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::NegativeInfinity() { return Math::Vec2<T>(-1 * (std::numeric_limits<T>::infinity()), -1 * (std::numeric_limits<T>::infinity())); };


/////// PORPRETIES ///////
template <typename T>
T Math::Vec2<T>::Magnitude() { return std::sqrt(m_x * m_x + m_y * m_y); }

template <typename T>
Math::Vec2<T> Math::Vec2<T>::Normalized() {
    T mag = Magnitude();
    if (mag != 0.0f)
        return Math::Vec2<T>(m_x / mag, m_y / mag);
    else
        return Math::Vec2<T>(0.0f, 0.0f);
}

template <typename T>
T Math::Vec2<T>::SqrtMagnitude() { 
    T mag = Magnitude();
    return pow((mag), 2);
}

template <typename T>
T Math::Vec2<T>::This(int i) { 
    if (i == 0) return m_x;
    else if (i == 1) return m_y;
}

template <typename T>
T Math::Vec2<T>::x() const { return m_x; } 

template <typename T>
T Math::Vec2<T>::y() const { return m_y; }


/////// PUBLIC METHODS ///////
template <typename T>
bool Math::Vec2<T>::Equal(Math::Vec2<T> other) { 
    if (m_x == other.m_x && m_y == other.m_y) return true;
    else return false;
}

template <typename T>
void Math::Vec2<T>::Set(T newX, T newY) { m_x = newX, m_y = newY; }

template <typename T>
std::string Math::Vec2<T>::ToString() { 
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}


/////// STATIC METHODS ///////
template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::MoveTowards(Vec2<T> current, Vec2<T> target, T maxDistanceDelta) { 
    Vec2<T> toVec = target - current;
    T dist = toVec.Magnitude();
    if (dist <= maxDistanceDelta || dist == 0.0f) {
        return target;
    }
    return current + toVec / dist * maxDistanceDelta;
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::ClampMagnitude(Vec2<T>& a, T maxLength) {
    T mag = a.Magnitude();
    if (mag > maxLength)
        return a.Normalized() * maxLength;
    return a;
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::LerpUnclamped(Vec2<T> a, Vec2<T> b, T t) {
    return a + (b - a) * t;
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Perpendicular(Vec2<T> inDirection) {
    return Vec2<T>(-inDirection.m_y, inDirection.m_x);
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Lerp(Vec2<T> a, Vec2<T> b, T t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return a + (b - a) * t;
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Scale(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(a.m_x * b.m_x, a.m_y * b.m_y);
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Min(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(std::fmin(a.m_x, b.m_x), std::fmin(a.m_y, b.m_y));
}

template <typename T>
inline Math::Vec2<T> Math::Vec2<T>::Max(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(std::fmax(a.m_x, b.m_x), std::fmax(a.m_y, b.m_y));
}


template <typename T>
inline T Math::Vec2<T>::SignedAngle(Vec2<T> from, Vec2<T> to) {
    T angle = Angle(from, to);
    T cross = from.m_x * to.m_y - from.m_y * to.m_x;
    return (cross < 0) ? -angle : angle;
}

template <typename T>
inline T Math::Vec2<T>::Distance(Vec2<T>& a, Vec2<T>& b) { // distance entre deux vecteurs
    return Vec2<T>(a - b).Magnitude();
}

template <typename T>
inline T Math::Vec2<T>::Angle(Vec2<T> a, Vec2<T> b) { // retourne l'angle entre deux vecteurs
    float dotProd = a.m_x * b.m_x + a.m_y * b.m_y;
    float lenA = std::sqrt(a.m_x * a.m_x + a.m_y * a.m_y);
    float lenB = std::sqrt(b.m_x * b.m_x + b.m_y * b.m_y);
    return std::acos(dotProd / (lenA * lenB)); // retourne en radians

}

template <typename T>
inline T Math::Vec2<T>::Dot(Vec2<T>& a, Vec2<T>& b) { // produit scalaire entre deux vecteurs
    return (a.m_x * b.m_x + a.m_y * b.m_y);
}


template <typename T>
void Math::Vec2<T>::Normalize() {
    T mag = Magnitude();
    m_x = m_x / mag;
    m_y = m_y / mag;
}


/////// CONVERSIONS ///////
template<typename T>
inline Math::Vec2<T> Math::Vec2<T>::ToVec2(Vec3<T>& vec) {  
    return Vec2<T>(vec.m_x, vec.m_y);
}

template <typename T>
Math::Vec3<T> Math::Vec2<T>::ToVec3() const { 
    T zValue = 0;
    return Math::Vec3<T>(this->m_x, this->m_y, zValue);
}


/////// OPERATORS ///////
template <typename T>
Math::Vec2<T> Math::Vec2<T>::operator+(const Vec2<T>& other) const {
    return Vec2<T>(this->m_x + other.m_x, this->m_y + other.m_y);
}

template <typename T>
Math::Vec2<T> Math::Vec2<T>::operator-(const Vec2<T>& other) const {
    return Vec2<T>(this->m_x - other.m_x, this->m_y - other.m_y);
}


template <typename T>
Math::Vec2<T> Math::Vec2<T>::operator*(const Vec2<T>& other) const {
    return Vec2<T>(this->m_x * other.m_x, this->m_y * other.m_y);
}

template <typename T>
Math::Vec2<T> Math::Vec2<T>::operator*(T scalar) const {
    return Vec2<T>(this->m_x * scalar, this->m_y * scalar);
}


template <typename T>
Math::Vec2<T> Math::Vec2<T>::operator/(const Vec2<T>& other) const {

    T newX = (other.m_x != 0.0f) ? (this->m_x / other.m_x) : 0.0f;
    T newY = (other.m_y != 0.0f) ? (this->m_y / other.m_y) : 0.0f;
    return Vec2<T>(newX, newY);
}

template <typename T>
Math::Vec2<T> Math::Vec2<T>::operator/(T scalar) const {
    if (scalar != 0.0f)
        return Vec2<T>(this->m_x / scalar, this->m_y / scalar);
    else
        return Vec2<T>(0.0f, 0.0f);
}


template <typename T>
bool Math::Vec2<T>::operator==(const Vec2<T>& other) const {
    return this->m_x == other.m_x && this->m_y == other.m_y;
}

template <typename T>
bool Math::Vec2<T>::operator!=(const Vec2<T>& other) const {
    return !(*this == other);
}