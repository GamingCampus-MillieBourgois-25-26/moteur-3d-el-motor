#pragma once

#include <iostream>
#include <string>

namespace Maths {

	template <typename T = float>
	class Vec3 {
	private:
		T m_x;
		T m_y;
		T m_z;

		static_assert(std::is_arithmetic_v<T>);

	public:
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
		static Vec3 Foward();
		static Vec3 One();
		static Vec3 Zero();
		static Vec3 PositiveInfinity();
		static Vec3 NegativeInfinity();

		//////// PORPRETIES ////////
		Vec3 Normalized();
		T SqrtMagnitude();
		T Magnitude();
		T This(int i);

	};
}