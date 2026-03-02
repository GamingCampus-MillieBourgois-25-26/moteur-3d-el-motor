#pragma once

#include <iostream>
#include <algorithm>
#include <string>

namespace Maths {

	template <typename T = float>
	class Vec3 {
	public:
		T m_x;
		T m_y;
		T m_z;

		static_assert(std::is_arithmetic_v<T>);

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
		void Set(T newX, T newY, T newZ) { m_x = newX, m_y = newY, m_z = newZ; }

		//////// STATIC PORPRETIES ////////
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

		//////// PORPRETIES ////////
		Vec3 Normalized();
		T SqrtMagnitude();
		T Magnitude();
		T This(int i);

		//////// PUBLIC METHODS ////////
		bool Equal(Vec3& other);
		std::string ToString();

		/////// STATIC METHODS ////////
		static Vec3 RotateTowards(Vec3 current, Vec3 target, T maxRadiansDelta, T maxMagnitudeDelta);
		static Vec3 MoveTowards(Vec3 current, Vec3 target, T maxDistanceDelta);
		static Vec3 ProjectOnPlane(Vec3 vector, Vec3 planeNormal);
		static Vec3 Reflect(Vec3 inDirection, Vec3 inNormal);
		static Vec3 ClampMagnitude(Vec3& a, T MaxLenght);
		static Vec3 SlerpUnclamped(Vec3 a, Vec3 b, T t);
		static Vec3 Project(Vec3 vector, Vec3 onNormal);
		static Vec3 LerpUnclamped(Vec3 a, Vec3 b, T t);
		static Vec3 Slerp(Vec3 a, Vec3 b, T t);
		static Vec3 Lerp(Vec3 a, Vec3 b, T t);
		static Vec3 Scale(Vec3& a, Vec3& b);
		static Vec3 Cross(Vec3& a, Vec3& b);
		static Vec3 Min(Vec3& a, Vec3& b);
		static Vec3 Max(Vec3& a, Vec3& b);

		static T SignedAngle(Vec3 from, Vec3 to, Vec3 axis);
		static T Distance(Vec3& a, Vec3& b);
		static T Angle(Vec3 a, Vec3 b); 
		static T Dot(Vec3& a, Vec3& b); 

		static void OrthoNormalize(Vec3& normal, Vec3& tangent);
		void Normalize();

		//////// OPERATOR ////////
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