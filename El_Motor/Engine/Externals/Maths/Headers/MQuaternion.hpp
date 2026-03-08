#pragma once

#include <iostream>
#include <limits>
#include <algorithm>
#include "MVec3.hpp"

namespace Maths {

    /**
     * @brief Quaternion class template for rotations in 3D space.
     *
     * Supports Euler conversion, normalization, multiplication, slerp/lerp,
     * angle-axis conversion, and rotation helpers.
     * @tparam T Numeric type (float or double)
     */
    template<typename T = float>
    class Quat {
    public:
        T m_x, m_y, m_z, m_w;  /**< Quaternion components */

        static_assert(std::is_arithmetic_v<T>);

        static constexpr T kEpsilon = static_cast<T>(1e-6);   /**< Small epsilon for floating-point comparisons */
        static constexpr T PI = static_cast<T>(3.14159265358979323846);

        /// @brief Constructor from individual components
        Quat(T m_x, T m_y, T m_z, T m_w);

        /// @brief Default constructor (uninitialized quaternion)
        Quat() = default;

        ~Quat() = default;

        ////////// GETTERS & SETTERS //////////

        T x() const { return m_x; } /**< Get X component */
        T y() const { return m_y; } /**< Get Y component */
        T z() const { return m_z; } /**< Get Z component */
        T w() const { return m_w; } /**< Get W component */

        void SetX(T newX) { m_x = newX; }
        void SetY(T newY) { m_y = newY; }
        void SetZ(T newZ) { m_z = newZ; }
        void SetW(T newW) { m_w = newW; }

        /**
         * @brief Set all components at once
         */
        void Set(T newX, T newY, T newZ, T newW) {
            m_x = newX; m_y = newY; m_z = newZ; m_w = newW;
        }

        ////////// STATIC PROPERTIES //////////

        /// @brief Return identity quaternion (no rotation)
        static Quat<T> Identity();

        ////////// INSTANCE METHODS //////////

        /// @brief Convert quaternion to Euler angles (radians)
        Vec3<T> EulerAngles() const;

        /// @brief Return normalized quaternion
        Quat<T> Normalized() const;

        /// @brief Compute magnitude of quaternion
        T Magnitude() const;

        /**
         * @brief Access component by index
         * @param i Component index (0=x,1=y,2=z,3=w)
         */
        T This(int i) const;

        /// @brief Set quaternion from forward and up vectors
        void SetLookRotation(const Vec3<T>& forward, const Vec3<T>& up);

        /// @brief Extract rotation angle and axis from quaternion
        void ToAngleAxis(T& angle, Vec3<T>& axis);

        /// @brief Set quaternion to represent rotation from this to another quaternion
        void setFromToRotation(const Quat<T>& to);

        /// @brief Check equality with another quaternion
        bool Equals(const Quat<T>& q) const;

        /// @brief Return a string representation for debugging
        std::string ToString() const;

        ////////// STATIC METHODS //////////

        static Quat<T> AngleAxis(T angle, const Quat<T>& axis);
        static Quat<T> SlerpUnclamped(const Quat<T>& b, T t);
        static Quat<T> LerpUnclamped(const Quat<T>& b, T t);
        static Quat<T> FromEuler(const Vec3<T>& eulerRad);
        static Quat<T> Slerp(const Quat<T>& a, const Quat<T>& b, T t);
        static Quat<T> Lerp(const Quat<T>& a, const Quat<T>& b, T t);
        static Quat<T> Cross(const Quat<T>& b);
        static Quat<T> Inverse(const Quat<T>& q);

        /// @brief Rotate a vector by a quaternion
        static Vec3<T> MulltiplyQuatVec(const Vec3<T>& v, const Quat<T>& q);

        /// @brief Compute angle between two quaternions
        static T Angle(const Quat<T>& a, const Quat<T>& b);

        /// @brief Dot product of two quaternions
        static T Dot(const Quat<T>& a, const Quat<T>& b);

        static void LookRotation(const Vec3<T>& forward, const Vec3<T>& up);
        static void RotateTowards(const Quat<T>& to, T maxDegreesDelta);
        static void FromToRotation(const Quat<T>& to);

        /// @brief Normalize quaternion in place
        void Normalize();

        ////////// OPERATORS //////////

        /// @brief Quaternion multiplication (composition of rotations)
        Quat<T> operator*(const Quat<T>& q) const;

        /// @brief Equality operator
        bool operator==(const Maths::Quat<T>& q) const;
    };

    /// @brief Float specialization
    using Quatf = Quat<float>;
}

#include "Maths/src/MQuaternion.inl"