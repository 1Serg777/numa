#pragma once

#include "Ray.h"
#include "Vec3.hpp"
#include "Vec2.hpp"

#include <limits>

namespace numa
{
	struct Sphere
	{
		Vec3  ComputeNormal(const Vec3& point) const;

		Vec3  center{};
		float radius{};
	};

	struct Plane
	{
		Plane(const Vec3& normal, float distance);
		Plane(const Vec3& normal, const Vec3& point);

		Vec3  normal{};
		float distance{};
	};

	struct Triangle
	{
		Vec3 normal{};

		// 1. 2 Vec2 vectors?
		//    For an ABC triangle, the vectors are
		//    B-A and C-A

		// 2. 3 Vec3 points?
		//    For an ABC triangle, the points are
		//    A, B, and C
	};

	// 1) When there's only one hit:
	//    - If the ray is 'in front', T1 contains the result (positive) (or 0?)
	//    - If the ray is 'behind',   T1 contains the result (negative) (or 0?)
	//    - If the ray is 'inside'    we can't have only one intersection when the ray is inside the sphere
	// 2) When there're two hits:
	//    - If the ray is 'in front', T2 is the closest and T1 is the farthest
	//    - If the ray is 'behind',   T1 is the closest and T2 is the farthest
	//    - If the ray is 'inside',   The T root with smallest absolute value is the closest (either in front or behind)
	//                                The other one therefore is the farthest
	struct RaySphereHit
	{
		bool  HitInFront() const;
		bool  HitBehind() const;
		bool  HitInside() const;

		bool  SingleHit() const;
		bool  DoubleHit() const;

		Ray   hitRay{ Vec3{ 0.0f }, Vec3{ 0.0f } };

		Vec3  hitPointT1{ 0.0f };
		Vec3  hitPointT2{ 0.0f };

		Vec3  hitNormalT1{ 0.0f };
		Vec3  hitNormalT2{ 0.0f };

		Vec2  hitUvT1{ 0.0f };
		Vec2  hitUvT2{ 0.0f };

		// The '+ Discriminant' root
		float hitDistanceT1{ std::numeric_limits<float>::infinity() };
		// The '- Discriminant' root
		float hitDistanceT2{ std::numeric_limits<float>::infinity() };

		bool  hit{ false };
	};

	struct RayPlaneHit
	{
		bool  HitInFront() const;
		bool  HitBehind() const;

		Ray   hitRay{ Vec3{ 0.0f }, Vec3{ 0.0f } };

		Vec3  hitPoint{ 0.0f };
		Vec3  hitNormal{ 0.0f };
		Vec2  hitUv{ 0.0f };

		float hitDistance{ std::numeric_limits<float>::infinity() };

		bool  hit{ false };
		bool  hitFrontFace{ false };
	};

	struct RayTriangleHit
	{
		// TODO
	};

	bool IntersectSphere(const Sphere& sphere, const Ray& ray, RaySphereHit& rayHit);
	bool IntersectPlane(const Plane& plane, const Ray& ray, RayPlaneHit& rayHit);
	bool IntersectTriangle(const Triangle& triangle, const Ray& ray, RayTriangleHit& rayHit);
}