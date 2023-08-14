#pragma once

struct Math
{
	static constexpr float PI = 3.14159265359f;

	inline static float Rad2Deg(float radian)
	{
		return radian * 180 / PI;
	}

	inline static float Deg2Rad(float degree)
	{
		return degree * PI / 180;
	}
};
