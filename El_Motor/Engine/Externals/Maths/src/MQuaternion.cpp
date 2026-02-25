#include "MQuaternion.hpp"


template<typename T>
static T clampValue(T v, T minVal, T maxVal) { // clamp v entre minVal et maxVal
    return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
}

template<typename T>
static T minValue(T a, T b) { // renvoie la plus petite des deux valeurs
    return (a < b) ? a : b;
}

template<typename T>
static T absValue(T v) { // renvoie la valeur absolue
    return (v < static_cast<T>(0)) ? -v : v;
}


template<typename T>
Maths::Quat<T>::Quat(T m_x, T m_y, T m_z, T m_w) : m_x(m_x), m_y(m_y), m_z(m_z), m_w(m_w) {}


//////// STATIC PORPRETIES ////////
template<typename T>
Maths::Quat<T> Maths::Quat<T>::Identity() { // Renvoie le Quat identité
    return Quat<T>(0, 0, 0, 1);
}


//////// PORPRETIES ////////
template<typename T>
void Maths::Quat<T>::EulerAngles() {
    const T two = static_cast<T>(2);

    T pitch = std::atan2(two * (m_w * m_x + m_y * m_z), 1 - two * (m_x * m_x + m_y * m_y));
    T yaw = std::asin(std::clamp(two * (m_w * m_y - m_z * m_x), static_cast<T>(-1), static_cast<T>(1)));
    T roll = std::atan2(two * (m_w * m_z + m_x * m_y), 1 - two * (m_y * m_y + m_z * m_z));

	return Vec3<T>(pitch, yaw, roll);
}  

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Normalized() {
    T len = this->Magnitude();
    if (len < kEpsilon) return Quat<T>::Identity();
    return Quat<T>(m_x / len, m_y / len, m_z / len, m_w / len);
}

template<typename T>
T Maths::Quat<T>::Magnitude() {
    return std::sqrt(w() * w() + x() * x() + y() * y() + z() * z());
}

template <typename T>
T Maths::Quat<T>::This(int i) {
    if (i == 0) return m_x;
    else if (i == 1) return m_y;
    else if (i == 2) return m_z;
    else if (i == 3) return m_w;
}


//////// PUBLIC METHODS ////////
template<typename T>
void Maths::Quat<T>::SetLookRotation(const Quat<T>& forward, const Quat<T>& up)
{

    Quat<T> f = forward;
    f.Normalize();

    Quat<T> u = up;
    u.Normalize();

    Quat<T> r(
        f.y() * u.z() - f.z() * u.y(),
        f.z() * u.x() - f.x() * u.z(),
        f.x() * u.y() - f.y() * u.x(),
        0
    );
    r.Normalize();

    u = Quat<T>(
        r.y() * f.z() - r.z() * f.y(),
        r.z() * f.x() - r.x() * f.z(),
        r.x() * f.y() - r.y() * f.x(),
        0
    );

    T m00 = r.x(), m01 = r.y(), m02 = r.z();
    T m10 = u.x(), m11 = u.y(), m12 = u.z();
    T m20 = -f.x(), m21 = -f.y(), m22 = -f.z();

    T trace = m00 + m11 + m22;
    if (trace > 0) {
        T s = std::sqrt(trace + 1.0) * 2;
        SetW(0.25 * s);
        SetX((m21 - m12) / s);
        SetY((m02 - m20) / s);
        SetZ((m10 - m01) / s);
    }
    else if ((m00 > m11) && (m00 > m22)) {
        T s = std::sqrt(1.0 + m00 - m11 - m22) * 2;
        SetW((m21 - m12) / s);
        SetX(0.25 * s);
        SetY((m01 + m10) / s);
        SetZ((m02 + m20) / s);
    }
    else if (m11 > m22) {
        T s = std::sqrt(1.0 + m11 - m00 - m22) * 2;
        SetW((m02 - m20) / s);
        SetX((m01 + m10) / s);
        SetY(0.25 * s);
        SetZ((m12 + m21) / s);
    }
    else {
        T s = std::sqrt(1.0 + m22 - m00 - m11) * 2;
        SetW((m10 - m01) / s);
        SetX((m02 + m20) / s);
        SetY((m12 + m21) / s);
        SetZ(0.25 * s);
    }

    Normalize();
}

template<typename T>
void Maths::Quat<T>::ToAngleAxis(T& angle, Quat<T>& axis)
{
    Quat<T> qNorm = *this;
    qNorm.Normalize();

    angle = 2 * std::acos(std::clamp(qNorm.w(), static_cast<T>(-1), static_cast<T>(1)));
    T s = std::sqrt(1 - qNorm.w() * qNorm.w());

    if (s < 1e-6) {
        axis = Quat<T>(0, 1, 0, 0);
    }
    else {
        axis = Quat<T>(0, qNorm.x() / s, qNorm.y() / s, qNorm.z() / s);
    }
}

template<typename T>
void Maths::Quat<T>::setFromToRotation(const Quat<T>& to)
{

    Quat<T> fromVec(0, x(), y(), z());
    Quat<T> toVec(0, to.x(), to.y(), to.z());

    T dot = fromVec.x() * toVec.x() + fromVec.y() * toVec.y() + fromVec.z() * toVec.z();
    dot = std::clamp(dot, static_cast<T>(-1.0), static_cast<T>(1.0));

    if (dot > static_cast<T>(0.9999)) {
        SetW(1); SetX(0); SetY(0); SetZ(0);
        return;
    }

    if (dot < static_cast<T>(-0.9999)) {
        Quat<T> orthoAxis;
        if (std::abs(fromVec.x()) < std::abs(fromVec.z())) {
            orthoAxis = Quat<T>(0, 0, -fromVec.z(), fromVec.y());
        }
        else {
            orthoAxis = Quat<T>(0, -fromVec.y(), fromVec.x(), 0);
        }
        orthoAxis.Normalize();
        AngleAxis(static_cast<T>(3.14159265), orthoAxis);
        return;
    }


    Quat<T> rotationAxis(0,
        fromVec.y() * toVec.z() - fromVec.z() * toVec.y(),
        fromVec.z() * toVec.x() - fromVec.x() * toVec.z(),
        fromVec.x() * toVec.y() - fromVec.y() * toVec.x());

    rotationAxis.Normalize();

    T angle = std::acos(dot);
    AngleAxis(angle, rotationAxis);
}


template<typename T>
bool Maths::Quat<T>::Equals(const Quat<T>& q)
{
    return (std::abs(w() - q.w()) < kEpsilon) &&
        (std::abs(x() - q.x()) < kEpsilon) &&
        (std::abs(y() - q.y()) < kEpsilon) &&
        (std::abs(z() - q.z()) < kEpsilon);
}

template <typename T>
std::string Maths::Quat<T>::ToString() {
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " + std::to_string(m_w) + ")";
}


//////// STATIC METHODS ////////
template<typename T>
static Maths::Quat<T> Maths::Quat<T>::AngleAxis(T angle, const Quat<T>& axis){

    T halfAngle = angle / 2;
    T s = std::sin(halfAngle);

    SetW(std::cos(halfAngle));
    SetX(axis.x() * s);
    SetY(axis.y() * s);
    SetZ(axis.z() * s);

    Normalize();
}

template<typename T>
static Maths::Quat<T> Maths::Quat<T>::SlerpUnclamped(const Quat<T>& b, T t)
{
    T dot = w() * b.w() + x() * b.x() + y() * b.y() + z() * b.z();

    Quat<T> bCopy = b;
    if (dot < 0.0f) {
        dot = -dot;
        bCopy = Quat<T>(-b.w(), -b.x(), -b.y(), -b.z());
    }

    if (dot > 0.9995f) {
        T W = w() + t * (bCopy.w() - w());
        T X = x() + t * (bCopy.x() - x());
        T Y = y() + t * (bCopy.y() - y());
        T Z = z() + t * (bCopy.z() - z());
        Quat<T> result(W, X, Y, Z);
        result.Normalize();
        return result;
    }

    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;

    Quat<T> c(
        bCopy.w() - w() * dot,
        bCopy.x() - x() * dot,
        bCopy.y() - y() * dot,
        bCopy.z() - z() * dot
    );
    c.Normalize();

    Quat<T> result(
        w() * std::cos(theta) + c.w() * std::sin(theta),
        x() * std::cos(theta) + c.x() * std::sin(theta),
        y() * std::cos(theta) + c.y() * std::sin(theta),
        z() * std::cos(theta) + c.z() * std::sin(theta)
    );

    return result;
}

template<typename T>
static Maths::Quat<T> Maths::Quat<T>::LerpUnclamped(const Quat<T>& b, T t)
{

    T W = w() * (1 - t) + b.w() * t;
    T X = x() * (1 - t) + b.x() * t;
    T Y = y() * (1 - t) + b.y() * t;
    T Z = z() * (1 - t) + b.z() * t;

    Quat<T> result(W, X, Y, Z);
    result.Normalize();

    return result;
}

template<typename T>
static Maths::Quat<T> Maths::Quat<T>::FromEuler(const Vec3<T>& eulerRad) {
    T cx = std::cos(eulerRad.m_x / 2);
    T sx = std::sin(eulerRad.m_x / 2);
    T cy = std::cos(eulerRad.m_y / 2);
    T sy = std::sin(eulerRad.m_y / 2);
    T cz = std::cos(eulerRad.m_z / 2);
    T sz = std::sin(eulerRad.m_z / 2);

    T qw = cy * cz * cx + sy * sz * sx;
    T qx = cy * cz * sx - sy * sz * cx;
    T qy = sy * cz * sx + cy * sz * cx;
    T qz = sy * cz * cx - cy * sz * sx;

    return Quat<T>(qx, qy, qz, qw);
}

template<typename T>
static Maths::Quat<T> Maths::Quat<T>::Lerp(const Quat<T>& b, T t)
{
    if (t < 0) t = 0;
    if (t > 1) t = 1;

    T W = w() * (1 - t) + b.w() * t;
    T X = x() * (1 - t) + b.x() * t;
    T Y = y() * (1 - t) + b.y() * t;
    T Z = z() * (1 - t) + b.z() * t;

    Quat<T> result(W, X, Y, Z);
    result.Normalize();
    return result;
}

template<typename T>
static Maths::Quat<T> Maths::Quat<T>::Slerp(const Quat<T>& b, T t)
{

    T dot = w() * b.w() + x() * b.x() + y() * b.y() + z() * b.z();


    Quat<T> bCopy = b;
    if (dot < 0.0f) {
        dot = -dot;
        bCopy = Quat<T>(-b.w(), -b.x(), -b.y(), -b.z());
    }


    if (dot > 0.9995f) {
        T W = w() + t * (bCopy.w() - w());
        T X = x() + t * (bCopy.x() - x());
        T Y = y() + t * (bCopy.y() - y());
        T Z = z() + t * (bCopy.z() - z());
        Quat<T> result(W, X, Y, Z);
        result.Normalize();
        return result;
    }


    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;


    Quat<T> c(bCopy.w() - w() * dot,
        bCopy.x() - x() * dot,
        bCopy.y() - y() * dot,
        bCopy.z() - z() * dot);
    c.Normalize();

    Quat<T> result(
        w() * std::cos(theta) + c.w() * std::sin(theta),
        x() * std::cos(theta) + c.x() * std::sin(theta),
        y() * std::cos(theta) + c.y() * std::sin(theta),
        z() * std::cos(theta) + c.z() * std::sin(theta)
    );

    return result;
}

template<typename T>
static Maths::Quat<T> Maths::Quat<T>::Cross(const Quat<T>& b) {
    // Produit vectoriel seulement sur x,y,z (ignore w)
    return Maths::Quat<T>(
        0,
        y() * b.z() - z() * b.y(),
        z() * b.x() - x() * b.z(),
        x() * b.y() - y() * b.x()
    );
}

template<typename T>
static void Maths::Quat<T>::Inverse()
{
    T normSq = w() * w() + x() * x() + y() * y() + z() * z();
    if (normSq == 0) {
        throw std::runtime_error("Impossible d'inverser un Quat nul");
    }

    SetW(w() / normSq);
    SetX(-x() / normSq);
    SetY(-y() / normSq);
    SetZ(-z() / normSq);
}



template<typename T>
static T Maths::Quat<T>::Angle(const Quat<T>& a, const Quat<T>& b) { // Renvoie l'angle entre deux quaternions en radians
    T d = absValue(Dot(a.Normalized(), b.Normalized()));
    d = minValue(d, static_cast<T>(1));
    return static_cast<T>(2) * std::acos(d);
}

template<typename T>
static T Maths::Quat<T>::Dot(const Quat& a, const Quat<T>& b)
{
    return a.m_w * b.m_w + a.m_x * b.x + a.m_y * b.m_y + a.m_z * b.m_z;
}




template<typename T>
static void Maths::Quat<T>::LookRotation(const Quat<T>& forward, const Quat<T>& up)
{

    Quat<T> f = forward;
    f.Normalize();

    Quat<T> u = up;
    u.Normalize();

    // Calcul du vecteur droit (right)
    Quat<T> r(
        f.y() * u.z() - f.z() * u.y(),
        f.z() * u.x() - f.x() * u.z(),
        f.x() * u.y() - f.y() * u.x(),
        0
    );
    r.Normalize();

    // Recalcul du vecteur up
    u = Quat<T>(
        r.y() * f.z() - r.z() * f.y(),
        r.z() * f.x() - r.x() * f.z(),
        r.x() * f.y() - r.y() * f.x(),
        0
    );

    // Matrice 3x3
    T m00 = r.x(), m01 = r.y(), m02 = r.z();
    T m10 = u.x(), m11 = u.y(), m12 = u.z();
    T m20 = -f.x(), m21 = -f.y(), m22 = -f.z();

    T trace = m00 + m11 + m22;
    if (trace > 0) {
        T s = std::sqrt(trace + 1.0) * 2;
        SetW(0.25 * s);
        SetX((m21 - m12) / s);
        SetY((m02 - m20) / s);
        SetZ((m10 - m01) / s);
    }
    else if ((m00 > m11) && (m00 > m22)) {
        T s = std::sqrt(1.0 + m00 - m11 - m22) * 2;
        SetW((m21 - m12) / s);
        SetX(0.25 * s);
        SetY((m01 + m10) / s);
        SetZ((m02 + m20) / s);
    }
    else if (m11 > m22) {
        T s = std::sqrt(1.0 + m11 - m00 - m22) * 2;
        SetW((m02 - m20) / s);
        SetX((m01 + m10) / s);
        SetY(0.25 * s);
        SetZ((m12 + m21) / s);
    }
    else {
        T s = std::sqrt(1.0 + m22 - m00 - m11) * 2;
        SetW((m10 - m01) / s);
        SetX((m02 + m20) / s);
        SetY((m12 + m21) / s);
        SetZ(0.25 * s);
    }

    Normalize();
}

template<typename T>
static void Maths::Quat<T>::RotateTowards(const Quat<T>& to, T maxDegreesDelta)
{

    T dot = w() * to.w() + x() * to.x() + y() * to.y() + z() * to.z();

    T angle = std::acos(std::min(std::abs(dot), static_cast<T>(1.0))) * 2.0 * (180.0 / 3.14159265);

    if (angle <= maxDegreesDelta)
    {
        SetW(to.w());
        SetX(to.x());
        SetY(to.y());
        SetZ(to.z());
        return;
    }

    T t = maxDegreesDelta / angle;

    Quat<T> result;
    T theta = std::acos(dot);
    T sinTheta = std::sin(theta);

    if (sinTheta > 1e-6) {
        T ratioA = std::sin((1 - t) * theta) / sinTheta;
        T ratioB = std::sin(t * theta) / sinTheta;

        result.SetW(w() * ratioA + to.w() * ratioB);
        result.SetX(x() * ratioA + to.x() * ratioB);
        result.SetY(y() * ratioA + to.y() * ratioB);
        result.SetZ(z() * ratioA + to.z() * ratioB);
    }
    else {
        result.SetW(w() * (1 - t) + to.w() * t);
        result.SetX(x() * (1 - t) + to.x() * t);
        result.SetY(y() * (1 - t) + to.y() * t);
        result.SetZ(z() * (1 - t) + to.z() * t);
    }

    SetW(result.w());
    SetX(result.x());
    SetY(result.y());
    SetZ(result.z());

    Normalize();
}

template<typename T>
static void Maths::Quat<T>::FromToRotation(const Quat<T>& to)
{
    Quat<T> f = this->normalized();
    Quat<T> t = to.normalized();

    T cosTheta = f.Dot(t);
    Quat<T> rotationAxis;

    if (cosTheta >= 1.0 - static_cast<T>(kEpsilon)) {
        SetW(1); SetX(0); SetY(0); SetZ(0);
        return;
    }

    if (cosTheta <= -1.0 + static_cast<T>(kEpsilon)) {
        rotationAxis = Quat<T>(0, 1, 0, 0).Cross(f);
        if (rotationAxis.Magnitude() < static_cast<T>(1e-6))
            rotationAxis = Quat<T>(1, 0, 0, 0).Cross(f);
        rotationAxis.Normalize();
        Angle(static_cast<T>(PI), rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
        return;
    }
    rotationAxis = f.Cross(t);
    T angle = std::acos(std::clamp(cosTheta, static_cast<T>(-1), static_cast<T>(1)));
    rotationAxis.Normalize();
    Angle(angle, rotationAxis.x(), rotationAxis.y(), rotationAxis.z());
}

template<typename T>
static void Maths::Quat<T>::Normalize()
{
    T mag = std::sqrt(w() * w() + x() * x() + y() * y() + z() * z());

    if (mag > std::numeric_limits<T>::epsilon()) {
        SetW(GetW() / mag);
        SetX(x() / mag);
        SetY(y() / mag);
        SetZ(z() / mag);
    }
    else {
        SetW(T(1));
        SetX(T(0));
        SetY(T(0));
        SetZ(T(0));
    }
}


//////// OPERATOR ////////
template<typename T>
Maths::Quat<T> Maths::Quat<T>::operator*(const Quat<T>& rhs) const {
    return Quat<T>(
        m_w * rhs.m_x + m_x * rhs.m_w + m_y * rhs.m_z - m_z * rhs.m_y,
        m_w * rhs.m_y - m_x * rhs.m_z + m_y * rhs.m_w + m_z * rhs.m_x,
        m_w * rhs.m_z + m_x * rhs.m_y - m_y * rhs.m_x + m_z * rhs.m_w,
        m_w * rhs.m_w - m_x * rhs.m_x - m_y * rhs.m_y - m_z * rhs.m_z
    );
}

template<typename T>
bool Maths::Quat<T>::operator==(const Quat<T>& q) const {
    return m_x == q.m_x && m_y == q.m_y && m_z == q.m_z && m_w == q.m_w;
}