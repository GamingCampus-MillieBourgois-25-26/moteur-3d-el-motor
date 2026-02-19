#pragma once

#include "Vec3.hpp"

template <typename T>
Math::Vec3<T>::Vec3(T m_x, T m_y, T m_z) : m_x(m_x), m_y(m_y), m_z(m_z) {}

/////// STATIC PORPRETIES ///////
template<typename T>
inline Math::Vec3<T> Math::Vec3<T>::Down() { return Math::Vec3<T>(0.0f, -1.0f, 0.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::Up() { return Math::Vec3<T>(0.0f, 1.0f, 0.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::Left() { return Math::Vec3<T>(-1.0f, 0.0f, 0.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::Right() { return Math::Vec3<T>(1.0f, 0.0f, 0.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::Back() { return Math::Vec3<T>(0.0f, 0.0f, -1.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::Forward() { return Math::Vec3<T>(0.0f, 0.0f, 1.0f); }


template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::One() { return Math::Vec3<T>(1.0f, 1.0f, 1.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::Zero() { return Math::Vec3<T>(0.0f, 0.0f, 0.0f); }

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::PositiveInfinity() { return Math::Vec3<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()), std::numeric_limits<T>::infinity()); };

template <typename T>
inline Math::Vec3<T> Math::Vec3<T>::NegativeInfinity() { return Math::Vec3<T>(-1 * (std::numeric_limits<T>::infinity()), -1 * (std::numeric_limits<T>::infinity())), 1 * (std::numeric_limits<T>::infinity())); };



/////// PORPRETIES ///////
template <typename T>
T Math::Vec3<T>::Magnitude() { return std::sqrt(m_x * m_x + m_y * m_y, m_z * m_z); }

template <typename T>
Math::Vec3<T> Math::Vec3<T>::Normalized() {
	T mag = Magnitude();
	if (mag != 0.0f)
		return Math::Vec3<T>(m_x / mag, m_y / mag, m_z / mag);
	else
		return Math::Vec3<T>(0.0f, 0.0f, 0.0f);
}

template <typename T>
T Math::Vec3<T>::SqrtMagnitude() {
	T mag = Magnitude();
	return pow((mag), 2);
}

template <typename T>
T Math::Vec3<T>::This(int i) {
	if (i == 0) return m_x;
	else if (i == 1) return m_y;
	else if (i == 2) return m_z;
}

template <typename T>
T Math::Vec3<T>::x() const { return m_x; }

template <typename T>
T Math::Vec3<T>::y() const { return m_y; }

template <typename T>
T Math::Vec3<T>::z() const { return m_z; }





/////// OPERATORS ///////
template <typename T>
Math::Vec3<T> Math::Vec3<T>::operator+(const Vec3<T>& other) const {
	return Vec3<T>(this->x + other.x, this->y + other.y, this->z - other.z);
}

template <typename T>
Math::Vec3<T> Math::Vec3<T>::operator-(const Vec3<T>& other) const {
	return Vec3<T>(this->x - other.x, this->y - other.y, this->z - other.z);
}


template <typename T>
Math::Vec3<T> Math::Vec3<T>::operator*(const Vec3<T>& other) const {
	return Vec3<T>(this->x * other.x, this->y * other.y, this->z - other.z);
}

template <typename T>
Math::Vec3<T> Math::Vec3<T>::operator*(T scalar) const {
	return Vec3<T>(this->x * scalar, this->y * scalar, this->z - scalar);
}


template <typename T>
Math::Vec3<T> Math::Vec3<T>::operator/(const Vec3<T>& other) const {

	T newX = (other.x != 0.0f) ? (this->x / other.x) : 0.0f;
	T newY = (other.y != 0.0f) ? (this->y / other.y) : 0.0f;
	T newZ = (other.z != 0.0f) ? (this->z / other.z) : 0.0f;
	return Vec3<T>(newX, newY, newZ);
}

template <typename T>
Math::Vec3<T> Math::Vec3<T>::operator/(T scalar) const {
	if (scalar != 0.0f)
		return Vec3<T>(this->x / scalar, this->y / scalar, this->z - scalar);
	else
		return Vec3<T>(0.0f, 0.0f, 0.0f);
}


template <typename T>
bool Math::Vec3<T>::operator==(const Vec3<T>& other) const {
	return this->x == other.x && this->y == other.y && this->z == other.z;
}

template <typename T>
bool Math::Vec3<T>::operator!=(const Vec3<T>& other) const {
	return !(*this == other);
}