#pragma once

#include "Vec.hpp"
#include "Mat.hpp"

#include <cmath>

namespace numa {

	template<typename T>
	Mat<T, 4, 4> Scale(const Mat<T, 4, 4>& frame, const numa::Vec<T, 3>& scale) {
		return Mat<T, 4, 4>{
			frame[0] * scale.x,
			frame[1] * scale.y,
			frame[2] * scale.z,
			frame[3]
		};
	}

	// Yaw-Pitch-Roll Rotation

	template<typename T>
	Mat<T, 3, 3> RotateYawPitchRoll(const numa::Vec<T, 3>& rot) {
		return RotateYaw(rot.y) * RotatePitch(rot.x) * RotateRoll(rot.z);
	}

	template<typename T>
	Mat<T, 3, 3> RotateYaw(const T& yaw) {
		return Mat<T, 3, 3> {
			Vec<T, 3>{std::cos(yaw), 0, -std::sin(yaw)}, // column #0
			Vec<T, 3>{0, 1, 0},                          // column #1
			Vec<T, 3>{std::sin(yaw), 0,  std::cos(yaw)}, // column #2
		};
	}
	template<typename T>
	Mat<T, 3, 3> RotatePitch(const T& pitch) {
		return Mat<T, 3, 3> {
			Vec<T, 3>{1, 0, 0},                              // column #0
			Vec<T, 3>{0,  std::cos(pitch), std::sin(pitch)}, // column #1
			Vec<T, 3>{0, -std::sin(pitch), std::cos(pitch)}, // column #2
		};
	}
	template<typename T>
	Mat<T, 3, 3> RotateRoll(const T& roll) {
		return Mat<T, 3, 3> {
			Vec<T, 3>{ std::cos(roll), std::sin(roll), 0}, // column #0
			Vec<T, 3>{-std::sin(roll), std::cos(roll), 0}, // column #1
			Vec<T, 3>{0, 0, 1},                            // column #2
		};
	}

	// Angle-Axis Rotation
	// TODO

	template<typename T>
	Mat<T, 4, 4> Translate(const Mat<T, 4, 4>& frame, const numa::Vec<T, 3>& translate) {
		return Mat<T, 4, 4>{
			frame[0],
			frame[1],
			frame[2],
			// frame[3] + numa::Vec<T, 4>(translate, 0)
			frame * numa::Vec<T, 4>(translate, 1)
		};
	}

}