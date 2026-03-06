#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <limits>

namespace Maths {

    template <typename T = float>
    class Vec3 {
    public:
        T m_x;
        T m_y;
        T m_z;

        static_assert(std::is_arithmetic_v<T>);

        // Constructors
        Vec3(T m_x, T m_y, T m_z);
        Vec3() = default;
        ~Vec3() = default;

        //////// GETTERS & SETTERS ////////
        T x() const { return m_x; }
        T y() const { return m_y; }
        T z() const { return m_z; }

        void SetX(T newX) { m_x = newX; }
        void SetY(T newY) { m_y = newY; }
        void SetZ(T newZ) { m_z = newZ; }
        void Set(T newX, T newY, T newZ) { m_x = newX; m_y = newY; m_z = newZ; }

        //////// STATIC PROPERTIES ////////
        static Vec3 Down();
        static Vec3 Up();
        static Vec3 Left();
        static Vec3 Right();
        static Vec3 Back();
        static Vec3 Forward();
        static Vec3 One();
        static Vec3 Zero();
        static Vec3 PositiveInfinity();
        static Vec3 NegativeInfinity();

        //////// PROPERTIES ////////
        Vec3 Normalized() const;
        T SqrtMagnitude() const;
        T Magnitude() const;
        T This(int i) const;

        //////// PUBLIC METHODS ////////
        bool Equal(const Vec3& other) const;
        std::string ToString() const;

        //////// STATIC METHODS ////////
        static Vec3 RotateTowards(const Vec3& current, const Vec3& target, const T maxRadiansDelta, const T maxMagnitudeDelta);
        static Vec3 MoveTowards(const Vec3& current, const Vec3& target, const T maxDistanceDelta);
        static Vec3 ProjectOnPlane(const Vec3& vector, const Vec3& planeNormal);
        static Vec3 Reflect(const Vec3& inDirection, const Vec3& inNormal);
        static Vec3 ClampMagnitude(const Vec3& a, const T MaxLength);
        static Vec3 SlerpUnclamped(const Vec3& a, const Vec3& b, const T t);
        static Vec3 Project(const Vec3& vector, const Vec3& onNormal);
        static Vec3 LerpUnclamped(const Vec3& a, const Vec3& b, const T t);
        static Vec3 Slerp(const Vec3& a, const Vec3& b, const T t);
        static Vec3 Lerp(const Vec3& a, const Vec3& b, const T t);
        static Vec3 Scale(const Vec3& a, const Vec3& b);
        static Vec3 Cross(const Vec3& a, const Vec3& b);
        static Vec3 Min(const Vec3& a, const Vec3& b);
        static Vec3 Max(const Vec3& a, const Vec3& b);

        static T SignedAngle(const Vec3& from, const Vec3& to, const Vec3& axis);
        static T Distance(const Vec3& a, const Vec3& b);
        static T Angle(const Vec3& a, const Vec3& b);
        static T Dot(const Vec3& a, const Vec3& b);

        static void OrthoNormalize(Vec3& normal, Vec3& tangent);
        void Normalize();

        //////// OPERATORS ////////
        Vec3 operator-(const Vec3& other) const;
        Vec3 operator+(const Vec3& other) const;

        Vec3 operator*(const Vec3& other) const;
        Vec3 operator*(T scalar) const;

        Vec3 operator/(const Vec3& other) const;
        Vec3 operator/(T scalar) const;

        bool operator==(const Vec3& other) const;
        bool operator!=(const Vec3& other) const;
    };

    using Vec3f = Vec3<float>;

}

#include "Maths/src/MVec3.inl"