#pragma once

struct Color
{
	// 생성자
	Color();
	Color(float r, float g, float b, float a);
	Color(const Color& other);

	// 정적멤버함수
	static Color Lerp(const Color& c1, const Color& c2, float t);
	static Color AdjustContrast(const Color& color, float c);
	static Color AdjustSaturation(const Color& color, float s);

	// 멤버함수
	float GetGrayScle() const;

	// 연산자
	operator DWORD() const;
	operator float* ();
	operator const float* () const;

	Color operator+() const;
	Color operator-() const;

	Color operator+(const Color& other) const;
	Color operator-(const Color& other) const;
	Color operator*(const float f) const;
	Color operator/(const float f) const;

	Color& operator+=(const Color& other);
	Color& operator-=(const Color& other);
	Color& operator*=(const float f);
	Color& operator/=(const float f);

	bool operator==(const Color& other) const;
	bool operator!=(const Color& other) const;

	// 정적멤버변수
	static const Color Black;
	static const Color Blue;
	static const Color Clear;
	static const Color Cyan;
	static const Color Gray;
	static const Color Green;
	static const Color Grey;
	static const Color Magenta;
	static const Color Red;
	static const Color White;
	static const Color Yellow;

	// 멤버변수
	union
	{
		struct
		{
			float R, G, B, A;
		};

		D3DXCOLOR NativeColor;
	};

};

