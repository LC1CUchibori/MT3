#pragma once
#define NOMINMAX
#include <limits>
#include <Novice.h>
#include<Matrix4x4.h>
#include<Vector2.h>
#include<Vector3.h>
#include <assert.h>
#include<cmath>
#include<algorithm>
#define N 4 //逆行列を求める行列の行数・列数 
#include <math.h>

#include <iostream>

#define M_PI 3.14




struct Sphere {
    Vector3 center; // !< 中心点
    float radius;   // !< 半径
};

struct Line {
    Vector3 origin; // !<始点
    Vector3 diff;   // !<終点への差分ベクトル
};

struct Ray {
    Vector3 origin; // !<始点
    Vector3 diff;   // !<終点への差分ベクトル
};

struct Segment {
    Vector3 origin; // !<始点
    Vector3 diff;   // !<終点への差分ベクトル
};

struct Plane {
    Vector3 normal; //!< 法線
    float distance; //!< 距離
};

struct Triangle {
    Vector3 vertices[3];//!< 頂点
};

struct AABB {
    Vector3 min; //!<最小点
    Vector3 max; //!<最大点
};

struct OBB {
    Vector3 center; //!<中心点
    Vector3 orientations[3]; //!<座標軸、正規化，直交必須
    Vector3 size; //!< 座標方向の長さの半分。中心から面までの距離
};

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

Matrix4x4 MakeRotateXYZMatrix(Vector3& rotate) {
    Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
    Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
    Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
    Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
    return rotateXYZMatrix;
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

//3次元ベクトル a をベクトル b に正射影する関数
Vector3 Project(const Vector3& v1, const Vector3& v2) {
    float dot = Dot(v1, v2);
    float magSquared = MagnitudeSquared(v2);
    float scalar = dot / magSquared;
    return { v2.x * scalar, v2.y * scalar, v2.z * scalar };
}

// 最近接点を計算する関数
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
    Vector3 pointOnLine = segment.origin; // 直線上の任意の点はセグメントの始点と同じと仮定
    float dot = Dot(segment.diff, Subtract(point, pointOnLine));
    float magSquared = MagnitudeSquared(segment.diff);
    float t = dot / magSquared;
    return { pointOnLine.x + segment.diff.x * t, pointOnLine.y + segment.diff.y * t, pointOnLine.z + segment.diff.z * t };
}

bool IsCollision(const Sphere& s1, const Sphere& s2) {
    // 2つの円の中心間の距離を計算
    float distance = float(std::sqrt(std::pow(s2.center.x - s1.center.x, 2) + std::pow(s2.center.y - s1.center.y, 2) + std::pow(s2.center.z - s1.center.z, 2)));
    // 中心間の距離が2つの円の半径の合計よりも小さい場合、衝突しているとみなす
    if (distance <= (s1.radius + s2.radius)) {
        return true;
    }
    else {
        return false;
    }
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {
    // 2つの円と平面の中心間の距離を計算
    float distance = std::abs((Dot(plane.normal, sphere.center)) - plane.distance);
    //float distance = float(std::sqrt(std::pow(plane.normal.x - sphere.center.x, 2) + std::pow(plane.normal.y - sphere.center.y, 2) + std::pow(plane.normal.z - sphere.center.z, 2)));
    // 中心間の距離が2つの円の半径の合計よりも小さい場合、衝突しているとみなす
    if (distance <= sphere.radius) {
        return true;
    }
    else {
        return false;
    }
}

bool IsCollision(const Segment& segment, const Plane& plane) {
    // まず垂直判定を行うために、法線と線の内積を求める
    float dot = Dot(plane.normal, segment.diff);
    // 垂直＝平行であるので、衝突しているはずがない
    if (dot == 0.0f) {
        return false;
    }
    // ｔを求める
    float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

    // 
    //float distance = Dot(segment.origin + (segment.diff * t), plane.normal);
    if (t >= 0.0f && t <= 1.0f) {
        return true;
    }
    else {
        return false;
    }
}

Plane CalculatePlane(Triangle triangle) {
    Vector3 v1 = triangle.vertices[0];
    Vector3 v2 = triangle.vertices[1];
    Vector3 v3 = triangle.vertices[2];

    Vector3 edge1 = v2 - v1;
    Vector3 edge2 = v3 - v1;
    Vector3 normal = Normalize(Cross(edge1, edge2));

    float distance = Dot(normal, v1);

    return Plane{ normal = normal, distance = distance };
}

Vector3 CalculateIntersection(Segment segment, Plane plane) {
    Vector3 p0 = segment.origin;
    Vector3 p1 = segment.origin + segment.diff;
    Vector3 lineDir = Normalize((p1 - p0));

    float t = (plane.distance - Dot(plane.normal, p0)) / Dot(plane.normal, lineDir);

    return p0 + lineDir * t;
}

Vector3 CalculateVector(Vector3 vertex, Vector3 intersectionPoint) {
    return intersectionPoint - vertex;
}

bool IsCollision(const Triangle& triangle, const Segment& segment) {
    Plane plane = CalculatePlane(triangle);
    if (!IsCollision(segment, plane)) {
        return false;
    }
    Vector3 v01 = Subtract(triangle.vertices[1], triangle.vertices[0]);
    Vector3 v12 = Subtract(triangle.vertices[2], triangle.vertices[1]);
    Vector3 v20 = Subtract(triangle.vertices[0], triangle.vertices[2]);
    Vector3 p = CalculateIntersection(segment, plane);
    Vector3 cross01 = Cross(v01, CalculateVector(triangle.vertices[0], p));
    Vector3 cross12 = Cross(v12, CalculateVector(triangle.vertices[1], p));
    Vector3 cross20 = Cross(v20, CalculateVector(triangle.vertices[2], p));
    // すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
    if (Dot(cross01, plane.normal) >= 0.0f &&
        Dot(cross12, plane.normal) >= 0.0f &&
        Dot(cross20, plane.normal) >= 0.0f) {
        return true;
    }
    else {
        return false;
    }
}

Vector3 Perpendicular(const Vector3& vector) {
    if (vector.x != 0.0f || vector.y != 0.0f) {
        return{ -vector.y, vector.x, 0.0f };
    }
    return{ 0.0f, -vector.z, vector.y };
}

bool IsCollision(const AABB& a, const AABB& b) {
    if ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&// x軸
        (a.min.y <= b.max.y && a.max.y >= b.min.y) &&// y軸
        (a.min.z <= b.max.z && a.max.z >= b.min.z)) {// z軸
        return true;
    }
    return false;
}

bool IsCollision(const Sphere& sphere, const AABB& aabb) {
    // 最近接点を求める
    Vector3 closestPoint{ std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
        std::clamp(sphere.center.y, aabb.min.y, aabb.max.y) ,
        std::clamp(sphere.center.z, aabb.min.z, aabb.max.z) };
    // 最近接点と球の中心との距離を求める
    float distance = Length(closestPoint - sphere.center);

    // 中心間の距離が2つの円の半径の合計よりも小さい場合、衝突しているとみなす
    if (distance <= sphere.radius) {
        return true;
    }
    else {
        return false;
    }
}

bool IsCollision(const AABB& aabb, const Segment& segment) {
    float tmin = (aabb.min.x - segment.origin.x) / segment.diff.x;
    float tmax = (aabb.max.x - segment.origin.x) / segment.diff.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (aabb.min.y - segment.origin.y) / segment.diff.y;
    float tymax = (aabb.max.y - segment.origin.y) / segment.diff.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (aabb.min.z - segment.origin.z) / segment.diff.z;
    float tzmax = (aabb.max.z - segment.origin.z) / segment.diff.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;

    return ((tmin < 1.0f) && (tmax > 0.0f));
}
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
    return Vector3{
        v1.x + t * (v2.x - v1.x),
        v1.y + t * (v2.y - v1.y),
        v1.z + t * (v2.z - v1.z)
    };
}



void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
    const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
    const int segments = 100;
    Vector3 previousPoint = controlPoint0;

    for (int i = 1; i <= segments; ++i) {
        float t = i / (float)segments;
        Vector3 point = Lerp(Lerp(controlPoint0, controlPoint1, t), Lerp(controlPoint1, controlPoint2, t), t);
        Vector3 transformedPrev = Transform(previousPoint, viewProjectionMatrix);
        transformedPrev = Transform(transformedPrev, viewportMatrix);
        Vector3 transformedCurrent = Transform(point, viewProjectionMatrix);
        transformedCurrent = Transform(transformedCurrent, viewportMatrix);

        Novice::DrawLine(
            static_cast<int>(transformedPrev.x),
            static_cast<int>(transformedPrev.y),
            static_cast<int>(transformedCurrent.x),
            static_cast<int>(transformedCurrent.y),
            color
        );

        previousPoint = point;
    }
}