#pragma once

#include <iostream>
#include <string>
#include "MVec3.hpp"

namespace Maths {

	template <typename T = float>
	class Vec2 {
	private:
		T m_x;
		T m_y;

		static_assert(std::is_arithmetic_v<T>);

	public:
		Vec2(T m_x, T m_y);
		Vec2() = default;
		~Vec2() = default;

		//////// GETTERS & SETTERS ////////
		T x() const { return x; }
		T y() const { return y; }

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
		Vec2 Normalized(); 
		T SqrtMagnitude();
		T Magnitude();
		T This(int i);

		//////// PUBLIC METHODS ////////
		bool Equal(Vec2 other); 
		std::string ToString();

		//////// STATIC METHODS ////////
		static Vec2 MoveTowards(Vec2 current, Vec2 target, T maxDistanceDelta);
		static Vec2 LerpUnclamped(Vec2 a, Vec2 b, T t);
		static Vec2 ClampMagnitude(Vec2& a, T MaxLenght);
		static Vec2 Perpendicular(Vec2 inDirection);
		static Vec2 Lerp(Vec2 a, Vec2 b, T t);
		static Vec2 Scale(Vec2& a, Vec2& b);
		static Vec2 Min(Vec2& a, Vec2& b);
		static Vec2 Max(Vec2& a, Vec2& b);

		static T SignedAngle(Vec2 from, Vec2 to);
		static T Distance(Vec2& a, Vec2& b);
		static T Angle(Vec2 a, Vec2 b); 
		static T Dot(Vec2& a, Vec2& b); 

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
}