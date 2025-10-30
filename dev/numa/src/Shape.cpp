#include "Shape.h"

namespace numa {

	Vec3 Sphere::ComputeNormal(const Vec3& point) const {
		Vec3 radiusVector = point - center;
		// 1. Assume that 'point' lies on the sphere
		// Vec3 normalVector = radiusVector / radius;
		// 2. Accept any point
		Vec3 normalVector = numa::Normalize(radiusVector);
		return normalVector;
	}

	Plane::Plane(const Vec3& normal, float distance)
		: normal(normal), distance(distance) {
	}
	Plane::Plane(const Vec3& normal, const Vec3& point)
		: Plane(normal, Dot(normal, point)) {
	}

	Triangle::Triangle(const numa::Vec3& A, const numa::Vec3& B, const numa::Vec3& C)
		: A(A), B(B), C(C) {
		ComputeNormal();
	}

	void Triangle::ComputeNormal() {
		numa::Vec3 AB = B - A;
		numa::Vec3 AC = C - A;

		N = numa::Normalize(numa::Cross(AB, AC));
	}

	Plane Triangle::GetTrianglePlane() const {
		return Plane{ComputePlane(A, B, C)};
	}

	Plane ComputePlane(const numa::Vec3& A, const numa::Vec3& B, const numa::Vec3& C) {
		numa::Vec3 AB = B - A;
		numa::Vec3 AC = C - A;
		numa::Vec3 N = numa::Normalize(numa::Cross(AB, AC));
		Plane plane{N, A};
		return plane;
	}

	numa::Vec3 ComputeCenterFromMinMax(const numa::Vec3& min, const numa::Vec3& max) {
		// or
		// return max - ComputeRadiusFromMinMax(min, max);
		return min + ComputeRadiusFromMinMax(min, max);
	}
	numa::Vec3 ComputeRadiusFromMinMax(const numa::Vec3& min, const numa::Vec3& max) {
		return (max - min) * 0.5f;
	}

	AABB Union(const AABB& A, const AABB& B) {
		AABB C{};
		numa::Vec3 newMin = numa::Min(A.MinPoint(), B.MinPoint());
		numa::Vec3 newMax = numa::Max(A.MaxPoint(), B.MaxPoint());
		C.InitializeFromMinMax(newMin, newMax);
		return C;
	}

}