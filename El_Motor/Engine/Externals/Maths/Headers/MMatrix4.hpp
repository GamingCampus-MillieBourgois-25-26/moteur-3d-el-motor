#pragma once

#include <array>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

#include "MVec3.hpp"
#include "MQuaternion.hpp"

namespace Maths {

    /**
     * @brief 4x4 matrix class template for 3D transformations.
     *
     * Supports translation, rotation, scaling, multiplication, inversion, and other common operations.
     * Stores elements in column-major order.
     * @tparam T Numeric type (float or double)
     */
    template<typename T = float>
    class Mat4 {
    public:
        T det;                            /**< Determinant of the matrix */
        std::array<T, 16> tabMat;        /**< Matrix elements stored in column-major order */
        float deg2rad = 3.14159265f / 180.f; /**< Conversion factor from degrees to radians */

        /// @brief Default constructor (uninitialized matrix)
        Mat4();

        /**
         * @brief Constructor with 16 individual elements (row-major order)
         */
        Mat4(T u, T d, T t, T q, T c, T si, T se, T h,
            T n, T di, T on, T dou, T tre, T qua, T qui, T sei);

        ~Mat4() = default;

        ////////// STATIC METHODS //////////

        /// @brief Returns identity matrix (no transformation)
        static Mat4 Identity();

        /// @brief Returns zero matrix
        static Mat4 Zero();

        ////////// INSTANCE METHODS //////////

        /**
         * @brief Compute rotation matrix from Euler angles in degrees
         * @param angleX Rotation around X axis
         * @param angleY Rotation around Y axis
         * @param angleZ Rotation around Z axis
         * @return Rotation matrix
         */
        Mat4 Rotation4x4(T angleX, T angleY, T angleZ);

        /**
         * @brief Returns transpose of the given matrix
         * @param mat Matrix to transpose
         * @return Transposed matrix as std::array
         */
        std::array<T, 16> Transpose4x4(const Mat4& mat);

        /**
         * @brief Computes inverse of this 4x4 matrix
         * @return Inverted matrix as std::array
         */
        std::array<T, 16> Inverse4x4() const;

        /// @brief Extract approximate scale from matrix
        Maths::Vec3<T> LossyScale4x4() const;

        /// @brief Checks if the matrix is identity
        bool isIdentity4x4() const;

        /// @brief Computes determinant of the matrix
        T Det4x4() const;

        /**
         * @brief Access matrix element at row r, column c
         * @param r Row index (0-3)
         * @param c Column index (0-3)
         * @return Reference to the element
         */
        T& at(int r, int c);

        ////////// TRANSFORMATION METHODS //////////

        /// @brief Multiply a 3D point by this matrix
        Maths::Vec3<T> MultiplyPoint3x4_4x4(const Vec3<T>& vector) const;

        /// @brief Multiply a vector (direction) by this matrix
        Maths::Vec3<T> MultiplyVector4x4(const Maths::Vec3<T>& vector) const;

        /// @brief Multiply a 3D point in homogeneous coordinates by this matrix
        Maths::Vec3<T> MultiplyPoint4x4(const Maths::Vec3<T>& vector) const;

        /// @brief Extract position vector from the matrix
        Maths::Vec3<T> GetPosition4x4() const;

        /// @brief Sets matrix using Translation, Rotation (Euler degrees), and Scale
        Mat4 SetTRS(const Vec3<T>& translation, const Vec3<T>& rotationEulerDeg, const Vec3<T>& scale);

        /// @brief Multiply two 4x4 matrices
        Mat4 MultiplyMat4x4(const Mat4& A, const Mat4& B) const;

        /// @brief Set a specific column of the matrix
        void SetColumn4x4(T columnNumber, T number1, T number2, T number3, T number4);

        /// @brief Set a specific row of the matrix
        void SetRow4x4(T rowNumber, T number1, T number2, T number3, T number4);

        /// @brief Placeholder: get a column of the matrix
        void GetColumn4x4(T column);

        /// @brief Placeholder: get a row of the matrix
        void GetRow4x4(T row);

        /// @brief Check if this matrix is a valid TRS (Translation, Rotation, Scale)
        bool ValidTRS() const;

        /// @brief Convert matrix to string for debugging
        std::string toString4x4() const;

        ////////// STATIC FACTORY METHODS //////////

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

        /// @brief Matrix multiplication operator
        Mat4 operator*(const Mat4& other) const;
    };

    /// @brief Float specialization
    using Mat4f = Mat4<float>;
}

#include "Maths/src/MMatrix4.inl"