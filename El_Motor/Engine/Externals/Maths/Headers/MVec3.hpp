#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <limits>

namespace Maths {

    /// @brief A 3D vector class template for mathematical operations.
    /// @tparam T The numeric type (e.g., float, double, int).
    template <typename T = float>
    class Vec3 {
    public:
        /// @brief X component of the vector.
        T m_x;

        /// @brief Y component of the vector.
        T m_y;

        /// @brief Z component of the vector.
        T m_z;

        /// @brief Ensure that T is an arithmetic type (float, double, int, etc.)
        static_assert(std::is_arithmetic_v<T>);

        ////////// CONSTRUCTORS //////////

        /// @brief Constructs a vector with the given x, y, z components.
        /// @param m_x The x-component.
        /// @param m_y The y-component.
        /// @param m_z The z-component.
        Vec3(T m_x, T m_y, T m_z);

        /// @brief Default constructor (initializes components to zero).
        Vec3() = default;

        /// @brief Destructor.
        ~Vec3() = default;

        ////////// GETTERS & SETTERS //////////

        /// @brief Returns the x-component.
        /// @return The x-component.
        T x() const { return m_x; }

        /// @brief Returns the y-component.
        /// @return The y-component.
        T y() const { return m_y; }

        /// @brief Returns the z-component.
        /// @return The z-component.
        T z() const { return m_z; }

        /// @brief Sets the x-component.
        /// @param newX The new x value.
        void SetX(T newX) { m_x = newX; }

        /// @brief Sets the y-component.
        /// @param newY The new y value.
        void SetY(T newY) { m_y = newY; }

        /// @brief Sets the z-component.
        /// @param newZ The new z value.
        void SetZ(T newZ) { m_z = newZ; }

        /// @brief Sets all three components.
        /// @param newX New x-component.
        /// @param newY New y-component.
        /// @param newZ New z-component.
        void Set(T newX, T newY, T newZ) { m_x = newX; m_y = newY; m_z = newZ; }

        ////////// STATIC PROPERTIES //////////

        /// @brief Returns a vector pointing down (0, -1, 0).
        static Vec3 Down();

        /// @brief Returns a vector pointing up (0, 1, 0).
        static Vec3 Up();

        /// @brief Returns a vector pointing left (-1, 0, 0).
        static Vec3 Left();

        /// @brief Returns a vector pointing right (1, 0, 0).
        static Vec3 Right();

        /// @brief Returns a vector pointing back (0, 0, -1).
        static Vec3 Back();

        /// @brief Returns a vector pointing forward (0, 0, 1).
        static Vec3 Forward();

        /// @brief Returns a vector with all components equal to 1.
        static Vec3 One();

        /// @brief Returns a zero vector (0, 0, 0).
        static Vec3 Zero();

        /// @brief Returns a vector with all components set to positive infinity.
        static Vec3 PositiveInfinity();

        /// @brief Returns a vector with all components set to negative infinity.
        static Vec3 NegativeInfinity();

        ////////// PROPERTIES //////////

        /// @brief Returns a normalized vector (unit length).
        /// @return Normalized vector.
        Vec3 Normalized() const;

        /// @brief Returns the squared magnitude of the vector.
        /// @return Squared magnitude.
        T SqrtMagnitude() const;

        /// @brief Returns the magnitude (length) of the vector.
        /// @return Magnitude.
        T Magnitude() const;

        /// @brief Returns the component at index i (0=x, 1=y, 2=z).
        /// @param i Index of component.
        /// @return Component value.
        T This(int i) const;

        ////////// PUBLIC METHODS //////////

        /// @brief Checks if this vector is equal to another vector.
        /// @param other The vector to compare.
        /// @return True if equal, otherwise false.
        bool Equal(const Vec3& other) const;

        /// @brief Converts the vector to a string representation.
        /// @return A string representing the vector.
        std::string ToString() const;

        ////////// STATIC METHODS //////////

        /// @brief Rotates a vector towards a target vector by a maximum radians delta and magnitude delta.
        static Vec3 RotateTowards(const Vec3& current, const Vec3& target, const T maxRadiansDelta, const T maxMagnitudeDelta);

        /// @brief Moves a vector towards a target vector by a maximum distance.
        static Vec3 MoveTowards(const Vec3& current, const Vec3& target, const T maxDistanceDelta);

        /// @brief Projects a vector onto a plane defined by its normal.
        static Vec3 ProjectOnPlane(const Vec3& vector, const Vec3& planeNormal);

        /// @brief Reflects a vector off a plane defined by a normal.
        static Vec3 Reflect(const Vec3& inDirection, const Vec3& inNormal);

        /// @brief Clamps the magnitude of a vector to a maximum length.
        static Vec3 ClampMagnitude(const Vec3& a, const T MaxLength);

        /// @brief Spherical linear interpolation (unclamped) between two vectors.
        static Vec3 SlerpUnclamped(const Vec3& a, const Vec3& b, const T t);

        /// @brief Projects a vector onto another vector.
        static Vec3 Project(const Vec3& vector, const Vec3& onNormal);

        /// @brief Linear interpolation (unclamped) between two vectors.
        static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, const T t);

        /// @brief Spherical linear interpolation (clamped) between two vectors.
        static Vec3 Slerp(const Vec3& a, const Vec3& b, const T t);

        /// @brief Linear interpolation (clamped) between two vectors.
        static Vec3 Lerp(const Vec3& a, const Vec3& b, const T t);

        /// @brief Component-wise multiplication of two vectors.
        static Vec3 Scale(const Vec3& a, const Vec3& b);

        /// @brief Cross product of two vectors.
        static Vec3 Cross(const Vec3& a, const Vec3& b);

        /// @brief Component-wise minimum of two vectors.
        static Vec3 Min(const Vec3& a, const Vec3& b);

        /// @brief Component-wise maximum of two vectors.
        static Vec3 Max(const Vec3& a, const Vec3& b);

        /// @brief Computes the signed angle between two vectors around a specified axis.
        static T SignedAngle(const Vec3& from, const Vec3& to, const Vec3& axis);

        /// @brief Calculates distance between two vectors.
        static T Distance(const Vec3& a, const Vec3& b);

        /// @brief Calculates angle between two vectors.
        static T Angle(const Vec3& a, const Vec3& b);

        /// @brief Dot product of two vectors.
        static T Dot(const Vec3& a, const Vec3& b);

        /// @brief Orthonormalizes two vectors (normal and tangent).
        static void OrthoNormalize(Vec3& normal, Vec3& tangent);

        /// @brief Normalizes the vector in place.
        void Normalize();

        ////////// OPERATORS //////////

        /// @brief Subtracts another vector from this vector.
        Vec3 operator-(const Vec3& other) const;

        /// @brief Adds another vector to this vector.
        Vec3 operator+(const Vec3& other) const;

        /// @brief Component-wise multiplication.
        Vec3 operator*(const Vec3& other) const;

        /// @brief Multiplies the vector by a scalar.
        Vec3 operator*(T scalar) const;

        /// @brief Component-wise division.
        Vec3 operator/(const Vec3& other) const;

        /// @brief Divides the vector by a scalar.
        Vec3 operator/(T scalar) const;

        /// @brief Checks equality between two vectors.
        bool operator==(const Vec3& other) const;

        /// @brief Checks inequality between two vectors.
        bool operator!=(const Vec3& other) const;
    };

    /// @brief Type alias for Vec3 with float components.
    using Vec3f = Vec3<float>;

}

#include "Maths/src/MVec3.inl"