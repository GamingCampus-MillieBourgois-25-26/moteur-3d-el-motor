#include "MVec3.hpp"

template <typename T>
Maths::Vec3<T>::Vec3(T m_x, T m_y, T m_z) : m_x(m_x), m_y(m_y), m_z(m_z) {}


//////// STATIC PORPRETIES ////////
template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Down() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Up() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Left() { return Maths::Vec3<T>(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Right() { return Maths::Vec3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Back() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Forward() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::One() { return Maths::Vec3<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::Zero() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::PositiveInfinity() { return Maths::Vec3<T>(std::numeric_limits<T>::infinity()), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()); }

template <typename T>
static Maths::Vec3<T> Maths::Vec3<T>::NegativeInfinity() { return Maths::Vec3<T>(-std::numeric_limits<T>::infinity()), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()); }


//////// PORPRETIES ////////
template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Normalized() { // Renvoies une copie normalisée du vecteur
	T mag = Magnitude();
	if (mag != 0.0f)
		return Maths::Vec3<T>(m_x / mag, m_y / mag, m_z / mag);
	else
		return Maths::Vec3<T>(0.0f, 0.0f, 0.0f);
}

template <typename T>
T Maths::Vec3<T>::Magnitude() { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); } 

template <typename T>
T Maths::Vec3<T>::SqrtMagnitude() {
	T mag = (*this).Magnitude();  
	return std::pow((mag), 2); } 

template <typename T>
T Maths::Vec3<T>::This(int i) {
	if (i == 0) return m_x;
	else if (i == 1) return m_y;
	else if (i == 2) return m_z;
}


//////// PUBLIC METHODS ////////
template <typename T>
bool Maths::Vec3<T>::Equal(Vec3<T>& other) { 
	if (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z) return true;
	else return false;
}

template <typename T>
std::string Maths::Vec3<T>::ToString() { 
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ")";
}


/////// STATIC METHODS ////////
template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::RotateTowards(Vec3<T> current, Vec3<T> target, T maxRadiansDelta, T maxMagnitudeDelta) { 
	Vec3 a = current.Normalized();
	Vec3 b = target.Normalized();
	T theta = acos(Dot(a, b));
	Vec3 rotationAxis = Cross(a, b);
	Vec3 nomalizedRotationAxis = rotationAxis.Normalized();
	return a * cos(theta) + Cross(rotationAxis, a) * sin(theta) + rotationAxis * (Dot(rotationAxis, a)) * (1 - cos(theta));
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::MoveTowards(Vec3<T> current, Vec3<T> target, T maxDistanceDelta) { 
	Vec3 direction = target - current;
	T distance = direction.Magnitude();
	if (distance == 0 || (maxDistanceDelta >= 0 && distance <= maxDistanceDelta)) { return target; }
	return current + direction / distance * maxDistanceDelta;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::ProjectOnPlane(Vec3<T> vector, Vec3<T> planeNormal) 
{
	T dot1 = Dot(vector, planeNormal);
	T dot2 = Dot(planeNormal, planeNormal);
	if (dot2 == 0) // éviter la division par zéro
		return Maths::Vec3<T>::Zero();
	return vector - planeNormal * (dot1 / dot2);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Reflect(Vec3<T> inDirection, Vec3<T> inNormal) { 
	Vec3<T> n = inNormal.Normalized();
	T dot = Dot(inDirection, inNormal);
	return inDirection - inNormal * dot * 2;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::ClampMagnitude(Vec3<T>& a, T maxLength) { 
	T mag = a.Magnitude();
	if (mag > maxLength)
		return a.Normalized() * maxLength;
	return a;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::SlerpUnclamped(Vec3<T> a, Vec3<T> b, T t) {  
	Vec3 aNormal = a.Normalized();
	Vec3 bNormal = b.Normalized();
	T theta = acos(Dot(aNormal, bNormal));
	return bNormal * (sin(t * theta) / sin(theta)) + aNormal * sin((1 - t) * theta) / sin(theta);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Project(Vec3<T> vector, Vec3<T> onNormal) {
	T dot1 = Dot(vector, onNormal);
	T dot2 = Dot(onNormal, onNormal);
	return onNormal * (dot1 / dot2);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::LerpUnclamped(Vec3<T> a, Vec3<T> b, T t) { 
	return a + (b - a) * t;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Slerp(Vec3<T> a, Vec3<T> b, T t) {
	Vec3<T> aNormal = a.Normalized();
	Vec3<T> bNormal = b.Normalized();

	T dotProd = Dot(aNormal, bNormal);
	dotProd = std::fmax(std::fmin(dotProd, 1.0f), -1.0f); // clamp [-1,1]
	T theta = std::acos(dotProd);
	T sinTheta = std::sin(theta);

	T factorA = std::sin((1 - t) * theta) / sinTheta;
	T factorB = std::sin(t * theta) / sinTheta;

	return (aNormal * factorA + bNormal * factorB).Normalized();
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Lerp(Vec3<T> a, Vec3<T> b, T t) { 
	t = std::clamp(t, 0.0f, 1.0f);
	return a + (b - a) * t;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Scale(Vec3<T>& a, Vec3<T>& b) {
	return Vec3(a.m_x * b.m_x, a.m_y * b.m_y, a.m_z * b.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Cross(Vec3<T>& a, Vec3<T>& b) { 
	return Vec3((a.m_y * b.m_z) - (a.m_z * b.m_y), (a.m_z * b.m_x) - (a.m_x * b.m_z), (a.m_x * b.m_y) - (a.m_y * b.m_x));
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Min(Vec3<T>& a, Vec3<T>& b) { 
	return Vec3(std::fmin(a.m_x, b.m_x), std::fmin(a.m_y, b.m_y), fmin(a.m_z, b.m_z));
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Max(Vec3<T>& a, Vec3<T>& b) { 
	return Vec3(std::fmax(a.m_x, b.m_x), std::fmax(a.m_y, b.m_y), fmax(a.m_z, b.m_z));
}


template <typename T>
T Maths::Vec3<T>::SignedAngle(Vec3<T> from, Vec3<T> to, Vec3<T> axis) { 
	T angle = Angle(from, to);
	Vector3 cross = Cross(from, to);
	return (Dot(axis, cross) < 0) ? -angle : angle;
}






//////// OPERATOR ////////
template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator-(const Vec3<T>& other) const {
	return Vec3<T>(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator+(const Vec3<T>& other) const {
	return Vec3<T>(m_x + other.m_x, m_y + other.m_y, m_z - other.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator*(const Vec3<T>& other) const {
	return Vec3<T>(m_x * other.m_x, m_y * other.m_y, m_z - other.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator*(T scalar) const {
	return Vec3<T>(m_x * scalar, m_y * scalar, m_z - scalar);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator/(const Vec3<T>& other) const {

	T newX = (other.m_x != 0.0f) ? (m_x / other.m_x) : 0.0f;
	T newY = (other.m_y != 0.0f) ? (m_y / other.m_y) : 0.0f;
	T newZ = (other.m_z != 0.0f) ? (m_z / other.m_z) : 0.0f;
	return Vec3<T>(newX, newY, newZ);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator/(T scalar) const {
	if (scalar != 0.0f)
		return Vec3<T>(m_x / scalar, m_y / scalar, m_z - scalar);
	else
		return Vec3<T>(0.0f, 0.0f, 0.0f);
}

template <typename T>
bool Maths::Vec3<T>::operator==(const Vec3<T>& other) const {
	return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

template <typename T>
bool Maths::Vec3<T>::operator!=(const Vec3<T>& other) const {
	return !(*this == other);
}