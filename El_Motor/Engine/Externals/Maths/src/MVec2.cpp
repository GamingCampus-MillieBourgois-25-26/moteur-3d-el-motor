#include "MVec2.hpp"

template <typename T>
Maths::Vec2<T>::Vec2(T m_x, T m_y) : m_x(m_x), m_y(m_y) {}

//////// STATIC PORPRETIES ////////

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Down() { return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(-1)); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Up() { return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(1)); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Left() { return Maths::Vec2<T>(static_cast<T>(-1), static_cast<T>(0)); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Right() { return Maths::Vec2<T>(static_cast<T>(1), static_cast<T>(0)); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::One() { return Maths::Vec2<T>(static_cast<T>(1), static_cast<T>(1)); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Zero() { return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::PositiveInfinity() { return Maths::Vec2<T>(std::numeric_limits<T>::infinity()), std::numeric_limits<T>::infinity()); }

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::NegativeInfinity() { return Maths::Vec2<T>(-std::numeric_limits<T>::infinity()), -std::numeric_limits<T>::infinity()); }


//////// PORPRETIES ////////
template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Normalized() {

    T mag = Magnitude();
    if (mag != 0.0f)
        return Maths::Vec2<T>(x / mag, y / mag);
    else
        return Maths::Vec2<T>(0.0f, 0.0f);
}

template <typename T>
T Maths::Vec2<T>::SqrtMagnitude() {
    T mag = Magnitude();
    return std::pow((mag), 2);
}

template <typename T>
T Maths::Vec2<T>::Magnitude() { return std::sqrt(m_x * m_x + m_y * m_y); }

template <typename T>
T Maths::Vec2<T>::This(int i) { 
    if (i == 0) return x;
    else if (i == 1) return y;
}


//////// PUBLIC METHODS ////////
template <typename T>
bool Maths::Vec2<T>::Equal(Vec2<T> other) { 
    if (m_x == other.m_x && m_y == other.m_y) return true;
    else return false;
}

template <typename T>
std::string Maths::Vec2<T>::ToString() { 
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}


//////// STATIC METHODS ////////
template<typename T>
static Maths::Vec2<T> Maths::Vec2<T>::MoveTowards(Vec2<T> current, Vec2<T> target, T maxDistanceDelta)
{
    Vec2<T> direction = target - current;
    T distance = direction.Magnitude();
    if (distance == 0 || (maxDistanceDelta >= 0 && distance <= maxDistanceDelta)) { return target; }

    return current + toVec / distance * maxDistanceDelta;
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::LerpUnclamped(Vec2<T> a, Vec2<T> b, T t) {
    return a + (b - a) * t;
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::ClampMagnitude(Vec2<T>& a, T maxLength) {
    T mag = a.Magnitude();
    if (mag > maxLength)
        return a.Normalized() * maxLength;
    return a;
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Perpendicular(Vec2<T> inDirection) {
    return Vec2<T>(-inDirection.m_y, inDirection.m_x);
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Lerp(Vec2<T> a, Vec2<T> b, T t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return a + (b - a) * t;
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Scale(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(a.x * b.x, a.y * b.y);
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Min(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(std::fmin(a.m_x, b.m_x), std::fmin(a.m_y, b.m_y));
}

template <typename T>
static Maths::Vec2<T> Maths::Vec2<T>::Max(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(std::fmax(a.m_x, b.m_x), std::fmax(a.m_y, b.m_y));
}


template <typename T>
static T Maths::Vec2<T>::SignedAngle(Vec2<T> from, Vec2<T> to) {
    T angle = Angle(from, to);
    T cross = from.x * to.y - from.y * to.x;
    return (cross < 0) ? -angle : angle;
}

template <typename T>
static T Maths::Vec2<T>::Distance(Vec2<T>& a, Vec2<T>& b) {
    return Vec2<T>(a - b).Magnitude();
}

template <typename T>
static T Maths::Vec2<T>::Angle(Vec2<T> a, Vec2<T> b) {
    float dotProd = a.x * b.x + a.y * b.y;
    float lenA = a.Magnitude();
    float lenB = b.Magnitude();
    T cosAngle = std::clamp(dotProd / (lenA * lenB), -1.0f, 1.0f);
    return std::acos(cosAngle) // retourne en radians

}

template <typename T>
static T Maths::Vec2<T>::Dot(Vec2<T>& a, Vec2<T>& b) {
    return (a.m_x * b.m_x + a.m_y * b.m_y);
}


template <typename T>
void Maths::Vec2<T>::Normalize() {
    T mag = Magnitude();
    m_x = m_x / mag;
    m_y = m_y / mag;
}


//////// CONVERSIONS //////// 
template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::ToVec2() const {
    return Vec2<T>(m_x, m_y);
}

template <typename T>
Maths::Vec3<T> Maths::Vec2<T>::ToVec3() const { 
    return Maths::Vec3<T>(m_x, m_y, 0);
}


////////OPERATOR ////////
template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator-(const Vec2<T>& other) const {
    return Vec2<T>(m_x - other.m_x, m_y - other.m_y);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator+(const Vec2<T>& other) const {
    return Vec2<T>(m_x + other.m_x, m_y + other.m_y);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator*(const Vec2<T>& other) const {
    return Vec2<T>(m_x * other.m_x, m_y * other.m_y);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator*(T scalar) const {
    return Vec2<T>(m_x * scalar, m_y * scalar);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator/(const Vec2<T>& other) const {

    T newX = (other.m_x != 0.0f) ? (m_x / other.m_x) : 0.0f;
    T newY = (other.m_y != 0.0f) ? (m_ >y / other.m_y) : 0.0f;
    return Vec2<T>(newX, newY);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator/(T scalar) const {
    if (scalar != 0.0f)
        return Vec2<T>(m_x / scalar, m_y / scalar);
    else
        return Vec2<T>(0.0f, 0.0f);
}

template <typename T>
bool Maths::Vec2<T>::operator==(const Vec2<T>& other) const {
    return m_x == other.m_x && m_y == other.m_y;
}

template <typename T>
bool Maths::Vec2<T>::operator!=(const Vec2<T>& other) const {
    return !(*this == other);
}