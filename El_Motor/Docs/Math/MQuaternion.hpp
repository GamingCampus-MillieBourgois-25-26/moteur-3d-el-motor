#pragma once

#include <iostream>
#include <limits>
#include <algorithm>
#include "MVec3.hpp"

namespace Maths {

    /// <summary>
    /// Quaternion class template for rotations in 3D space
    /// Supports Euler conversion, normalization, multiplication, slerp/lerp, and rotation helpers
    /// </summary>
    template<typename T = float>
    class Quat {
    public:
        T m_x, m_y, m_z, m_w;          // Quaternion components

        static_assert(std::is_arithmetic_v<T>);

        static constexpr T kEpsilon = static_cast<T>(1e-6);   // Small epsilon for floating-point comparisons
        static constexpr T PI = static_cast<T>(3.14159265358979323846);

        /// <summary>Constructor from components</summary>
        Quat(T m_x, T m_y, T m_z, T m_w);

        /// <summary>Default constructor (uninitialized)</summary>
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

        void Set(T newX, T newY, T newZ, T newW) {
            m_x = newX; m_y = newY; m_z = newZ; m_w = newW;
        }

        //////// STATIC PROPERTIES ////////
        /// <summary>Return identity quaternion (no rotation)</summary>
        static Quat<T> Identity();

        //////// INSTANCE PROPERTIES ////////
        /// <summary>Convert quaternion to Euler angles (radians)</summary>
        Vec3<T> EulerAngles() const;

        /// <summary>Return normalized quaternion</summary>
        Quat<T> Normalized() const;

        /// <summary>Compute magnitude of quaternion</summary>
        T Magnitude() const;

        /// <summary>Access component by index (0=x,1=y,2=z,3=w)</summary>
        T This(int i) const;

        //////// PUBLIC METHODS ////////
        /// <summary>Set quaternion from forward and up vectors</summary>
        void SetLookRotation(const Vec3<T>& forward, const Vec3<T>& up);

        /// <summary>Extract rotation angle and axis from quaternion</summary>
        void ToAngleAxis(T& angle, Vec3<T>& axis);

        /// <summary>Set quaternion to represent rotation from this to another quaternion</summary>
        void setFromToRotation(const Quat<T>& to);

        /// <summary>Check equality with another quaternion</summary>
        bool Equals(const Quat<T>& q) const;

        /// <summary>Return a string representation for debugging</summary>
        std::string ToString() const;

        //////// STATIC METHODS ////////
        static Quat<T> AngleAxis(T angle, const Quat<T>& axis);
        static Quat<T> SlerpUnclamped(const Quat<T>& b, T t);
        static Quat<T> LerpUnclamped(const Quat<T>& b, T t);
        static Quat<T> FromEuler(const Vec3<T>& eulerRad);
        static Quat<T> Slerp(const Quat<T>& a, const Quat<T>& b, T t);
        static Quat<T> Lerp(const Quat<T>& a, const Quat<T>& b, T t);
        static Quat<T> Cross(const Quat<T>& b);
        static Quat<T> Inverse(const Quat<T>& q);

        /// <summary>Rotate a vector by quaternion</summary>
        static Vec3<T> MulltiplyQuatVec(const Vec3<T>& v, const Quat<T>& q);

        /// <summary>Compute angle between two quaternions</summary>
        static T Angle(const Quat<T>& a, const Quat<T>& b);

        /// <summary>Dot product of two quaternions</summary>
        static T Dot(const Quat<T>& a, const Quat<T>& b);

        static void LookRotation(const Vec3<T>& forward, const Vec3<T>& up);
        static void RotateTowards(const Quat<T>& to, T maxDegreesDelta);
        static void FromToRotation(const Quat<T>& to);

        /// <summary>Normalize quaternion in place</summary>
        void Normalize();

        //////// OPERATORS ////////
        /// <summary>Quaternion multiplication (composition of rotations)</summary>
        Quat<T> operator*(const Quat<T>& q) const;

        /// <summary>Equality operator</summary>
        bool operator==(const Maths::Quat<T>& q) const;
    };

    /// <summary>Float specialization</summary>
    using Quatf = Quat<float>;
}

#include "Maths/src/MQuaternion.inl"