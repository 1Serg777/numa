#pragma once

#include "Vec.hpp"

namespace numa {

	class Ray {
	public:
		Ray() = default;
		Ray(const Vec3& origin, const Vec3& direction);

		numa::Vec3 GetPoint(float distance) const;

		const Vec3& GetOrigin() const;
		const Vec3& GetDirection() const;

	private:
		Vec3 origin{};
		Vec3 direction{};
	};

}