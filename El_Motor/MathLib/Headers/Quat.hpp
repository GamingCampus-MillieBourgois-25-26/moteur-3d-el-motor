#pragma once 

#include <iostream>
#include "Vec3.hpp"

namespace Math {

    template<typename T = float>
    class Quat {
    private:
        T m_x;
        T m_y;
        T m_z;
        T m_w;

    public:
        Quat();
        Quat(T m_x, T m_y, T m_z, T m_w);

		////// STATIC PROPRETIE //////
        static Quat Identity();

        ////// PROPRETIE //////
        Quat Normalized() const;
        T This(int i);
        T x() const;
        T y() const;
        T z() const;
        T w() const;
        T Length();


        ////// PUBLIC METHODS //////
        void ToAxisAngle(Vec3<T>& outAxis, T& outAngle);
        Quat Conjugate();

        ////// STATIC METHODS //////
        static Quat Slerp(const Quat& a, const Quat& b, T t);
        static Quat AngleAxis(T angle, const Vec3<T>& axis);
        static Quat Lerp(const Quat& a, const Quat& b, T t);
        static Quat FromAxisAngle(Vec3<T>& axis, T angle);
        static Quat Inverse();

        static T Angle(const Quat& a, const Quat& b);
        static T Dot(const Quat& a, const Quat& b);
        static T Clamp(T v, T minVal, T maxVal);
        static T Min(T a, T b);
        static T Abs(T v);

        void Normalize();

        ////// OPERATORS //////
        Vec3<T> operator*(const Vec3<T>& v) const;
        Quat operator*(const Quat& rhs) const;
        bool operator==(const Quat& q) const;


        static constexpr T PI = static_cast<T>(3.14159265358979323846);
        static constexpr T kEpsilon = static_cast<T>(1e-6);

        template<typename TypeToCastTo>
        explicit operator TypeToCastTo()

    };

}

// #include "Quat.inl"