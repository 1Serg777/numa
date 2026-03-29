#include "Sample.h"

namespace numa {

	Vec3 SampleHemisphereUniform(const Vec2& xi, UpAxisConfig upAxis) {
		return SampleHemisphereUniform(xi.x, xi.y, upAxis);
	}
	Vec3 SampleHemisphereUniform(float xi1, float xi2, UpAxisConfig upAxis) {
		// TODO:
		return Vec3();
	}

	Vec3 SampleHemisphereCosWeight(const Vec2& xi, UpAxisConfig upAxis) {
		return SampleHemisphereCosWeight(xi.x, xi.y, upAxis);
	}
	Vec3 SampleHemisphereCosWeight(float xi1, float xi2, UpAxisConfig upAxis) {
		// TODO:
		return Vec3();
	}

}