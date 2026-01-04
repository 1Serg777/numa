#pragma once

#include <type_traits>

namespace numa {

	namespace internal {
		constexpr double PiConst();
		constexpr double PiOverTwoConst();
		constexpr double TwoPiConst();

		double ToRad(double deg);
		double ToDeg(double rad);
	}

	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	constexpr T Pi() {
		// return static_cast<T>(internal::PiConst());
		return static_cast<T>(3.14159265358979323846264338327950288);
	}
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	constexpr T PiOverTwo() {
		// return static_cast<T>(internal::PiOverTwoConst());
		return static_cast<T>(3.14159265358979323846264338327950288 / 2.0);
	}
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	constexpr T TwoPi() {
		// return static_cast<T>(internal::TwoPiConst());
		return static_cast<T>(2.0 * 3.14159265358979323846264338327950288);
	}

	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T Rad(T deg) {
		// return static_cast<T>(internal::ToRad(static_cast<T>(deg)));
		// static constexpr double RadConversionFactor{0.01745329251994329576923690768489};
		static constexpr double conversionFactor = 3.14159265358979323846264338327950288 / 180.0;
		return static_cast<T>(deg * conversionFactor);
	}
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	T Deg(T rad) {
		// return static_cast<T>(internal::ToDeg(static_cast<T>(deg)));
		// static constexpr double DegConversionFactor{57.295779513082320876798154814105};
		static constexpr double conversionFactor = 180.0 / 3.14159265358979323846264338327950288;
		return static_cast<T>(rad * conversionFactor);
	}

}