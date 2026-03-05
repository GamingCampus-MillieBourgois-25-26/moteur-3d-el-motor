#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include "MVec3.hpp"

namespace Maths {

	template <typename T = float>
	class Vec2 {
	public:
		T m_x;
		T m_y;

		static_assert(std::is_arithmetic_v<T>);

		Vec2(T m_x, T m_y);
		Vec2() = default;
		~Vec2() = default;

		//////// GETTERS & SETTERS ////////
		T x() const { return m_x; }
		T y() const { return m_y; }

		void SetX(T newX) { m_x = newX; }
		void SetY(T newY) { m_y = newY; }
		void Set(T newX, T newY) { m_x = newX, m_y = newY; }

		//////// STATIC PORPRETIES ////////
		static Vec2 Down();
		static Vec2 Up();
		static Vec2 Left();
		static Vec2 Right();
		static Vec2 One();
		static Vec2 Zero();
		static Vec2 PositiveInfinity();
		static Vec2 NegativeInfinity();

		//////// PORPRETIES ////////
		Vec2 Normalized() const;
		T SqrtMagnitude() const;
		T Magnitude() const;
		T This(int i) const;

		//////// PUBLIC METHODS ////////
		bool Equal(const Vec2& other) const; 
		std::string ToString() const;

		//////// STATIC METHODS ////////
		static Vec2 MoveTowards(const Vec2& current, const Vec2& target, T maxDistanceDelta);
		static Vec2 LerpUnclamped(const Vec2& a, const Vec2& b, T t);
		static Vec2 ClampMagnitude(const Vec2& a, T maxLength);
		static Vec2 Perpendicular(const Vec2& inDirection);
		static Vec2 Lerp(const Vec2& a, const Vec2& b, T t);
		static Vec2 Scale(const Vec2& a, const Vec2& b);
		static Vec2 Min(const Vec2& a, const Vec2& b);
		static Vec2 Max(const Vec2& a, const Vec2& b);

		static T SignedAngle(const Vec2& from, const Vec2& to);
		static T Distance(const Vec2& a, const Vec2& b);
		static T Angle(const Vec2& a, const Vec2& b);
		static T Dot(const Vec2& a, const Vec2& b);

		void Normalize();

		//////// CONVERSIONS ////////
		Vec2<T> ToVec2() const;
		Vec3<T> ToVec3() const;

		////////OPERATOR ////////
		Vec2 operator-(const Vec2& other) const;
		Vec2 operator+(const Vec2& other) const;

		Vec2 operator*(const Vec2& other) const;
		Vec2 operator*(T scalar) const;

		Vec2 operator/(const Vec2& other) const;
		Vec2 operator/(T scalar) const;

		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;
	};
	using Vec2f = Vec2<float>;
}

#include "Maths/src/MVec2.inl"