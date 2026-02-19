#pragma once

#include <iostream>
#include"Vec3.hpp"

namespace Math {

	template<typename T = float>
	class Vec2 {
	private:
		T m_x;
		T m_y;

	public:
		Vec2() = default;
		Vec2(T m_x, T m_y);

		/////// STATIC PORPRETIES ///////
		static Vec2 Down();
		static Vec2 Up();
		static Vec2 Left();
		static Vec2 Right();

		static Vec2 One();
		static Vec2 Zero();
		static Vec2 PositiveInfinity();
		static Vec2 NegativeInfinity();


		/////// PORPRETIES ///////
		Vec2 Normalized();
		T SqrtMagnitude();
		T Magnitude();
		T This(int i);
		T x() const;
		T y() const;


		/////// PUBLIC METHODS ///////
		bool Equal(Vec2 other);
		void Set(T newX, T newY);
		std::string ToString();


		/////// STATIC METHODS ///////
		static Vec2 MoveTowards(Vec2 current, Vec2 target, T maxDistanceDelta);
		static Vec2 ClampMagnitude(Vec2& a, T MaxLenght);
		static Vec2 LerpUnclamped(Vec2 a, Vec2 b, T t);
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
		

		/////// CONVERSIONS ///////
		static Vec2<T> ToVec2(Vec3<T>& vec);
		Vec3<T> ToVec3() const;

		/////// OPERATORS ///////
		Vec2 operator+(const Vec2& other) const;
		Vec2 operator-(const Vec2& other) const;

		Vec2 operator*(const Vec2& other) const;
		Vec2 operator*(T scalar) const;

		Vec2 operator/(const Vec2& other) const;
		Vec2 operator/(T scalar) const;

		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;

	};
}
