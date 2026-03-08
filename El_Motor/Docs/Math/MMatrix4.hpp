#pragma once

#include <array>       // For std::array
#include <cmath>       // For cos, sin, sqrt, abs
#include <string>      // For std::string and toString
#include <sstream>     // For std::stringstream
#include <iomanip>     // For std::setprecision

#include "MVec3.hpp"
#include "MQuaternion.hpp"

namespace Maths {

    /// <summary>
    /// 4x4 Matrix class template for 3D transformations
    /// Supports translation, rotation, scaling, multiplication, inversion, and more
    /// </summary>
    template<typename T = float>
    class Mat4 {
    public:
        T det;                            // Determinant of the matrix
        std::array<T, 16> tabMat;        // Matrix elements stored in column-major order
        float deg2rad = 3.14159265f / 180.f; // Conversion factor from degrees to radians

        /// <summary>Default constructor (uninitialized matrix)</summary>
        Mat4();

        /// <summary>Constructor with 16 individual elements (row-major order)</summary>
        Mat4(T u, T d, T t, T q, T c, T si, T se, T h, T n, T di, T on, T dou, T tre, T qua, T qui, T sei);

        ~Mat4() = default;

        ////////// STATIC PROPERTIES //////////

        /// <summary>Returns identity matrix (no transformation)</summary>
        static Mat4 Identity();

        /// <summary>Returns zero matrix</summary>
        static Mat4 Zero();

        ////////// INSTANCE PROPERTIES //////////

        /// <summary>Compute rotation matrix from Euler angles (degrees)</summary>
        Mat4 Rotation4x4(T angleX, T angleY, T angleZ);

        /// <summary>Transpose the given 4x4 matrix</summary>
        std::array<T, 16> Transpose4x4(const Mat4& mat);

        /// <summary>Compute inverse of this 4x4 matrix</summary>
        std::array<T, 16> Inverse4x4() const;

        /// <summary>Extract approximate scale from matrix</summary>
        Maths::Vec3<T> LossyScale4x4() const;

        /// <summary>Check if matrix is identity</summary>
        bool isIdentity4x4() const;

        /// <summary>Compute determinant of the 4x4 matrix</summary>
        T Det4x4() const;

        /// <summary>Access matrix element at row r, column c</summary>
        T& at(int r, int c);

        ////////// PUBLIC METHODS //////////

        /// <summary>Multiply a 3D point (Vec3) by 4x4 matrix</summary>
        Maths::Vec3<T> MultiplyPoint3x4_4x4(const Vec3<T>& vector) const;

        /// <summary>Multiply a vector (direction) by 4x4 matrix</summary>
        Maths::Vec3<T> MultiplyVector4x4(const Maths::Vec3<T>& vector) const;

        /// <summary>Multiply a point (Vec3) in homogeneous coordinates by 4x4 matrix</summary>
        Maths::Vec3<T> MultiplyPoint4x4(const Maths::Vec3<T>& vector) const;

        /// <summary>Extract position vector from matrix</summary>
        Maths::Vec3<T> GetPosition4x4() const;

        /// <summary>Set matrix using Translation, Rotation (Euler deg), Scale</summary>
        Mat4 SetTRS(const Vec3<T>& translation, const Vec3<T>& rotationEulerDeg, const Vec3<T>& scale);

        /// <summary>Multiply two 4x4 matrices</summary>
        Mat4 MultiplyMat4x4(const Mat4& A, const Mat4& B) const;

        /// <summary>Set a specific column with 4 values</summary>
        void SetColumn4x4(T columnNumber, T number1, T number2, T number3, T number4);

        /// <summary>Set a specific row with 4 values</summary>
        void SetRow4x4(T rowNumber, T number1, T number2, T number3, T number4);

        /// <summary>Get a column (TODO: fix signature, currently just placeholder)</summary>
        void GetColumn4x4(T column);

        /// <summary>Get a row (TODO: fix signature, currently just placeholder)</summary>
        void GetRow4x4(T row);

        /// <summary>Check if this matrix is a valid TRS (Translation, Rotation, Scale) matrix</summary>
        bool ValidTRS() const;

        /// <summary>Convert matrix to string (for debugging)</summary>
        std::string toString4x4() const;

        ////////// STATIC METHODS //////////

        static Mat4 TRS(const Maths::Vec3<T>& position, const Maths::Vec3<T>& rotationEuler, const Maths::Vec3<T>& scale);
        static Mat4 LookAt4x4(const Maths::Vec3<T>& from, const Maths::Vec3<T>& to, const Maths::Vec3<T>& up);
        static Mat4 Ortho4x4(T left, T right, T bottom, T top, T zNear, T zFar);
        static Mat4 Perspective4x4(T fovY, T aspect, T nearP, T farP);
        static Mat4 TranslateVec4x4(const Maths::Vec3<T>& t);
        static Mat4 Rotate4x4(const Maths::Quat<T>& q);
        static Mat4 ScaleVec4x4(const Maths::Vec3<T>& s);
        static Mat4 Translate4x4(T tx, T ty, T tz);
        static Mat4 Scale4x4(T sx, T sy, T sz);

        ////////// OPERATORS //////////
        /// <summary>Matrix multiplication operator</summary>
        Mat4 operator*(const Mat4& other) const;
    };

    /// <summary>Float specialization</summary>
    using Mat4f = Mat4<float>;
}

#include "Maths/src/MMatrix4.inl"