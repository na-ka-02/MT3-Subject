#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Sphere.h"
#include"line.h"
#include"Plane.h"
#include<cstdint>

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
//X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radius);
//Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radius);
//Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radius);
//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
//正射影行列
Matrix4x4 MakeOrthographiMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatirix(float left, float top, float width, float height, float minDepth, float maxDepth);
//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);
//グリッド
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatirx);
//球
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatirx, const Matrix4x4& viewportMatrix, uint32_t color);
//正射影ベクトル
Vector3 Project(const Vector3& v1, const Vector3& v2);
//最近接点
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
//当たり判定(球と球)
bool IsCollision(const Sphere& s1, const Sphere& s2);
//当たり判定(球と平面)
bool IsCollision(const Sphere& sphere, const Plane& plsne);
//無限投影平面
Vector3 Perpendicular(const Vector3& vector);
//平面の描画
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);