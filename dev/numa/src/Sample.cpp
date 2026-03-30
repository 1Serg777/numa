#include "Sample.h"

#include "Numa.h"

#include <cmath>

namespace numa {

	Vec3 SampleHemisphereUniform(const Vec2& xi, UpAxisConfig upAxis) {
		return SampleHemisphereUniform(xi.x, xi.y, upAxis);
	}
	Vec3 SampleHemisphereUniform(float xi1, float xi2, UpAxisConfig upAxis) {
		float phi = xi1 * numa::TwoPi<float>();
		float cosTheta = xi2;
		float sinTheta = std::sqrtf(1.0f - xi2 * xi2);
		return numa::Vec3{
			std::cos(phi) * sinTheta,
			cosTheta,
			std::sin(phi) * sinTheta
		};
	}

	Vec3 SampleHemisphereCosWeight(const Vec2& xi, UpAxisConfig upAxis) {
		return SampleHemisphereCosWeight(xi.x, xi.y, upAxis);
	}
	Vec3 SampleHemisphereCosWeight(float xi1, float xi2, UpAxisConfig upAxis) {
		float phi = xi1 * numa::TwoPi<float>();
		float cosTheta = std::sqrtf(xi2);
		float sinTheta = std::sqrtf(1.0f - xi2);
		return numa::Vec3{
			std::cos(phi) * sinTheta,
			cosTheta,
			std::sin(phi) * sinTheta
		};
	}

}