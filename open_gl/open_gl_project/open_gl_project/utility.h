#pragma once

class Utility
{
public:
	template <typename T>
	static T Clamp(T value, T min, T max);
	template <typename T>
	static T Lerp(T from, T to, T rate);
};

template<typename T>
inline T Utility::Clamp(T value, T min, T max)
{
	if (value >= max) {
		return max;
	}
	else if (value <= min)
	{
		return min;
	}
	return value;
}

template<typename T>
inline T Utility::Lerp(T from, T to, T rate)
{
	return from + rate * (to - from);
}
