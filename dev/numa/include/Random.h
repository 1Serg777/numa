#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"

namespace numa
{
	// [0, 1)
	double RandomDouble();
	double RandomDouble(double min, double max);

	// [0, 1)
	float RandomFloat();
	float RandomFloat(double min, double max);

	// [0, 1) for each component
	Vec2 RandomVec2();
	Vec2 RandomVec2(double min, double max);

	// [0, 1) for each component
	Vec3 RandomVec3();
	Vec3 RandomVec3(double min, double max);

	// [-1, 1) for each component
	Vec2 RandomInUnitSquare();
	// [-side, side) for each component
	Vec2 RandomInSquare(double side);

	// [-1, 1) for each component
	Vec3 RandomInUnitCube();
	// [-side, side) for each component
	Vec3 RandomInCube(double side);

	// [-1, 1) for each component with the condition
	// that the length of the resulting vector is <= 1.0
	Vec3 RandomInUnitSphere();
	// [-1, 1) for each component with the condition
	// that the length of the resulting vector is == 1.0
	Vec3 RandomOnUnitSphere();
	// [-radius, radius) for each component with the condition
	// that the length of the resulting vector is <= radius
	Vec3 RandomInSphere(double radius);
}