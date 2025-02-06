#pragma once

#include "Vec.hpp"

#include <algorithm>
#include <type_traits>

namespace numa
{
	template<typename T, int Rows, int Cols>
	class Mat
	{
	public:

		using column_type = Vec<T, Rows>;

		using column_type_ref = column_type&;
		using column_type_cref = const column_type&;

		using component_type = typename column_type::component_type;

		using component_type_ref = component_type&;
		using component_type_cref = const component_type&;

		using component_type_ptr = component_type*;
		using component_type_cptr = const component_type*;

		// Constructors

		Mat() : columns() {};

		template<int R = Rows, int C = Cols, typename U, std::enable_if_t<R != C, bool> = true>
		Mat(const U& u)
		{
			for (int col = 0; col < Cols; col++)
			{
				columns[col] = column_type{ u };
			}
		}

		template<int R = Rows, int C = Cols, typename U, std::enable_if_t<R == C, bool> = true>
		Mat(const U& u)
			: columns()
		{
			for (int i = 0; i < Cols; i++)
			{
				columns[i][i] = static_cast<T>(u);
			}
		}

		// Converting constructors

		template<typename U, int Rows2, int Cols2>
		Mat(const Mat<U, Rows2, Cols2>& mat);

		// Operators

		template<typename U>
		Mat<T, Rows, Cols>& operator+=(const Mat<U, Rows, Cols>& mat);

		template<typename U>
		Mat<T, Rows, Cols>& operator-=(const Mat<U, Rows, Cols>& mat);

		template<typename U>
		Mat<T, Rows, Cols>& operator*=(const U& u);

		template<typename U>
		Mat<T, Rows, Cols>& operator/=(const U& u);

		column_type_ref& operator[](int idx)
		{
			return columns[idx];
		}
		column_type_cref& operator[](int idx) const
		{
			return columns[idx];
		}

		component_type_ptr Data()
		{
			return columns[0].Data();
		}
		component_type_cptr Data() const
		{
			return columns[0].Data();
		}

	private:

		column_type columns[Cols];
	};

	// Constructors

	// Converting constructors

	template<typename T, int Rows, int Cols>
	template<typename U, int Rows2, int Cols2>
	Mat<T, Rows, Cols>::Mat(const Mat<U, Rows2, Cols2>& mat)
		: columns()
	{
		int minColsDim = std::min(Cols, Cols2);
		for (int i = 0; i < minColsDim; i++)
		{
			this->columns[i] = mat[i];
		}
	}

	// Operators

	// 1) Defined in the class

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator+=(const Mat<U, Rows, Cols>& mat)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] += mat[i];
		}
		return *this;
	}

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator-=(const Mat<U, Rows, Cols>& mat)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] -= mat[i];
		}
		return *this;
	}

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator*=(const U& u)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] *= u;
		}
		return *this;
	}

	template<typename T, int Rows, int Cols>
	template<typename U>
	Mat<T, Rows, Cols>& Mat<T, Rows, Cols>::operator/=(const U& u)
	{
		for (int i = 0; i < Cols; i++)
		{
			this->columns[i] /= u;
		}
		return *this;
	}

	// 2) Defined as separate functions

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator+(const Mat<T, Rows, Cols>& m1, const Mat<U, Rows, Cols>& m2)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m1[i] + m2[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator-(const Mat<T, Rows, Cols>& m1, const Mat<U, Rows, Cols>& m2)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m1[i] - m2[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator*(const Mat<T, Rows, Cols>& m, const U& u)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m[i] * u;
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator*(const U& u, const Mat<T, Rows, Cols>& m)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = u * m[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Vec<U, Rows> operator*(const Mat<T, Rows, Cols>& m, const Vec<U, Cols>& v)
	{
		Vec<U, Rows> res{};
		for (int i = 0; i < Cols; i++)
		{
			res += m[i] * v[i];
		}
		return res;
	}

	template<typename T, typename U, int Rows, int Cols>
	Mat<T, Rows, Cols> operator/(const Mat<T, Rows, Cols>& m, const U& u)
	{
		Mat<T, Rows, Cols> res{};
		for (int i = 0; i < Cols; i++)
		{
			res[i] = m[i] / u;
		}
		return res;
	}

	template<
		typename T, int M, int N,
		typename U, int K>
	Mat<T, M, K> operator*(const Mat<T, M, N>& mat1, const Mat<U, N, K>& mat2)
	{
		Mat<T, M, K> res{};

		// We can view matrix-matrix multiplication [M, N]x[N, K] as
		// K linear combinations of the column vectors of the first matrix.
		// These K linear combinations, which are m-dimensional column vectors,
		// form the resulting [M, K] matrix.

		for (int i = 0; i < K; i++)
		{
			res[i] = mat1 * mat2[i];
		}

		return res;
	}
}