#pragma once

#include "Vec.hpp"
#include "Mat.hpp"

#include <cmath>

namespace numa {

	template<typename T>
	Mat<T, 3, 3> EulerAnglesPitch(const T& pitch) {
		return Mat<T, 3, 3>{
			// Columns
			numa::Vec<T, 3>{1.0, 0.0, 0.0},
			numa::Vec<T, 3>{0, std::cos(pitch), std::sin(pitch)},
			numa::Vec<T, 3>{0, -std::sin(pitch), std::cos(pitch)}
		};
	}
	template<typename T>
	Mat<T, 3, 3> EulerAnglesYaw(const T& yaw) {
		return Mat<T, 3, 3>{
			// Columns
			numa::Vec<T, 3>{std::cos(yaw), 0, -std::sin(yaw)},
			numa::Vec<T, 3>{0, 1, 0},
			numa::Vec<T, 3>{std::sin(yaw), 0, std::cos(yaw)}
		};
	}
	template<typename T>
	Mat<T, 3, 3> EulerAnglesRoll(const T& roll) {
		return Mat<T, 3, 3>{
			// Columns
			numa::Vec<T, 3>{std::cos(roll), std::sin(roll), 0},
			numa::Vec<T, 3>{-std::sin(roll), std::cos(roll), 0},
			numa::Vec<T, 3>{0, 0, 1}
		};
	}

	template<typename T>
	Mat<T, 3, 3> EulerAnglesRotate(const T& pitch, const T& yaw, const T& roll) {
		numa::Mat3 p = EulerAnglesPitch(pitch);
		numa::Mat3 y = EulerAnglesYaw(yaw);
		numa::Mat3 r = EulerAnglesRoll(roll);
		numa::Mat3 R = y * p * r;
		return R;
	}
	template<typename T>
	Mat<T, 3, 3> EulerAnglesRotate(const Vec<T, 3>& rot) {
		return EulerAnglesRotate(rot.x, rot.y, rot.z);
	}

}