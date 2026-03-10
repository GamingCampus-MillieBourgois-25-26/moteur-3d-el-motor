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
    return Quat<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
}


//////// PORPRETIES ////////
template<typename T>
Maths::Vec3<T> Maths::Quat<T>::EulerAngles() const {
    T two = T(2);

    T sinp = two * (m_w * m_x + m_y * m_z);
    T cosp = T(1) - two * (m_x * m_x + m_y * m_y);
    T pitch = std::atan2(sinp, cosp);

    T siny = two * (m_w * m_y - m_z * m_x);
    siny = std::clamp(siny, T(-1), T(1));
    T yaw = std::asin(siny);

    T sinr = two * (m_w * m_z + m_x * m_y);
    T cosr = T(1) - two * (m_y * m_y + m_z * m_z);
    T roll = std::atan2(sinr, cosr);

    return Vec3<T>(pitch, yaw, roll);
}  

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Normalized() const {
    Quat<T> q = *this;
    q.Normalize();
    return q;
}

template<typename T>
T Maths::Quat<T>::Magnitude() const {
    return std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
}

template <typename T>
T Maths::Quat<T>::This(int i) const {
    switch (i) {
    case 0: return m_x;
    case 1: return m_y;
    case 2: return m_z;
    case 3: return m_w;
    default: throw std::out_of_range("Quat index must be 0-3");
    }
}


//////// PUBLIC METHODS ////////
template<typename T>
void Maths::Quat<T>::SetLookRotation(const Vec3<T>& forward, const Vec3<T>& up)
{
    Vec3<T> f = forward.Normalized();
    Vec3<T> u = up.Normalized();

    // Right = forward x up
    Vec3<T> r = Vec3<T>::Cross(f, u).Normalized();


    // Recompute orthogonal up
    u = Vec3<T>::Cross(r, f).Normalized();

    // 3x3 rotation matrix
    T m00 = r.m_x, m01 = r.m_y, m02 = r.m_z;
    T m10 = u.m_x, m11 = u.m_y, m12 = u.m_z;
    T m20 = -f.m_x, m21 = -f.m_y, m22 = -f.m_z;

    T trace = m00 + m11 + m22;

    if (trace > static_cast<T>(0))
    {
        T s = std::sqrt(trace + static_cast<T>(1)) * static_cast<T>(2);
        m_w = static_cast<T>(0.25) * s;
        m_x = (m21 - m12) / s;
        m_y = (m02 - m20) / s;
        m_z = (m10 - m01) / s;
    }
    else if (m00 > m11 && m00 > m22)
    {
        T s = std::sqrt(static_cast<T>(1) + m00 - m11 - m22) * static_cast<T>(2);
        m_w = (m21 - m12) / s;
        m_x = static_cast<T>(0.25) * s;
        m_y = (m01 + m10) / s;
        m_z = (m02 + m20) / s;
    }
    else if (m11 > m22)
    {
        T s = std::sqrt(static_cast<T>(1) + m11 - m00 - m22) * static_cast<T>(2);
        m_w = (m02 - m20) / s;
        m_x = (m01 + m10) / s;
        m_y = static_cast<T>(0.25) * s;
        m_z = (m12 + m21) / s;
    }
    else
    {
        T s = std::sqrt(static_cast<T>(1) + m22 - m00 - m11) * static_cast<T>(2);
        m_w = (m10 - m01) / s;
        m_x = (m02 + m20) / s;
        m_y = (m12 + m21) / s;
        m_z = static_cast<T>(0.25) * s;
    }

    Normalize();
}

template<typename T>
void Maths::Quat<T>::ToAngleAxis(T& angle, Vec3<T>& axis)
{
    Quat<T> qNorm = *this;
    qNorm.Normalize();

    angle = static_cast<T>(2) * std::acos(std::clamp(qNorm.m_w, static_cast<T>(-1), static_cast<T>(1)));
    T s = std::sqrt(static_cast<T>(1) - qNorm.m_w * qNorm.m_w);

    if (s < static_cast<T>(kEpsilon)) {
        axis = Vec3<T>(1, 0, 0);
    }
    else {
        axis = Vec3<T>(qNorm.m_x / s, qNorm.m_y / s, qNorm.m_z / s);
    }
}

template<typename T>
void Maths::Quat<T>::setFromToRotation(const Quat<T>& to)
{
    // Convertir les quaternions en vecteurs (x,y,z)
    Vec3<T> fromVec(m_x, m_y, m_z);
    Vec3<T> toVec(to.m_x, to.m_y, to.m_z);

    // Calcul du dot produit
    T dot = std::clamp(fromVec.Dot(toVec), static_cast<T>(-1), static_cast<T>(1));

    // Cas vecteurs quasi identiques
    if (dot > static_cast<T>(0.9999)) {
        *this = Identity();
        return;
    }

    // Cas vecteurs opposés
    if (dot < static_cast<T>(-0.9999)) {
        Vec3<T> orthoAxis;
        if (absValue(fromVec.x()) < absValue(fromVec.z())) {
            orthoAxis = Vec3<T>(0, 0, 1).Cross(fromVec);
        }
        else {
            orthoAxis = Vec3<T>(1, 0, 0).Cross(fromVec);
        }
        orthoAxis.Normalize();
        *this = AngleAxis(static_cast<T>(PI), Quat<T>(orthoAxis.x(), orthoAxis.y(), orthoAxis.z(), 0));
        return;
    }

    // Calcul de l’axe de rotation via cross product
    Vec3<T> rotationAxis = fromVec.Cross(toVec).Normalized();

    // Angle de rotation
    T angle = std::acos(dot);

    // Appliquer la rotation
    *this = AngleAxis(angle, Quat<T>(rotationAxis.x(), rotationAxis.y(), rotationAxis.z(), 0));
}


template<typename T>
bool Maths::Quat<T>::Equals(const Quat<T>& q) const
{
    return (std::abs(m_w - q.m_w) < kEpsilon) &&
        (std::abs(m_x - q.m_x) < kEpsilon) &&
        (std::abs(m_y - q.m_y) < kEpsilon) &&
        (std::abs(m_z - q.m_z) < kEpsilon);
}

template <typename T>
std::string Maths::Quat<T>::ToString() const {
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " + std::to_string(m_w) + ")";
}


//////// STATIC METHODS ////////
template<typename T>
Maths::Quat<T> Maths::Quat<T>::AngleAxis(T angle, const Quat<T>& axis){

    T halfAngle = angle / static_cast<T>(2);
    T s = std::sin(halfAngle);

    Maths::Quat<T> q = Maths::Quat<T>(axis.m_x * s, axis.m_y * s, axis.m_z * s, std::cos(halfAngle));
    q.Normalize();
    return q;
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::SlerpUnclamped(const Quat<T>& b, T t)
{
    T dot = m_w * b.m_w + m_x * b.m_x + m_y * b.m_y + m_z * b.m_z;

    Quat<T> bCopy = b;
    if (dot < static_cast<T>(0)) {
        dot = -dot;
        bCopy = Quat<T>(-b.m_w, -b.m_x, -b.m_y, -b.m_z);
    }

    if (dot > static_cast<T>(0.9995)) {
        T W = m_w + t * (bCopy.m_w - m_w);
        T X = m_x + t * (bCopy.m_x - m_x);
        T Y = m_y + t * (bCopy.m_y - m_y);
        T Z = m_z + t * (bCopy.m_z - m_z);
        Quat<T> result(W, X, Y, Z);
        result.Normalize();
        return result;
    }

    T theta_0 = std::acos(dot);
    T theta = theta_0 * t;

    Quat<T> c(
        bCopy.m_w - m_w * dot,
        bCopy.m_x - m_x * dot,
        bCopy.m_y - m_y * dot,
        bCopy.m_z - m_z * dot
    );
    c.Normalize();

    Quat<T> result(
        m_w * std::cos(theta) + c.m_w * std::sin(theta),
        m_x * std::cos(theta) + c.m_x * std::sin(theta),
        m_y * std::cos(theta) + c.m_y * std::sin(theta),
        m_z * std::cos(theta) + c.m_z * std::sin(theta)
    );

    return result;
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::LerpUnclamped(const Quat<T>& b, T t)
{

    T W = m_w * (static_cast<T>(1) - t) + b.m_w * t;
    T X = m_x * (static_cast<T>(1) - t) + b.m_x * t;
    T Y = m_y * (static_cast<T>(1) - t) + b.m_y * t;
    T Z = m_z * (static_cast<T>(1) - t) + b.m_z * t;

    Quat<T> result(W, X, Y, Z);
    result.Normalize();

    return result;
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::FromEuler(const Vec3<T>& eulerRad) {
    T cx = std::cos(eulerRad.x() / static_cast<T>(2));
    T sx = std::sin(eulerRad.x() / static_cast<T>(2));
    T cy = std::cos(eulerRad.y() / static_cast<T>(2));
    T sy = std::sin(eulerRad.y() / static_cast<T>(2));
    T cz = std::cos(eulerRad.z() / static_cast<T>(2));
    T sz = std::sin(eulerRad.z() / static_cast<T>(2));

    T qw = cy * cz * cx + sy * sz * sx;
    T qx = cy * cz * sx - sy * sz * cx;
    T qy = sy * cz * sx + cy * sz * cx;
    T qz = sy * cz * cx - cy * sz * sx;

    return Quat<T>(qx, qy, qz, qw);
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Lerp(const Quat<T>& a, const Quat<T>& b, T t){
    t = std::clamp(t, static_cast<T>(0), static_cast<T>(1));

    Quat<T> result(
        a.m_x * (static_cast<T>(1) - t) + b.m_x * t,
        a.m_y * (static_cast<T>(1) - t) + b.m_y * t,
        a.m_z * (static_cast<T>(1) - t) + b.m_z * t,
        a.m_w * (static_cast<T>(1) - t) + b.m_w * t
    );
    result.Normalize();
    return result;
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Slerp(const Quat<T>& a, const Quat<T>& b, T t){
    t = std::clamp(t, static_cast<T>(0), static_cast<T>(1));

    T dot = Dot(a, b);
    Quat<T> end = b;

    if (dot < static_cast<T>(0)){
        dot = -dot;
        end = Quat<T>(-b.m_x, -b.m_y, -b.m_z, -b.m_w);
    }

    if (dot > static_cast<T>(0.9995))
        return Lerp(a, end, t);

    T theta0 = std::acos(dot);
    T theta = theta0 * t;

    T sinTheta = std::sin(theta);
    T sinTheta0 = std::sin(theta0);

    T s0 = std::cos(theta) - dot * sinTheta / sinTheta0;
    T s1 = sinTheta / sinTheta0;

    return Quat<T>(
        a.m_x * s0 + end.m_x * s1,
        a.m_y * s0 + end.m_y * s1,
        a.m_z * s0 + end.m_z * s1,
        a.m_w * s0 + end.m_w * s1
    );
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Cross(const Quat<T>& b){
    return Quat<T>(
        m_y * b.m_z - m_z * b.m_y,
        m_z * b.m_x - m_x * b.m_z,
        m_x * b.m_y - m_y * b.m_x,
        static_cast<T>(0) // w = 0 pour un vecteur
    );
}

template<typename T>
Maths::Quat<T> Maths::Quat<T>::Inverse(const Quat<T>& q)
{
    T magSq = Dot(q, q);

    if (magSq <= kEpsilon)
        return Identity();

    return Quat<T>(-q.m_x / magSq, -q.m_y / magSq, -q.m_z / magSq, q.m_w / magSq);
}



template<typename T>
Maths::Vec3<T> Maths::Quat<T>::MulltiplyQuatVec(const Vec3<T>& v, const Maths::Quat<T>& q) {
    Quat<T> vQuat(v.x(), v.y(), v.z(), static_cast<T>(0));
    Quat<T> qInv = Quat<T>::Inverse(q);
    Quat<T> res = q * vQuat * qInv;
    return Vec3<T>(res.m_x, res.m_y, res.m_z);
}


template<typename T>
T Maths::Quat<T>::Angle(const Quat<T>& a, const Quat<T>& b) { // Renvoie l'angle entre deux quaternions en radians
    T d = absValue(Dot(a.Normalized(), b.Normalized()));
    d = minValue(d, static_cast<T>(1));
    return static_cast<T>(2) * std::acos(d);
}

template<typename T>
T Maths::Quat<T>::Dot(const Quat<T>& a, const Quat<T>& b)
{
    return a.m_w * b.m_w + a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z;
}




template<typename T>
void Maths::Quat<T>::LookRotation(const Vec3<T>& forward, const Vec3<T>& up)
{
    Vec3<T> f = forward.Normalized();
    Vec3<T> u = up.Normalized();

    // Right = forward x up
    Vec3<T> r = f.Cross(u).Normalized();

    // Recompute orthogonal up
    u = r.Cross(f);

    // 3x3 rotation matrix
    T m00 = r.m_x, m01 = r.m_y, m02 = r.m_z;
    T m10 = u.m_x, m11 = u.m_y, m12 = u.m_z;
    T m20 = -f.m_x, m21 = -f.m_y, m22 = -f.m_z;

    T trace = m00 + m11 + m22;

    if (trace > static_cast<T>(0))
    {
        T s = std::sqrt(trace + static_cast<T>(1)) * static_cast<T>(2);
        w = static_cast<T>(0.25) * s;
        x = (m21 - m12) / s;
        y = (m02 - m20) / s;
        z = (m10 - m01) / s;
    }
    else if (m00 > m11 && m00 > m22)
    {
        T s = std::sqrt(static_cast<T>(1) + m00 - m11 - m22) * static_cast<T>(2);
        m_w = (m21 - m12) / s;
        m_x = static_cast<T>(0.25) * s;
        m_y = (m01 + m10) / s;
        m_z = (m02 + m20) / s;
    }
    else if (m11 > m22)
    {
        T s = std::sqrt(static_cast<T>(1) + m11 - m00 - m22) * static_cast<T>(2);
        m_w = (m02 - m20) / s;
        m_x = (m01 + m10) / s;
        m_y = static_cast<T>(0.25) * s;
        m_z = (m12 + m21) / s;
    }
    else
    {
        T s = std::sqrt(static_cast<T>(1) + m22 - m00 - m11) * static_cast<T>(2);
        m_w = (m10 - m01) / s;
        m_x = (m02 + m20) / s;
        m_y = (m12 + m21) / s;
        m_z = static_cast<T>(0.25) * s;
    }
    Normalize();
}

template<typename T>
void Maths::Quat<T>::RotateTowards(const Quat<T>& to, T maxDegreesDelta)
{
    Quat<T> from = this->Normalized();
    Quat<T> target = to.Normalized();

    T dot = Dot(from, target);
    if (dot < 0) {
        dot = -dot;
        target = Quat<T>(-target.m_x, -target.m_y, -target.m_z, -target.m_w);
    }

    T angle = T(2) * std::acos(dot < T(-1) ? T(-1) : (dot > T(1) ? T(1) : dot));
    if (angle <= T(0)) return;

    T maxRadiansDelta = maxDegreesDelta * (T(PI) / T(180));

    // Remplace std::min par un ternaire simple
    T t = (maxRadiansDelta >= angle) ? T(1) : maxRadiansDelta / angle;

    *this = SlerpUnclamped(target, t).Normalized();
}

template<typename T>
void Maths::Quat<T>::FromToRotation(const Quat<T>& to)
{
    Quat<T> f = this->Normalized();
    Quat<T> t = to.Normalized();

    Vec3<T> fromVec(f.m_x, f.m_y, f.m_z);
    Vec3<T> toVec(t.m_x, t.m_y, t.m_z);

    T cosTheta = std::clamp(fromVec.Dot(toVec), T(-1), T(1));

    // Vecteurs quasi identiques
    if (cosTheta > static_cast<T>(0.9999)) {
        *this = Identity();
        return;
    }

    // Vecteurs opposés
    if (cosTheta < static_cast<T>(-0.9999)) {
        Vec3<T> orthoAxis = (absValue(fromVec.x()) < absValue(fromVec.z())) ? Vec3<T>(0, 0, 1).Cross(fromVec) : Vec3<T>(1, 0, 0).Cross(fromVec);
        orthoAxis.Normalize();
        *this = AngleAxis(static_cast<T>(PI), Quat<T>(orthoAxis.x(), orthoAxis.y(), orthoAxis.z(), 0));
        return;
    }

    // Axe de rotation normalisé
    Vec3<T> rotationAxis = fromVec.Cross(toVec).Normalized();
    T angle = std::acos(cosTheta);

    *this = AngleAxis(angle, Quat<T>(rotationAxis.x(), rotationAxis.y(), rotationAxis.z(), 0));
}

template<typename T>
void Maths::Quat<T>::Normalize()
{
    T mag = std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);

    if (mag > std::numeric_limits<T>::epsilon()) {
        m_x /= mag;
        m_y /= mag;
        m_z /= mag;
        m_w /= mag;
    }
    else {
        *this = Identity();
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
    return (std::abs(m_x - q.m_x) < kEpsilon) &&
        (std::abs(m_y - q.m_y) < kEpsilon) &&
        (std::abs(m_z - q.m_z) < kEpsilon) &&
        (std::abs(m_w - q.m_w) < kEpsilon);
}