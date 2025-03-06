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

		Vec() : components() {};

		template<typename U>
		Vec(const U& u);

		// Converting constructors

		template<typename U, int S2>
		Vec(const Vec<U, S2>& v);

		// Operators

		Vec<T, S> operator-() const;

		template<typename U>
		Vec<T, S>& operator+=(const Vec<U, S>& rhs);

		template<typename U>
		Vec<T, S>& operator-=(const Vec<U, S>& rhs);

		template<typename U>
		Vec<T, S>& operator*=(const Vec<U, S>& rhs);

		template<typename U>
		Vec<T, S>& operator*=(const U& u);

		template<typename U>
		Vec<T, S>& operator/=(const Vec<U, S>& rhs);

		template<typename U>
		Vec<T, S>& operator/=(const U& u);

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
	template<typename U>
	Vec<T, S>::Vec(const U& u)
	{
		std::fill(Data(), Data() + S, static_cast<T>(u));
	}

	// Converting constructors

	template<typename T, int S1>
	template<typename U, int S2>
	Vec<T, S1>::Vec(const Vec<U, S2>& v)
		: components()
	{
		int minDimensions = std::min(S1, S2);
		for (int i = 0; i < minDimensions; i++)
		{
			components[i] = static_cast<T>(v[i]);
		}
	}

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
	template<typename U>
	Vec<T, S>& Vec<T, S>::operator+=(const Vec<U, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] += static_cast<T>(rhs[i]);
		}
		return *this;
	}

	template<typename T, int S>
	template<typename U>
	Vec<T, S>& Vec<T, S>::operator-=(const Vec<U, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] -= static_cast<T>(rhs[i]);
		}
		return *this;
	}

	template<typename T, int S>
	template<typename U>
	Vec<T, S>& Vec<T, S>::operator*=(const Vec<U, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] *= static_cast<T>(rhs[i]);
		}
		return *this;
	}
	
	template<typename T, int S>
	template<typename U>
	Vec<T, S>& Vec<T, S>::operator*=(const U& u)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] *= static_cast<T>(u);
		}
		return *this;
	}

	template<typename T, int S>
	template<typename U>
	Vec<T, S>& Vec<T, S>::operator/=(const Vec<U, S>& rhs)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] /= static_cast<T>(rhs[i]);
		}
		return *this;
	}
	
	template<typename T, int S>
	template<typename U>
	Vec<T, S>& Vec<T, S>::operator/=(const U& u)
	{
		for (int i = 0; i < S; i++)
		{
			components[i] /= static_cast<T>(u);
		}
		return *this;
	}

	// 2) Defined as separate functions

	template<typename T, typename U, int S>
	Vec<T, S> operator+(const Vec<T, S>& v1, const Vec<U, S>& v2)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = v1[i] + static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> operator-(const Vec<T, S>& v1, const Vec<U, S>& v2)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = v1[i] - static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> operator*(const Vec<T, S>& v, const U& u)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = v[i] * static_cast<T>(u);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> operator*(const U& u, const Vec<T, S>& v)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = static_cast<T>(u) * v[i];
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> operator*(const Vec<T, S>& v1, const Vec<U, S>& v2)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = v1[i] * static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> operator/(const Vec<T, S>& v, const U& u)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = v[i] / static_cast<T>(u);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> operator/(const Vec<T, S>& v1, const Vec<U, S>& v2)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = v1[i] / static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> Min(const Vec<T, S>& v1, const Vec<T, S>& v2)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = std::min(v1[i], v2[i]);
		}
		return res;
	}

	template<typename T, typename U, int S>
	Vec<T, S> Max(const Vec<T, S>& v1, const Vec<T, S>& v2)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = std::max(v1[i], v2[i]);
		}
		return res;
	}

	template<typename T, typename U, typename V, int S>
	Vec<T, S> Clamp(const Vec<T, S>& value, const Vec<U, S>& low, const Vec<V, S>& high)
	{
		Vec<T, S> res{};
		for (int i = 0; i < S; i++)
		{
			res[i] = value[i];
			res[i] = std::min(res[i], static_cast<T>(high[i]));
			res[i] = std::max(res[i], static_cast<T>(low[i]));
		}
		return res;
	}

	template<typename T, typename U, int S>
	T Dot(const Vec<T, S>& v1, const Vec<U, S>& v2)
	{
		T res{ 0 };
		for (int i = 0; i < S; i++)
		{
			res += v1[i] * static_cast<T>(v2[i]);
		}
		return res;
	}

	template<typename T, int S>
	T Length2(const Vec<T, S>& v)
	{
		return Dot(v, v);
	}

	template<typename T, int S>
	T Length(const Vec<T, S>& v)
	{
		return static_cast<T>(std::sqrt(Length2(v)));
	}

	template<typename T, int S>
	Vec<T, S> Normalize(const Vec<T, S>& v)
	{
		return v / Length(v);
	}

	template<
		typename T, typename U, int S,
		std::enable_if_t<std::is_floating_point_v<T>&& std::is_floating_point_v<U>, bool> = true>
	Vec<T, S> Pow(const Vec<T, S>& v, const U& p)
	{
		Vec<T, S> res{};

		for (int i = 0; i < S; i++)
		{
			res[i] = static_cast<T>(std::pow(v[i], p));
		}

		return res;
	}

	template<
		typename T, int S,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	Vec<T, S> Sqrt(const Vec<T, S>& v)
	{
		Vec<T, S> res{};

		for (int i = 0; i < S; i++)
		{
			res[i] = static_cast<T>(std::sqrt(v[i]));
		}

		return res;
	}

	template<
		typename T, int S,
		std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
	Vec<T, S> Exp(const Vec<T, S>& v)
	{
		Vec<T, S> res{};

		for (int i = 0; i < S; i++)
		{
			res[i] = static_cast<T>(std::exp(v[i]));
		}

		return res;
	}
}