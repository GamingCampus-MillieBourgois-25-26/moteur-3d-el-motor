#pragma once

#include <iostream>
#include <limits>
#include <algorithm>
#include "MVec3.hpp"

namespace Maths {

    template<typename T = float>
    class Quat {
    public:
        T m_x, m_y, m_z, m_w;

        static_assert(std::is_arithmetic_v<T>);

        static constexpr T kEpsilon = static_cast<T>(1e-6);
        static constexpr T PI = static_cast<T>(3.14159265358979323846);

        Quat(T m_x, T m_y, T m_z, T m_w);
        Quat() = default;
		~Quat() = default;

        //////// GETTERS & SETTERS ////////
        T x() const { return m_x; }
        T y() const { return m_y; }
        T z() const { return m_z; }
        T w() const { return m_w; }

        void SetX(T newX) { m_x = newX; }
        void SetY(T newY) { m_y = newY; }
        void SetZ(T newZ) { m_z = newZ; }
        void SetW(T newW) { m_w = newW; }
        void Set(T newX, T newY, T newZ, T newW) { m_x = newX, m_y = newY, m_z = newZ, m_w = newW; }

		//////// STATIC PORPRETIES ////////
        static Quat<T> Identity();

        //////// PORPRETIES ////////
        Vec3<T> EulerAngles() const;
        Quat<T> Normalized() const;
        T Magnitude() const;
        T This(int i) const;

		//////// PUBLIC METHODS ////////
        void SetLookRotation(const Vec3<T>& forward, const Vec3<T>& up);
        void ToAngleAxis(T& angle, Vec3<T>& axis);
        void setFromToRotation(const Quat<T>& to);

        bool Equals(const Quat<T>& q) const;
        std::string ToString() const;

        //////// STATIC METHODS ////////
        static Quat<T> AngleAxis(T angle, const Quat<T>& axis);
        static Quat<T> SlerpUnclamped(const Quat<T>& b, T t);
        static Quat<T> LerpUnclamped(const Quat<T>& b, T t);
        static Quat<T> FromEuler(const Vec3<T>& eulerRad);
        static Quat<T> Slerp(const Quat<T>& a, const Quat<T>& b, T t);
        static Quat<T> Lerp(const Quat<T>& a, const Quat<T>& b, T t);
        static Quat<T> Cross(const Quat<T>& b) const;
        static Quat<T> Inverse(const Quat<T>& q);
        
        static Vec3<T> MulltiplyQuatVec(const Vec3<T>& v, const Quat<T>& q);
        static T Angle(const Quat<T>& a, const Quat<T>& b);
        static T Dot(const Quat<T>& a, const Quat<T>& b);

        static void LookRotation(const Vec3<T>& forward, const Vec3<T>& up);
        static void RotateTowards(const Quat<T>& to, T maxDegreesDelta);
        static void FromToRotation(const Quat<T>& to);
        void Normalize();

        //////// OPERATOR ////////
        Quat<T> operator*(const Quat<T>& q) const;
		bool operator==(const Maths::Quat<T>& q) const;
    };
    using Quatf = Quat<float>;
}

#include "Maths/src/MQuaternion.inl"