#pragma once
#include <Novice.h>
#include<Matrix4x4.h>
#include<Vector3.h>
#include <assert.h>
#include<cmath>

#define N 4 //逆行列を求める行列の行数・列数 
#include <math.h>
#define _USE_MATH_DEFINES

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}
// 内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	return result;
}
// 長さ（ノルム）
float Length(const Vector3& v) {
	float result;
	result = float(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	return result;
}
// 正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result;
	result.x = float(v.x / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.y = float(v.y / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
	result.z = float(v.z / sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));

	return result;
}

Vector3 Perpendicular(const Vector3& vector){
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return{ -vector.y,vector.x,0.0f };
	}
	return{ 0.0f,-vector.z,vector.y };
}

// ベクトルの大きさの2乗を計算する関数
float MagnitudeSquared(const Vector3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}
// ベクトル間の距離を計算する関数
float Distance(const Vector3& a, const Vector3& b) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	return std::sqrt(dx * dx + dy * dy + dz * dz);
}
int check(double mat[N][N], double inv[N][N]) {

	double inner_product;
	int i, j, k;
	double ans;
	double diff;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			inner_product = 0;
			for (k = 0; k < N; k++) {
				inner_product += mat[i][k] * inv[k][j];
			}

			ans = (i == j) ? 1 : 0;
			diff = ans - inner_product;


		}
	}

	return 1;
}

// 行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}
	return result;

}
// 行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}
	return result;
}
/*
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
Vector3 result;
result.x = v1.x - v2.x;
result.y= v1.y - v2.y;
result.z = v1.z - v2.z;
return result;
}
*/
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			result.m[j][i] = m.m[i][j];
		}
	}
	return result;
}
// 単位行列の作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		result.m[i][i] = 1.0;
	}
	return result;
}
// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = { 0 };
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}
// １．平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[1][0] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[3][0] = translate.x;
	result.m[0][1] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[2][1] = 0.0f;
	result.m[3][1] = translate.y;
	result.m[0][2] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[3][2] = translate.z;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}
// ２．拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result;
	result.m[0][0] = scale.x;
	result.m[1][0] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[0][1] = 0.0f;
	result.m[1][1] = scale.y;
	result.m[2][1] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[2][2] = scale.z;
	result.m[3][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}
// ３．座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}
// ４．X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result;
	result.m[0][0] = 1.0f;
	result.m[1][0] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[0][1] = 0.0f;
	result.m[1][1] = std::cosf(radian);
	result.m[2][1] = -std::sinf(radian);
	result.m[3][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][2] = std::sinf(radian);
	result.m[2][2] = std::cosf(radian);
	result.m[3][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}
// ５．Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result;
	result.m[0][0] = std::cosf(radian);
	result.m[1][0] = 0.0f;
	result.m[2][0] = std::sinf(radian);
	result.m[3][0] = 0.0f;
	result.m[0][1] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[2][1] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[0][2] = -std::sinf(radian);
	result.m[1][2] = 0.0f;
	result.m[2][2] = std::cosf(radian);
	result.m[3][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}
// ６．Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result;
	result.m[0][0] = std::cosf(radian);
	result.m[1][0] = -std::sinf(radian);
	result.m[2][0] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[0][1] = std::sinf(radian);
	result.m[1][1] = std::cosf(radian);
	result.m[2][1] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[3][2] = 0.0f;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}
// 3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result;
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	result = Multiply(rotateXYZMatrix, Multiply(scaleMatrix, translateMatrix));
	return result;
}
// 透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = (1 / std::tanf(fovY / 2)) / aspectRatio;
	result.m[1][0] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[3][0] = 0.0f;
	result.m[0][1] = 0.0f;
	result.m[1][1] = (1 / std::tanf(fovY / 2));
	result.m[2][1] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[2][2] = farClip / farClip - nearClip;
	result.m[3][2] = (-farClip * nearClip) / (farClip - nearClip);
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 1.0f;
	result.m[3][3] = 0.0f;
	return result;
}

// 正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = 2 / (right - left);
	result.m[1][0] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[3][0] = (left + right) / (left - right);
	result.m[0][1] = 0.0f;
	result.m[1][1] = 2 / (top - bottom);
	result.m[2][1] = 0.0f;
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[0][2] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[2][2] = 1 / (farClip - nearClip);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;
	result.m[0][0] = width / 2;
	result.m[1][0] = 0.0f;
	result.m[2][0] = 0.0f;
	result.m[3][0] = left + (width / 2);
	result.m[0][1] = 0.0f;
	result.m[1][1] = -(height / 2);
	result.m[2][1] = 0.0f;
	result.m[3][1] = top + (height / 2);
	result.m[0][2] = 0.0f;
	result.m[1][2] = 0.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[3][2] = minDepth;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;
	return result;
}
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result = { 0 };
	/* 逆行列を求める行列用の２次元配列 */
	double mat[N][N];

	/* 逆行列用の２次元配列 */
	double inv[N][N];

	/* 掃き出し法を行う行列 */
	double sweep[N][N * 2];

	int i; /* 行 */
	int j; /* 列 */
	int k; /* 注目対角成分が存在する列 */

	double a; /* 定数倍用 */

	/* 正方行列の各成分をセット */
	mat[0][0] = m.m[0][0]; mat[0][1] = m.m[0][1]; mat[0][2] = m.m[0][2]; mat[0][3] = m.m[0][3];
	mat[1][0] = m.m[1][0]; mat[1][1] = m.m[1][1]; mat[1][2] = m.m[1][2]; mat[1][3] = m.m[1][3];
	mat[2][0] = m.m[2][0]; mat[2][1] = m.m[2][1]; mat[2][2] = m.m[2][2]; mat[2][3] = m.m[2][3];
	mat[3][0] = m.m[3][0]; mat[3][1] = m.m[3][1]; mat[3][2] = m.m[3][2]; mat[3][3] = m.m[3][3];

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			/* sweepの左側に逆行列を求める行列をセット */
			sweep[i][j] = mat[i][j];

			/* sweepの右側に単位行列をセット */
			sweep[i][N + j] = (i == j) ? 1 : 0;
		}
	}


	/* 全ての列の対角成分に対する繰り返し */
	for (k = 0; k < N; k++) {

		/* 最大の絶対値を注目対角成分の絶対値と仮定 */
		double max = fabs(sweep[k][k]);
		int max_i = k;

		/* k列目が最大の絶対値となる行を探す */
		for (i = k + 1; i < N; i++) {
			if (fabs(sweep[i][k]) > max) {
				max = fabs(sweep[i][k]);
				max_i = i;
			}
		}



		/* 操作（１）：k行目とmax_i行目を入れ替える */
		if (k != max_i) {
			for (j = 0; j < N * 2; j++) {
				double tmp = sweep[max_i][j];
				sweep[max_i][j] = sweep[k][j];
				sweep[k][j] = tmp;
			}
		}

		/* sweep[k][k]に掛けると1になる値を求める */
		a = 1 / sweep[k][k];

		/* 操作（２）：k行目をa倍する */
		for (j = 0; j < N * 2; j++) {
			/* これによりsweep[k][k]が1になる */
			sweep[k][j] *= a;
		}

		/* 操作（３）によりk行目以外の行のk列目を0にする */
		for (i = 0; i < N; i++) {
			if (i == k) {
				/* k行目はそのまま */
				continue;
			}

			/* k行目に掛ける値を求める */
			a = -sweep[i][k];

			for (j = 0; j < N * 2; j++) {
				/* i行目にk行目をa倍した行を足す */
				/* これによりsweep[i][k]が0になる */
				sweep[i][j] += sweep[k][j] * a;
			}
		}
	}

	/* sweepの右半分がmatの逆行列 */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			inv[i][j] = sweep[i][N + j];
		}
	}

	/* 逆行列invを表示 */
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			result.m[i][j] = float(inv[i][j]);
			//printf("%0.2f, ", inv[i][j]);
		}
		//printf("\n");
	}

	/* 検算 */
	if (check(mat, inv)) {
		//printf("invはmatの逆行列です！！\n");
	}
	else {
		//printf("invはmatの逆行列になってません...\n");
	}
	return result;
}
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}
void VectorScreenPrintf(int x, int y, Vector3 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
}
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return result;
}
/*
float Dot(const Vector3& v1,const Vector3& v2 ) {
float result;
result = (v1.x * v2.x) + (v1.y * v2.y)+ (v1.z * v2.z);
return result;
}
*/

