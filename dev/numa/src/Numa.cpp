#include "Numa.h"

#define _USE_MATH_DEFINES
#include <cmath>

namespace numa {

	namespace constants {

		static constexpr double Pi       {3.14159265358979323846264338327950288};
		static constexpr double PiOverTwo{Pi / 2.0};
		static constexpr double TwoPi    {2.0 * Pi};

		// Pi / 180
		// static constexpr double RadConversionFactor{0.01745329251994329576923690768489};
		static constexpr double RadConversionFactor{Pi / 180.0};
		// 180 / Pi
		// static constexpr double DegConversionFactor{57.295779513082320876798154814105};
		static constexpr double DegConversionFactor{180.0 / Pi};

	}

	namespace internal {

		constexpr double PiConst() {
			return constants::Pi;
		}
		constexpr double PiOverTwoConst() {
			return constants::PiOverTwo;
		}
		constexpr double TwoPiConst() {
			return constants::TwoPi;
		}
	
		double ToRad(double deg) {
			return deg * constants::RadConversionFactor;
		}
		double ToDeg(double rad) {
			return rad * constants::DegConversionFactor;
		}

	}
}