#pragma once
#include <cmath>

namespace kiko
{
	constexpr float Pi = 3.14159265359f; //constexpr is a compile time conversion
	constexpr float TwoPi = 6.28318530718f;
	constexpr float HalfPi = 1.57079632679f;

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }


	inline float Wrap(int value, int max)
	{
		return (value, max) + ((value < 0) ? max : 0);
	}
	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T>
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}
	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max)
	{
		if (min > max) std::swap(min, max);

		if (value < min) value = min;
		else if (value > max) value = max;

		return value;
	}
}