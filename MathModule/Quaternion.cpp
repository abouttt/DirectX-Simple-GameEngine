#include "pch.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "Quaternion.h"

const Quaternion Quaternion::Identity(0.f, 0.f, 0.f, 1.f);

Quaternion::Quaternion()
	: NativeQuaternion(0.f, 0.f, 0.f, 1.f)
{
}

Quaternion::Quaternion(const Quaternion& other)
	: NativeQuaternion(other.NativeQuaternion)
{
}

Quaternion::Quaternion(float x, float y, float z, float w)
	: NativeQuaternion(x, y, z, w)
{
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, const float t)
{
	Quaternion result;
	D3DXQuaternionSlerp(&result.NativeQuaternion, &q1.NativeQuaternion, &q2.NativeQuaternion, t);
	return result;
}

void Quaternion::AngleAxis(const float angle, const Vector3& axis)
{
	D3DXQuaternionRotationAxis(&NativeQuaternion, &axis.NativeVector3, angle);
}

void Quaternion::ToAngleAxis(float* const angle, Vector3* const axis) const
{
	assert(angle);
	assert(axis);

	D3DXQuaternionToAxisAngle(&NativeQuaternion, &axis->NativeVector3, angle);
}

float Quaternion::Dot(const Quaternion& other) const
{
	return D3DXQuaternionDot(&NativeQuaternion, &other.NativeQuaternion);
}

void Quaternion::Inverse()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

Quaternion Quaternion::GetInverse() const
{
	return Quaternion(-X, -Y, -Z, W);
}

void Quaternion::Normalize()
{
	const float squareSum = X * X + Y * Y + Z * Z + W * W;

	if (squareSum >= FLT_EPSILON)
	{
		const float scale = 1.f / sqrtf(squareSum);

		X *= scale;
		Y *= scale;
		Z *= scale;
		W *= scale;
	}
	else
	{
		*this = Quaternion::Identity;
	}
}

Quaternion Quaternion::GetNormalize() const
{
	Quaternion result(*this);
	result.Normalize();
	return result;
}

Vector3 Quaternion::ToEuler() const
{
	Vector3 result;

	float sinrCosp = 2 * (W * Z + X * Y);
	float cosrCosp = 1 - 2 * (Z * Z + X * X);
	result.Z = Math::Rad2Deg(atan2f(sinrCosp, cosrCosp));

	float pitchTest = W * X - Y * Z;
	float asinThreshold = 0.4999995f;
	if (pitchTest < -asinThreshold)
	{
		result.X = -90;
	}
	else if (pitchTest > asinThreshold)
	{
		result.X = 90;
	}
	else
	{
		float sinp = 2 * pitchTest;
		result.X = Math::Rad2Deg(asinf(sinp));
	}

	float sinyCosp = 2 * (W * Y + X * Z);
	float cosyCosp = 1.f - 2 * (X * X + Y * Y);
	result.Y = Math::Rad2Deg(atan2f(sinyCosp, cosyCosp));

	return result;
}

Vector3 Quaternion::operator*(const Vector3& v) const
{
	Quaternion q1 = GetInverse();
	Quaternion q2 = q1 * Quaternion(v.X, v.Y, v.Z, 1.f) * (*this);
	return Vector3(q2.X, q2.Y, q2.Z);
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
	Quaternion result;
	result.NativeQuaternion = NativeQuaternion * other.NativeQuaternion;
	return result;
}

Quaternion Quaternion::operator*=(const Quaternion& other)
{
	NativeQuaternion *= other.NativeQuaternion;
	return *this;
}

bool Quaternion::operator==(const Quaternion& other) const
{
	return NativeQuaternion == other.NativeQuaternion;
}

bool Quaternion::operator!=(const Quaternion& other) const
{
	return NativeQuaternion != other.NativeQuaternion;;
}
