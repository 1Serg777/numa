#pragma once

#include "Vec.hpp"

#include <cstdint>

namespace numa
{
	template<typename T>
	class Vec<T, 3>
	{
	public:

		using component_type = T;

		// Constructors

		Vec() = default;
		~Vec() = default;

		template<typename U>
		Vec(const U& u);
		template<typename U, typename V, typename W>
		Vec(const U& x, const V& y, const W& w);

		// Converting constructors

		template<typename U, int S>
		Vec(const Vec<U, S>& v);

		// Operators

		Vec<T, 3> operator-() const;

		template<typename U>
		Vec<T, 3>& operator+=(const Vec<U, 3>& rhs);

		template<typename U>
		Vec<T, 3>& operator*=(const Vec<U, 3>& rhs);

		template<typename U>
		Vec<T, 3>& operator*=(const U& u);

		template<typename U>
		Vec<T, 3>& operator/=(const Vec<U, 3>& rhs);

		template<typename U>
		Vec<T, 3>& operator/=(const U& u);

		T& operator[](int idx)
		{
			return components[idx];
		}
		const T& operator[](int idx) const
		{
			return components[idx];
		}

		T* Data()
		{
			return components;
		}
		const T* Data() const
		{
			return components;
		}

		union
		{
			struct { T x; T y; T z };
			struct { T r; T g; T b };
			T components[3];
		};
	};

	// Constructors

	template<typename T>
	template<typename U>
	Vec<T, 3>::Vec(const U& u)
	{
		this->x = static_cast<T>(u);
		this->y = static_cast<T>(u);
		this->z = static_cast<T>(u);
	}

	template<typename T>
	template<typename U, typename V, typename W>
	Vec<T, 3>::Vec(const U& x, const V& y, const W& w)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
		this->z = static_cast<T>(w);
	}

	// Converting constructors

	template<typename T>
	template<typename U, int S>
	Vec<T, 3>::Vec(const Vec<U, S>& v)
	{
		int minDimensions = std::min(3, S);
		for (int i = 0; i < minDimensions; i++)
		{
			components[i] = static_cast<T>(v[i]);
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T>
	Vec<T, 3> Vec<T, 3>::operator-() const
	{
		Vec<T, 3> res{};
		res.x = -this.x;
		res.y = -this.y;
		res.z = -this.z;
		return res;
	}

	template<typename T>
	template<typename U>
	Vec<T, 3>& Vec<T, 3>::operator+=(const Vec<U, 3>& rhs)
	{
		this->x += static_cast<T>(rhs.x);
		this->y += static_cast<T>(rhs.y);
		this->z += static_cast<T>(rhs.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 3>& Vec<T, 3>::operator*=(const Vec<U, 3>& rhs)
	{
		this->x *= static_cast<T>(rhs.x);
		this->y *= static_cast<T>(rhs.y);
		this->z *= static_cast<T>(rhs.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 3>& Vec<T, 3>::operator*=(const U& u)
	{
		this->x *= static_cast<T>(u);
		this->y *= static_cast<T>(u);
		this->z *= static_cast<T>(u);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 3>& Vec<T, 3>::operator/=(const Vec<U, 3>& rhs)
	{
		this->x /= static_cast<T>(rhs.x);
		this->y /= static_cast<T>(rhs.y);
		this->z /= static_cast<T>(rhs.z);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 3>& Vec<T, 3>::operator/=(const U& u)
	{
		this->x /= static_cast<T>(u);
		this->y /= static_cast<T>(u);
		this->z /= static_cast<T>(u);
		return *this;
	}

	// 2) Defined as separate functions

	//    ---

	// Common type definitions

	using Vec3 = Vec<float, 3>;
	using dVec3 = Vec<double, 3>;

	using iVec3 = Vec<int, 3>;
	using uVec3 = Vec<unsigned int, 3>;

	using u8Vec3 = Vec<uint8_t, 3>;
	using u16Vec3 = Vec<uint16_t, 3>;
	using u32Vec3 = Vec<uint32_t, 3>;
	using u64Vec3 = Vec<uint64_t, 3>;

	using i8Vec3 = Vec<int8_t, 3>;
	using i16Vec3 = Vec<int16_t, 3>;
	using i32Vec3 = Vec<int32_t, 3>;
	using i64Vec3 = Vec<int64_t, 3>;
}