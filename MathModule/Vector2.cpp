#include "pch.h"
#include "MathUtil.h"
#include "Vector2.h"
#include "Vector3.h"

const Vector2 Vector2::Left(-1.f, 0.f);
const Vector2 Vector2::Right(1.f, 0.f);
const Vector2 Vector2::Up(0.f, 1.f);
const Vector2 Vector2::Down(0.f, -1.f);
const Vector2 Vector2::One(1.f, 1.f);
const Vector2 Vector2::Zero(0.f, 0.f);

Vector2::Vector2()
	: NativeVector2(0.f, 0.f)
{
}

Vector2::Vector2(float x, float y)
	: NativeVector2(x, y)
{
}

Vector2::Vector2(const Vector2& other)
	: NativeVector2(other.NativeVector2)
{
}

Vector2::Vector2(const Vector3& other)
	: NativeVector2(other.X, other.Y)
{
}

Vector3 Vector2::ToVector3() const
{
	return Vector3(X, Y, 0.f);
}

float Vector2::Angle(const Vector2& other) const
{
	float size = std::sqrtf(SizeSq() * other.SizeSq());
	float dot = Dot(other);
	float cosAngle = std::acosf(dot / size);
	cosAngle = Math::Rad2Deg(cosAngle);
	return (X * other.Y - Y * other.X > 0.f) ? cosAngle : -cosAngle;
}

float Vector2::Size() const
{
	return X * X + Y * Y;
}

float Vector2::SizeSq() const
{
	return sqrtf(Size());
}

float Vector2::Distance(const Vector2& other) const
{
	float xDist = X - X;
	float yDist = Y - Y;
	return std::sqrtf((xDist * xDist) + (yDist * yDist));
}

void Vector2::Normalize()
{
	float size = Size();
	X /= size;
	Y /= size;
}

Vector2 Vector2::GetNormalize() const
{
	Vector2 result(*this);
	result.Normalize();
	return result;
}

Vector2 Vector2::Min(const Vector2& other) const
{
	return Vector2(std::fminf(X, other.X), std::fminf(Y, other.Y));
}

Vector2 Vector2::Max(const Vector2& other) const
{
	return Vector2(std::fmaxf(X, other.X), std::fmaxf(Y, other.Y));
}

float Vector2::Dot(const Vector2& other) const
{
	return X * other.X + Y * other.Y;
}

Vector2 Vector2::operator-()
{
	return Vector2(-X, -Y);
}

Vector2 Vector2::operator*(const float d) const
{
	return Vector2(X * d, Y * d);
}

Vector2 Vector2::operator/(const float d) const
{
	return Vector2(X / d, Y / d);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(X + other.X, Y + other.Y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(X - other.X, Y - other.Y);
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return Vector2(X * other.X, Y * other.Y);
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	X += other.X;
	Y += other.Y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	X -= other.X;
	Y -= other.Y;
	return *this;
}

Vector2 Vector2::operator*=(const float d)
{
	X *= d;
	Y *= d;
	return *this;
}

Vector2 Vector2::operator/=(const float d)
{
	X /= d;
	Y /= d;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	float xAbs = std::fabsf(X - other.X);
	float yAbs = std::fabsf(Y - other.Y);
	return (xAbs <= FLT_EPSILON && yAbs <= FLT_EPSILON);
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

Vector2 Vector2::operator=(const Vector3& other)
{
	X = other.X;
	Y = other.Y;
	return *this;
}
