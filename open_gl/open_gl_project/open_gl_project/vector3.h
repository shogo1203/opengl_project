#pragma once
#include "object.h"
#include "utility.h"
#include <cmath>

class Vector3 : public Object
{
public:
	static Vector3 Up();
	static Vector3 Down();
	static Vector3 Left();
	static Vector3 Right();
	static Vector3 Forward();
	static Vector3 Back();
	static Vector3 Zero();
	static Vector3 Clamp(const Vector3& vector3, const Vector3& min, const Vector3& max);
	static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);
	static Vector3 Lerp(const Vector3& vec1, const Vector3& vec2, float rate);
	static float Distance(const Vector3& vec1, const Vector3& vec2);
	static float Dot(const Vector3& vec1, const Vector3& vec2);
	static Vector3 Max(const Vector3& vec1, const Vector3& vec2);
	static Vector3 Min(const Vector3& vec1, const Vector3& vec2);
	static Vector3 Reflect(const Vector3& direction, const Vector3& normal);

	Vector3();
	Vector3(float x, float y, float z);
	float GetLength() const;
	Vector3 GetNormalize();
	std::string ToString() const override;
	void Set(float x, float y, float z);
	void Set(Vector3& vector3);

	float x_;
	float y_;
	float z_;

	friend Vector3 operator *(const Vector3& vec, float value);
	friend Vector3 operator *(float value, const Vector3& vec);
	friend Vector3 operator *(const Vector3& vec, const Vector3& value);
	friend Vector3 operator +(Vector3& vec, Vector3& vec1);
	friend Vector3 operator +(Vector3 vec, Vector3 vec1);
	friend Vector3 operator -(Vector3& vec, Vector3& vec1);
	friend bool operator ==(Vector3& vec, Vector3& value);
	Vector3& operator =(Vector3& value);
};

