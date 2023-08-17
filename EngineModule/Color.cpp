#include "pch.h"
#include "Color.h"

const Color Color::Black = Color(0.f, 0.f, 0.f, 1.f);
const Color Color::Blue = Color(0.f, 0.f, 1.f, 1.f);
const Color Color::Clear = Color(0.f, 0.f, 0.f, 0.f);
const Color Color::Cyan = Color(0.f, 1.f, 1.f, 1.f);
const Color Color::Gray = Color(0.5f, 0.5f, 0.5f, 1.f);
const Color Color::Green = Color(0.f, 1.f, 0.f, 1.f);
const Color Color::Grey = Color(0.5f, 0.5f, 0.5f, 1.f);
const Color Color::Magenta = Color(1.f, 0.f, 1.f, 1.f);
const Color Color::Red = Color(1.f, 0.f, 0.f, 1.f);
const Color Color::White = Color(1.f, 1.f, 1.f, 1.f);
const Color Color::Yellow = Color(1.f, 0.92f, 0.016f, 1.f);

Color::Color()
	: NativeColor()
{
}

Color::Color(float r, float g, float b, float a)
	: NativeColor(r, g, b, a)
{
}

Color::Color(const Color& other)
	: NativeColor(other.NativeColor)
{
}

Color Color::Lerp(const Color& c1, const Color& c2, float t)
{
	Color result;
	D3DXColorLerp(&result.NativeColor, &c1.NativeColor, &c2.NativeColor, t);
	return result;
}

Color Color::AdjustContrast(const Color& color, float c)
{
	Color result;
	D3DXColorAdjustContrast(&result.NativeColor, &color.NativeColor, c);
	return result;
}

Color Color::AdjustSaturation(const Color& color, float s)
{
	Color result;
	D3DXColorAdjustSaturation(&result.NativeColor, &color.NativeColor, s);
	return result;
}

float Color::GetGrayScle() const
{
	return (0.299f * R) + (0.587f * G) + (0.114f * B);
}

Color::operator DWORD() const
{
	DWORD dwR = R >= 1.0f ? 0xff : R <= 0.0f ? 0x00 : (DWORD)(R * 255.0f + 0.5f);
	DWORD dwG = G >= 1.0f ? 0xff : G <= 0.0f ? 0x00 : (DWORD)(G * 255.0f + 0.5f);
	DWORD dwB = B >= 1.0f ? 0xff : B <= 0.0f ? 0x00 : (DWORD)(B * 255.0f + 0.5f);
	DWORD dwA = A >= 1.0f ? 0xff : A <= 0.0f ? 0x00 : (DWORD)(A * 255.0f + 0.5f);

	return (dwA << 24) | (dwR << 16) | (dwG << 8) | dwB;
}

Color::operator float* ()
{
	return (float*)&R;
}

Color::operator const float* () const
{
	return (const float*)&R;
}

Color Color::operator+() const
{
	return Color(+R, +G, +B, +A);
}

Color Color::operator-() const
{
	return Color(-R, -G, -B, +A);
}

Color Color::operator+(const Color& other) const
{
	return Color(R + other.R, G + other.G, B + other.B, A + other.A);
}

Color Color::operator-(const Color& other) const
{
	return Color(R - other.R, G - other.G, B - other.B, A - other.A);
}

Color Color::operator*(const float f) const
{
	return Color(R * f, G * f, B * f, A * f);
}

Color Color::operator/(const float f) const
{
	float fInv = 1.f / f;
	return Color(R / fInv, G / fInv, B / fInv, A / fInv);
}

Color& Color::operator+=(const Color& other)
{
	R += other.R;
	G += other.G;
	B += other.B;
	A += other.A;
	return *this;
}

Color& Color::operator-=(const Color& other)
{
	R -= other.R;
	G -= other.G;
	B -= other.B;
	A -= other.A;
	return *this;
}

Color& Color::operator*=(const float f)
{
	R *= f;
	G *= f;
	B *= f;
	A *= f;
	return *this;
}

Color& Color::operator/=(const float f)
{
	float fInv = 1.f / f;
	R /= fInv;
	G /= fInv;
	B /= fInv;
	A /= fInv;
	return *this;
}

bool Color::operator==(const Color& other) const
{
	return R == other.R && G == other.G && B == other.B && A == other.A;
}

bool Color::operator!=(const Color& other) const
{
	return R != other.R || G != other.G || B != other.B || A != other.A;
}
