#pragma once

#include "Vec.hpp"

#include <cstdint>

namespace numa
{
	template<typename T>
	class Vec<T, 4>
	{
	public:

		using component_type = T;

		// Constructors

		Vec() = default;
		~Vec() = default;

		template<typename U>
		Vec(const U& u);
		template<typename X, typename Y, typename Z, typename W>
		Vec(const X& x, const Y& y, const Z& z, const W& w);

		// Converting constructors

		template<typename U, int S>
		Vec(const Vec<U, S>& v);

		// Operators

		Vec<T, 4> operator-() const;

		template<typename U>
		Vec<T, 4>& operator+=(const Vec<U, 4>& rhs);

		template<typename U>
		Vec<T, 4>& operator*=(const Vec<U, 4>& rhs);

		template<typename U>
		Vec<T, 4>& operator*=(const U& u);

		template<typename U>
		Vec<T, 4>& operator/=(const Vec<U, 4>& rhs);

		template<typename U>
		Vec<T, 4>& operator/=(const U& u);

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
			struct { T x; T y; T z; T w; };
			struct { T r; T g; T b; T a; };
			T components[4];
		};
	};

	// Constructors

	template<typename T>
	template<typename U>
	Vec<T, 4>::Vec(const U& u)
	{
		this->x = static_cast<T>(u);
		this->y = static_cast<T>(u);
		this->z = static_cast<T>(u);
		this->w = static_cast<T>(u);
	}

	template<typename T>
	template<typename X, typename Y, typename Z, typename W>
	Vec<T, 4>::Vec(const X& x, const Y& y, const Z& z, const W& w)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
		this->z = static_cast<T>(z);
		this->w = static_cast<T>(w);
	}

	// Converting constructors

	template<typename T>
	template<typename U, int S>
	Vec<T, 4>::Vec(const Vec<U, S>& v)
	{
		int minDimensions = std::min(4, S);
		for (int i = 0; i < minDimensions; i++)
		{
			components[i] = static_cast<T>(v[i]);
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T>
	Vec<T, 4> Vec<T, 4>::operator-() const
	{
		Vec<T, 4> res{};
		res.x = -this.x;
		res.y = -this.y;
		res.z = -this.z;
		res.w = -this.w;
		return res;
	}

	template<typename T>
	template<typename U>
	Vec<T, 4>& Vec<T, 4>::operator+=(const Vec<U, 4>& rhs)
	{
		this->x += static_cast<T>(rhs.x);
		this->y += static_cast<T>(rhs.y);
		this->z += static_cast<T>(rhs.z);
		this->w += static_cast<T>(rhs.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 4>& Vec<T, 4>::operator*=(const Vec<U, 4>& rhs)
	{
		this->x *= static_cast<T>(rhs.x);
		this->y *= static_cast<T>(rhs.y);
		this->z *= static_cast<T>(rhs.z);
		this->w *= static_cast<T>(rhs.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 4>& Vec<T, 4>::operator*=(const U& u)
	{
		this->x *= static_cast<T>(u);
		this->y *= static_cast<T>(u);
		this->z *= static_cast<T>(u);
		this->w *= static_cast<T>(u);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 4>& Vec<T, 4>::operator/=(const Vec<U, 4>& rhs)
	{
		this->x /= static_cast<T>(rhs.x);
		this->y /= static_cast<T>(rhs.y);
		this->z /= static_cast<T>(rhs.z);
		this->w /= static_cast<T>(rhs.w);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 4>& Vec<T, 4>::operator/=(const U& u)
	{
		this->x /= static_cast<T>(u);
		this->y /= static_cast<T>(u);
		this->z /= static_cast<T>(u);
		this->w /= static_cast<T>(u);
		return *this;
	}

	// 2) Defined as separate functions

	//    ---

	// Common type definitions

	using Vec4 = Vec<float, 4>;
	using dVec4 = Vec<double, 4>;

	using iVec4 = Vec<int, 4>;
	using uVec4 = Vec<unsigned int, 4>;

	using u8Vec4 = Vec<uint8_t, 4>;
	using u16Vec4 = Vec<uint16_t, 4>;
	using u32Vec4 = Vec<uint32_t, 4>;
	using u64Vec4 = Vec<uint64_t, 4>;

	using i8Vec4 = Vec<int8_t, 4>;
	using i16Vec4 = Vec<int16_t, 4>;
	using i32Vec4 = Vec<int32_t, 4>;
	using i64Vec4 = Vec<int64_t, 4>;
}