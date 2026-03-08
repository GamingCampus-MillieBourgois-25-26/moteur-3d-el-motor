#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include "MVec3.hpp"

namespace Maths {

    /// @brief A 2D vector class template for mathematical operations.
    /// @tparam T The numeric type (e.g., float, double, int).
    template <typename T = float>
    class Vec2 {
    public:
        /// @brief X component of the vector.
        T m_x;

        /// @brief Y component of the vector.
        T m_y;

        /// @brief Ensure that T is an arithmetic type (e.g., float, int).
        static_assert(std::is_arithmetic_v<T>);

        /// @brief Constructs a vector with the given x and y components.
        /// @param m_x The x-component.
        /// @param m_y The y-component.
        Vec2(T m_x, T m_y);

        /// @brief Default constructor (initializes to (0,0)).
        Vec2() = default;

        /// @brief Destructor.
        ~Vec2() = default;

        ////////// GETTERS & SETTERS //////////

        /// @brief Returns the x-component.
        /// @return The x-component.
        T x() const { return m_x; }

        /// @brief Returns the y-component.
        /// @return The y-component.
        T y() const { return m_y; }

        /// @brief Sets the x-component to a new value.
        /// @param newX The new x value.
        void SetX(T newX) { m_x = newX; }

        /// @brief Sets the y-component to a new value.
        /// @param newY The new y value.
        void SetY(T newY) { m_y = newY; }

        /// @brief Sets both components of the vector.
        /// @param newX The new x value.
        /// @param newY The new y value.
        void Set(T newX, T newY) { m_x = newX, m_y = newY; }

        ////////// STATIC PROPERTIES //////////

        /// @brief Returns a vector pointing down (0, -1).
        /// @return The down vector.
        static Vec2 Down();

        /// @brief Returns a vector pointing up (0, 1).
        /// @return The up vector.
        static Vec2 Up();

        /// @brief Returns a vector pointing left (-1, 0).
        /// @return The left vector.
        static Vec2 Left();

        /// @brief Returns a vector pointing right (1, 0).
        /// @return The right vector.
        static Vec2 Right();

        /// @brief Returns a vector with both components set to 1 (1, 1).
        /// @return The one vector.
        static Vec2 One();

        /// @brief Returns a zero vector (0, 0).
        /// @return The zero vector.
        static Vec2 Zero();

        /// @brief Returns a vector with both components set to positive infinity.
        /// @return The positive infinity vector.
        static Vec2 PositiveInfinity();

        /// @brief Returns a vector with both components set to negative infinity.
        /// @return The negative infinity vector.
        static Vec2 NegativeInfinity();

        ////////// PROPERTIES //////////

        /// @brief Returns a normalized (unit length) vector.
        /// @return The normalized vector.
        Vec2 Normalized() const;

        /// @brief Returns the squared magnitude of the vector.
        /// @return The squared magnitude.
        T SqrtMagnitude() const;

        /// @brief Returns the magnitude (length) of the vector.
        /// @return The magnitude.
        T Magnitude() const;

        /// @brief Returns the component at index i (0 -> x, 1 -> y).
        /// @param i The index (0 or 1).
        /// @return The component at index i.
        T This(int i) const;

        ////////// PUBLIC METHODS //////////

        /// @brief Checks if this vector is equal to another vector.
        /// @param other The vector to compare with.
        /// @return True if equal, otherwise false.
        bool Equal(const Vec2& other) const;

        /// @brief Converts the vector to a string representation.
        /// @return A string representing the vector.
        std::string ToString() const;

        ////////// STATIC METHODS //////////

        /// @brief Moves the current vector towards the target vector by a maximum distance delta.
        /// @param current The current vector.
        /// @param target The target vector.
        /// @param maxDistanceDelta The maximum distance to move.
        /// @return The resulting vector after moving towards the target.
        static Vec2 MoveTowards(const Vec2& current, const Vec2& target, T maxDistanceDelta);

        /// @brief Linearly interpolates (unclamped) between two vectors.
        /// @param a The start vector.
        /// @param b The end vector.
        /// @param t Interpolation factor (unclamped).
        /// @return The interpolated vector.
        static Vec2 LerpUnclamped(const Vec2& a, const Vec2& b, T t);

        /// @brief Clamps the magnitude of a vector to a maximum length.
        /// @param a The vector to clamp.
        /// @param maxLength The maximum allowed length.
        /// @return The clamped vector.
        static Vec2 ClampMagnitude(const Vec2& a, T maxLength);

        /// @brief Returns a vector perpendicular to the input vector.
        /// @param inDirection The original vector.
        /// @return The perpendicular vector.
        static Vec2 Perpendicular(const Vec2& inDirection);

        /// @brief Linearly interpolates (clamped) between two vectors.
        /// @param a The start vector.
        /// @param b The end vector.
        /// @param t Interpolation factor (clamped).
        /// @return The interpolated vector.
        static Vec2 Lerp(const Vec2& a, const Vec2& b, T t);

        /// @brief Component-wise multiplication of two vectors.
        /// @param a First vector.
        /// @param b Second vector.
        /// @return The resulting vector after component-wise multiplication.
        static Vec2 Scale(const Vec2& a, const Vec2& b);

        /// @brief Returns the component-wise minimum of two vectors.
        /// @param a First vector.
        /// @param b Second vector.
        /// @return The vector with the minimum components.
        static Vec2 Min(const Vec2& a, const Vec2& b);

        /// @brief Returns the component-wise maximum of two vectors.
        /// @param a First vector.
        /// @param b Second vector.
        /// @return The vector with the maximum components.
        static Vec2 Max(const Vec2& a, const Vec2& b);

        /// @brief Calculates the signed angle (in radians) between two vectors.
        /// @param from The first vector.
        /// @param to The second vector.
        /// @return The signed angle between the vectors.
        static T SignedAngle(const Vec2& from, const Vec2& to);

        /// @brief Calculates the distance between two vectors.
        /// @param a First vector.
        /// @param b Second vector.
        /// @return The distance between the vectors.
        static T Distance(const Vec2& a, const Vec2& b);

        /// @brief Calculates the angle (in radians) between two vectors.
        /// @param a First vector.
        /// @param b Second vector.
        /// @return The angle between the vectors.
        static T Angle(const Vec2& a, const Vec2& b);

        /// @brief Calculates the dot product of two vectors.
        /// @param a First vector.
        /// @param b Second vector.
        /// @return The dot product.
        static T Dot(const Vec2& a, const Vec2& b);

        /// @brief Normalizes the vector in place (makes it a unit vector).
        void Normalize();

        ////////// CONVERSIONS //////////

        /// @brief Returns the vector as itself (no conversion).
        /// @return The same vector.
        Vec2<T> ToVec2() const;

        /// @brief Converts this 2D vector to a 3D vector (z-component = 0).
        /// @return The corresponding 3D vector.
        Vec3<T> ToVec3() const;

        ////////// OPERATORS //////////

        /// @brief Subtracts another vector from this vector.
        /// @param other The vector to subtract.
        /// @return The resulting vector.
        Vec2 operator-(const Vec2& other) const;

        /// @brief Adds another vector to this vector.
        /// @param other The vector to add.
        /// @return The resulting vector.
        Vec2 operator+(const Vec2& other) const;

        /// @brief Component-wise multiplication of two vectors.
        /// @param other The vector to multiply with.
        /// @return The resulting vector.
        Vec2 operator*(const Vec2& other) const;

        /// @brief Multiplies this vector by a scalar.
        /// @param scalar The scalar to multiply with.
        /// @return The resulting vector.
        Vec2 operator*(T scalar) const;

        /// @brief Component-wise division of two vectors.
        /// @param other The vector to divide by.
        /// @return The resulting vector.
        Vec2 operator/(const Vec2& other) const;

        /// @brief Divides this vector by a scalar.
        /// @param scalar The scalar to divide by.
        /// @return The resulting vector.
        Vec2 operator/(T scalar) const;

        /// @brief Checks if this vector is equal to another vector.
        /// @param other The vector to compare with.
        /// @return True if equal, otherwise false.
        bool operator==(const Vec2& other) const;

        /// @brief Checks if this vector is not equal to another vector.
        /// @param other The vector to compare with.
        /// @return True if not equal, otherwise false.
        bool operator!=(const Vec2& other) const;
    };

    /// @brief Type alias for a Vec2 with float components.
    using Vec2f = Vec2<float>;
}

#include "Maths/src/MVec2.inl"