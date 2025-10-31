#pragma once

#include "Vec.hpp"
#include "Mat.hpp"

namespace numa {

	struct Sphere {
		Vec3  ComputeNormal(const Vec3& point) const;

		Vec3  center{};
		float radius{};
	};

	struct Plane {
		Plane(const Vec3& normal, float distance);
		Plane(const Vec3& normal, const Vec3& point);

		Vec3  normal{};
		float distance{};
	};

	struct Triangle {
		// 1. 2 Vec2 vectors?
		//    For an ABC triangle, the vectors are
		//    B-A and C-A
		// 2. 3 Vec3 points?
		//    For an ABC triangle, the points are
		//    A, B, and C
		Triangle(const numa::Vec3& A, const numa::Vec3& B, const numa::Vec3& C);

		void ComputeNormal();
		Plane GetTrianglePlane() const;

		numa::Vec3 A{};
		numa::Vec3 B{};
		numa::Vec3 C{};

		numa::Vec3 N{};
	};

	struct AABB {
		void InitializeFromMinMax(const numa::Vec3& min, const numa::Vec3& max);

		numa::Vec3 MinPoint() const;
		numa::Vec3 MaxPoint() const;

		std::array<numa::Vec3, 8> GetAABBVertexPositions() const;

		numa::Vec3 center{0.0f};
		numa::Vec3 radius{0.5f};
	};

	struct OBB {
		numa::Mat4 ConstructWorldMatrix() const;

		numa::Vec3 center{0.0f};
		numa::Mat3 rotMat{1.0f};
		numa::Vec3 radius{0.5f};
	};

	// Points must not be collinear, and the order is assumed to be CCW.
	Plane ComputePlane(const numa::Vec3& A, const numa::Vec3& B, const numa::Vec3& C);

	numa::Vec3 ComputeCenterFromMinMax(const numa::Vec3& min, const numa::Vec3& max);
	numa::Vec3 ComputeRadiusFromMinMax(const numa::Vec3& min, const numa::Vec3& max);

	AABB Union(const AABB& A, const AABB& B);

}