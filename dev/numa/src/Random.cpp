#include "Random.h"

#include <random>

namespace numa
{
	double RandomDouble()
	{
		// Returns a random real in the [0,1) range.
		// return rand() / (RAND_MAX + 1.0); // C-style alternative

		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator{}; // static std::mt19937 generator;
		return distribution(generator);
	}
	double RandomDouble(double min, double max)
	{
		// Returns a random real in [min,max).
		return min + (max - min) * RandomDouble();
	}

	float RandomFloat()
	{
		return static_cast<float>(RandomDouble());
	}
	float RandomFloat(double min, double max)
	{
		return static_cast<float>(RandomDouble(min, max));
	}

	Vec2 RandomVec2()
	{
		return Vec2{
			RandomDouble(),
			RandomDouble()
		};
	}
	Vec2 RandomVec2(double min, double max)
	{
		return Vec2{
			RandomDouble(min, max),
			RandomDouble(min, max)
		};
	}

	Vec3 RandomVec3()
	{
		return Vec3{
			RandomDouble(),
			RandomDouble(),
			RandomDouble()
		};
	}
	Vec3 RandomVec3(double min, double max)
	{
		return Vec3{
			RandomDouble(min, max),
			RandomDouble(min, max),
			RandomDouble(min, max)
		};
	}

	Vec2 RandomInUnitSquare()
	{
		return RandomVec2(-1.0, 1.0);
	}
	Vec2 RandomInSquare(double side)
	{
		return RandomInUnitSquare() * side;
	}

	Vec3 RandomInUnitCube()
	{
		return RandomVec3(-1.0, 1.0f);
	}
	Vec3 RandomInCube(double side)
	{
		return RandomInUnitCube() * side;
	}

	Vec3 RandomInUnitSphere()
	{
		while (true)
		{
			Vec3 randomVec3 = RandomInUnitCube();
			if (Length2(randomVec3) <= 1.0f)
				return randomVec3;
		}
	}
	Vec3 RandomOnUnitSphere()
	{
		return Normalize(RandomInUnitCube());
	}
	Vec3 RandomInSphere(double radius)
	{
		return RandomInUnitSphere() * radius;
	}
}