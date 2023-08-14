#pragma once

struct Vector3;

struct Vector2
{
	// 생성자
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);
	Vector2(const Vector3& other);

	// 멤버함수
	Vector3 ToVector3() const;
	float Angle(const Vector2& other) const;
	float Size() const;
	float SizeSq() const;
	float Distance(const Vector2& other) const;
	void Normalize();
	Vector2 GetNormalize() const;
	Vector2 Min(const Vector2& other) const;
	Vector2 Max(const Vector2& other) const;
	float Dot(const Vector2& other) const;

	// 연산자
	Vector2 operator-();

	Vector2 operator*(const float d) const;
	Vector2 operator/(const float d) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;

	Vector2 operator*=(const float d);
	Vector2 operator/=(const float d);
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);

	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	Vector2 operator=(const Vector3& other);

	// 정적멤버변수
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 One;
	static const Vector2 Zero;

	// 멤버변수
	union
	{
		struct
		{
			float X, Y;
		};

		D3DXVECTOR2 NativeVector2;
	};
};

