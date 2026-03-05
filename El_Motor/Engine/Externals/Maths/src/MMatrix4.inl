#include "Maths/Headers/MMatrix4.hpp"

//////////////////// CONSTRUCTEURS ////////////////////
template<typename T>
Maths::Mat4<T>::Mat4() {
    tabMat.fill(static_cast<T>(0));
}

template<typename T>
Maths::Mat4<T>::Mat4(T u, T d, T t, T q, T c, T si, T se, T h, T n, T di, T on, T dou, T tre, T qua, T qui, T sei)
{
    this->tabMat = {
        u, d, t, q,
        c, si, se, h,
        n, di, on, dou,
        tre, qua, qui, sei
    };
}

//////////////////// STATIC PROPERTIES ////////////////////
template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Identity()
{
    Mat4<T> matrix;
    matrix.tabMat = {
        static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
        static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)
    };
    return matrix;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Zero()
{
    Mat4<T> matrix;
    matrix.tabMat.fill(static_cast<T>(0));
    return matrix;
}

//////////////////// PROPERTIES ////////////////////
template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Rotation4x4(T angleX, T angleY, T angleZ)
{
    T radX = angleX * deg2rad;
    T radY = angleY * deg2rad;
    T radZ = angleZ * deg2rad;

    Mat4<T> rotX = Identity();
    Mat4<T> rotY = Identity();
    Mat4<T> rotZ = Identity();

    // Rotation autour de l'axe X
    rotX.at(1, 1) = std::cos(radX);
    rotX.at(1, 2) = -std::sin(radX);
    rotX.at(2, 1) = std::sin(radX);
    rotX.at(2, 2) = std::cos(radX);

    // Rotation autour de l'axe Y
    rotY.at(0, 0) = std::cos(radY);
    rotY.at(0, 2) = std::sin(radY);
    rotY.at(2, 0) = -std::sin(radY);
    rotY.at(2, 2) = std::cos(radY);

    // Rotation autour de l'axe Z
    rotZ.at(0, 0) = std::cos(radZ);
    rotZ.at(0, 1) = -std::sin(radZ);
    rotZ.at(1, 0) = std::sin(radZ);
    rotZ.at(1, 1) = std::cos(radZ);

    // multiplication des matrices de rotation
    return rotZ * rotY * rotX;
}

template<typename T>
std::array<T, 16> Maths::Mat4<T>::Transpose4x4(const Mat4<T>& mat)
{
    std::array<T, 16> transpo;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            transpo[i * 4 + j] = mat.tabMat[j * 4 + i];
        }
    }
    this->tabMat = transpo;
    return this->tabMat;
}

template<typename T>
std::array<T, 16> Maths::Mat4<T>::Inverse4x4() const
{
    const auto& m = this->tabMat;
    T det = this->Det4x4();
    if (std::abs(det) < static_cast<T>(1e-6)) {
        // matrice non inversible
        return std::array<T, 16>{};
    }

    std::array<T, 16> cof;

    cof[0] = m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13]);
    cof[1] = -(m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12]));
    cof[2] = m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9] * m[12]);
    cof[3] = -(m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9] * m[12]));

    cof[4] = -(m[1] * (m[10] * m[15] - m[11] * m[14]) - m[2] * (m[9] * m[15] - m[11] * m[13]) + m[3] * (m[9] * m[14] - m[10] * m[13]));
    cof[5] = m[0] * (m[10] * m[15] - m[11] * m[14]) - m[2] * (m[8] * m[15] - m[11] * m[12]) + m[3] * (m[8] * m[14] - m[10] * m[12]);
    cof[6] = -(m[0] * (m[9] * m[15] - m[11] * m[13]) - m[1] * (m[8] * m[15] - m[11] * m[12]) + m[3] * (m[8] * m[13] - m[9] * m[12]));
    cof[7] = m[0] * (m[9] * m[14] - m[10] * m[13]) - m[1] * (m[8] * m[14] - m[10] * m[12]) + m[2] * (m[8] * m[13] - m[9] * m[12]);

    cof[8] = m[1] * (m[6] * m[15] - m[7] * m[14]) - m[2] * (m[5] * m[15] - m[7] * m[13]) + m[3] * (m[5] * m[14] - m[6] * m[13]);
    cof[9] = -(m[0] * (m[6] * m[15] - m[7] * m[14]) - m[2] * (m[4] * m[15] - m[7] * m[12]) + m[3] * (m[4] * m[14] - m[6] * m[12]));
    cof[10] = m[0] * (m[5] * m[15] - m[7] * m[13]) - m[1] * (m[4] * m[15] - m[7] * m[12]) + m[3] * (m[4] * m[13] - m[5] * m[12]);
    cof[11] = -(m[0] * (m[5] * m[14] - m[6] * m[13]) - m[1] * (m[4] * m[14] - m[6] * m[12]) + m[2] * (m[4] * m[13] - m[5] * m[12]));

    cof[12] = -(m[1] * (m[6] * m[11] - m[7] * m[10]) - m[2] * (m[5] * m[11] - m[7] * m[9]) + m[3] * (m[5] * m[10] - m[6] * m[9]));
    cof[13] = m[0] * (m[6] * m[11] - m[7] * m[10]) - m[2] * (m[4] * m[11] - m[7] * m[8]) + m[3] * (m[4] * m[10] - m[6] * m[8]);
    cof[14] = -(m[0] * (m[5] * m[11] - m[7] * m[9]) - m[1] * (m[4] * m[11] - m[7] * m[8]) + m[3] * (m[4] * m[9] - m[5] * m[8]));
    cof[15] = m[0] * (m[5] * m[10] - m[6] * m[9]) - m[1] * (m[4] * m[10] - m[6] * m[8]) + m[2] * (m[4] * m[9] - m[5] * m[8]);

    std::array<T, 16> inverse;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            inverse[i * 4 + j] = cof[j * 4 + i] / det;

    return inverse;
}

///////////////////// LOSSY SCALE ////////////////////
template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::LossyScale4x4() const
{
    // On prend les 3 colonnes de la matrice et on calcule leur longueur.
    auto length = [](T x, T y, T z) {
        return std::sqrt(x * x + y * y + z * z);
        };

    Maths::Vec3<T> scale;
    scale.SetX(length(at(0, 0), at(1, 0), at(2, 0)));
    scale.SetY(length(at(0, 1), at(1, 1), at(2, 1)));
    scale.SetZ(length(at(0, 2), at(1, 2), at(2, 2)));

    // calcul du determinant 3x3
    T det = at(0, 0) * (at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1)) - at(0, 1) * (at(1, 0) * at(2, 2) - at(1, 2) * at(2, 0)) + at(0, 2) * (at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0));
    if (det < static_cast<T>(0)) scale.SetX(-scale.x());

    return scale;
}

///////////////////// IDENTITY CHECK ////////////////////
template<typename T>
bool Maths::Mat4<T>::isIdentity4x4() const
{
    const T eps = static_cast<T>(1e-6);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (i == j ? std::abs(tabMat[i * 4 + j] - T(1)) > eps : std::abs(tabMat[i * 4 + j]) > eps)
                return false;
    return true;
}

///////////////////// DÉTERMINANT ////////////////////
template<typename T>
T Maths::Mat4<T>::Det4x4() const
{
    const auto& m = this->tabMat;
    return
        m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[9] * m[15] - m[11] * m[13]) + m[7] * (m[9] * m[14] - m[10] * m[13]))
        - m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14]) - m[6] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[14] - m[10] * m[12]))
        + m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13]) - m[5] * (m[8] * m[15] - m[11] * m[12]) + m[7] * (m[8] * m[13] - m[9] * m[12]))
        - m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13]) - m[5] * (m[8] * m[14] - m[10] * m[12]) + m[6] * (m[8] * m[13] - m[9] * m[12]));
}

///////////////////// ACCESSEUR ////////////////////
template<typename T>
T& Maths::Mat4<T>::at(int r, int c) {
    return tabMat[r * 4 + c];
}