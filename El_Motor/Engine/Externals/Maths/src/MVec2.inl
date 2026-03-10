template <typename T>
Maths::Vec2<T>::Vec2(T m_x, T m_y) : m_x(m_x), m_y(m_y) {}


//////// STATIC PORPRETIES ////////
template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Down() { return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(-1)); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Up() { return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(1)); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Left() { return Maths::Vec2<T>(static_cast<T>(-1), static_cast<T>(0)); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Right() { return Maths::Vec2<T>(static_cast<T>(1), static_cast<T>(0)); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::One() { return Maths::Vec2<T>(static_cast<T>(1), static_cast<T>(1)); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Zero() { return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::PositiveInfinity() { return Maths::Vec2<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()); }

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::NegativeInfinity() { return Maths::Vec2<T>(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()); }


//////// PORPRETIES ////////
template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Normalized() const {

    T mag = Magnitude();
    if (mag != 0.0f)
        return Maths::Vec2<T>(m_x / mag, m_y / mag);
    else
        return Maths::Vec2<T>(static_cast<T>(0), static_cast<T>(0));
}

template <typename T>
T Maths::Vec2<T>::SqrtMagnitude() const {
    return m_x * m_x + m_y * m_y;
}
template <typename T>
T Maths::Vec2<T>::Magnitude()const { return std::sqrt(m_x * m_x + m_y * m_y); }

template <typename T>
T Maths::Vec2<T>::This(int i) const {
    if (i == 0) return m_x;
    if (i == 1) return m_y;
    throw std::out_of_range("Vec2 index");
}

//////// PUBLIC METHODS ////////
template <typename T>
bool Maths::Vec2<T>::Equal(const Vec2& other) const {
    if (m_x == other.m_x && m_y == other.m_y) return true;
    else return false;
}

template <typename T>
std::string Maths::Vec2<T>::ToString() const { 
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}


//////// STATIC METHODS ////////
template<typename T>
Maths::Vec2<T> Maths::Vec2<T>::MoveTowards(const Vec2& current, const Vec2& target, T maxDistanceDelta)
{
    Vec2<T> direction = target - current;
    T distance = direction.Magnitude();
    if (distance == 0 || (maxDistanceDelta >= 0 && distance <= maxDistanceDelta)) { return target; }

    return current + (target - current).Normalized() * maxDistanceDelta;
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::LerpUnclamped(const Vec2& a, const Vec2& b, T t) {
    return a + (b - a) * t;
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::ClampMagnitude(const Vec2& a, T maxLength) {
    T mag = a.Magnitude();
    if (mag > maxLength)
        return a.Normalized() * maxLength;
    return a;
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Perpendicular(const Vec2& inDirection) {
    return Vec2<T>(-inDirection.m_y, inDirection.m_x);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Lerp(const Vec2& a, const Vec2& b, T t) {
    t = std::clamp(t, static_cast<T>(0), static_cast<T>(1));
    return a + (b - a) * t;
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Scale(const Vec2& a, const Vec2& b) {
    return Vec2<T>(a.m_x * b.m_x, a.m_y * b.m_y);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Min(const Vec2& a, const Vec2& b) {
    return Vec2<T>(std::fmin(a.m_x, b.m_x), std::fmin(a.m_y, b.m_y));
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::Max(const Vec2& a, const Vec2& b) {
    return Vec2<T>(std::fmax(a.m_x, b.m_x), std::fmax(a.m_y, b.m_y));
}


template <typename T>
T Maths::Vec2<T>::SignedAngle(const Vec2& from, const Vec2& to) {
    T angle = Angle(from, to);
    T cross = from.m_x * to.m_y - from.m_y * to.m_x;
    return (cross < 0) ? -angle : angle;
}

template <typename T>
T Maths::Vec2<T>::Distance(const Vec2& a, const Vec2& b) {
    return Vec2<T>(a - b).Magnitude();
}

template <typename T>
T Maths::Vec2<T>::Angle(const Vec2& a, const Vec2& b) {
    T dotProd = a.m_x * b.m_x + a.m_y * b.m_y;
    T lenA = a.Magnitude();
    T lenB = b.Magnitude();
    T cosAngle = std::clamp(dotProd / (lenA * lenB), -1.0f, 1.0f);
    return std::acos(cosAngle); // retourne en radians

}

template <typename T>
T Maths::Vec2<T>::Dot(const Vec2& a, const Vec2& b) {
    return (a.m_x * b.m_x + a.m_y * b.m_y);
}


template <typename T>
void Maths::Vec2<T>::Normalize() {
    T mag = Magnitude();
    if (mag != static_cast<T>(0)) {
        m_x /= mag;
        m_y /= mag;
    }
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

    T newX = (other.m_x != static_cast<T>(0)) ? (m_x / other.m_x) : static_cast<T>(0);
    T newY = (other.m_y != static_cast<T>(0)) ? (m_y / other.m_y) : static_cast<T>(0);
    return Vec2<T>(newX, newY);
}

template <typename T>
Maths::Vec2<T> Maths::Vec2<T>::operator/(T scalar) const {
    if (scalar != static_cast<T>(0))
        return Vec2<T>(m_x / scalar, m_y / scalar);
    else
        return Vec2<T>(static_cast<T>(0), static_cast<T>(0));
}

template <typename T>
bool Maths::Vec2<T>::operator==(const Vec2<T>& other) const {
    return m_x == other.m_x && m_y == other.m_y;
}

template <typename T>
bool Maths::Vec2<T>::operator!=(const Vec2<T>& other) const {
    return !(*this == other);
}