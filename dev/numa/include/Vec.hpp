#pragma once

#include <algorithm>
#include <cmath>

namespace numa
{
	template<typename T, int S>
	class Vec
	{
	public:

		using component_type = T;

		// Constructors

		Vec() = default;
		~Vec() = default;

		Vec(T t);

		template<typename U>
		Vec(U u);

		// Converting constructors

		template<typename U, int S2>
		Vec(const Vec<U, S2>& v);

		// Conversion functions

		/*
		template<typename U, int S>
		operator Vec<U, S>() const;
		*/

		// Operators

		Vec<T, S> operator-() const;

		Vec<T, S>& operator+=(const Vec<T, S>& rhs);
		Vec<T, S>& operator*=(const Vec<T, S>& rhs);
		Vec<T, S>& operator/=(const Vec<T, S>& rhs);

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

	private:

		T components[S];
	};

	// Constructors

	template<typename T, int S>
	Vec<T, S>::Vec(T t)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] = t;
		}
	}

	template<typename T, int S>
	template<typename U>
	Vec<T, S>::Vec(U u)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] = static_cast<T>(u);
		}
	}

	// Converting constructors

	template<typename T, int S1>
	template<typename U, int S2>
	Vec<T, S1>::Vec(const Vec<U, S2>& v)
	{
		int minDimensions = std::min(S1, S2);
		for (int i = 0; i < minDimensions; i++)
		{
			components[i] = static_cast<T>(v[i]);
		}
	}

	// Conversion functions

	/*
	template<typename T, int S1>
	template<typename U, int S2>
	Vec<T, S1>::operator Vec<U, S2>() const
	{
		Vec<U, S2> v{};
		int dimensions = std::min(S1, S2);
		for (int i = 0; i < dimensions; i++)
		{
			v[i] = static_cast<U>(components[i]);
		}
		return v;
	}
	*/

	// Operators

	// 1) Defined in the class

	template<typename T, int S>
	Vec<T, S> Vec<T, S>::operator-() const
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = -components[i];
		}
		return res;
	}

	template<typename T, int S>
	Vec<T, S>& Vec<T, S>::operator+=(const Vec<T, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] += rhs[i];
		}
		return *this;
	}
	template<typename T, int S>
	Vec<T, S>& Vec<T, S>::operator*=(const Vec<T, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] *= rhs[i];
		}
		return *this;
	}
	template<typename T, int S>
	Vec<T, S>& Vec<T, S>::operator/=(const Vec<T, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] /= rhs[i];
		}
		return *this;
	}

	// 2) Defined as separate functions

	template<typename T, int Size>
	Vec<T, Size> operator+(const Vec<T, Size>& v1, const Vec<T, Size>& v2)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = v1[i] + v2[i];
		}
		return res;
	}

	template<typename T, int Size>
	Vec<T, Size> operator-(const Vec<T, Size>& v1, const Vec<T, Size>& v2)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = v1[i] - v2[i];
		}
		return res;
	}

	template<typename T, typename U, int Size>
	Vec<T, Size> operator*(const Vec<T, Size>& v, U u)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = v[i] * static_cast<T>(u);
		}
		return res;
	}

	template<typename T, typename U, int Size>
	Vec<T, Size> operator*(U u, const Vec<T, Size>& v)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = static_cast<T>(u) * v[i];
		}
		return res;
	}

	template<typename T, typename U, int Size>
	Vec<T, Size> operator*(const Vec<T, Size>& v1, const Vec<U, Size>& v2)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = v1[i] * static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, typename U, int Size>
	Vec<T, Size> operator/(const Vec<T, Size>& v, U u)
	{
		Vec<T, Size> vec{};
		for (int i = 0; i < Size; i++)
		{
			vec[i] = v[i] / static_cast<T>(u);
		}
		return vec;
	}

	template<typename T, typename U, int Size>
	Vec<T, Size> operator/(const Vec<T, Size>& v1, const Vec<U, Size>& v2)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = v1[i] / static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, typename U, typename V, int Size>
	Vec<T, Size> Clamp(const Vec<T, Size>& value, const Vec<U, Size>& low, const Vec<V, Size>& high)
	{
		Vec<T, Size> res{};
		for (int i = 0; i < Size; i++)
		{
			res[i] = value[i];
			res[i] = std::min(res[i], static_cast<T>(high[i]));
			res[i] = std::max(res[i], static_cast<T>(low[i]));
		}
		return res;
	}

	template<typename T, typename U, int Size>
	T Dot(const Vec<T, Size>& v1, const Vec<U, Size>& v2)
	{
		T res{ 0 };
		for (int i = 0; i < Size; i++)
		{
			res += v1[i] * static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, int Size>
	T Length2(const Vec<T, Size>& v)
	{
		return Dot(v, v);
	}

	template<typename T, int Size>
	T Length(const Vec<T, Size>& v)
	{
		return static_cast<T>(std::sqrt(Length2(v)));
	}

	template<typename T, int Size>
	Vec<T, Size> Normalize(const Vec<T, Size>& v)
	{
		return v / Length(v);
	}
}