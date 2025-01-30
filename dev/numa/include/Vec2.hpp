#pragma once

#include "Vec.hpp"

#include <cstdint>

namespace numa
{
	template<typename T>
	class Vec<T, 2>
	{
	public:

		using component_type = T;

		// Constructors

		Vec() = default;
		~Vec() = default;

		template<typename U>
		Vec(const U& u);
		template<typename X, typename Y>
		Vec(const X& x, const Y& y);

		// Converting constructors

		template<typename U, int S>
		Vec(const Vec<U, S>& v);

		// Operators

		Vec<T, 2> operator-() const;

		template<typename U>
		Vec<T, 2>& operator+=(const Vec<U, 2>& rhs);

		template<typename U>
		Vec<T, 2>& operator-=(const Vec<U, 2>& rhs);

		template<typename U>
		Vec<T, 2>& operator*=(const Vec<U, 2>& rhs);

		template<typename U>
		Vec<T, 2>& operator*=(const U& u);

		template<typename U>
		Vec<T, 2>& operator/=(const Vec<U, 2>& rhs);

		template<typename U>
		Vec<T, 2>& operator/=(const U& u);

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
			struct { T x; T y; };
			struct { T u; T v; };
			T components[2];
		};
	};

	// Constructors

	template<typename T>
	template<typename U>
	Vec<T, 2>::Vec(const U& u)
	{
		this->x = static_cast<T>(u);
		this->y = static_cast<T>(u);
	}

	template<typename T>
	template<typename X, typename Y>
	Vec<T, 2>::Vec(const X& x, const Y& y)
	{
		this->x = static_cast<T>(x);
		this->y = static_cast<T>(y);
	}

	// Converting constructors

	template<typename T>
	template<typename U, int S>
	Vec<T, 2>::Vec(const Vec<U, S>& v)
	{
		// components[0] = components[1] = T(0);
		x = y = T(0);

		int minDimensions = std::min(2, S);
		for (int i = 0; i < minDimensions; i++)
		{
			components[i] = static_cast<T>(v[i]);
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T>
	Vec<T, 2> Vec<T, 2>::operator-() const
	{
		Vec<T, 2> res{};
		res.x = -this.x;
		res.y = -this.y;
		return res;
	}

	template<typename T>
	template<typename U>
	Vec<T, 2>& Vec<T, 2>::operator+=(const Vec<U, 2>& rhs)
	{
		this->x += static_cast<T>(rhs.x);
		this->y += static_cast<T>(rhs.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 2>& Vec<T, 2>::operator-=(const Vec<U, 2>& rhs)
	{
		this->x -= static_cast<T>(rhs.x);
		this->y -= static_cast<T>(rhs.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 2>& Vec<T, 2>::operator*=(const Vec<U, 2>& rhs)
	{
		this->x *= static_cast<T>(rhs.x);
		this->y *= static_cast<T>(rhs.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 2>& Vec<T, 2>::operator*=(const U& u)
	{
		this->x *= static_cast<T>(u);
		this->y *= static_cast<T>(u);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 2>& Vec<T, 2>::operator/=(const Vec<U, 2>& rhs)
	{
		this->x /= static_cast<T>(rhs.x);
		this->y /= static_cast<T>(rhs.y);
		return *this;
	}

	template<typename T>
	template<typename U>
	Vec<T, 2>& Vec<T, 2>::operator/=(const U& u)
	{
		this->x /= static_cast<T>(u);
		this->y /= static_cast<T>(u);
		return *this;
	}

	// 2) Defined as separate functions

	//    ---

	// Common type definitions

	using Vec2 = Vec<float, 2>;
	using dVec2 = Vec<double, 2>;

	using iVec2 = Vec<int, 2>;
	using uVec2 = Vec<unsigned int, 2>;

	using u8Vec2 = Vec<uint8_t, 2>;
	using u16Vec2 = Vec<uint16_t, 2>;
	using u32Vec2 = Vec<uint32_t, 2>;
	using u64Vec2 = Vec<uint64_t, 2>;

	using i8Vec2 = Vec<int8_t, 2>;
	using i16Vec2 = Vec<int16_t, 2>;
	using i32Vec2 = Vec<int32_t, 2>;
	using i64Vec2 = Vec<int64_t, 2>;
}