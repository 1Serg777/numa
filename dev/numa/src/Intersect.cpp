#include "Intersect.h"

#include <optional>

namespace numa
{
	Vec3 Sphere::ComputeNormal(const Vec3& point) const
	{
		Vec3 radiusVector = point - center;

		// 1. Assume that 'point' lies on the sphere
		// Vec3 normalVector = radiusVector / radius;

		// 2. Accept any point
		Vec3 normalVector = numa::Normalize(radiusVector);

		return normalVector;
	}

	Plane::Plane(const Vec3& normal, float distance)
		: normal(normal), distance(distance)
	{
	}
	Plane::Plane(const Vec3& normal, const Vec3& point)
		: Plane(normal, Dot(normal, point))
	{
	}

	bool RaySphereHit::HitInFront() const
	{
		if (SingleHit())
		{
			return hitDistanceT1 >= 0.0f;
		}
		else if (DoubleHit())
		{
			bool condition1 = hitDistanceT1 > 0.0f && hitDistanceT2 >= 0.0f;
			bool condition2 = hitDistanceT1 > hitDistanceT2; // t2 is the closest // unnecessary?
			return hit && condition1 && condition2;
		}
		else
		{
			return false;
		}
	}
	bool RaySphereHit::HitBehind() const
	{
		if (SingleHit())
		{
			return hitDistanceT1 < 0.0f;
		}
		else if (DoubleHit())
		{
			bool condition1 = hitDistanceT1 <= 0.0f && hitDistanceT2 < 0.0f;
			bool condition2 = hitDistanceT1 > hitDistanceT2; // t1 is the closest // unnecessary?
			return hit && condition1 && condition2;
		}
		else
		{
			return false;
		}
	}
	bool RaySphereHit::HitInside() const
	{
		if (DoubleHit())
		{
			bool condition1 = hitDistanceT1 > 0.0f && hitDistanceT2 < 0.0f;
			bool condition2 = hitDistanceT1 > hitDistanceT2; // t1 is in front, t2 is behind // unnecessary?

			// In order to determine which t is the closest and which one is the farthest
			// we need to realize that since the ray's origin is inside the sphere and 
			// t tells us the distance along the ray to the intersection point, we can
			// simply compare the absolute values of the two roots. The one that is smaller
			// is the closest intersection.

			return hit && condition1 && condition2;
		}
		else /* if (!hit || SingleHit()) */
		{
			return false;
		}
	}

	bool RaySphereHit::SingleHit() const
	{
		return hit && hitDistanceT2 == std::numeric_limits<float>::infinity();
	}
	bool RaySphereHit::DoubleHit() const
	{
		return hit && !SingleHit();
	}

	bool RayPlaneHit::HitInFront() const
	{
		return hit && hitDistance >= 0.0f;
	}
	bool RayPlaneHit::HitBehind() const
	{
		// return hit && hitDistance < 0.0f;
		return hit && !HitInFront();
	}

	bool IntersectSphere(const Sphere& sphere, const Ray& ray, RaySphereHit& rayHit)
	{
		// We need to solve a quadratic polynomial of 't', where 't' represents
		// the distance along the ray to the point of intersection with the sphere
		// We can have either
		// 1. One intersection point (one root), when the ray is tangent to the sphere at a point
		// 2. Two intersection points (two roots), when the ray intersects the sphere twice:
		//    - when it "enters" the sphere
		//    - when it "leaves" the sphere
		// 3. No intersection points (no roots), which means the ray doesn't intersect the sphere
		//
		// at^2 + bt + c = 0

		rayHit.hitRay = ray;

		Vec3 Os = sphere.center;
		Vec3 Or = ray.GetOrigin();
		Vec3 Dr = ray.GetDirection();

		float radius = sphere.radius;
		float r_sqr = radius * radius;

		float D_dot_D = Dot(Dr, Dr);

		Vec3 Or_minus_Os = Or - Os;

		float a = D_dot_D; // should always be 1
		float b = 2.0f * Dot(Dr, Or_minus_Os);
		float c = Dot(Or_minus_Os, Or_minus_Os) - r_sqr;

		float discriminant = b * b - 4.0f * a * c;

		if (discriminant > 0.0f) // The most frequent scenario
		{
			float discriminant_sqrt = std::sqrtf(discriminant);

			float t1 = (-b + discriminant_sqrt) / (2 * a);
			float t2 = (-b - discriminant_sqrt) / (2 * a);

			rayHit.hitDistanceT1 = t1;
			rayHit.hitDistanceT2 = t2;

			rayHit.hitPointT1 = rayHit.hitRay.GetPoint(rayHit.hitDistanceT1);
			rayHit.hitPointT2 = rayHit.hitRay.GetPoint(rayHit.hitDistanceT2);

			rayHit.hitNormalT1 = sphere.ComputeNormal(rayHit.hitPointT1);
			rayHit.hitNormalT2 = sphere.ComputeNormal(rayHit.hitPointT2);

			rayHit.hit = true;
		}
		else if (discriminant == 0.0f) // Should happen relatively rare
		{
			float t = -b / (2 * a);

			rayHit.hitDistanceT1 = t;

			rayHit.hitPointT1 = rayHit.hitRay.GetPoint(rayHit.hitDistanceT1);
			rayHit.hitNormalT1 = sphere.ComputeNormal(rayHit.hitPointT1);

			rayHit.hit = true;
		}
		else /* if (discriminant < 0.0f) */ // No roots, no intersection
		{
			rayHit.hit = false;
		}

		return rayHit.hit;
	}
	bool IntersectPlane(const Plane& plane, const Ray& ray, RayPlaneHit& rayHit)
	{
		// We need to solve a simple equation of 't', where 't' represents
		// the distance along the ray to the point of intersection with the plane
		// We can have either
		// 1. One intersection, which either hits the front of the plane or its back
		// 2. No intersection, when the denominator in the equation is 0
		//
		// t = Dot((P_0 - Or), n) / (Dr_dot_n)
		// or
		// t = (d - Or_dot_n) / (Dr_dot_n)

		rayHit.hitRay = ray;

		const Vec3& Or = ray.GetOrigin();
		const Vec3& Dr = ray.GetDirection();

		float Dr_dot_n = Dot(Dr, plane.normal);

		if (Dr_dot_n != 0.0f)
		{
			float Or_dot_n = Dot(Or, plane.normal);

			float t = (plane.distance - Or_dot_n) / Dr_dot_n;

			if (Dr_dot_n < 0.0f)
			{
				rayHit.hitFrontFace = true;
			}
			else
			{
				rayHit.hitFrontFace = false;
			}

			rayHit.hitDistance = t;
			rayHit.hitPoint = rayHit.hitRay.GetPoint(rayHit.hitDistance);
			rayHit.hitNormal = plane.normal;
			rayHit.hitUv; // TODO

			rayHit.hit = true;
		}
		else /* if (D_dot_n == 0.0f) */
		{
			rayHit.hit = false;
		}

		return rayHit.hit;
	}
	bool IntersectTriangle(const Triangle& triangle, const Ray& ray, RayTriangleHit& rayHit)
	{
		// TODO
		return false;
	}
}