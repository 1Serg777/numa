#include "Ray.h"

namespace numa {

	Ray::Ray(const Vec3& origin, const Vec3& direction)
		: origin(origin), direction(direction) {
	}

	numa::Vec3 Ray::GetPoint(float distance) const {
		return origin + distance * direction;
	}

	const Vec3& Ray::GetOrigin() const {
		return origin;
	}
	const Vec3& Ray::GetDirection() const {
		return direction;
	}

}