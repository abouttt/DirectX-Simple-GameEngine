#pragma once

struct Vector2;
struct Quaternion;

struct Vector3
{
	// ������
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);
	Vector3(const Vector2& other);

	// ����Լ�
	float Angle(const Vector3& other) const;
	float Size() const;
	float SizeSq() const;
	float Distance(const Vector3& other) const;
	void Normalize();
	Vector3 GetNormalize() const;
	Vector3 Min(const Vector3& other) const;
	Vector3 Max(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;
	float Dot(const Vector3& other) const;
	Vector2 ToVector2() const;
	Quaternion ToQuaternion() const;

	// ������
	Vector3 operator-();

	Vector3 operator*(const float d) const;
	Vector3 operator/(const float d) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator*(const Vector3& other) const;

	Vector3 operator*=(const float d);
	Vector3 operator/=(const float d);
	Vector3 operator+=(const Vector3& other);
	Vector3 operator-=(const Vector3& other);

	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;

	Vector3 operator=(const Vector2& other);

	// �����������
	static const Vector3 Left;
	static const Vector3 Right;
	static const Vector3 Forward;
	static const Vector3 Back;
	static const Vector3 Up;
	static const Vector3 Down;
	static const Vector3 One;
	static const Vector3 Zero;

	// �������
	union
	{
		struct
		{
			float X, Y, Z;
		};

		D3DXVECTOR3 NativeVector3;
	};
};