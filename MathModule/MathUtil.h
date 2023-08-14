#pragma once

#include "pch.h"

// 출처 : https://github.com/onlybooks/gamemath/blob/main/Source/Runtime/Math/Public/MathUtil.h

struct Math
{
	static constexpr float PI = 3.14159265359f;
	static constexpr float TwoPI = { 2.f * PI };
	static constexpr float HalfPI = { 1.57079632679f };
	static constexpr float InvPI = { 0.31830988618f };

	static inline float Rad2Deg(float radian)
	{
		return radian * 180 / PI;
	}

	static inline float Deg2Rad(float degree)
	{
		return degree * PI / 180;
	}

	// 언리얼 엔진 코드에서 가져옴. 지정된 각도에 대한 두 삼각함수를 함께 가져오는 함수. 
	static inline constexpr void GetSinCosRad(float* const outSin, float* const outCos, float radian)
	{
		// Copied from UE4 Source Code
		// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
		float quotient = (InvPI * 0.5f) * radian;
		if (radian >= 0.0f)
		{
			quotient = (float)((int)(quotient + 0.5f));
		}
		else
		{
			quotient = (float)((int)(quotient - 0.5f));
		}
		float y = radian - (2.0f * PI) * quotient;

		// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
		float sign = 0.f;
		if (y > HalfPI)
		{
			y = PI - y;
			sign = -1.0f;
		}
		else if (y < -HalfPI)
		{
			y = -PI - y;
			sign = -1.0f;
		}
		else
		{
			sign = +1.0f;
		}

		float y2 = y * y;

		// 11-degree minimax approximation
		*outSin = (((((-2.3889859e-08f * y2 + 2.7525562e-06f) * y2 - 0.00019840874f) * y2 + 0.0083333310f) * y2 - 0.16666667f) * y2 + 1.0f) * y;

		// 10-degree minimax approximation
		float p = ((((-2.6051615e-07f * y2 + 2.4760495e-05f) * y2 - 0.0013888378f) * y2 + 0.041666638f) * y2 - 0.5f) * y2 + 1.0f;
		*outCos = sign * p;
	}

	static inline constexpr void GetSinCos(float* const outSin, float* const outCos, float degree)
	{
		if (degree == 0.f)
		{
			*outSin = 0.f;
			*outCos = 1.f;
		}
		else if (degree == 90.f)
		{
			*outSin = 1.f;
			*outCos = 0.f;
		}
		else if (degree == 180.f)
		{
			*outSin = 0.f;
			*outCos = -1.f;
		}
		else if (degree == 270.f)
		{
			*outSin = -1.f;
			*outCos = 0.f;
		}
		else
		{
			GetSinCosRad(outSin, outCos, Math::Deg2Rad(degree));
		}
	}

	// 언리얼 엔진 코드에서 가져옴. 고속 역제곱근 공식
	static inline float InvSqrt(float value)
	{
		// Performs two passes of Newton-Raphson iteration on the hardware estimate
		//    v^-0.5 = x
		// => x^2 = v^-1
		// => 1/(x^2) = v
		// => F(x) = x^-2 - v
		//    F'(x) = -2x^-3

		//    x1 = x0 - F(x0)/F'(x0)
		// => x1 = x0 + 0.5 * (x0^-2 - Vec) * x0^3
		// => x1 = x0 + 0.5 * (x0 - Vec * x0^3)
		// => x1 = x0 + x0 * (0.5 - 0.5 * Vec * x0^2)
		//
		// This final form has one more operation than the legacy factorization (X1 = 0.5*X0*(3-(Y*X0)*X0)
		// but retains better accuracy (namely InvSqrt(1) = 1 exactly).

		const __m128 fOneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float temp;

		Y0 = _mm_set_ss(value);
		X0 = _mm_rsqrt_ss(Y0);	// 1/sqrt estimate (12 bits)
		FOver2 = _mm_mul_ss(Y0, fOneHalf);

		// 1st Newton-Raphson iteration
		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		// 2nd Newton-Raphson iteration
		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(fOneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&temp, X2);
		return temp;
	}
};
