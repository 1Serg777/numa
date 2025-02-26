#pragma once

#include "Vec.hpp"

#include <cmath>
#include <type_traits>

namespace numa
{
	namespace internal
	{
		constexpr double PiConst();
		constexpr double PiOverTwoConst();
		constexpr double TwoPiConst();

		double ToRad(double deg);
		double ToDeg(double rad);
	}

	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	constexpr T Pi()
	{
		return static_cast<T>(3.1415926535897932384626433832795);		
	}

	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	constexpr T PiOverTwo()
	{
		return static_cast<T>(Pi<double>() / 2.0);
	}

	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	constexpr T TwoPi()
	{
		return static_cast<T>(2.0 * Pi<double>());
	}

	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T Rad(T deg)
	{
		return static_cast<T>(internal::ToRad(static_cast<T>(deg)));
	}

	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T Deg(T deg)
	{
		return static_cast<T>(internal::ToDeg(static_cast<T>(deg)));
	}
}