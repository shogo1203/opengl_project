#include "vector3.h"

Vector3::Vector3() :
	x_(0),
	y_(0),
	z_(0)
{
}

Vector3::Vector3(float x, float y, float z) :
	x_(x),
	y_(y),
	z_(z)
{
}

float Vector3::GetLength() const
{
	return x_ * x_ + y_ * y_ + z_ * z_;
}

Vector3 Vector3::GetNormalize()
{
	float mag = GetLength();
	mag = 1.0f / mag;
	return Vector3(x_ * mag, y_ * mag, z_ * mag);
}

std::string Vector3::ToString() const
{
	return "Vector3 (" + std::to_string(x_) + "," + std::to_string(y_) + "," + std::to_string(z_) + ")";
}

void Vector3::Set(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

void Vector3::Set(Vector3& vector3)
{
	Set(vector3.x_, vector3.y_, vector3.z_);
}

Vector3& Vector3::operator=(Vector3& vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	z_ = vec.z_;
	return *this;
}

Vector3 Vector3::Up()
{
	return Vector3(0, 1, 0);
}

Vector3 Vector3::Down()
{
	return Vector3(0, -1, 0);
}

Vector3 Vector3::Left()
{
	return Vector3(-1, 0, 0);
}

Vector3 Vector3::Right()
{
	return Vector3(1, 0, 0);
}

Vector3 Vector3::Forward()
{
	return Vector3(0, 0, 1);
}

Vector3 Vector3::Back()
{
	return Vector3(0, 0, -1);
}

Vector3 Vector3::Zero()
{
	return Vector3();
}

Vector3 Vector3::Clamp(const Vector3& vector, const Vector3& min, const Vector3& max)
{
	float x = Utility::Clamp(vector.x_, min.x_, max.x_);
	float y = Utility::Clamp(vector.y_, min.y_, max.y_);
	float z = Utility::Clamp(vector.z_, min.z_, max.z_);
	return Vector3(x, y, z);
}

Vector3 Vector3::Cross(const Vector3& vec1, const Vector3& vec2)
{
	float x = vec1.y_ * vec2.z_ - vec1.z_ * vec2.y_;
	float y = vec1.z_ * vec2.x_ - vec1.x_ * vec2.z_;
	float z = vec1.x_ * vec2.y_ - vec1.y_ * vec2.x_;

	return Vector3(x, y, z);
}

Vector3 Vector3::Lerp(const Vector3& from, const Vector3& to, float rate)
{
	float x = Utility::Lerp(from.x_, to.x_, rate);
	float y = Utility::Lerp(from.y_, to.y_, rate);
	float z = Utility::Lerp(from.z_, to.z_, rate);
	return Vector3(x, y, z);
}

float Vector3::Distance(const Vector3& vec1, const Vector3& vec2)
{
	return std::abs(vec1.GetLength() - vec2.GetLength());
}

float Vector3::Dot(const Vector3& vec1, const Vector3& vec2)
{
	Vector3 ans = vec1 * vec2;
	return ans.x_ + ans.y_ + ans.z_;
}

Vector3 Vector3::Max(const Vector3& vec1, const Vector3& vec2)
{
	float x = (vec1.x_ < vec2.x_) ? vec2.x_ : vec1.x_;
	float y = (vec1.y_ < vec2.y_) ? vec2.y_ : vec1.y_;
	float z = (vec1.z_ < vec2.z_) ? vec2.z_ : vec1.z_;

	return Vector3(x, y, z);
}

Vector3 Vector3::Min(const Vector3& vec1, const Vector3& vec2)
{
	float x = (vec1.x_ > vec2.x_) ? vec2.x_ : vec1.x_;
	float y = (vec1.y_ > vec2.y_) ? vec2.y_ : vec1.y_;
	float z = (vec1.z_ > vec2.z_) ? vec2.z_ : vec1.z_;

	return Vector3(x, y, z);
}

Vector3 Vector3::Reflect(const Vector3& direction, const Vector3& normal)
{
	float a = Vector3::Dot(direction * -1.0f, normal);
	Vector3 na2 = normal * (2 * a);
	return direction + na2;
}

Vector3 operator*(const Vector3& vec, float value)
{
	return Vector3(vec.x_ * value, vec.y_ * value, vec.z_ * value);
}

Vector3 operator*(float value, const Vector3& vec)
{
	return vec * value;
}

Vector3 operator*(const Vector3& vec, const Vector3& vec1)
{
	return Vector3(vec.x_ * vec1.x_, vec.y_ * vec1.y_, vec.z_ * vec1.z_);
}

Vector3 operator+(Vector3& vec, Vector3& vec1)
{
	return Vector3(vec.x_ + vec1.x_, vec.y_ + vec1.y_, vec.z_ + vec1.z_);
}

Vector3 operator+(Vector3 vec, Vector3 vec1)
{
	return Vector3(vec.x_ - vec1.x_, vec.y_ - vec1.y_, vec.z_ - vec1.z_);
}

Vector3 operator-(Vector3& vec, Vector3& vec1)
{
	return Vector3(vec.x_ - vec1.x_, vec.y_ - vec1.y_, vec.z_ - vec1.z_);
}

bool operator==(Vector3& vec, Vector3& vec1)
{
	return vec.x_ == vec1.x_ && vec.y_ == vec1.y_ && vec.z_ == vec1.z_;
}
