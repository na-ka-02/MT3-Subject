#include "mathVector3.h"
#include <Novice.h>
#include "math.h"

//加算__
Vector3 Add(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {};
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return Vector3(result);
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2)
{
	Vector3 result = {};
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return Vector3(result);
}

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v)
{
	Vector3 result = {};
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return Vector3(result);
}

//内積 fabsf←絶対値
float Dot(const Vector3& v1, const Vector3& v2)
{
	float result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return float(result);
}

//長さ(ノルム) sqrt←ルート
float Length(const Vector3& v)
{
	float result = 0;
	result = sqrtf(Dot(v, v));
	return float(result);
}

//正規化 fabsf←絶対値
Vector3 Nomalize(const Vector3& v)
{
	Vector3 result = {};
	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);
	return Vector3(result);
}

//表示関数
static const int kColumnWidth = 60;
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

