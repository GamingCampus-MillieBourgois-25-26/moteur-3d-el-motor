#pragma once

#include <iostream>
#include <array>
#include <sstream>
#include <iomanip>

#include "MVec3.hpp"
#include "MQuaternion.hpp"

namespace Maths {
	template<typename T = float>
	class Mat4 {
	private:
		T det;
		std::array<T, 16> tabMat;
		float deg2rad = 3.14159265f / 180.f;

	public:
		Mat4();
		Mat4(T u, T d, T t, T q, T c, T si, T se, T h, T n, T di, T on, T dou, T tre, T qua, T qui, T sei);
		~Mat4() = default;

		//////// STATIC PORPRETIES ////////
		static Mat4 Identity();
		static Mat4 Zero();

		//////// PORPRETIES ////////
		Mat4 Rotation4x4(T angleX, T angleY, T angleZ);
		std::array<T, 16> Transpose4x4(Mat4 mat);
		std::array<T, 16> Inverse4x4();
		Maths::Vec3<T> LossyScale4x4();
		bool isIdentity4x4();

		T Det4x4() const;
		T& at(int r, int c);


		//////// PUBLIC METHODS ////////
		Maths::Vec3<T> MultiplyPoint3x4_4x4(const Vec3<T>& vector);
		Maths::Vec3<T> MultiplyVector4x4(Maths::Vec3<T>& vector);
		Maths::Vec3<T> MultiplyPoint4x4(Maths::Vec3<T>& vector);
		Maths::Vec3<T> GetPosition4x4() const;

		Mat4 SetTRS(const Vec3<T>& translation, const Vec3<T>& rotationEulerDeg, const Vec3<T>& scale);
		Mat4 MultiplyMat4x4(Mat4& A, Mat4& B);

		void SetColumn4x4(T columnNumber, T number1, T number2, T number3, T number4);
		void SetRow4x4(T rowNumber, T number1, T number2, T number3, T number4);
		void GetColumn4x4(T column);
		void GetRow4x4(T row);
		bool ValidTRS();

		std::string toString4x4();


		/////// STATIC METHODS ////////

		static Mat4 TRS(const Maths::Vec3<T>& position, const Maths::Vec3<T>& rotationEuler, const Maths::Vec3<T>& scale);
		static Mat4 LookAt4x4(Maths::Vec3<T>& from, const Maths::Vec3<T>& to, Maths::Vec3<T>& up);
		static Mat4 Ortho4x4(T left, T right, T bottom, T top, T zNear, T zFar);
		static Mat4 Perspective4x4(T fovY, T aspect, T nearP, T farP);
		static Mat4 TranslateVec4x4(const Maths::Vec3<T>& t);
		static Mat4 Rotate4x4(const Maths::Quat<T>& q);
		static Mat4 ScaleVec4x4(const Maths::Vec3<T>& s);
		static Mat4 Translate4x4(T tx, T ty, T tz);
		static Mat4 Scale4x4(T sx, T sy, T sz);


		//////// OPERATOR ////////
		Mat4 operator*(const Mat4& other) const;
	};
	using Mat4f = Mat4<float>;
}

#include "Maths/src/MMatrix4.inl"