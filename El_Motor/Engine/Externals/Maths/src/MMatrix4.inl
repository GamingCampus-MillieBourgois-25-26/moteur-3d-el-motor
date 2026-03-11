#include "Maths/Headers/MMatrix4.hpp"


template<typename T>
Maths::Mat4<T>::Mat4() { tabMat.fill(static_cast<T>(0)); }

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


//////// STATIC PORPRETIES ////////
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
	matrix.tabMat = {
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
		static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0)
	};
	return matrix;
}


//////// PORPRETIES ////////
template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Rotation4x4(T angleX, T angleY, T angleZ)
{
	T radX = angleX * deg2rad;
	T radY = angleY * deg2rad;
	T radZ = angleZ * deg2rad;

	Mat4 rotX, rotY, rotZ;

	// on va commencer par l'axe X 
	rotX.at(1, 1) = cos(radX);
	rotX.at(1, 2) = -sin(radX);
	rotX.at(2, 1) = sin(radX);
	rotX.at(2, 2) = cos(radX);

	rotY.at(0, 0) = cos(radY);
	rotY.at(0, 2) = -sin(radY);
	rotY.at(2, 0) = sin(radY);
	rotY.at(2, 2) = cos(radY);

	rotZ.at(0, 0) = cos(radZ);
	rotZ.at(0, 1) = -sin(radZ);
	rotZ.at(1, 0) = sin(radZ);
	rotZ.at(1, 1) = cos(radZ);

	// normalement l'opérator est censé marcher inshallah
	return rotX * rotY * rotZ;
}


template<typename T>
std::array<T, 16> Maths::Mat4<T>::Transpose4x4(Maths::Mat4<T> mat)
{  
	std::array<T, 16> transpo;

	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			transpo[i * 4 + j] = mat.tabMat[j * 4 + i];
		}
	}
	this->tabMat = transpo;
	return this->tabMat;
}

template<typename T>
std::array<T, 16> Maths::Mat4<T>::Inverse4x4()
{
	const auto& m = this->tabMat;
	T det = this->Det4x4();
	if (std::abs(det) < static_cast<T>(1e-6)) { // verification pour savoir si elle est inversible
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
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			inverse[i * 4 + j] = cof[j * 4 + i] / det;
		}
	}

	return inverse;
}

template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::LossyScale4x4()
{
	/*On prend les 3 colonnes de la matrice.
	  On calcule leur longueur.
	  Si le déterminant est négatif, un axe est inversé.
	  Cela donne l’échelle approximative (d’où “lossy”).*/

	  // ensuite on va faire en sorte de créé une bébé fonction qui va permettre de 
	  // calculer la longueur d'un vecteur 3D grace au [] qui créé une fonction comme
	  // si on créé un float dans la fonction.

	auto length = [](T x, T y, T z) { // le [] s'appelle lambda
		return std::sqrt(x * x + y * y + z * z);  // norme = √(x² + y² + z²)
		};

	// ca permet de ne pas créé des fonctions qu'on réutilisera pas.

	Maths::Vec3<T> scale; // avec ce vecteur, on va stocker les valeurs d'échelles (x,y,z)

	// Chaque colonne correspond à un axe (X, Y, Z) transformé par la matrice.

	// Colonne 0 → axe X transformé → sa longueur donne l’échelle sur X
	// si on regarde sans la fonction at et length, on a :
	scale.SetX(std::sqrt(
		(tabMat[0 * 4 + 0]) * (tabMat[0 * 4 + 0]) + // at(0,0)
		(tabMat[1 * 4 + 0]) * (tabMat[1 * 4 + 0]) + // at(1,0)
		(tabMat[2 * 4 + 0]) * (tabMat[2 * 4 + 0]))	// at(2,0)
	);

	// Colonne 1 → axe Y transformé → sa longueur donne l’échelle sur Y
	scale.SetY(length(at(0, 1), at(1, 1), at(2, 1)));

	// Colonne 2 → axe Z transformé → sa longueur donne l’échelle sur Z
	scale.SetZ(length(at(0, 2), at(1, 2), at(2, 2)));

	// donc avec les at et lenght c'est vachement plus simple et rapido :)

	// calcul du determinant
	T det =
		at(0, 0) * (at(1, 1) * at(2, 2) - at(1, 2) * at(2, 1)) -
		at(0, 1) * (at(1, 0) * at(2, 2) - at(1, 2) * at(2, 0)) +
		at(0, 2) * (at(1, 0) * at(2, 1) - at(1, 1) * at(2, 0));

	// si le determinant est négatif alors on inverse le signe d'un axe
	// c'est a dire que ca va faire un genre d'effet miroir chelou
	if (det < static_cast<T>(0))
		scale.SetX(-scale.x());

	// enfin on retourne le vecteur de ses morts et paf ca fais des chocapics
	return scale;
}

template<typename T>
bool Maths::Mat4<T>::isIdentity4x4()
{
	const T eps = static_cast<T>(1e-6);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				if (std::abs(tabMat[i * 4 + j] - T(1)) > eps) return false;
			}
			else {
				if (std::abs(tabMat[i * 4 + j]) > eps) return false;
			}
		}
	}
	return true;
}


template<typename T>
T Maths::Mat4<T>::Det4x4() const
{
	const auto& m = this->tabMat;

	return
		m[0] * (m[5] * (m[10] * m[15] - m[11] * m[14])
			- m[6] * (m[9] * m[15] - m[11] * m[13])
			+ m[7] * (m[9] * m[14] - m[10] * m[13]))
		- m[1] * (m[4] * (m[10] * m[15] - m[11] * m[14])
			- m[6] * (m[8] * m[15] - m[11] * m[12])
			+ m[7] * (m[8] * m[14] - m[10] * m[12]))
		+ m[2] * (m[4] * (m[9] * m[15] - m[11] * m[13])
			- m[5] * (m[8] * m[15] - m[11] * m[12])
			+ m[7] * (m[8] * m[13] - m[9] * m[12]))
		- m[3] * (m[4] * (m[9] * m[14] - m[10] * m[13])
			- m[5] * (m[8] * m[14] - m[10] * m[12])
			+ m[6] * (m[8] * m[13] - m[9] * m[12]));
}

template<typename T>
T& Maths::Mat4<T>::at(int r, int c) {
	return tabMat[r * 4 + c];
}


//////// PUBLIC METHODS ////////
template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::MultiplyPoint3x4_4x4(const Maths::Vec3<T>& vect)
{
	T x = vect.x();
	T y = vect.y();
	T z = vect.z();

	T resultX = at(0, 0) * x + at(0, 1) * y + at(0, 2) * z + at(0, 3);
	T resultY = at(1, 0) * x + at(1, 1) * y + at(1, 2) * z + at(1, 3);
	T resultZ = at(2, 0) * x + at(2, 1) * y + at(2, 2) * z + at(2, 3);

	return Vec3<T>(resultX, resultY, resultZ);

}

template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::MultiplyVector4x4(Maths::Vec3<T>& vect)
{
	T x = vect.x();
	T y = vect.y();
	T z = vect.z();

	// ici on utilise la meme méthode qu'avant : index = row ∗ 4  +col

	T resultX = at(0, 0) * x + at(0, 1) * y + at(0, 2) * z + at(0, 3);
	T resultY = at(1, 0) * x + at(1, 1) * y + at(1, 2) * z + at(1, 3);
	T resultZ = at(2, 0) * x + at(2, 1) * y + at(2, 2) * z + at(2, 3);
	T resultW = at(3, 0) * x + at(3, 1) * y + at(3, 2) * z + at(3, 3);

	// normalisation si besoin
	if (resultW != static_cast<T>(0) && resultW != static_cast<T>(1)) {
		resultX /= resultW;
		resultY /= resultW;
		resultZ /= resultW;
	}
	return Maths::Vec3<T>(resultX, resultY, resultZ);
}

template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::MultiplyPoint4x4(Maths::Vec3<T>& vect)
{
	const auto& m = this->tabMat;

	T x = vect.x();
	T y = vect.y();
	T z = vect.z();

	T resultX = m[0 * 4 + 0] * x + m[0 * 4 + 1] * y + m[0 * 4 + 2] * z + m[0 * 4 + 3];
	T resultY = m[1 * 4 + 0] * x + m[1 * 4 + 1] * y + m[1 * 4 + 2] * z + m[1 * 4 + 3];
	T resultZ = m[2 * 4 + 0] * x + m[2 * 4 + 1] * y + m[2 * 4 + 2] * z + m[2 * 4 + 3];
	T resultW = 1;

	if (resultW != 0 && resultW != 1) {
		resultX /= resultW;
		resultY /= resultW;
		resultZ /= resultW;
	}
	return Maths::Vec3<T>(resultX, resultY, resultZ);
}

template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::GetPosition4x4() const
{
	return Maths::Vec3<T>(tabMat[12], tabMat[13], tabMat[14]);
}


template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::SetTRS(const Maths::Vec3<T>& translation, const Maths::Vec3<T>& rotationEulerDeg, const Maths::Vec3<T>& scale) {
	T rx = rotationEulerDeg.x() * static_cast<T>(deg2rad);
	T ry = rotationEulerDeg.y() * static_cast<T>(deg2rad);
	T rz = rotationEulerDeg.z() * static_cast<T>(deg2rad);

	Mat4<T> result = Mat4<T>::Identity();

	result.at(0, 0) = scale.x();
	result.at(1, 1) = scale.y();
	result.at(2, 2) = scale.z();

	Mat4<T> rotX = Mat4<T>::Identity();
	rotX.at(1, 1) = std::cos(rx); rotX.at(1, 2) = -std::sin(rx);
	rotX.at(2, 1) = std::sin(rx); rotX.at(2, 2) = std::cos(rx);

	Mat4<T> rotY = Mat4<T>::Identity();
	rotY.at(0, 0) = std::cos(ry); rotY.at(0, 2) = std::sin(ry);
	rotY.at(2, 0) = -std::sin(ry); rotY.at(2, 2) = std::cos(ry);

	Mat4<T> rotZ = Mat4<T>::Identity();
	rotZ.at(0, 0) = std::cos(rz); rotZ.at(0, 1) = -std::sin(rz);
	rotZ.at(1, 0) = std::sin(rz); rotZ.at(1, 1) = std::cos(rz);

	result = rotZ * (rotY * (rotX * result));

	result.at(0, 3) = translation.x();
	result.at(1, 3) = translation.y();
	result.at(2, 3) = translation.z();

	return result;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::MultiplyMat4x4(Mat4<T>& A, Mat4<T>& B){
	Mat4 result{}; // initialise tous les éléments à zéro

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			for (int i = 0; i < 4; ++i) {
				result.tabMat[row, col] += A.tabMat[row, i] * B.tabMat[i, col];
			}
		}
	}
	return result;
}


template<typename T>
void Maths::Mat4<T>::SetColumn4x4(T columnNumber, T number1, T number2, T number3, T number4){
	int col = static_cast<int>(columnNumber);
	if (col < 0 || col > 3) { return; }

	this->tabMat[0 * 4 + col] = number1;
	this->tabMat[1 * 4 + col] = number2;
	this->tabMat[2 * 4 + col] = number3;
	this->tabMat[3 * 4 + col] = number4;
}

template<typename T>
void Maths::Mat4<T>::SetRow4x4(T rowNumber, T number1, T number2, T number3, T number4) {
	int row = static_cast<int>(rowNumber);
	 if (row < 0 || row > 3) { return; }

	this->tabMat[row * 4 + 0] = number1;
	this->tabMat[row * 4 + 1] = number2;
	this->tabMat[row * 4 + 2] = number3;
	this->tabMat[row * 4 + 3] = number4;
}

template<typename T>
void Maths::Mat4<T>::GetColumn4x4(T column)
{
	if (column < static_cast<T>(0) || column > static_cast<T>(3)) {
		std::cout << "Un mauvais numero a ete entre, il faut un numero entre 0 et 3.\n";
		return;
	}

	std::cout
		<< this->tabMat[column] << " "
		<< this->tabMat[column + 4] << " "
		<< this->tabMat[column + 8] << " "
		<< this->tabMat[column + 12] << " \n";
}

template<typename T>
void Maths::Mat4<T>::GetRow4x4(T row)
{
	if (row < static_cast<T>(0) || row > static_cast<T>(3)) {
		std::cout << "Un mauvais numero a ete entre, il faut un numero entre 0 et 3.\n";
		return;
	}

	int index = row * 4;

	std::cout
		<< this->tabMat[index] << " "
		<< this->tabMat[index + 1] << " "
		<< this->tabMat[index + 2] << " "
		<< this->tabMat[index + 3] << " \n";
}

template<typename T>
bool Maths::Mat4<T>::ValidTRS() {
	const T EPS = static_cast<T>(1e-6);

	T x0 = at(0, 0), x1 = at(1, 0), x2 = at(2, 0);
	T y0 = at(0, 1), y1 = at(1, 1), y2 = at(2, 1);
	T z0 = at(0, 2), z1 = at(1, 2), z2 = at(2, 2);

	auto length = [](T a, T b, T c) { return std::sqrt(a * a + b * b + c * c); };

	if (length(x0, x1, x2) < EPS) return false;
	if (length(y0, y1, y2) < EPS) return false;
	if (length(z0, z1, z2) < EPS) return false;

	auto dot = [](T a0, T a1, T a2, T b0, T b1, T b2) { return a0 * b0 + a1 * b1 + a2 * b2; };

	if (std::abs(dot(x0, x1, x2, y0, y1, y2)) > EPS) return false;
	if (std::abs(dot(x0, x1, x2, z0, z1, z2)) > EPS) return false;
	if (std::abs(dot(y0, y1, y2, z0, z1, z2)) > EPS) return false;

	if (std::abs(at(3, 0)) > EPS || std::abs(at(3, 1)) > EPS ||
		std::abs(at(3, 2)) > EPS || std::abs(at(3, 3) - 1) > EPS)
		return false;

	return true;
}


template<typename T>
std::string Maths::Mat4<T>::toString4x4()
{
	// en std
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j)
			std::cout << this->tabMat[i * 4 + j] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;

	// convertit en string
	std::ostringstream ss; // permet d'écrire une string comme si c'était un cout
	ss << std::fixed << std::setprecision(3); // 3 chiffres après la virgule

	ss << "Matrice 4x4 :" << std::endl;
	for (int i = 0; i < 4; ++i) {
		ss << "| ";
		for (int j = 0; j < 4; ++j) {
			ss << std::setw(8) << this->tabMat[i * 4 + j] << " ";
		}
		ss << "|" << std::endl;
	}

	return ss.str();
}

/////// STATIC METHODS ////////
template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::TRS( const Maths::Vec3<T>& position, const Maths::Vec3<T>& rotationEuler, const Maths::Vec3<T>& scale) {
	Mat4<T> S = Maths::Mat4<T>::ScaleVec4x4(scale);

	T cx = std::cos(rotationEuler.x()), sx = std::sin(rotationEuler.x());
	T cy = std::cos(rotationEuler.y()), sy = std::sin(rotationEuler.y());
	T cz = std::cos(rotationEuler.z()), sz = std::sin(rotationEuler.z());

	Mat4<T> Rx, Ry, Rz;

	Rx.tabMat[0] = 1; Rx.tabMat[5] = cx; Rx.tabMat[6] = -sx; Rx.tabMat[9] = sx; Rx.tabMat[10] = cx; Rx.tabMat[15] = 1;
	Ry.tabMat[0] = cy; Ry.tabMat[2] = sy; Ry.tabMat[5] = 1; Ry.tabMat[8] = -sy; Ry.tabMat[10] = cy; Ry.tabMat[15] = 1;
	Rz.tabMat[0] = cz; Rz.tabMat[1] = -sz; Rz.tabMat[4] = sz; Rz.tabMat[5] = cz; Rz.tabMat[10] = 1; Rz.tabMat[15] = 1;

	Mat4<T> R = Rz * Ry * Rx;
	Mat4<T> Trans = Mat4<T>::TranslateVec4x4(position);
	Mat4<T> TRS = Trans * (R * S);

	return TRS;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::LookAt4x4(Maths::Vec3<T>& from, const Maths::Vec3<T>& to, Maths::Vec3<T>& up)
{
	// forward = direction vers la cible
	Maths::Vec3<T> forward = (to - from);
	forward.Normalized();

	// right = perpendiculaire à forward et up
	Maths::Vec3<T> right = up.Cross(up, forward).Normalized();

	// upCorrected = vecteur up corrigé (orthogonal)
	Maths::Vec3<T> upCorrected = forward.Cross(forward, right);

	// --- Création de la matrice LookAt ---
	Mat4<T> result;

	// colonne 0 → axe droit (X)
	result.tabMat[0] = right.x();
	result.tabMat[1] = right.y();
	result.tabMat[2] = right.z();
	result.tabMat[3] = static_cast<T>(0);

	// colonne 1 → axe up (Y)
	result.tabMat[4] = upCorrected.x();
	result.tabMat[5] = upCorrected.y();
	result.tabMat[6] = upCorrected.z();
	result.tabMat[7] = static_cast<T>(0);

	// colonne 2 → -forward (Z)
	result.tabMat[8] = -forward.x();
	result.tabMat[9] = -forward.y();
	result.tabMat[10] = -forward.z();
	result.tabMat[11] = static_cast<T>(0);

	// colonne 3 → translation
	Maths::Vec3<T> rInverse = right * static_cast<T>(-1);
	Maths::Vec3<T> upInverse = upCorrected * static_cast<T>(-1);

	result.tabMat[12] = Maths::Vec3<T>::Dot(rInverse, from);
	result.tabMat[13] = Maths::Vec3<T>::Dot(upInverse, from);
	result.tabMat[14] = Maths::Vec3<T>::Dot(forward, from);
	result.tabMat[15] = static_cast<T>(1);

	return result;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Ortho4x4(T left, T right, T bottom, T top, T zNear, T zFar)
{
	Mat4<T> matrix;

	matrix.tabMat[0] = static_cast<T>(2) / (right - left);
	matrix.tabMat[1] = static_cast<T>(0);
	matrix.tabMat[2] = static_cast<T>(0);
	matrix.tabMat[3] = static_cast<T>(0);
	matrix.tabMat[4] = static_cast<T>(0);
	matrix.tabMat[5] = static_cast<T>(2) / (top - bottom);
	matrix.tabMat[6] = static_cast<T>(0);
	matrix.tabMat[7] = static_cast<T>(0);
	matrix.tabMat[8] = static_cast<T>(0);
	matrix.tabMat[9] = static_cast<T>(0);
	matrix.tabMat[10] = static_cast<T>(-2) / (zFar - zNear);
	matrix.tabMat[11] = static_cast<T>(0);
	matrix.tabMat[12] = -(right + left) / (right - left);
	matrix.tabMat[13] = -(top + bottom) / (top - bottom);
	matrix.tabMat[14] = -(zFar + zNear) / (zFar - zNear);
	matrix.tabMat[15] = static_cast<T>(-1);

	return matrix;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Perspective4x4(T fovY, T aspect, T nearP, T farP) {

	Mat4<T> result;

	// Calcul du facteur f = 1 / tan(fov/2)
	T f = static_cast<T>(1) / std::tan(fovY * static_cast<T>(0.5));

	// Mise à zéro de la matrice
	for (int i = 0; i < 16; ++i) result.tabMat[i] = static_cast<T>(0);

	// Remplissage des éléments
	result.tabMat[0] = f / aspect;  // m00
	result.tabMat[5] = f;           // m11
	result.tabMat[10] = (farP + nearP) / (nearP - farP);  // m22
	result.tabMat[11] = static_cast<T>(-1);          // m23
	result.tabMat[14] = static_cast<T>(2) * (farP * nearP) / (nearP - farP); // m32
	result.tabMat[15] = static_cast<T>(0);           // m33

	return result;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::TranslateVec4x4(const Maths::Vec3<T>& t)
{
	Mat4<T> result = Mat4<T>::Identity();

	result.at(0, 3) = t.x();
	result.at(1, 3) = t.y();
	result.at(2, 3) = t.z();

	return result;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Rotate4x4(const Maths::Quat<T>& q)
{
	Mat4<T> mat;

	const T x = q.x();
	const T y = q.y();
	const T z = q.z();
	const T w = q.w();

	const T xx = x * x;
	const T yy = y * y;
	const T zz = z * z;
	const T xy = x * y;
	const T xz = x * z;
	const T yz = y * z;
	const T wx = w * x;
	const T wy = w * y;
	const T wz = w * z;

	mat.tabMat[0] = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
	mat.tabMat[1] = static_cast<T>(2) * (xy - wz);
	mat.tabMat[2] = static_cast<T>(2) * (xz + wy);
	mat.tabMat[3] = static_cast<T>(0);

	mat.tabMat[4] = static_cast<T>(2) * (xy + wz);
	mat.tabMat[5] = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
	mat.tabMat[6] = static_cast<T>(2) * (yz - wx);
	mat.tabMat[7] = static_cast<T>(0);

	mat.tabMat[8] = static_cast<T>(2) * (xz - wy);
	mat.tabMat[9] = static_cast<T>(2) * (yz + wx);
	mat.tabMat[10] = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);
	mat.tabMat[11] = static_cast<T>(0);

	mat.tabMat[12] = static_cast<T>(0);
	mat.tabMat[13] = static_cast<T>(0);
	mat.tabMat[14] = static_cast<T>(0);
	mat.tabMat[15] = static_cast<T>(1);

	return mat;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::ScaleVec4x4(const Maths::Vec3<T>& s)
{
	return Scale4x4(s.x(), s.y(), s.z());
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Translate4x4(T tx, T ty, T tz)
{
	Mat4<T> result = Identity();
	result.at(0, 3) = tx;
	result.at(1, 3) = ty;
	result.at(2, 3) = tz;
	result.at(3, 3) = static_cast<T>(1);
	return result;
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::Scale4x4(T x, T y, T z)
{
	Mat4<T> result = Identity();
	result.at(0, 0) = x;
	result.at(1, 1) = y;
	result.at(2, 2) = z;
	return result;
}


//////// OPERATOR ////////
template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::operator*(const Mat4<T>& other) const {
	Mat4<T> result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.tabMat[i * 4 + j] = static_cast<T>(0);
			for (int k = 0; k < 4; ++k) {
				result.tabMat[i * 4 + j] += tabMat[i * 4 + k] * other.tabMat[k * 4 + j];
			}
		}
	}
	return result;
}

template<typename T>
Maths::Quat<T> Maths::Mat4<T>::operator*(const Maths::Quat<T>& v) {

    return Maths::Quat<T>(
        this->at(0, 0) * v.m_x + this->at(0, 1) * v.m_y + this->at(0, 2) * v.m_z + this->at(0, 3) * v.m_w,
        this->at(1, 0) * v.m_x + this->at(1, 1) * v.m_y + this->at(1, 2) * v.m_z + this->at(1, 3) * v.m_w,
        this->at(2, 0) * v.m_x + this->at(2, 1) * v.m_y + this->at(2, 2) * v.m_z + this->at(2, 3) * v.m_w,
        this->at(3, 0) * v.m_x + this->at(3, 1) * v.m_y + this->at(3, 2) * v.m_z + this->at(3, 3) * v.m_w
    );
}

template<typename T>
Maths::Vec3<T> Maths::Mat4<T>::operator*(const Maths::Vec3<T>& v) {
    T x = v.x();
    T y = v.y();
    T z = v.z();

    T resultX = this->at(0, 0) * x + this->at(0, 1) * y + this->at(0, 2) * z + this->at(0, 3);
    T resultY = this->at(1, 0) * x + this->at(1, 1) * y + this->at(1, 2) * z + this->at(1, 3);
    T resultZ = this->at(2, 0) * x + this->at(2, 1) * y + this->at(2, 2) * z + this->at(2, 3);
    T resultW = this->at(3, 0) * x + this->at(3, 1) * y + this->at(3, 2) * z + this->at(3, 3);

    if (resultW != static_cast<T>(0) && resultW != static_cast<T>(1)) {
        resultX /= resultW;
        resultY /= resultW;
        resultZ /= resultW;
    }

    return Maths::Vec3<T>(resultX, resultY, resultZ);
}

template<typename T>
Maths::Mat4<T> Maths::Mat4<T>::ConvertArrayToMat4(const std::array<T, 16>& arr) {
	Maths::Mat4<T> result;
	for (int i = 0; i < 16; ++i) {
		result.tabMat[i] = arr[i];
	}
	return result;
}