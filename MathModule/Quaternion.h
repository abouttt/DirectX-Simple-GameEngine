#pragma once

struct Vector3;

struct Quaternion
{
	// 생성자
	Quaternion();
	Quaternion(const Quaternion& other);
	Quaternion(float x, float y, float z, float w);

	// 정적멤버함수
	static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, const float t);

	// 멤버함수
	void AngleAxis(const float angle, const Vector3& axis);
	void ToAngleAxis(float* const angle, Vector3* const axis) const;
	float Dot(const Quaternion& other) const;
	void Inverse();
	Quaternion GetInverse() const;
	void Normalize();
	Quaternion GetNormalize() const;
	Vector3 ToEuler() const;

	// 연산자
	Vector3 operator*(const Vector3& v) const;
	Quaternion operator*(const Quaternion& other) const;
	Quaternion operator*=(const Quaternion& other);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;

	// 정적멤버변수
	static const Quaternion Identity;

	// 멤버변수
	union
	{
		struct
		{
			float X, Y, Z, W;
		};

		D3DXQUATERNION NativeQuaternion;
	};
};

