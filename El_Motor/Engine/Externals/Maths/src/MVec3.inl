template <typename T>
Maths::Vec3<T>::Vec3(T m_x, T m_y, T m_z) : m_x(m_x), m_y(m_y), m_z(m_z) {}


//////// STATIC PORPRETIES ////////
template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Down() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Up() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Left() { return Maths::Vec3<T>(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Right() { return Maths::Vec3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Back() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Forward() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::One() { return Maths::Vec3<T>(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Zero() { return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::PositiveInfinity() { return Maths::Vec3<T>(std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity(), std::numeric_limits<T>::infinity()); }

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::NegativeInfinity() { return Maths::Vec3<T>(-std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity()); }


//////// PORPRETIES ////////
template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Normalized() const { // Renvoies une copie normalisée du vecteur
	T mag = Magnitude();
	if (mag != 0.0f)
		return Maths::Vec3<T>(m_x / mag, m_y / mag, m_z / mag);
	else
		return Maths::Vec3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
}

template <typename T>
T Maths::Vec3<T>::Magnitude() const {
	return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); 
} 

template <typename T>
T Maths::Vec3<T>::SqrtMagnitude() const {
	T mag = (*this).Magnitude();  
	return std::pow((mag), static_cast<T>(2)); 
}

template <typename T>
T Maths::Vec3<T>::This(int i) const {
	if (i == 0) return m_x;
	if (i == 1) return m_y;
	if (i == 2) return m_z;
	return static_cast<T>(0);
}


//////// PUBLIC METHODS ////////
template <typename T>
bool Maths::Vec3<T>::Equal(const Vec3<T>& other) const { 
	if (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z) return true;
	else return false;
}

template <typename T>
std::string Maths::Vec3<T>::ToString() const {
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ")";
}


/////// STATIC METHODS ////////
template<typename T>
Maths::Vec3<T> Maths::Vec3<T>::RotateTowards(
	const Vec3<T>& current,
	const Vec3<T>& target,
	const T maxRadiansDelta,
	const T maxMagnitudeDelta)
{
	T currentMag = current.Magnitude();
	T targetMag = target.Magnitude();

	// Si un vecteur est nul, utiliser MoveTowards simple
	if (currentMag == T(0) || targetMag == T(0))
		return MoveTowards(current, target, maxMagnitudeDelta);

	Vec3<T> from = current.Normalized();
	Vec3<T> to = target.Normalized();

	// Angle entre from et to
	T dot = std::clamp(Dot(from, to), T(-1), T(1));
	T angle = std::acos(dot);

	// Ajuste la magnitude en respectant maxMagnitudeDelta
	T diffMag = targetMag - currentMag;
	T deltaMag = (diffMag > maxMagnitudeDelta) ? maxRadiansDelta : (diffMag < -maxMagnitudeDelta ? -maxMagnitudeDelta : diffMag);
	T newMag = currentMag + deltaMag;

	if (angle == T(0))
	{
		// Même direction, ajuster la magnitude seulement
		return to * newMag;
	}

	// Fraction de rotation à appliquer
	T t = (maxRadiansDelta >= angle) ? T(1) : maxRadiansDelta / angle;

	// Rotation sphérique (SLERP)
	Vec3<T> rotated = SlerpUnclamped(from, to, t);

	return rotated * newMag;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::MoveTowards(const Vec3& current, const Vec3& target, const T maxDistanceDelta) {
	Vec3 direction = target - current;
	T distance = direction.Magnitude();
	if (distance == 0 || (maxDistanceDelta >= 0 && distance <= maxDistanceDelta)) { return target; }
	return current + direction / distance * maxDistanceDelta;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::ProjectOnPlane(const Vec3& vector, const Vec3& planeNormal)
{
	T dot1 = Dot(vector, planeNormal);
	T dot2 = Dot(planeNormal, planeNormal);
	if (dot2 == 0) // éviter la division par zéro
		return Maths::Vec3<T>::Zero();
	return vector - planeNormal * (dot1 / dot2);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Reflect(const Vec3& inDirection, const Vec3& inNormal) {
	Vec3<T> n = inNormal.Normalized();
	T dot = Dot(inDirection, n);
	return inDirection - n * dot * static_cast<T>(2);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::ClampMagnitude(const Vec3<T>& a, const T maxLength) {
	T mag = a.Magnitude();
	if (mag > maxLength)
		return a.Normalized() * maxLength;
	return a;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::SlerpUnclamped(const Vec3& a, const Vec3& b, const T t) {
	Vec3<T> aNormal = a.Normalized();
	Vec3<T> bNormal = b.Normalized();
	T dot = std::clamp(Dot(aNormal, bNormal), T(-1), T(1));
	T theta = std::acos(dot);
	return bNormal * (sin(t * theta) / sin(theta)) + aNormal * (sin((T(1) - t) * theta) / sin(theta));
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Project(const Vec3& vector, const Vec3& onNormal) {
	T dot1 = Dot(vector, onNormal);
	T dot2 = Dot(onNormal, onNormal);
	if (dot2 == T(0))
		return Vec3<T>::Zero();
	return onNormal * (dot1 / dot2);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::LerpUnclamped(const Vec3& a, const Vec3& b, const T t) {
	return a + (b - a) * t;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Slerp(const Vec3& a, const Vec3& b, const T t) {
	Vec3<T> aNormal = a.Normalized();
	Vec3<T> bNormal = b.Normalized();

	T dotProd = Dot(aNormal, bNormal);
	dotProd = std::fmax(std::fmin(dotProd, 1.0f), -1.0f); // clamp [-1,1]
	T theta = std::acos(dotProd);
	T sinTheta = std::sin(theta);

	T factorA = std::sin((1 - t) * theta) / sinTheta;
	T factorB = std::sin(t * theta) / sinTheta;

	return Vec3<T>(aNormal * factorA + bNormal * factorB).Normalized();
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Lerp(const Vec3& a, const Vec3& b, const T t) {
	t = std::clamp(t, 0.0f, 1.0f);
	return a + (b - a) * t;
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Scale(const Vec3<T>& a,const Vec3<T>& b) {
	return Vec3(a.m_x * b.m_x, a.m_y * b.m_y, a.m_z * b.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Cross(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3((a.m_y * b.m_z) - (a.m_z * b.m_y), (a.m_z * b.m_x) - (a.m_x * b.m_z), (a.m_x * b.m_y) - (a.m_y * b.m_x));
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Min(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3(std::fmin(a.m_x, b.m_x), std::fmin(a.m_y, b.m_y), fmin(a.m_z, b.m_z));
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::Max(const Vec3<T>& a, const Vec3<T>& b) {
	return Vec3(std::fmax(a.m_x, b.m_x), std::fmax(a.m_y, b.m_y), fmax(a.m_z, b.m_z));
}


template <typename T>
T Maths::Vec3<T>::SignedAngle(const Vec3& from, const Vec3& to, const Vec3& axis) {
	T angle = Angle(from, to);
	Vec3<T> cross = Cross(from, to);
	return (Dot(axis, cross) < 0) ? -angle : angle;
}

template <typename T>
T Maths::Vec3<T>::Distance(const Vec3<T>& a, const Vec3<T>& b) {
	return (a - b).Magnitude();
}

template <typename T>
T Maths::Vec3<T>::Angle(const Vec3& a, const Vec3& b) {
	T dotProduct = Dot(a, b);
	T MagA = a.Magnitude();
	T MagB = b.Magnitude();
	T cosAngle = std::clamp(dotProduct / (MagA * MagB), -1.0f, 1.0f);
	return acos(cosAngle);
}

template <typename T>
T Maths::Vec3<T>::Dot(const Vec3<T>& a, const  Vec3<T>& b) {
	return (a.m_x * b.m_x + a.m_y * b.m_y + a.m_z * b.m_z);
}


template <typename T>
void Maths::Vec3<T>::OrthoNormalize(Vec3<T>& normal, Vec3<T>& tangent) {
	normal.Normalize();
	tangent = tangent - (normal * Dot(normal, tangent));
	tangent.Normalize();
}

template <typename T>
void Maths::Vec3<T>::Normalize() { 
	T mag = Magnitude();
	if (mag != T(0))
	{
		m_x /= mag;
		m_y /= mag;
		m_z /= mag;
	}
}


//////// OPERATOR ////////
template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator-(const Vec3<T>& other) const {
	return Vec3<T>(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator+(const Vec3<T>& other) const {
	return Vec3<T>(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator*(const Vec3<T>& other) const {
	return Vec3<T>(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator*(T scalar) const {
	return Vec3<T>(m_x * scalar, m_y * scalar, m_z * scalar);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator/(const Vec3<T>& other) const {

	T newX = (other.m_x != 0.0f) ? (m_x / other.m_x) : 0.0f;
	T newY = (other.m_y != 0.0f) ? (m_y / other.m_y) : 0.0f;
	T newZ = (other.m_z != 0.0f) ? (m_z / other.m_z) : 0.0f;
	return Vec3<T>(newX, newY, newZ);
}

template <typename T>
Maths::Vec3<T> Maths::Vec3<T>::operator/(T scalar) const {
	if (scalar != 0.0f)
		return Vec3<T>(m_x / scalar, m_y / scalar, m_z / scalar);
	else
		return Vec3<T>(0.0f, 0.0f, 0.0f);
}

template <typename T>
bool Maths::Vec3<T>::operator==(const Vec3<T>& other) const {
	return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

template <typename T>
bool Maths::Vec3<T>::operator!=(const Vec3<T>& other) const {
	return !(*this == other);
}