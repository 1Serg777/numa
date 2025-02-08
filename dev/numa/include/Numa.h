#pragma once

#include "Vec.hpp"

#include <cmath>
#include <type_traits>

namespace numa
{
	namespace internal
	{
		double PiConst();
		double PiOverTwoConst();
		double TwoPiConst();

		double ToRad(double deg);
		double ToDeg(double rad);
	}

	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T Pi()
	{
		return static_cast<T>(internal::PiConst());
	}
	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T PiOverTwo()
	{
		return static_cast<T>(internal::PiOverTwoConst());
	}
	template<
		typename T,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T TwoPi()
	{
		return static_cast<T>(internal::TwoPiConst());
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