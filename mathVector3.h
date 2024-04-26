#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
// スカラー倍
Vector3 Multiply(float scalar, const Vector3& v);
// 内積
float Dot(const Vector3& v1, const Vector3& v2);
// 長さ(ノルム)
float Length(const Vector3& v);
//正規化
Vector3 Nomalize(const Vector3& v);
//表示関数
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

//1.行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//2.行列の減法
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
//3.行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
//4.逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
//5.転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
//6.単位行列の作成
Matrix4x4 MakeIndentity4x4();
//表示関数
static const int kRowHeight = 20;
static const int kColumWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix);

//平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
//座標変換 
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);