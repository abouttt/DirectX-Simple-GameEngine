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

Vector3::Vector3(float x, float y, float z)
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

float Vector3::Angle(const Vector3& other) const
{
	float size = std::sqrtf(SizeSq() * other.SizeSq());
	float dot = Dot(other);
	float cosAngle = std::acosf(dot / size);
	cosAngle = Math::Rad2Deg(cosAngle);
	return (X * other.Y - Y * other.X > 0.f) ? cosAngle : -cosAngle;
}

float Vector3::Size() const
{
	return X * X + Y * Y + Z * Z;
}

float Vector3::SizeSq() const
{
	return sqrtf(Size());
}

float Vector3::Distance(const Vector3& other) const
{
	float xDist = X - X;
	float yDist = Y - Y;
	float zDist = Z - Z;
	return std::sqrtf((xDist * xDist) + (yDist * yDist) + (zDist * zDist));
}

void Vector3::Normalize()
{
	float size = Size();
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

Vector3 Vector3::Min(const Vector3& other) const
{
	return Vector3(std::fminf(X, other.X), std::fminf(Y, other.Y), std::fminf(Z, other.Z));
}

Vector3 Vector3::Max(const Vector3& other) const
{
	return Vector3(std::fmaxf(X, other.X), std::fmaxf(Y, other.Y), std::fmaxf(Z, other.Z));
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(
		Y * other.Z - Z * other.Y,
		Z * other.X - X * other.Z,
		X * other.Y - Y * other.X);
}

float Vector3::Dot(const Vector3& other) const
{
	return X * other.X + Y * other.Y + Z * other.Z;
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

Vector3 Vector3::operator-()
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
	return (xAbs <= FLT_EPSILON && yAbs <= FLT_EPSILON && zAbs <= FLT_EPSILON);
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