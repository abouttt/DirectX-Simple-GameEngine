#include "pch.h"
#include "MathUtil.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

const Vector3 Vector3::Left(-1.f, 0.f, 0.f);
const Vector3 Vector3::Right(1.f, 0.f, 0.f);
const Vector3 Vector3::Forward(0.f, 0.f, 1.f);
const Vector3 Vector3::Back(0.f, 0.f, -1.f);
const Vector3 Vector3::Up(0.f, 1.f, 0.f);
const Vector3 Vector3::Down(0.f, -1.f, 0.f);
const Vector3 Vector3::One(1.f, 1.f, 1.f);
const Vector3 Vector3::Zero(0.f, 0.f, 0.f);

Vector3::Vector3()
	: NativeVector3(0.f, 0.f, 0.f)
{
}

Vector3::Vector3(const float x, const float y, const float z)
	: NativeVector3(x, y, z)
{
}

Vector3::Vector3(const Vector3& other)
	: NativeVector3(other.NativeVector3)
{
}

Vector3::Vector3(const Vector2& other)
	: NativeVector3(other.X, other.Y, 0.f)
{
}

float Vector3::Angle(const Vector3& from, const Vector3& to)
{
	float size = std::sqrtf(from.GetSizeSq() * to.GetSizeSq());
	float dot = Dot(from, to);
	float cosAngle = std::acosf(dot / size);
	cosAngle = Math::Rad2Deg(cosAngle);
	return (from.X * to.Y - from.Y * to.X > 0.f) ? cosAngle : -cosAngle;
}

Vector3 Vector3::Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3(
		v1.Y * v2.Z - v1.Z * v2.Y,
		v1.Z * v2.X - v1.X * v2.Z,
		v1.X * v2.Y - v1.Y * v2.X);
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
}

float Vector3::Distance(const Vector3& v1, const Vector3& v2)
{
	float xDist = v1.X - v2.X;
	float yDist = v1.Y - v2.Y;
	float zDist = v1.Z - v2.Z;
	return std::sqrtf((xDist * xDist) + (yDist * yDist) + (zDist * zDist));
}

Vector3 Vector3::Min(const Vector3& v1, const Vector3& v2)
{
	return Vector3(std::fminf(v1.X, v2.X), std::fminf(v1.Y, v2.Y), std::fminf(v1.Z, v2.Z));
}

Vector3 Vector3::Max(const Vector3& v1, const Vector3& v2)
{
	return Vector3(std::fmaxf(v1.X, v2.X), std::fmaxf(v1.Y, v2.Y), std::fmaxf(v1.Z, v2.Z));
}

float Vector3::GetSize() const
{
	return sqrtf(X * X + Y * Y + Z * Z);
}

float Vector3::GetSizeSq() const
{
	return X * X + Y * Y + Z * Z;
}

void Vector3::Normalize()
{
	float size = GetSize();
	X /= size;
	Y /= size;
	Z /= size;
}

Vector3 Vector3::GetNormalize() const
{
	Vector3 result(*this);
	result.Normalize();
	return result;
}

float Vector3::GetMin() const
{
	return std::fminf(std::fminf(X, Y), Z);
}

float Vector3::GetMax() const
{
	return std::fmaxf(std::fmaxf(X, Y), Z);
}

Vector2 Vector3::ToVector2() const
{
	return Vector2(X, Y);
}

Quaternion Vector3::ToQuaternion() const
{
	float sp = 0.f, sy = 0.f, sr = 0.f;
	float cp = 0.f, cy = 0.f, cr = 0.f;

	Math::GetSinCos(&sp, &cp, X * 0.5f);
	Math::GetSinCos(&sy, &cy, Y * 0.5f);
	Math::GetSinCos(&sr, &cr, Z * 0.5f);

	Quaternion q;
	q.W = sy * sp * sr + cy * cp * cr;
	q.X = sy * sr * cp + sp * cy * cr;
	q.Y = sy * cp * cr - sp * sr * cy;
	q.Z = -sy * sp * cr + sr * cy * cp;
	return q;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-X, -Y, -Z);
}

Vector3 Vector3::operator*(const float d) const
{
	return Vector3(X * d, Y * d, Z * d);
}

Vector3 Vector3::operator/(const float d) const
{
	return Vector3(X / d, Y / d, Z / d);
}

Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(X + other.X, Y + other.Y, Z + other.Z);
}

Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(X - other.X, Y - other.Y, Z - other.Z);
}

Vector3 Vector3::operator*(const Vector3& other) const
{
	return Vector3(X * other.X, Y * other.Y, Z * other.Z);
}

Vector3 Vector3::operator+=(const Vector3& other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3& other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	return *this;
}

Vector3 Vector3::operator*=(const float d)
{
	X *= d;
	Y *= d;
	Z *= d;
	return *this;
}

Vector3 Vector3::operator/=(const float d)
{
	X /= d;
	Y /= d;
	Z /= d;
	return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
	float xAbs = std::fabsf(X - other.X);
	float yAbs = std::fabsf(Y - other.Y);
	float zAbs = std::fabsf(Z - other.Z);
	return (xAbs <= Math::SMALL_NUMBER && yAbs <= Math::SMALL_NUMBER && zAbs <= Math::SMALL_NUMBER);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

Vector3 Vector3::operator=(const Vector2& other)
{
	X = other.X;
	Y = other.Y;
	return *this;
}
