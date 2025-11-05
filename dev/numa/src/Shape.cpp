#include "Shape.h"

#include <array>

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

	void AABB::InitializeFromMinMax(const numa::Vec3& min, const numa::Vec3& max) {
		this->center = ComputeCenterFromMinMax(min, max);
		this->radius = ComputeRadiusFromMinMax(min, max);
	}

	numa::Vec3 AABB::MinPoint() const {
		return center - radius;
	}
	numa::Vec3 AABB::MaxPoint() const {
		return center + radius;
	}

	std::array<numa::Vec3, 8> AABB::GetAABBVertexPositions() const {
		std::array<numa::Vec3, 8> vertexPositions{};
		numa::Vec3 min = MinPoint();
		numa::Vec3 max = MaxPoint();

		vertexPositions[0] = numa::Vec3{min.x, min.y, min.z};
		vertexPositions[1] = numa::Vec3{min.x, min.y, max.z};

		vertexPositions[2] = numa::Vec3{min.x, max.y, min.z};
		vertexPositions[3] = numa::Vec3{min.x, max.y, max.z};

		vertexPositions[4] = numa::Vec3{max.x, min.y, min.z};
		vertexPositions[5] = numa::Vec3{max.x, min.y, max.z};

		vertexPositions[6] = numa::Vec3{max.x, max.y, min.z};
		vertexPositions[7] = numa::Vec3{max.x, max.y, max.z};

		return vertexPositions;
	}

	numa::Mat4 OBB::ConstructWorldMatrix() const {
		// Scale is only needed when we're rendering OBBs using the unit cube.
		// numa::Mat4 scale = numa::Scale(numa::Mat4{1.0f}, this->radius);
		numa::Mat4 world = this->rotMat;
		world[3] = numa::Vec4{this->center, 1.0f};
		return world;
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