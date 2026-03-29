#pragma once

#include "Vec.hpp"

namespace numa {

	enum class UpAxisConfig {
		Y_UP, // Default
		Z_UP
	};

	Vec3 SampleHemisphereUniform(const Vec2& xi, UpAxisConfig upAxis = UpAxisConfig::Y_UP);
	Vec3 SampleHemisphereUniform(float xi1, float xi2, UpAxisConfig upAxis = UpAxisConfig::Y_UP);

	Vec3 SampleHemisphereCosWeight(const Vec2& xi, UpAxisConfig upAxis = UpAxisConfig::Y_UP);
	Vec3 SampleHemisphereCosWeight(float xi1, float xi2, UpAxisConfig upAxis = UpAxisConfig::Y_UP);

}